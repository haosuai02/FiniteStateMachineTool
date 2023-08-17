#include "statemachine.h"

StateMachine::StateMachine()
{

}
StateMachine::StateMachine(int st, int act)
{
    set(st, act);
}
void StateMachine::set(int st, int act)
{
    stateNum = st;
    actionNum = act;
    setStateName(st);
    setActionName(act);
    fsmTable.resize(st);
    for(int i = 0;i < stateNum;i++)
    {
        for(int j = 0;j < actionNum;j++)
        {
            fsmTable[i].push_back(false);
        }
    }
}
void StateMachine::setStateName(int st)
{
    stateList.clear();
    for(int i = 0;i < st;i++)
    {
        string stateName = "state";
        stateName += to_string(i);
        stateList.push_back(stateName);
    }
}

void StateMachine::setActionName(int act)
{
    actionList.clear();
    for(int i = 0;i < act;i++)
    {
        string actionName = "action";
        actionName += to_string(i);
        actionList.push_back(actionName);
    }
}
