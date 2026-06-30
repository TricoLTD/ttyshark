#include "ttyshark.h"
#include <vector>
#include <string>
#include "serialcap/serialcap.h"


int main() {
    //ttyshark();
    auto monitor = serialcap("device goes here", B9600, "./cap.bin");
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

    return 1;
}
