#ifndef _FSM_H_
#define _FSM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//QP FSM Event Processor Basic Macros and Functions

#define Q_RET_HANDLED                   ((QState)0)
#define Q_RET_IGNORED                   ((QState)1)
#define Q_RET_TRAN                      ((QState)2)
#define Q_RET_INIT                      ((QState)3)
#define MAX_REGISTERED_EVENTS            4

#define ENTRY                            0
#define EXIT                             1
#define INIT                             2
#define USER                             3


#define QFsm_Ctor( me_ , initial_ )     ((me_)->state = ( QStateHandler )(initial_))


#define Q_IGNORED()                     (Q_RET_IGNORED)
#define Q_HANDLED()                     (Q_RET_HANDLED)
#define Q_INITIALIZED()                 (Q_RET_INIT)

#define Q_TRAN(target_)                 ((((QFsm*)me)->state = ( QStateHandler )( target_ )) , Q_RET_TRAN);
#define Q_INIT(target_)                 ((((QFsm*)me)->state = ( QStateHandler )( target_ )));

#define Q_Log( string_ )                printf(string_);printf("\n");

typedef uint8_t     QState;
typedef uint8_t     QSignal;
typedef struct {

    QSignal sig;
    uint8_t dynamic_;

} QEvent;

typedef QState (*QStateHandler)( void* me , QEvent const* e );

typedef struct {
    QStateHandler   state;
} QFsm;

enum QReservedSignals {

    Q_ENTRY_SIG = 1,
    Q_EXIT_SIG,
    Q_INIT_SIG,
    Q_USER_SIG

};

void QFsm_Init( QFsm* const me , QEvent const * e );
void QFsm_Dispatch( QFsm* const me , QEvent const * e );


#endif // _FSM_H_
