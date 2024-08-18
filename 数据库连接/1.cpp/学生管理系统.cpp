#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tchar.h>
#include "mysql.h"
#include "student.h"
#include "manager.h"

using namespace std;


int main() {
    Manager mng;
    
    while (1)
    {
        mng.showMenu();
        int choose;
        cout << "请输入您的选择:" << endl;
        cin >> choose;
        switch (choose)
        {
        case 1: // 显示学生信息
        {
            mng.showStu();
            break;
        }
        case 2: // 添加学生信息
        {
            mng.addStu();
            break;
        }
        case 3: // 查找学生信息
        {
            mng.searchStu();
            break;
        }
        case 4: // 修改学生信息
        {
            mng.alterStu();
            break;
        }
        case 5: // 删除学生信息
        {
            mng.moveStu();
            break;
        }
        case 6: // 清空学生信息
        {
            mng.clearStu();
            break;
        }
        case 0: // 退出学生系统
        {
            mng.exitSys();
            break;
        }
        default:
            cout << "您的输入有误！" << endl;
        }
        system("pause");
        system("cls");
    }
    return 0;
}



