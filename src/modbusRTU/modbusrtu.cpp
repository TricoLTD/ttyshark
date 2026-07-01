//
// Created by sera on 6/30/26.
//

#include "modbusrtu.h"
#include <fstream>
#include <iostream>


std::pair<uint8_t, uint8_t> modbusrtu::plausibleTwo(const std::string &fileName, std::size_t stride) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file) return {248, 248};

    std::vector<uint8_t> dataBuffer{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};

    uint8_t fbest = 0;
    uint8_t fnextBest = 0;
    uint64_t bestScore = 0;

    for (std::size_t offset = 0; offset < stride; offset++) {
        std::array<uint64_t, 256> dHisto{};

        for (std::size_t i = offset; i < dataBuffer.size(); i++) {
            dHisto[dataBuffer.at(i)]++;
        }

        uint8_t best = 1;
        uint8_t nextBest = 2;

        for (std::size_t iter = 1; iter < 256; iter++) {
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

std::pair<uint8_t, uint8_t> modbusrtu::smartTwo(const std::string &fileName, int stride) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file) return {248, 248};

    const std::vector<uint8_t> dataBuffer{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
    std::pair<uint8_t, int> address = {0, -1000};
    std::pair<uint8_t, int> address2 = {0, -1000};
    
    size_t maxOffset = std::min<size_t>(stride, dataBuffer.size());
    
    for (size_t offset = 0; offset < maxOffset; offset++) {
        for (size_t iter = offset; iter < dataBuffer.size(); iter++) {
            uint8_t candidate = dataBuffer.at(iter);
            int score = 0;
            if (candidate == 0 || candidate >= 247) {
                score -= 5;
            } else {
                if (iter + 1 >= dataBuffer.size()) {
                    score -= 500;
                } else {
                    uint8_t function = dataBuffer.at(iter + 1);

                    score++;
                    switch (function) {
                        case 0x01:
                        case 0x02:
                        case 0x03:
                        case 0x04:
                        case 0x05:
                        case 0x0F:
                        case 0x10:
                        {
                            if (dataBuffer.size() > iter + 7) {
                                uint8_t msgCnt[] = {candidate, function, dataBuffer.at(iter + 2), dataBuffer.at(iter + 3), dataBuffer.at(iter + 4), dataBuffer.at(iter + 5)};
                                uint8_t crcLow = dataBuffer.at(iter + 6);
                                uint8_t crcHigh = dataBuffer.at(iter + 7);
                                uint16_t crc = (crcLow << 8) | crcHigh;
                                if (uint16_t guessCrc = crcCalculation(msgCnt, 6); guessCrc == crc) {
                                    score += 100;
                                } else {
                                    score -= 100;
                                }
                            } else {
                                score -= 100;
                            }
                        }
                            //case 0x17:
                            score++;
                            break;
                        default:
                            score -= 5;
                            break;
                    }

                }
                if (candidate == address.first) {
                    if (score > address.second) {
                        address.second = score;
                    }
                } else if (score > address.second) {
                    address2 = address;
                    address = {candidate, score};
                }
                else if (candidate != address2.first && score > address2.second) {
                    address2 = {candidate, score};
                }
            }
        }
    }

    return {address.first, address2.first};
}

std::array<std::array<bool, 2>, 2> modbusrtu::confidenceMatrix(const std::pair<uint8_t, uint8_t> &guessSetone,
    const std::pair<uint8_t, uint8_t> &guessSettwo) {
    return std::array{ba2{(guessSetone.first == guessSettwo.first), (guessSetone.first == guessSettwo.second)},
        ba2{(guessSetone.second == guessSettwo.first), (guessSetone.second == guessSettwo.second)}};

}
