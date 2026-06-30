//
// Created by sera on 6/30/26.
//

#ifndef TTYSHARK_SERIALCAP_H
#define TTYSHARK_SERIALCAP_H
#include <atomic>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <expected>
#include <system_error>
#include <utility>
#include <termios.h>


class serialcap {
public:
    /**
     * Create a new serial capture instance
     * @param device
     * @param baud
     */
    serialcap(std::string device, const speed_t baud, std::string capfile)
        : device_(std::move(device)),
          baud_(baud),
          capfile_(std::move(capfile))
    {
    }

    /**
     * Run main monitoring loop
     * @param await time in deciseconds to wait before returning buffered bytes
     * @param chunkness amount of bytes to hold before write at a time
     */
    std::expected<int, std::runtime_error> run(unsigned int await, unsigned int chunkness);

    void stop() { running_ = false; }

private:
    using status = std::expected<int, std::string>;

    /**
     * Open serial port
     * @return error iff contains string
     */
    status open_port();

    /**
     * Close a port
     * this action should never fail
     */
    void close_port();

    std::string device_;
    speed_t baud_;
    int fd_{-1};
    std::atomic<bool> running_ = false;
    std::string capfile_;
};


#endif //TTYSHARK_SERIALCAP_H
