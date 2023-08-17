#include "code.h"
#include <time.h>
#include <fstream>

Code::Code()
{

}
Code::Code(Code & c)
{
    setStateAction(c.fsm.stateNum, c.fsm.actionNum);
    this->headStr = c.headStr;
    this->cppStr = c.cppStr;
}
void Code::createCallbackFunInHeadfile()
{
    headStr += "\n";
    //状态的enum
    headStr += "enum state{\n";
    for(int i = 0;i < fsm.stateNum;i++)
    {
        headStr += "\t";
        headStr += fsm.stateList[i];
        headStr += ",\n";
    }
    headStr += "\tENUM_STATE_MAX\n};\n";

    //动作的enum
    headStr += "enum action{\n";
    for(int i = 0;i < fsm.actionNum;i++)
    {
        headStr += "\t";
        headStr += fsm.actionList[i];
        headStr += ",\n";
    }
    headStr += "\tENUM_ACTION_MAX\n};\n\n";

    for(int i = 0; i < fsm.stateNum;i++)
    {
        for(int j = 0;j < fsm.actionNum;j++)
        {
            //检测该状态是否有动作
            if(fsm.fsmTable[i][j])
            {
                headStr += "void *";
                headStr += fsm.stateList[i];
                headStr += "_";
                headStr += fsm.actionList[j];
                headStr += "(void *);\n";
            }

        }
    }
    headStr += "\n";
}
Code::Code(int st, int act)
{  
    setStateAction(st, act);
}
void Code::setStateAction(int st, int act)
{
    fsm.set(st,act);
    srand((unsigned int)time(0));
    uniqueInt = rand();
}
void Code::createFSMDataStruct()
{
    cppStr += "\n";
//    //状态的enum
//    cppStr += "enum state{\n";
//    for(int i = 0;i < fsm.stateNum;i++)
//    {
//        cppStr += "\t";
//        cppStr += fsm.stateList[i];
//        cppStr += ",\n";
//    }
//    cppStr += "\tENUM_STATE_MAX\n};\n";

//    //动作的enum
//    cppStr += "enum action{\n";
//    for(int i = 0;i < fsm.actionNum;i++)
//    {
//        cppStr += "\t";
//        cppStr += fsm.actionList[i];
//        cppStr += ",\n";
//    }
//    cppStr += "\tENUM_ACTION_MAX\n};\n\n";

    //函数指针
    cppStr += "typedef  void* (*pStateDofun)(void*);\n";
    //存放函数指针的数组
    cppStr += "pStateDofun fsmTable [ENUM_STATE_MAX][ENUM_ACTION_MAX] = {\n";
    for(int i = 0;i < fsm.stateNum;i++)
    {
        cppStr += "\t{";
        for(int j = 0;j < fsm.actionNum;j++)
        {
            //只有勾选的状态表中的才显示
            if(fsm.fsmTable[i][j])
            {
                cppStr += fsm.stateList[i];
                cppStr += "_";
                cppStr += fsm.actionList[j];
                if(j == fsm.actionNum - 1)
                {
                    //最后一项不要，
                    break;
                }
                else
                {
                    cppStr += ",\t";
                }
            }
            //没有勾选状态表中动作为null;
            else
            {
                if(j == fsm.actionNum - 1)
                {
                    //最后一项不要，
                    cppStr +="NULL";
                    break;
                }
                else
                {
                    cppStr +="NULL,\t";
                }

            }
        }
        //最后一项不要，
        if(i != fsm.stateNum - 1)
        {
           cppStr += "},\n";
        }
        else
        {
            cppStr += "}\n";
        }

    }
    cppStr += "};\n";

    //加入状态全局变量int gCurrentState = 0;
    cppStr += "int gCurrentState = 0;\n";
    cppStr += "\n";
}
int Code::createCppFile(string filePath)
{
    //1.加入头文件
    string randStr = to_string(uniqueInt);
    string headFileName =  "statemachine";
    headFileName += randStr;
    headFileName += ".h";
    cppStr += "#include \"";
    cppStr += headFileName;
    cppStr += "\"\n";
    cppStr += "#include <stdio.h>\n\n";

    //2.加入状态机的数据结构
    createFSMDataStruct();
    //3.加入状态机的回调函数
    createCallbackFunInCppfile();
    //4.加入状态机的接口函数
    createFSMFunInCppFile();
    //5.生成源代码
    fstream fs;
    string fileName =  filePath;
    fileName += "/statemachine";
    fileName += randStr;
    fileName += ".cpp";
    fs.open(fileName, ios::out);
    if(!fs.is_open())
    {
        return -1;
    }
    fs.write(cppStr.c_str(), cppStr.size());
    fs.close();
    return 0;
}
void Code::createFSMFunInCppFile()
{
    cppStr += "\n";
    cppStr += "void initFsm(int thState){\n\tgCurrentState = thState;\n}\n";
    cppStr += "void changeState(int thState){\n\tgCurrentState = thState;\n}\n";

    cppStr += "void fsm_trans(int thState, int thAction, void *p){\n\tif(thState >= ENUM_STATE_MAX || thAction >= ENUM_ACTION_MAX){\n";
    cppStr += "\t\treturn ;\n";
    cppStr += "\t}\n\tfsmTable[thState][thAction](p);\n}\n";
    cppStr += "\n";
}
void Code::createCallbackFunInCppfile()
{
    cppStr += "\n";
    for(int i = 0; i < fsm.stateNum;i++)
    {
        for(int j = 0;j < fsm.actionNum;j++)
        {
            if(fsm.fsmTable[i][j])
            {
                //函数名称
                cppStr += "void *";
                cppStr += fsm.stateList[i];
                cppStr += "_";
                cppStr += fsm.actionList[j];
                cppStr += "(void *)";

                //函数实现
                cppStr += "{\n\treturn NULL;\n}\n";
            }
        }
    }
    cppStr += "\n";
}
int Code::createHeadFile( string filePath)
{
    string randStr = to_string(uniqueInt);
    headStr += "#ifndef ";
    headStr += "STATEMACHINE_";
    headStr += randStr;
    headStr += "\n#define ";
    headStr += "STATEMACHINE_";
    headStr += randStr;
    headStr += "\n";

    createCallbackFunInHeadfile();
    createFSMFunInHeadFile();
    headStr += "\n#endif";

    fstream fs;
    string fileName =  filePath;
    fileName += "/statemachine";
    fileName += randStr;
    fileName += ".h";
    fs.open(fileName, ios::out);
    if(!fs.is_open())
    {
        return -1;
    }
    fs.write(headStr.c_str(), headStr.size());
    fs.close();
    return 0;
}
void Code::createFSMFunInHeadFile()
{
    headStr += "\n";
    headStr += "void initFsm(int thState);\n";
    headStr += "void changeState(int thState);\n";
    headStr += "void fsm_trans(int thState, int thAction, void *p);\n";
    headStr += "\n";
}
