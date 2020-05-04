/*
 * hsm.h
 *
 *  Created on: 2019/04/15
 *      Author: KakishiS
 */

#ifndef _HSM_H_
#define _HSM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define HSM_BUF_SIZE	16

typedef enum
{
	HSM_ST_NULL,
	HSM_ST_ENTRY,
	HSM_ST_START,
	HSM_ST_EXIT,
	HSM_ST_USER,
} HSMEvent_t;

typedef int Event;
typedef void (*EvtHndlr)(Event const);

typedef struct HSMStateObject_t
{
	struct HSMStateObject_t *parent_e;
	int8_t const *name_s8;
	EvtHndlr handler;
} HSMState_t;

void HSM_Init(HSMState_t *top);
void HSM_Create(HSMState_t *me, HSMState_t *parent, char const *name, EvtHndlr evtHdl);
void HSM_Dispatch(Event evt);
int HSM_Transition(HSMState_t *state_t);
void HSM_Cyclic(void);
const char* HSM_GetEventName(Event evt);

#ifdef __cplusplus
}
#endif

#endif /* _HSM_H_ */
