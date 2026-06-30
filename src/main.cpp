#include "ttyshark.h"
#include <vector>
#include <string>


int main() {
    ttyshark();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    ttyshark_print_vector(vec);
}
