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
        cout << "����������ѡ��:" << endl;
        cin >> choose;
        switch (choose)
        {
        case 1: // ��ʾѧ����Ϣ
        {
            mng.showStu();
            break;
        }
        case 2: // ���ѧ����Ϣ
        {
            mng.addStu();
            break;
        }
        case 3: // ����ѧ����Ϣ
        {
            mng.searchStu();
            break;
        }
        case 4: // �޸�ѧ����Ϣ
        {
            mng.alterStu();
            break;
        }
        case 5: // ɾ��ѧ����Ϣ
        {
            mng.moveStu();
            break;
        }
        case 6: // ���ѧ����Ϣ
        {
            mng.clearStu();
            break;
        }
        case 0: // �˳�ѧ��ϵͳ
        {
            mng.exitSys();
            break;
        }
        default:
            cout << "������������" << endl;
        }
        system("pause");
        system("cls");
    }
    return 0;
}



