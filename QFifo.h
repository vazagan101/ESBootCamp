#ifndef _Q_FIFO_H_
#define _Q_TIMER_H_

#include "FSM.h"

#define SIZE_OF_QEVENT          sizeof(

typedef struct QFIFOStrTag {

    uint8_t  HeadIndex;
    uint8_t  TailIndex;
    uint8_t* pQFifoBuffer;
    bool     Status;

}QFifo_t,*pQFifo_t;






#endif // _Q_FIFO_H_
