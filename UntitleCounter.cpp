//
// Created by Andrzej Borucki on 2022-08-13
//

#include "UntitleCounter.h"

int UntitleCounter::getNextId() {
    int cnt = bitArray->count();
    int result = cnt;
    for (int i=1; i<cnt; i++)
    {
        if (!bitArray->testBit(i)) {
            result = i;
            break;
        }
    };
    assert(bitArray->size()>=result);
    if (bitArray->size()==result)
        bitArray->resize(result+RESIZE);
    bitArray->setBit(result);
    return result;
}

bool UntitleCounter::releaseId(int id) {
    assert(id>=1);
    assert(bitArray->testBit(id));
    bitArray->clearBit(id);
    return true;
}

UntitleCounter::UntitleCounter() {
    bitArray = new QBitArray(RESIZE);
    bitArray->setBit(0); //not used for untitled
}
