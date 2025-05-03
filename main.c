#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "QTimer.h"
#include <windows.h>
#include "FSM.h"

#define TIME_TO_RELEASE         10

/*.................................................................................*/
extern QEvent QEP_ReservedEvt_[];
/*.................................................................................*/
//Fsm Data structure
typedef struct {

    QFsm        super;
    uint32_t   data;
    uint8_t    TIME_OUT;

} FsmDemo ;


typedef void (*pFunction)(void);
HANDLE timerHandle;
QTimer_ID_t xTimer;

VOID CALLBACK TimerCallBack(PVOID lpParameter, BOOLEAN TimerOrWaitFired)
{
    static int  x = 0;
    printf("Tick() - CALLED! #%d\n",x++%10);
    QTimer_Tick();
}


static void gstAllDataBufferTarrifInit( void )
{
 //   memset(&gstAllDataBuffer->stPriceSched , 0 , PRICE_SCHED_SIZE );
 //   memset(&gstAllDataBuffer)
}

/*.................................................................................*/
static QState FsmDemo_VALIDATION( QFsm* const me , QEvent* const e );
static QState FsmDemo_IDLE( QFsm* const me , QEvent* const e );
static QState FsmDemo_APPROVED_WORKING_PLAN( QFsm* const me , QEvent* const e );
static QState FsmDemo_Pending_Future_Plan( QFsm* const me , QEvent* const e );
/*.................................................................................*/
static QState FsmDemo_IDLE( QFsm* const me , QEvent* const e )
{
    switch( e->sig ){

    case Q_ENTRY_SIG:{
            Q_Log("IDLE STATE - ENTRY SIG  ");
            Q_Log("LED_SWITCHED_OFF !!\n")
            return Q_HANDLED();
        }
    case Q_EXIT_SIG:{
            Q_Log("IDLE STATE - EXIT SIG  ");
            return Q_HANDLED();
        }
    case Q_INIT_SIG:{
            Q_Log("IDLE STATE - INIT SIG  ");
            return Q_INITIALIZED();
        }
    case Q_USER_SIG:{
            Q_Log("IDLE STATE - USER SIG  ");
            Q_Log("LED_USER_OFF !!\n")
            return Q_TRAN(&FsmDemo_VALIDATION);
        }
    }
    return Q_IGNORED();
}
/*.................................................................................*/
static QState FsmDemo_VALIDATION( QFsm* const me , QEvent* const e )
{
    switch( e->sig )
    {
    case Q_ENTRY_SIG:{
            Q_Log("VALIDATION STATE - ENTRY SIG  ");
            Q_Log("LED_SWITCHED_ON !!\n")
            return Q_HANDLED();
        }
    case Q_EXIT_SIG:{
            Q_Log("VALIDATION STATE - EXIT SIG  ");
            return Q_HANDLED();
        }
    case Q_USER_SIG:{
            Q_Log("VALIDATION STATE - Q_USER_SIG  ");
            Q_Log("LED_SWITCHED_USER_OFF !!\n")
            return Q_TRAN(&FsmDemo_IDLE);
        }
    }
    return Q_IGNORED();
}
/*.................................................................................*/

QState FsmDemo_APPROVED_WORKING_PLAN( QFsm* const me , QEvent* const e )
{
    switch( e->sig )
    {
    case Q_ENTRY_SIG:{
            return Q_HANDLED();
        }
    case Q_EXIT_SIG:{
            return Q_HANDLED();
        }
    }
    return Q_IGNORED();
}
/*.................................................................................*/

static QState FsmDemo_Pending_Future_Plan( QFsm* const me , QEvent* const e )
{
    switch( e->sig )
    {
    case Q_ENTRY_SIG:{
            return Q_HANDLED();
        }
    case Q_EXIT_SIG:{
            return Q_HANDLED();
        }
    }
    return Q_IGNORED();
}
/*.................................................................................*/
void FsmDemo_Ctor( FsmDemo*  me , QStateHandler Handler )
{
    me->TIME_OUT = TIME_TO_RELEASE;
    Q_INIT(Handler);
}
/*.................................................................................*/
static FsmDemo instance;

void QTimerCallBackFunction( void )
{
    Q_Log("[+] QTimer lOG Function Called ! \n");
    QFsm_Dispatch(&instance, &QEP_ReservedEvt_[USER]);
    //QTimer_Pause(xTimer);

}


void SYSTEM_Init( void )
{
    FsmDemo_Ctor( &instance, FsmDemo_IDLE);
    QFsm_Dispatch( &instance, &QEP_ReservedEvt_[INIT]);
    QTimer_Init();
    xTimer = QTimer_Create(NULL , 0, true ,&QTimerCallBackFunction );
}


int main()
{

   MSG msg;

   HANDLE timerQueue = CreateTimerQueue();


    if (timerQueue == NULL)
    {
        // Handle error
        return 1;
    }

    // Create a timer in the timer queue
    if (!CreateTimerQueueTimer(&timerHandle, timerQueue, (WAITORTIMERCALLBACK)TimerCallBack, NULL, 0, 500, 0))
    {
        // Handle error
        CloseHandle(timerQueue);
        return 1;
    }
        SYSTEM_Init();
        QTimer_Start(xTimer, 20 );

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
/*.................................................................................*/









