//
// Created by sera on 6/30/26.
//

#include "serialcap.h"

#include <cstring>
#include <fstream>
#include <ios>
#include <vector>
#include <sys/file.h>

void serialcap::start(unsigned int await, unsigned int chunkness) {
    if (running_) {
        throw std::logic_error("Capture already running.");
    }

    worker_ = std::async(
    std::launch::async,
    &serialcap::run,
    this,
    await,
    chunkness
);
}

auto serialcap::wait() -> std::expected<int, std::runtime_error> {
    return worker_.get();
}

auto serialcap::run(unsigned int await, unsigned int chunkness) -> std::expected<int, std::runtime_error> {
        if (auto result = open_port()) {
        printf("Successfully opened %s", device_.c_str());
    } else {
        printf("Failed to open %s\n", device_.c_str());
        printf("%s\n", result.error().c_str());
        return std::unexpected(std::runtime_error("Failed to open"));
    }

    if (flock(fd_, LOCK_EX | LOCK_NB) == -1) {
        return std::unexpected(std::runtime_error("Serial port with file descriptor " + std::to_string(fd_) + " is already locked by another process."));
    }

    termios tty{};
    if (tcgetattr(fd_, &tty) != 0) {
        printf("tcgetattr failed");
        close_port();
        return std::unexpected(std::runtime_error("tcgetattr failed"));
    }

    cfsetispeed(&tty, baud_);

    // reference material https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/
    // CFLAGS
    tty.c_cflag &= ~(PARENB | CSTOPB | CSIZE | CRTSCTS);
    tty.c_cflag |= CS8 | CREAD | CLOCAL;

    // LFLAGS
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHONL | ISIG );

    // IFLAGS
    tty.c_iflag &= ~(IXON | IXOFF | IXANY | IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

    // OFLAGS
    #ifdef _WIN32
    tty.c_oflag &= ~(OPOST | ONLCR | OXTABS | ONOEOT);
    #else
    tty.c_oflag &= ~(OPOST | ONLCR);
    #endif

    tty.c_cc[VMIN] = chunkness;
    tty.c_cc[VTIME] = await;

    if (tcsetattr(fd_, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return std::unexpected(std::runtime_error("Error " + std::to_string(errno) + "from tcsetattr" + strerror(errno)));
    }

    running_ = true;
    std::ofstream out (capfile_, std::ios::binary);
    std::vector<char> capture_buffer;
    capture_buffer.reserve(5079040);

    char buffer[256];
    do {
        if (ssize_t n = ::read(fd_, &buffer[0], sizeof(buffer)); n > 0) {
            capture_buffer.insert(capture_buffer.end(), buffer, buffer + n);
        }

        if (capture_buffer.size() >= 5079040) {
            out.write(capture_buffer.data(), capture_buffer.size());
            capture_buffer.clear();
        }

    } while (running_);
    capture_buffer.insert(capture_buffer.end(), buffer, buffer + 256);
    if (!capture_buffer.empty()) {
        out.write(capture_buffer.data(), capture_buffer.size());
    }

    out.close();
    close_port();
    return 1;
}

auto serialcap::open_port() -> serialcap::status {
    fd_ = ::open(device_.c_str(), O_RDONLY | O_NOCTTY);

    if (fd_ == -1) {
        return std::unexpected("Device inaccessible! is it correct and do you have permissions?");
    }

    return 1;
}

void serialcap::close_port() {
    fd_ = ::close(fd_);
}