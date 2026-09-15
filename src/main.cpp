#include "modbusRTU/modbusrtu.h"
#include "serialcap/serialcap.h"
#include "ttyshark.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#define USAGE                                                                  \
  "Usage: ttyshark [--help | -h]\n"                                            \
  "ttyshark [--capture | -c] <serial_device> <capture_location [default is "   \
  "./cap_Y-M-D-H-M-S.bin]> : capture of a serial device specification is "     \
  "order sensitive.\n"

void runCap(std::string device, std::string location) {
  printf("How many seconds to run capture for: ");
  int waitTime;
  scanf("%d", &waitTime);
  printf("What is the baud: ");
  int bRate;
  scanf("%d", &bRate);
  auto cap = serialcap(device, bRate, location);
  cap.start(waitTime, 0);
  auto result = cap.wait();

  if (result) {
    printf("%d", *result);
  } else {
    printf("%s", result.error().what());
  }

  return;
}

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
    } else if (args[i] == "--capture" || args[i] == "-c") {
      if ((i + 2) < args.size()) {
        auto sD = static_cast<std::string>(args[i + 1]);
        auto cL = static_cast<std::string>(args[i + 2]);
        runCap(sD, cL);
        i += 2;
      } else {
        if ((i + 1) < args.size()) {
          auto now = std::chrono::system_clock::now();
          std::time_t nowT = std::chrono::system_clock::to_time_t(now);

          struct tm local_time;
          localtime_r(&nowT, &local_time);

          std::stringstream nameString;
          nameString << std::put_time(&local_time,
                                      "./cap_%Y-%m-%d-%H-%M-%S.bin");
          std::string fileString = nameString.str();
          auto sD = static_cast<std::string>(args[i + 1]);

          runCap(sD, fileString);
        } else {
          printf("Invalid arguments for capture");
        }
      }
    }
  }
  return 1;
}
