//
// Created by sera on 6/30/26.
//

#ifndef TTYSHARK_MODBUSRTU_H
#define TTYSHARK_MODBUSRTU_H
#include <cstdint>
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
     * @return
     */
    static std::pair<uint8_t, uint8_t> plausibleTwo(const std::string &fileName, std::size_t stride);

};


#endif //TTYSHARK_MODBUSRTU_H
