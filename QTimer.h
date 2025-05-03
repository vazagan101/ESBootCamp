#ifndef _Q_TIMER_H_
#define _Q_TIMER_H_

#include <stdint.h>
#include <stdbool.h>
#include "FSM.h"


#define     MAX_NO_OF_QTIMERS           5
#define     NO_QTIMERS_AVAILABLE        23

typedef uint16_t         QTimer_Tick_t;
typedef uint8_t          QTimer_ID_t;
typedef uint32_t         QFifo_t;    //----->TODO
typedef void (*QTimerCallBack)( void );

typedef enum {

    QTimer_OFF,
    QTimer_ON,
    QTimer_PAUSED,
    QTimer_UNUSED,
    QTimer_UNKNOWN

} QTimer_State_t, *pQTimer_State_t;

typedef struct {

    QTimer_State_t  QTimerStatus;
    bool            QTimerCyclic;
    uint16_t        QTimerPreset;
    uint16_t        QTimerElapsedTicks;
    QFifo_t*        QTimerFIFOBuffer;
    QSignal         evTimeOut;
    QTimerCallBack  QTimerCbkFunction;

}QTimer_t,*pQTimer_t;

/*.............................................................................................*/

QTimer_State_t      QTimer_Start( QTimer_ID_t const TimerID, QTimer_Tick_t const Ticks );
QTimer_State_t      QTimer_GetStatus( QTimer_ID_t const TimerID );
QTimer_ID_t         QTimer_Create( QFifo_t* const fifo ,QSignal const Sig, bool QTimerKind, QTimerCallBack Cbk );
void                QTimer_Stop( QTimer_ID_t const TimerID );
void                QTimer_Init( void );
bool                QTimer_Tick( void );
void                QTimer_Pause( QTimer_ID_t const TimerID );
void                QTimer_Continue( QTimer_ID_t const TimerID );
void                QTimer_Remove( QTimer_ID_t const TimerID );

/*.............................................................................................*/

#endif
