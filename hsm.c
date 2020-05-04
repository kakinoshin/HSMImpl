#include <stddef.h>
#include "typedef.h"
#include "hsm.h"

typedef struct
{
	//HSMStateObject_t* top;
	HSMState_t* current;
	Event lastEvent;
} HSMMng_t;

/* private */
static HSMMng_t hsm_mng;

/* public */
void HSM_Init(HSMState_t *top)
{
	hsm_mng.current = top;
	hsm_mng.lastEvent = HSM_ST_NULL;
}

void HSM_Create(HSMState_t *me, HSMState_t *parent, char const *name, EvtHndlr evtHdl)
{
	if (me != NULL)
	{
		me->parent_e = parent;
		me->name_s8 = name;
		me->handler = evtHdl;
	}
}

void HSM_Dispatch(Event evt)
{
	if (hsm_mng.current->handler != NULL)
	{
		hsm_mng.current->handler(evt);
	}
}

int HSM_Transition(HSMState_t *state_t)
{
	int i, j;
	int ret = -1;
	int startFlag = 0;
	HSMState_t* state = NULL;
	HSMState_t* ClimbBuffer[HSM_BUF_SIZE];
	HSMState_t* GetOffBuffer[HSM_BUF_SIZE];
	HSMState_t* CrossedState = NULL;

	for (i = 0; i < HSM_BUF_SIZE; i++)
	{
		ClimbBuffer[i] = NULL;
		GetOffBuffer[i] = NULL;
	}

	if (state_t != NULL)
	{
		/* create route information */
		state = hsm_mng.current;
		for (i = 0; i < HSM_BUF_SIZE; i++)
		{
			ClimbBuffer[i] = state;
			if (state != NULL && state->parent_e != NULL)
			{
				state = state->parent_e;
			}
			else
			{
				break;
			}
		}

		state = state_t;
		for (i = 0; i < HSM_BUF_SIZE; i++)
		{
			GetOffBuffer[i] = state;
			if (state != NULL && state->parent_e != NULL)
			{
				state = state->parent_e;
			}
			else
			{
				break;
			}
		}

		/* find crossed state */
		for (i = 0; i < HSM_BUF_SIZE && ClimbBuffer[i] != NULL; i++)
		{
			for (j = 0; j < HSM_BUF_SIZE && GetOffBuffer[j] != NULL; j++)
			{
				if (ClimbBuffer[i] == GetOffBuffer[j])
				{
					CrossedState = ClimbBuffer[i];
					break;
				}
			}
			if (CrossedState != NULL)
			{
				break;
			}
		}

		/* if CrossedState is NULL, probably buffer is not enough or 
		   there is design issue in state definition */
		if (CrossedState != NULL)
		{
			/* run exit */
			for (i = 0; i < HSM_BUF_SIZE && ClimbBuffer[i] != NULL; i++)
			{
				if (ClimbBuffer[i]->handler != NULL)
				{
					ClimbBuffer[i]->handler(HSM_ST_EXIT);
				}
				if (ClimbBuffer[i] == CrossedState)
				{
					break;
				}
			}
			/* run entry */
			for (j = HSM_BUF_SIZE - 1; j >= 0; j--)
			{
				if (GetOffBuffer[j] == CrossedState)
				{
					startFlag = 1;
				}
				if (GetOffBuffer[j] != NULL && GetOffBuffer[j]->handler != NULL && startFlag == 1)
				{
					GetOffBuffer[j]->handler(HSM_ST_ENTRY);
				}
			}
			/* run start */
			if (state_t->handler != NULL)
			{
				state_t->handler(HSM_ST_START);
			}

			/* update information in manager */
			hsm_mng.lastEvent = HSM_ST_NULL;
			hsm_mng.current = state_t;

			ret = 0;
		}
	}

	return ret;
}

void HSM_Cyclic(void)
{
	if (hsm_mng.current->handler != NULL)
	{
		hsm_mng.current->handler(hsm_mng.lastEvent);
	}
}

const char* HSM_GetEventName(Event evt)
{
	switch (evt)
	{
	case HSM_ST_NULL:	return "HSM_ST_NULL";	break;
	case HSM_ST_ENTRY:	return "HSM_ST_ENTRY";	break;
	case HSM_ST_START:	return "HSM_ST_START";	break;
	case HSM_ST_EXIT:	return "HSM_ST_EXIT";	break;
	default:
		if (evt >= HSM_ST_USER)
		{
			return "HSM_ST_USER";
		}
		else
		{
			return "HSM_ST_ERROR";
		}
	}
}
