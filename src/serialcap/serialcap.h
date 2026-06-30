//
// Created by sera on 6/30/26.
//

#ifndef TTYSHARK_SERIALCAP_H
#define TTYSHARK_SERIALCAP_H
#include <string>


class serialcap {
public:
    serialcap(std::string device, const int baud)
        : device_(std::move(device)),
          baud_(baud)
    {
    }

    void run();

private:
    void open_port();
    void close_port();

    std::string device_;
    int baud_;
    int fd_{-1};
};


#endif //TTYSHARK_SERIALCAP_H
