#include "modbusRTU/modbusrtu.h"
#include "serialcap/serialcap.h"
#include "ttyshark.h"
#include <chrono>
#include <ftxui/ftxui.hpp>
#include <string>
#include <vector>
using namespace ftxui;

int main() {
  auto document = vbox({
      hbox({
          text("one") | border,
          text("two") | border | flex,
          text("three") | border | flex,
      }),

      gauge(0.25) | color(Color::Red),
      gauge(0.50) | color(Color::White),
      gauge(0.75) | color(Color::Blue),
  });

  auto screen = Screen::Create(Dimension::Full());
  Render(screen, document);
  screen.Print();
  // ttyshark();
  /*auto monitor = serialcap("device goes here", B9600, "./cap.bin");
  monitor.start(0, 2);
  sleep(15);
  monitor.stop();
  if (auto output = monitor.wait()) {
      printf("Successfully stopped\n");
  } else {
      printf("Failed to stop successfully\n");
      printf("%s\n", output.error().what());
      return -1;
  }
  auto start = std::chrono::high_resolution_clock::now();
  auto addresses = modbusrtu::plausibleTwo("./cap.bin");
  auto end = std::chrono::high_resolution_clock::now();

  auto addr1 = addresses.first;
  auto addr2 = addresses.second;

  printf("cap.bin Histogram Guesses\n");
  printf("Guessed Addr1: %#x\n", addr1);
  printf("Guessed Addr2: %#x\n", addr2);

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end -
  start); printf("Execution took: %lld ms\n", static_cast<long
  long>(duration.count())); printf("Smart Search\n");

  start = std::chrono::high_resolution_clock::now();
  auto addresses2 = modbusrtu::smartTwo("./cap.bin");
  end = std::chrono::high_resolution_clock::now();

  addr1 = addresses2.first;
  addr2 = addresses2.second;

  printf("Guessed Addr1: %#x\n" , addr1);
  printf("Guessed Addr2: %#x\n" , addr2);
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  printf("Execution took: %lld ms\n", static_cast<long long>(duration.count()));
  printf("Matrix of Confidence: \n");
  auto matrix = modbusrtu::confidenceMatrix(addresses, addresses2);
  for (auto row : matrix) {
      for (auto val : row) {
          printf("   %d   ", val);
      }
      printf("\n");
  }

  printf("\n\n\n");


  auto results = modbusrtu::lexCapture("./cap.bin");
  printf("Amount Seen: %lu\n", results.size());
  std::vector<modbusrtu::stringifyPdu> strung = modbusrtu::stringify(results);
  for (auto str : strung) {
      modbusrtu::prettyPrint(str);
      printf("\n");
  }

  /*start = std::chrono::high_resolution_clock::now();
  addresses = modbusrtu::plausibleTwo("./cap.bin");
  end = std::chrono::high_resolution_clock::now();

  addr1 = addresses.first;
  addr2 = addresses.second;

  printf("cap.bin Histogram Guesses\n");
  printf("Guessed Addr1: %#x\n", addr1);
  printf("Guessed Addr2: %#x\n", addr2);

  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  printf("Execution took: %lld ms\n", static_cast<long long>(duration.count()));
  printf("Smart Search\n");

  start = std::chrono::high_resolution_clock::now();
  addresses2 = modbusrtu::smartTwo("./cap.bin");
  end = std::chrono::high_resolution_clock::now();

  addr1 = addresses2.first;
  addr2 = addresses2.second;

  printf("Guessed Addr1: %#x\n" , addr1);
  printf("Guessed Addr2: %#x\n" , addr2);
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  printf("Execution took: %lld ms\n", static_cast<long long>(duration.count()));
  printf("Matrix of Confidence: \n");
  matrix = modbusrtu::confidenceMatrix(addresses, addresses2);
  for (auto row : matrix) {
      for (auto val : row) {
          printf("   %d   ", val);
      }
      printf("\n");
  }

  printf("\n\n\n");

  start = std::chrono::high_resolution_clock::now();
  addresses = modbusrtu::plausibleTwo("./cap.bin");
  end = std::chrono::high_resolution_clock::now();

  addr1 = addresses.first;
  addr2 = addresses.second;

  printf("cap.bin Histogram Guesses\n");
  printf("Guessed Addr1: %#x\n", addr1);
  printf("Guessed Addr2: %#x\n", addr2);

  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  printf("Execution took: %lld ms\n", static_cast<long long>(duration.count()));
  printf("Smart Search\n");

  start = std::chrono::high_resolution_clock::now();
  addresses2 = modbusrtu::smartTwo("./cap.bin");
  end = std::chrono::high_resolution_clock::now();

  addr1 = addresses2.first;
  addr2 = addresses2.second;

  printf("Guessed Addr1: %#x\n" , addr1);
  printf("Guessed Addr2: %#x\n" , addr2);
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  printf("Execution took: %lld ms\n", static_cast<long long>(duration.count()));
  printf("Matrix of Confidence: \n");
  matrix = modbusrtu::confidenceMatrix(addresses, addresses2);
  for (auto row : matrix) {
      for (auto val : row) {
          printf("   %d   ", val);
      }
      printf("\n");
  }*/

  return 1;
}
