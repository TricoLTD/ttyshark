//
// Created by sera on 6/30/26.
//

#include "serialcap.h"

void serialcap::run() {
    if (auto result = open_port()) {
        printf("Successfully opened %s", device_.c_str());
    } else {
        printf("Failed to open %s\n", device_.c_str());
        printf("%s\n", result.error().c_str());
        return;
    }

    termios tty{};
    if (tcgetattr(fd_, &tty) != 0) {
        printf("tcgetattr failed");
        close_port();
        return;
    }

    cfsetispeed(&tty, baud_);

}

serialcap::status serialcap::open_port() {
    fd_ = ::open(device_.c_str(), O_RDONLY | O_NOCTTY);

    if (fd_ == -1) {
        return std::unexpected("Device inaccessible! is it correct and do you have permissions?");
    }

    return 1;
}

void serialcap::close_port() {
    fd_ = ::close(fd_);
}