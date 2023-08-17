#ifndef STATEMACHINE_H
#define STATEMACHINE_H
//根据状态和动作生成状态表
#include <string>
#include <vector>

using namespace  std;
//定义回调函数的类型
typedef  void *(pStateDofun)(void *);
class StateMachine
{
public:
    //状态总数
    int stateNum;
    int actionNum;
    //状态名称列表
    vector<string> stateList;
    vector<string> actionList;
    //状态机回调函数数组(很难通过字符串动态创建函数，fsmTable无法填写)
    //vector<vector<pStateDofun>> fsmTable;
    vector<vector<bool>> fsmTable;
    StateMachine();
    StateMachine(int st, int act);
    void set(int st, int act);
private:
    //根据状态数量生成默认的状态名
    void setStateName(int st);

    void setActionName(int act);
};

#endif // STATEMACHINE_H
