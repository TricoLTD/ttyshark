#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define TTYSHARK_EXPORT __declspec(dllexport)
#else
  #define TTYSHARK_EXPORT
#endif

TTYSHARK_EXPORT void ttyshark();
TTYSHARK_EXPORT void ttyshark_print_vector(const std::vector<std::string> &strings);
