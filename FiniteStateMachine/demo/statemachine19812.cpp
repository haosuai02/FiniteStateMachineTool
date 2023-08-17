#include "statemachine19812.h"
#include <stdio.h>


typedef  void* (*pStateDofun)(void*);
pStateDofun fsmTable [ENUM_STATE_MAX][ENUM_ACTION_MAX] = {
	{state0_action0,	NULL},
	{state1_action0,	NULL},
	{NULL,	state2_action1}
};
int gCurrentState = 0;


void *state0_action0(void *){
    //1.修改回调函数
    printf("state0_action0 被调用\n");
    if(gCurrentState != state0)
    {
        return NULL;
    }

    changeState(state1);
	return NULL;
}
void *state1_action0(void *){
	return NULL;
}
void *state2_action1(void *){
	return NULL;
}


void initFsm(int thState){
	gCurrentState = thState;
}
void changeState(int thState){
	gCurrentState = thState;
}
void fsm_trans(int thState, int thAction, void *p){
	if(thState >= ENUM_STATE_MAX || thAction >= ENUM_ACTION_MAX){
		return ;
	}
	fsmTable[thState][thAction](p);
}

