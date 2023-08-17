#ifndef CODE_H
#define CODE_H
//根据用户输入的动作和状态生成源代码
#include <string>

#include <sstream>
#include "statemachine.h"

using namespace std;
class Code
{
public:
    Code();
    Code(int st, int act);
    Code(Code & c);
    int uniqueInt;
    StateMachine fsm;
    //头文件的内容
    string headStr;
    //源文件的内容
    string cppStr;
    //string fileName;

    void setStateAction(int st, int act);
    int createHeadFile(string filePath);
    int createCppFile(string filePath);



private:
    void createCallbackFunInHeadfile();
    void createFSMFunInHeadFile();
    //生成状态机回调函数
    void createCallbackFunInCppfile();
    //生成状态机的接口函数
    void createFSMFunInCppFile();
    void createFSMDataStruct();
};

#endif // CODE_H
