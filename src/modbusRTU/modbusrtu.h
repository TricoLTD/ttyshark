//
// Created by sera on 6/30/26.
//

#ifndef TTYSHARK_MODBUSRTU_H
#define TTYSHARK_MODBUSRTU_H
#include <cstdint>
#include <ranges>
#include <stdexcept>
#include <vector>

class ModbusAddr {
    public:
    explicit ModbusAddr(const uint16_t Addr) {
        if (Addr < 1 || Addr > 247) {
            throw std::out_of_range("Address Not Valid");
        }
    };
};

class modbusrtu {
public:
    using ba2 = std::array<bool, 2>;
    enum class modbusFunc {ReadCoils, ReadDiscreteInputs, ReadHoldingRegisters, ReadInputRegisters, WriteSingleCoil,
        WriteSingleRegister, Diagnostics, GCEC, WriteMultipleCoils, WriteMultipleRegisters, ReportServerID,
        MaskWriteReg, ReadWriteMultipleReg, Unknown};

    /**
     * PDU for modbus
     */
    struct modbusPdu {
        ModbusAddr Addr;
        modbusFunc Func;
        std::vector<uint8_t> Data;
        uint16_t CRC;
    };

    struct stringifyPdu {
        std::string Addr;
        std::string Func;
        std::string Data;
        std::string CRC;
    };

    /**
     * Guess two plausible addresses
     *
     * @param fileName
     * @param stride default 4
     * @return
     */
    static std::pair<uint8_t, uint8_t> plausibleTwo(const std::string &fileName, std::size_t stride = 5);

    /**
     * Smart calculate best address guess
     *
     * @param fileName
     * @param stride
     * @return
     */
    static std::pair<uint8_t, uint8_t> smartTwo(const std::string &fileName, int stride = 5);

    static std::array<ba2, 2> confidenceMatrix(const std::pair<uint8_t, uint8_t> &guessSetone, const std::pair<uint8_t, uint8_t> &guessSettwo);

    static uint16_t crcCalculation(const uint8_t* buffer, int length) {
        uint16_t result = 0xFFFF;

        for (int i = 0; i < length; i++) {
            result ^= static_cast<uint16_t>(buffer[i]);
            for (int j = 8; j != 0; j--) {
                if ((result & 0x0001) != 0) {
                    result >>= 1;
                    result ^= 0xA001;
                } else {
                    result >>= 1;
                }
            }
        }

        const uint8_t low = result & 0xFF;
        const uint8_t high = (result >> 8) & 0xFF;
        const uint16_t crc = (low << 8) | high;

        return crc;
    }

};


#endif //TTYSHARK_MODBUSRTU_H
