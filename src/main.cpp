#include "ttyshark.h"
#include <vector>
#include <string>

#include "modbusRTU/modbusrtu.h"
#include "serialcap/serialcap.h"


int main() {
    //ttyshark();
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
    }*/
    auto [addr1, addr2] = modbusrtu::plausibleTwo("./cap.bin", 16);
    printf("cap.bin\n");
    printf("Guessed Addr1: %i\n", addr1);
    printf("Guessed Addr2: %i\n", addr2);
    auto [addr3, addr4] = modbusrtu::plausibleTwo("./cap.bin", 16);
    printf("cap2.bin\n");
    printf("Guessed Addr1: %i\n", addr3);
    printf("Guessed Addr2: %i\n", addr4);
    auto [addr5, addr6] = modbusrtu::plausibleTwo("./cap.bin", 16);
    printf("cap3.bin\n");
    printf("Guessed Addr1: %i\n", addr5);
    printf("Guessed Addr2: %i\n", addr6);
    return 1;
}
