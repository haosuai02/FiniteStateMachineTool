#include <QCoreApplication>
#include "statemachine19812.h"

extern int gCurrentState;
/*
 * 例子：
       现在有状态STATE0，STATE1，STATE2。
       其中   STATE0--action0-->STATE1,
              STATE1--action0-->STATE2,
              STATE2--action1-->STATE1,
       现在需要使用程序来表示上面的情况。
 * */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //初始化状态
    initFsm(state0);
    printf("gCurrentState = [%d]\n", gCurrentState);
    //由state0状态产生action0动作，自动调用state0_action0函数，需要自己修改回调函数
    fsm_trans(state0, action0, NULL);
    printf("gCurrentState = [%d]\n", gCurrentState);
    return a.exec();
}
