#include "modbusRTU/modbusrtu.h"
#include "serialcap/serialcap.h"
#include "ttyshark.h"
#include <chrono>
#include <stdio.h>
#include <string>
#include <vector>
#define USAGE                                                                  \
  "Usage: ttyshark [--help | -h]\n"                                            \
  "ttyshark [--capture | -c] <serial_file>\n"

int main(int argc, char *argv[]) {
  // printf("%d", argc);
  if (argc == 1) {
    printf("%s", USAGE);
    return 1;
  }
  std::vector<std::string_view> args(argv + 1, argv + argc);
  for (size_t i = 0; i < args.size(); i++) {
    if (args[i] == "-h" || args[i] == "--help") {
      printf("%s", USAGE);
    }
  }
  return 1;
}
