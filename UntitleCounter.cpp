//
// Created by Andrzej Borucki on 2022-08-13
//

#include "UntitleCounter.h"

int UntitleCounter::getNextId() {
    int cnt = bitArray.count();
    int result = cnt;
    for (int i=1; i<cnt; i++)
    {
        if (!bitArray.testBit(i)) {
            result = i;
            break;
        }
    };
    if (bitArray.size()<result+1)
        bitArray.resize(result+1);
    bitArray.setBit(result);
    return result;
}

bool UntitleCounter::releaseId(int id) {
    if (id<1) return false;
    if (!bitArray.testBit(id)) return false;
    bitArray.clearBit(id);
    return true;
}

UntitleCounter::UntitleCounter() {
    if (bitArray.size()<1)
        bitArray.resize(1);
    bitArray.setBit(0); //not used for untitled
}
