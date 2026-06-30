#include "ttyshark.h"
#include <vector>
#include <string>
#include <modbus/modbus.h>


int main() {
    ttyshark();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    ttyshark_print_vector(vec);
}
