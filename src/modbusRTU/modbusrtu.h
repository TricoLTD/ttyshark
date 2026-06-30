//
// Created by sera on 6/30/26.
//

#ifndef TTYSHARK_MODBUSRTU_H
#define TTYSHARK_MODBUSRTU_H
#include <cstdint>
#include <variant>
#include <vector>


class modbusrtu {
    struct ReadCoilsRequest {
        uint8_t slave;
        uint16_t start;
        uint16_t quantity;
    };

    struct ReadHoldingRegistersRequest {
        uint8_t slave;
        uint16_t start;
        uint16_t quantity;
    };

    struct ReadHoldingRegistersResponse {
        uint8_t slave;
        std::vector<uint16_t> registers;
    };

    struct WriteSingleRegisterRequest {
        uint8_t slave;
        uint16_t address;
        uint16_t value;
    };

    struct WriteMultipleRegistersRequest {
        uint8_t slave;
        uint16_t address;
        std::vector<uint16_t> values;
    };

    struct ExceptionResponse {
        uint8_t slave;
        uint8_t function;
        uint8_t exception;
    };

    struct UnknownFunction {
        uint8_t slave;
        uint8_t function;
        std::vector<std::byte> payload;
    };

    using Pdu = std::variant<
            ReadCoilsRequest,
            ReadHoldingRegistersRequest,
            ReadHoldingRegistersResponse,
            WriteSingleRegisterRequest,
            ExceptionResponse,
            UnknownFunction
    >;

    struct ParseResult {
        bool valid_crc;
        uint8_t addr;
        uint8_t function;
        Pdu payload;
    };
};


#endif //TTYSHARK_MODBUSRTU_H
