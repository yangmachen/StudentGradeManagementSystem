#include "manager.h"
#include <Windows.h>




// ���캯��
Manager::Manager()
{
	// ���ݿ����� MYSQL* m_conn+;m_stuNum+;v_stu+;is_empty+;
    this->is_empty = true;
	this->m_conn = mysql_init(NULL);
    mysql_options(this->m_conn, MYSQL_SET_CHARSET_NAME, "GBK");
    if (mysql_real_connect(this->m_conn, "localhost", "root", "123456", "student", 3306, NULL, 0)) {
        this->is_conn = true;
        // ��ʾ���ӳɹ���ʾ
        cout << "database connect sucess!" << endl;
    }
    else
    {
        this->is_conn = false;
        cout << "error" << endl;
        return;
    }


    // ��ȡ���ݿ����������
    string S = "select * from student";
    if (mysql_query(this->m_conn, S.c_str()))
    {
        cout << "��ȡѧ��������ʧ��" << endl;
    }
    
    // ��������
    res = mysql_store_result(this->m_conn);
    this->m_stuNum = 0;
    if (res)
    {
        while (row = mysql_fetch_row(res))
        {
            // ��������
            int id = atoi(row[0]);
            string name = row[1];
            int chi = atoi(row[2]);
            int math = atoi(row[3]);
            int eng = atoi(row[4]);
            
            // ����ѧ��
            Student stu(id, name, chi, math, eng);
            // ����ѧ������
            this->v_stu.push_back(stu);
            this->m_stuNum++;
            this->is_empty = false;
        }
    }
    else
    {
        this->is_empty = true;
    }

}
// ��������
Manager::~Manager()
{
    mysql_close(this->m_conn);
}




