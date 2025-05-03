#include <stdint.h>
#include "FSM.h"

//Reserved Events
QEvent QEP_ReservedEvt_[ MAX_REGISTERED_EVENTS ]= {

    { (QSignal)Q_ENTRY_SIG , 0},
    { (QSignal)Q_EXIT_SIG  , 0},
    { (QSignal)Q_INIT_SIG  , 0},
    { (QSignal)Q_USER_SIG  , 0}

};

void QFsm_Init( QFsm* const me , QEvent const * e )
{
    (*(me->state))( me , e );
    (*(me->state))( me , &QEP_ReservedEvt_[ENTRY]);
}

void QFsm_Dispatch( QFsm* const me , QEvent const * e )
{
    QStateHandler Source = me->state;
    QState Ret           = (*(Source))( me , e);

    if( Ret == Q_RET_INIT )
        {
            (void)((*me->state)( me, (&QEP_ReservedEvt_[ENTRY])));
        }

    if( Ret == Q_RET_TRAN )
        {
            (void)((*Source)( me , &QEP_ReservedEvt_[EXIT]));
            (void)((*me->state)( me, (&QEP_ReservedEvt_[ENTRY])));
        }
}
