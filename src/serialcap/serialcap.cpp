//
// Created by sera on 6/30/26.
//

#include "serialcap.h"

void serialcap::run() {

}

serialcap::status serialcap::open_port() {
    fd_ = ::open(device_.c_str(), O_RDONLY | O_NOCTTY);

    if (fd_ == -1) {
        return std::unexpected("Device inaccessible! is it correct and do you have permissions?");
    }

}

void serialcap::close_port() {}