// ��ʾ�˵�
void Manager::showMenu()
{
    cout << "******************************" << endl;
    cout << "***��ӭ����ѧ���ɼ�����ϵͳ***" << endl;
    cout << "********1 ��ʾѧ����Ϣ********" << endl;
    cout << "********2 ���ѧ����Ϣ********" << endl;
    cout << "********3 ����ѧ����Ϣ********" << endl;
    cout << "********4 �޸�ѧ����Ϣ********" << endl;
    cout << "********5 ɾ��ѧ����Ϣ********" << endl;
    cout << "********6 ���ѧ����Ϣ********" << endl;
    cout << "********0 �˳�ѧ��ϵͳ********" << endl;
    cout << "******************************" << endl;
}
// ���ѧ����Ϣ
void Manager::addStu()
{
    int id;
    string name;
    int chi;
    int math;
    int eng;
    cout << "������id��:" << endl;
    cin >> id;
    cout << "����������:" << endl;
    cin >> name;
    cout << "���������ĳɼ�:" << endl;
    cin >> chi;
    cout << "��������ѧ�ɼ�:" << endl;
    cin >> math;
    cout << "������Ӣ��ɼ�:" << endl;
    cin >> eng;
    // ����ѧ��
    Student stu(id, name, chi, math, eng);
    
    // �������ݿ�
    char cstr[1000];
    sprintf_s(cstr, "insert into student(id, name, chinese, math, english, total) values(%d, '%s', %d, %d, %d, %d)",
        stu.m_id, stu.m_name.c_str(), stu.m_chi, stu.m_math, stu.m_eng, stu.m_total);
    if (mysql_query(this->m_conn, cstr))
    {
        cout << "����ʧ��" << endl;
        return;
    }
    else
    {
        cout << "��ӳɹ�" << endl;
    }
    // ��������
    this->v_stu.push_back(stu);
    this->m_stuNum++;
    this->is_empty = false;
}
// ����ѧ���Ƿ����(�����±�)
int Manager::findStu(int id)
{
    for (int i = 0; i < this->m_stuNum; i++)
    {
        if (this->v_stu[i].m_id == id)
        {
            return i;
        }
    }
    return -1;
}
// �޸�ѧ����Ϣ
void Manager::alterStu()
{
    cout << "������id��:" << endl;
    int id;
    cin >> id;
    int index = this->findStu(id);
    if (index != -1)
    {
        cout << "�������޸ĵ���:" << endl;
        cout << "1 id��" << endl;
        cout << "2 ����" << endl;
        cout << "3 ���ĳɼ�" << endl;
        cout << "4 ��ѧ�ɼ�" << endl;
        cout << "5 Ӣ��ɼ�" << endl;
        int op;
        cin >> op;
        char cstr[1000];
        switch (op)
        {
        case 1: // id��
        {
            int newid;
            cout << "�������µ�id:" << endl;
            cin >> newid;
            sprintf_s(cstr, "update student set id = %d where id = %d", newid, id);
            if (mysql_query(this->m_conn, cstr))
            {
                cout << "����ʧ��" << endl;
                return;
            }
            else
            {
                cout << "���³ɹ�" << endl;
                // ����vstu
                this->v_stu[index].m_id = newid;
            }
            break;
        }
        case 2: // ����
        {
            string newName;
            cout << "�������µ�����:" << endl;
            cin >> newName;
            sprintf_s(cstr, "update student set name = '%s' where id = %d", newName.c_str(), id);
            if (mysql_query(this->m_conn, cstr))
            {
                cout << "����ʧ��" << endl;
                return;
            }
            else
            {
                cout << "���³ɹ�" << endl;
                // ����vstu
                this->v_stu[index].m_name = newName;
            }
            break;
        }
        case 3: // ���ĳɼ�
        {
            int newChi;
            cout << "�������µ����ĳɼ�:" << endl;
            cin >> newChi;
            // ���޸�vstr
            this->v_stu[index].m_chi = newChi;
            this->v_stu[index].cal_total();
            sprintf_s(cstr, "update student set chinese = %d, total = %d where id = %d", newChi, this->v_stu[index].m_total, id);
            if (mysql_query(this->m_conn, cstr))
            {
                cout << "����ʧ��" << endl;
                return;
            }
            else
            {
                cout << "���³ɹ�" << endl;
            }
            break;
        }
        case 4: // ��ѧ�ɼ�
        {
            int newMath;
            cout << "�������µ���ѧ�ɼ�:" << endl;
            cin >> newMath;
            // ���޸�vstr
            this->v_stu[index].m_math = newMath;
            this->v_stu[index].cal_total();
            sprintf_s(cstr, "update student set math = %d, total = %d where id = %d", newMath, this->v_stu[index].m_total, id);
            if (mysql_query(this->m_conn, cstr))
            {
                cout << "����ʧ��" << endl;
                return;
            }
            else
            {
                cout << "���³ɹ�" << endl;
            }
            break;
        }
        case 5: // Ӣ��ɼ�
        {
            int newEng;
            cout << "�������µ�Ӣ��ɼ�:" << endl;
            cin >> newEng;
            // ���޸�vstr
            this->v_stu[index].m_eng = newEng;
            this->v_stu[index].cal_total();
            sprintf_s(cstr, "update student set english = %d, total = %d where id = %d", newEng, this->v_stu[index].m_total, id);
            if (mysql_query(this->m_conn, cstr))
            {
                cout << "����ʧ��" << endl;
                return;
            }
            else
            {
                cout << "���³ɹ�" << endl;
            }
            break;
        }
        }
    }
    else
    {
        cout << "���޴���" << endl;
        return;
    }
}
//�鿴ѧ����Ϣ
void Manager::searchStu()
{
    cout << "ѡ����Ҫ���ҵķ�ʽ:" << endl;
    cout << "1 ѧ��id" << endl;
    cout << "2 ѧ������" << endl;
    int op;
    cin >> op;
    char cstr[1000];
    switch (op)
    {
    case 1:
    {
        // ����id���в���
        int id;
        cout << "������id��:" << endl;
        cin >> id;
        // ͨ�����ݿ���в���
        sprintf_s(cstr, sizeof(cstr),  "select * from student where id = %d", id);
        if (mysql_query(this->m_conn, cstr))
        {
            cout << "���޴���" << endl;
        }
        else
        {
            this->res = mysql_store_result(this->m_conn);
            int findNum = mysql_num_rows(this->res);
            if (findNum == 0)
            {
                cout << "���޴���" << endl;
            }
            if (res)
            {
                while (this->row = mysql_fetch_row(res))
                {
                    printf("id:%4s\t����:%5s\t����:%4s\t��ѧ:%4s\tӢ��:%4s\t�ܷ�:%4s\n", 
                        row[0], row[1], row[2], row[3], row[4], row[5]);
                }
            }
            else
            {
                cout << "���޴���" << endl;
            }
        }
        break;
    }
    case 2:
    {
        // �����������в���
        string name;
        cout << "������ѧ������:" << endl;
        cin >> name;
        // ͨ�����ݿ���в���
        sprintf_s(cstr, sizeof(cstr), "select * from student where name = '%s'", name.c_str());
        if (mysql_query(this->m_conn, cstr))
        {
            cout << "���޴���" << endl;
        }
        else
        {
            this->res = mysql_store_result(this->m_conn);
            int findNum = mysql_num_rows(this->res);
            if (findNum == 0)
            {
                cout << "���޴���" << endl;
            }
            if (res)
            {
                while (this->row = mysql_fetch_row(res))
                {
                    printf("id:%4s\t����:%5s\t����:%4s\t��ѧ:%4s\tӢ��:%4s\t�ܷ�:%4s\n",
                        row[0], row[1], row[2], row[3], row[4], row[5]);
                }
            }
            else
            {
                cout << "���޴���" << endl;
            }
        }
        break;
    }
    default:
    {
        cout << "������������" << endl;
        break;
    }
    }
}
// ɾ��ѧ����Ϣ
void Manager::moveStu()
{
    if (this->is_empty)
    {
        cout << "ѧ����Ϊ��" << endl;
        return;
    }
    int id;
    cout << "������id��" << endl;
    cin >> id;
    int index = this->findStu(id);
    if (index != -1)
    {
        char cstr[1000];
        sprintf_s(cstr, "delete from student where id = %d", id);
        if (mysql_query(this->m_conn, cstr))
        {
            cout << "ɾ��ʧ��" << endl;
        }
        else
        {
            // ɾ��vstr�е�
            for (int i = index; i < this->m_stuNum - 1; i++)
            {
                this->v_stu[i] = this->v_stu[i + 1];
            }
            this->v_stu.pop_back();
            this->m_stuNum--;
            if (this->m_stuNum == 0)
            {
                this->is_empty = true;
            }
            cout << "ɾ���ɹ�" << endl;
        }
    }
    else
    {
        cout << "���޴��ˣ�ɾ��ʧ��" << endl;
    }
}
// ���ѧ����Ϣ
void Manager::clearStu()
{
    cout << "���������ѧ����Ϣ����ȷ���Ƿ�ִ��" << endl;
    cout << "1 ȷ��" << endl;
    cout << "2 ����" << endl;
    int op;
    cin >> op;
    switch (op)
    {
    case 1:
    {
        if (mysql_query(this->m_conn, "delete from student"))
        {
            cout << "���ʧ��" << endl;
        }
        else
        {
            // ���vstu
            while (this->m_stuNum > 0)
            {
                this->v_stu.pop_back();
                this->m_stuNum--;
            }
            this->is_empty = true;
            cout << "��ճɹ�" << endl;
        }
        break;
    }
    default:
    {
        cout << "ȡ�����" << endl;
        return;
    }
    }
}
// �˳�ϵͳ
void Manager::exitSys()
{
    cout << "��ӭ�´�ʹ��" << endl;
    system("pause");
    system("cls");
    exit(0);
}

// ��ʾѧ����Ϣ
void Manager::showStu()
{
    if (this->is_empty)
    {
        cout << "ѧ����Ϊ��" << endl;
    }
    for (int i = 0; i < this->m_stuNum; i++)
    {
        this->v_stu[i].printStu();
    }
}