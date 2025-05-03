#include <stdint.h>
#include "FSM.h"

//Hardware initializations will always be placed inside the init function !


typedef struct {

    QFsm            super;
    uint32_t       data;

}ButtonSM_t,*pButtonSM_t;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - - */
static QState ButtonSM_DePressed( QFsm* const me , QEvent* const e )
{
    switch( e->sig ){

    case Q_ENTRY_SIG:{
            Q_Log("DePressed STATE - ENTRY SIG  ");
            Q_Log("LED_SWITCHED_OFF !!\n")
            return Q_HANDLED();
        }
    case Q_EXIT_SIG:{
            Q_Log("DePressed STATE - EXIT SIG  ");
            return Q_HANDLED();
        }
    case Q_INIT_SIG:{
            Q_Log("DePressed STATE - INIT SIG  ");
            return Q_INITIALIZED();
        }
    case Q_USER_SIG:{
            Q_Log("DePressed STATE - USER SIG  ");
            Q_Log("BUTTON_USER_DePressed !!\n")
            return Q_TRAN(&ButtonSM_Pressed);
        }
    }
    return Q_IGNORED();
}
/*.................................................................................*/
static QState ButtonSM_Pressed( QFsm* const me , QEvent* const e )
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
