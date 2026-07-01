//
// Created by sera on 6/30/26.
//

#include "modbusrtu.h"
#include <fstream>
#include <iostream>


std::pair<uint8_t, uint8_t> modbusrtu::plausibleTwo(const std::string &fileName, std::size_t stride = 8) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file)
        return {248, 248};

    std::vector<uint8_t> dataBuffer{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};

    uint8_t fbest = 0;
    uint8_t fnextBest = 0;
    uint64_t bestScore = 0;

    for (std::size_t offset = 0; offset < stride; offset++) {
        std::array<uint64_t, 256> dHisto;

        for (std::size_t i = offset; i < dataBuffer.size(); i++) {
            dHisto[dataBuffer[i]]++;
        }

        uint8_t best = 1;
        uint8_t nextBest = 2;

        for (std::size_t iter = 1; iter < dataBuffer.size(); iter++) {
            if (dHisto[iter] > dHisto[best]) {
                nextBest = best;
                best = static_cast<uint8_t>(iter);
            } else if (iter != best && dHisto[iter] > dHisto[nextBest]) {
                nextBest = static_cast<uint8_t>(iter);
            }
        }

        if (uint64_t score = dHisto[best] + dHisto[nextBest]; score > bestScore) {
            fbest = best;
            fnextBest = nextBest;
            bestScore = score;
        }
    }

    return {fbest, fnextBest};
}
