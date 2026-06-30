#ifdef TTYSHARK_IGMNET_H
#define TTYSHARK_IGMNET_H
#include <cstdint>
#include <variant>
#include <vector>

class igm_commands {
    struct response_buffer {
        uint16_t sent_command;
        uint16_t unit_type;
        uint16_t declared_buffer_size;
        // There's zero good reason why alarm_values_variable and alarm_values_fixed should differ, but consider: Liebert.
        std::vector<uint16_t> runtime_values;
        std::vector<uint16_t> alarm_values_variable;
        std::vector<uint16_t> control_values;
        std::vector<uint16_t> status_values;
        std::vector<uint16_t> alarm_values_fixed;
        uint16_t set_command_response;
        // Raw response retained for posterity and reference in the event of requiring hand-parsing
        std::vector<uint16_t> raw_response;   
    };

    // GET Commands
    struct clear_alarms {
        uint16_t command = 0x3D;
    };
    struct reset_alarms {
        uint16_t command = 0x3E;
    };
    struct get_customer_alarm_1_text {
        uint16_t command = 0x7C;
    };
    struct get_customer_alarm_2_text {
        uint16_t command = 0x7D;
    };
    struct get_unit_type_data {
        uint16_t command = 0x7E;
    };
    // One guard always tells the truth, one guard always lies - The command
    struct get_unit_status_buffer_size {
        uint16_t command = 0x7F;
    };
    struct acknowledge_alarms {
        uint16_t command = 0xAE;
    };
    struct get_data_runtime_values {
        uint16_t command = 0xB2;
    };
    // Variable length response
    struct get_alarm_values_variable {
        uint16_t command = 0xBC
    };
    struct get_control_values {
        uint16_t command = 0xBD;
    };
    struct get_data_status_values {
        uint16_t command = 0xBE;
    };
    // As mentioned before, 0xBF and 0xBC should be identical in response
    struct get_alarm_values_fixed {
        uint16_t command = 0xBF;
    };

    // SET commands
    struct set_temp_setpoint {
        uint16_t command = 0x80;
        uint16_t temp_value;
    };
    struct set_temp_tolerance {
        uint16_t command = 0x81;
        uint16_t temp_tolerance;
    }
};


#endif