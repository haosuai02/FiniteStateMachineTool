#ifndef STATEMACHINE_19812
#define STATEMACHINE_19812

enum state{
	state0,
	state1,
	state2,
	ENUM_STATE_MAX
};
enum action{
	action0,
	action1,
	ENUM_ACTION_MAX
};

void *state0_action0(void *);
void *state1_action0(void *);
void *state2_action1(void *);


void initFsm(int thState);
void changeState(int thState);
void fsm_trans(int thState, int thAction, void *p);


#endif