//
// Created by Andrzej Borucki on 2022-08-13
//

#ifndef EDITWRITE_UNTITLECOUNTER_H
#define EDITWRITE_UNTITLECOUNTER_H


#include <QBitArray>

/* Named editors will have id=0, untitled from 1,2... */
class UntitleCounter {
    const int RESIZE = 32;
    QBitArray *bitArray;
public:
    UntitleCounter();
    ~UntitleCounter() {delete bitArray;};
    int getNextId();
    bool releaseId(int id);
};


#endif //EDITWRITE_UNTITLECOUNTER_H
