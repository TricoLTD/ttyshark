//
// Created by sera on 6/30/26.
//

#ifndef TTYSHARK_SERIALCAP_H
#define TTYSHARK_SERIALCAP_H
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <expected>
#include <system_error>


class serialcap {
public:
    /**
     * Create a new serial capture instance
     * @param device
     * @param baud
     */
    serialcap(std::string device, const int baud)
        : device_(std::move(device)),
          baud_(baud)
    {
    }

    /**
     * Run main loop
     */
    void run();

private:
    using status = std::expected<void, std::string>;

    /**
     * Open serial port
     * @return error iff contains string
     */
    status open_port();
    void close_port();

    std::string device_;
    int baud_;
    int fd_{-1};
};


#endif //TTYSHARK_SERIALCAP_H
