//
// Created by sera on 6/30/26.
//

#ifndef TTYSHARK_MODBUSRTU_H
#define TTYSHARK_MODBUSRTU_H
#include <cstdint>
#include <format>
#include <ranges>
#include <stdexcept>
#include <vector>

/**
 * Fancy uint8_t
 */
class ModbusAddr {
    public:
    explicit ModbusAddr(const uint8_t Addr) : Address(Addr) {
        if (Addr > 247) {
            throw std::out_of_range("Address Not Valid");
        }
    };

    uint8_t Address;

    std::string getName() {
        switch (Address) {
            case 0x00:
                return "Global/Broadcast 0x00";
                break;
            default:
                return std::format("Device {:x}", Address);
        }
    }
};

class modbusrtu {
public:
    using ba2 = std::array<bool, 2>;
    enum class modbusFunc {ReadCoils, ReadDiscreteInputs, ReadHoldingRegisters, ReadInputRegisters, WriteSingleCoil,
        WriteSingleRegister, Diagnostics, GCEC, WriteMultipleCoils, WriteMultipleRegisters, ReportServerID,
        MaskWriteReg, ReadWriteMultipleReg, Unknown};

    struct devAddr {
        ModbusAddr modbusAddr;
        std::string devName;
    };

    struct functionInfo {
        std::string FunctionName;
        uint8_t FunctionID;
        modbusFunc FunctionType;
        size_t RequestSize;
        size_t ResponseSize;
    };

    static functionInfo getFunctionType(const uint8_t code) {
        functionInfo value;
        switch (code) {
            case 0x01:
                value.FunctionName = "Read Coils";
                value.FunctionID = code;
                value.FunctionType = modbusFunc::ReadCoils;
                value.RequestSize = 8;
                value.ResponseSize = 7;
                break;
            case 0x02:
                value.FunctionName = "Read Discrete Inputs";
                value.FunctionID = code;
                value.FunctionType = modbusFunc::ReadDiscreteInputs;
                value.RequestSize = 8;
                value.ResponseSize = 7;
                break;
            case 0x03:
                value.FunctionName = "Read Holding Registers";
                value.FunctionID = code;
                value.FunctionType = modbusFunc::ReadHoldingRegisters;
                value.RequestSize = 8;
                value.ResponseSize = 9;
                break;
            case 0x04:
                value.FunctionName = "Read Input Registers";
                value.FunctionID = code;
                value.FunctionType = modbusFunc::ReadInputRegisters;
                value.RequestSize = 8;
                value.ResponseSize = 9;
                break;
            case 0x05:
                value.FunctionName = "Write Single Coil";
                value.FunctionID = code;
                value.FunctionType = modbusFunc::WriteSingleCoil;
                value.RequestSize = 8;
                value.ResponseSize = 8;
                break;
            case 0x06:
                value.FunctionName = "Write Single Register";
                value.FunctionID = code;
                value.FunctionType = modbusFunc::WriteSingleRegister;
                value.RequestSize = 8;
                value.ResponseSize = 8;
                break;
            case 0x08:
                value.FunctionName = "Diagnostics";
                value.FunctionID = code;
                value.FunctionType = modbusFunc::Diagnostics;
                value.RequestSize = 0;
                value.ResponseSize = 0;
                break;
            case 0x0B:
                value.FunctionName = "Get Comm Event Counter";
                value.FunctionID = code;
                value.FunctionType = modbusFunc::GCEC;
                value.RequestSize = 0;
                value.ResponseSize = 0;
                break;
            case 0x0F:
                value.FunctionName = "Write Multiple Coils";
                value.FunctionID = code;
                value.FunctionType = modbusFunc::WriteMultipleCoils;
                value.RequestSize = 11;
                value.ResponseSize = 8;
                break;
            case 0x10:
                value.FunctionName = "Write Multiple Registers";
                value.FunctionID = code;
                value.FunctionType = modbusFunc::WriteMultipleRegisters;
                value.RequestSize = 13;
                value.ResponseSize = 8;
                break;
            case 0x11:
                value.FunctionName = "Report Server ID";
                value.FunctionID = code;
                value.FunctionType = modbusFunc::ReportServerID;
                value.RequestSize = 0;
                value.ResponseSize = 0;
                break;
            case 0x16:
                value.FunctionName = "Mask Write Register";
                value.FunctionID = code;
                value.FunctionType = modbusFunc::ReadCoils;
                value.RequestSize = 0;
                value.ResponseSize = 0;
                break;
            case 0x17:
                value.FunctionName = "Read/Write Multiple Registers";
                value.FunctionID = code;
                value.FunctionType = modbusFunc::ReadCoils;
                value.RequestSize = 0;
                value.ResponseSize = 0;
                break;
            default:
                value.FunctionName = "Unknown Function";
                value.FunctionID = code;
                value.FunctionType = modbusFunc::Unknown;
                value.RequestSize = 0;
                value.ResponseSize = 0;
                break;
        }
        return value;
    }

    /**
     * PDU for modbus
     */
    struct modbusPdu {
        devAddr Addr;
        functionInfo Func;
        std::vector<uint8_t> Data;
        uint16_t CRC;
    };

    /**
     * PDU as strings
     */
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

    /**
     * Generate a confidence matrix of guesses to see if any align.
     *
     * @param guessSetone
     * @param guessSettwo
     * @return
     */
    static std::array<ba2, 2> confidenceMatrix(const std::pair<uint8_t, uint8_t> &guessSetone, const std::pair<uint8_t, uint8_t> &guessSettwo);

    /**
     * Calculate a messages CRC
     *
     * @param buffer
     * @param length
     * @return
     */
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

    /**
     * Lex a capture file and return modbus PDU's
     * @param fileName
     * @return
     */
    static std::vector<modbusPdu> lexCapture(const std::string &fileName);

};


#endif //TTYSHARK_MODBUSRTU_H
