#include <stdint.h>
#include <stdbool.h>
#include "QTimer.h"

/*.............................................................................................*/
static QTimer_t QTimersList[ MAX_NO_OF_QTIMERS ];
/*.............................................................................................*/
QTimer_State_t
QTimer_Start( QTimer_ID_t const TimerID, QTimer_Tick_t const Ticks )
{
    if( TimerID  > MAX_NO_OF_QTIMERS )
    {
        return QTimer_UNKNOWN;
    }

    QTimersList[ TimerID ].QTimerElapsedTicks = 0U;
    QTimersList[ TimerID ].QTimerPreset       = Ticks;
    QTimersList[ TimerID ].QTimerStatus       = QTimer_ON;

    return QTimer_ON;
}
/*.............................................................................................*/
QTimer_State_t
QTimer_GetStatus( QTimer_ID_t TimerID )
{
   if( TimerID > MAX_NO_OF_QTIMERS )
    {
        return QTimer_UNKNOWN;
    }

    return QTimersList[ TimerID ].QTimerStatus;
}
/*.............................................................................................*/
QTimer_ID_t
QTimer_Create( QFifo_t* const fifo ,QSignal const Sig, bool QTimerKind , QTimerCallBack Cbk )
{
    uint8_t  TimerCount  = 0U;
    //fifo = NULL;
    while( TimerCount < MAX_NO_OF_QTIMERS )
    {
        if( QTimersList[ TimerCount ].QTimerStatus == QTimer_UNUSED )
        {
            QTimersList[ TimerCount ].QTimerStatus          = QTimer_OFF;
            QTimersList[ TimerCount ].QTimerCyclic          = QTimerKind;
            QTimersList[ TimerCount ].QTimerElapsedTicks    = 0U;
            QTimersList[ TimerCount ].QTimerFIFOBuffer      = fifo;
            QTimersList[ TimerCount ].evTimeOut             = Sig;
            QTimersList[ TimerCount ].QTimerCbkFunction     = Cbk;

            return TimerCount;  //This will Return the QTimerCount ID Number
        }
        TimerCount++;
    }
    return 0;
}
/*.............................................................................................*/
void
QTimer_Stop( QTimer_ID_t    TimerID )
{
    if( TimerID > MAX_NO_OF_QTIMERS )
    {
        return;
    }

    QTimersList[ TimerID ].QTimerStatus = QTimer_OFF;
}
/*.............................................................................................*/
void    QTimer_Init( void )
{
    uint8_t x;

    for( x = 0 ; x < MAX_NO_OF_QTIMERS ; x++ )
    {
        QTimersList[ x ].QTimerStatus       = QTimer_UNUSED;
        QTimersList[ x ].QTimerCyclic       = false;
        QTimersList[ x ].QTimerPreset       = 0U;
        QTimersList[ x ].QTimerElapsedTicks = 0U;
        QTimersList[ x ].QTimerFIFOBuffer   = NULL;
        QTimersList[ x ].evTimeOut          = 0U;
    }
}
/*.............................................................................................*/
bool
QTimer_Tick( void )
{
    bool    QTimeOutOccurence  = false;
    uint8_t TimerCounter;



    for( TimerCounter = 0U ; TimerCounter < MAX_NO_OF_QTIMERS ; TimerCounter++ )
    {
        if( QTimersList[ TimerCounter].QTimerStatus == QTimer_ON )
        {
            QTimersList[ TimerCounter ].QTimerElapsedTicks++;

            if( QTimersList[ TimerCounter ].QTimerElapsedTicks == QTimersList[ TimerCounter ].QTimerPreset )
            {
                if( QTimersList[ TimerCounter ].QTimerCyclic == true )
                {
                    QTimersList[ TimerCounter ].QTimerElapsedTicks = 0U;
                }else
                {
                    QTimersList[ TimerCounter ].QTimerStatus = QTimer_OFF;
                }
					#if (AO == 1)
						QFifoPost();
					#endif
                //Disable IRQ
                //Post the  Timeout event to the Timer's Queue
                 (QTimersList[ TimerCounter ].QTimerCbkFunction)();
                //Enable IRQ
                QTimeOutOccurence = true;
            }
        }
    }
    return QTimeOutOccurence;
}
/*.............................................................................................*/

void
QTimer_Pause( QTimer_ID_t TimerID )
{
    if( TimerID > MAX_NO_OF_QTIMERS )
    {
        return;
    }

    QTimersList[ TimerID ].QTimerStatus = QTimer_PAUSED;

}
/*.............................................................................................*/
void
QTimer_Continue( QTimer_ID_t TimerID )
{
    if( TimerID > MAX_NO_OF_QTIMERS )
    {
        return;
    }

    QTimersList[ TimerID ].QTimerStatus = QTimer_ON;

}
/*.............................................................................................*/
void
QTimer_Remove( QTimer_ID_t TimerID )
{
    if( TimerID > MAX_NO_OF_QTIMERS )
    {
        return;
    }
    QTimersList[ TimerID ].QTimerStatus = QTimer_OFF;
}
