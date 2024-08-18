#include "manager.h"
#include <Windows.h>




// 构造函数
Manager::Manager()
{
	// 数据库连接 MYSQL* m_conn+;m_stuNum+;v_stu+;is_empty+;
    this->is_empty = true;
	this->m_conn = mysql_init(NULL);
    mysql_options(this->m_conn, MYSQL_SET_CHARSET_NAME, "GBK");
    if (mysql_real_connect(this->m_conn, "localhost", "root", "123456", "student", 3306, NULL, 0)) {
        this->is_conn = true;
        // 显示连接成功提示
        cout << "database connect sucess!" << endl;
    }
    else
    {
        this->is_conn = false;
        cout << "error" << endl;
        return;
    }


    // 读取数据库的所有数据
    string S = "select * from student";
    if (mysql_query(this->m_conn, S.c_str()))
    {
        cout << "读取学生表数据失败" << endl;
    }
    
    // 接受数据
    res = mysql_store_result(this->m_conn);
    this->m_stuNum = 0;
    if (res)
    {
        while (row = mysql_fetch_row(res))
        {
            // 接受数据
            int id = atoi(row[0]);
            string name = row[1];
            int chi = atoi(row[2]);
            int math = atoi(row[3]);
            int eng = atoi(row[4]);
            
            // 创建学生
            Student stu(id, name, chi, math, eng);
            // 加入学生容器
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
// 析构函数
Manager::~Manager()
{
    mysql_close(this->m_conn);
}




// 显示菜单
void Manager::showMenu()
{
    cout << "******************************" << endl;
    cout << "***欢迎进入学生成绩管理系统***" << endl;
    cout << "********1 显示学生信息********" << endl;
    cout << "********2 添加学生信息********" << endl;
    cout << "********3 查找学生信息********" << endl;
    cout << "********4 修改学生信息********" << endl;
    cout << "********5 删除学生信息********" << endl;
    cout << "********6 清空学生信息********" << endl;
    cout << "********0 退出学生系统********" << endl;
    cout << "******************************" << endl;
}
// 添加学生信息
void Manager::addStu()
{
    int id;
    string name;
    int chi;
    int math;
    int eng;
    cout << "请输入id号:" << endl;
    cin >> id;
    cout << "请输入姓名:" << endl;
    cin >> name;
    cout << "请输入语文成绩:" << endl;
    cin >> chi;
    cout << "请输入数学成绩:" << endl;
    cin >> math;
    cout << "请输入英语成绩:" << endl;
    cin >> eng;
    // 创建学生
    Student stu(id, name, chi, math, eng);
    
    // 插入数据库
    char cstr[1000];
    sprintf_s(cstr, "insert into student(id, name, chinese, math, english, total) values(%d, '%s', %d, %d, %d, %d)",
        stu.m_id, stu.m_name.c_str(), stu.m_chi, stu.m_math, stu.m_eng, stu.m_total);
    if (mysql_query(this->m_conn, cstr))
    {
        cout << "插入失败" << endl;
        return;
    }
    else
    {
        cout << "添加成功" << endl;
    }
    // 插入容器
    this->v_stu.push_back(stu);
    this->m_stuNum++;
    this->is_empty = false;
}
// 查找学生是否存在(返回下标)
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
// 修改学生信息
void Manager::alterStu()
{
    cout << "请输入id号:" << endl;
    int id;
    cin >> id;
    int index = this->findStu(id);
    if (index != -1)
    {
        cout << "请输入修改的项:" << endl;
        cout << "1 id号" << endl;
        cout << "2 姓名" << endl;
        cout << "3 语文成绩" << endl;
        cout << "4 数学成绩" << endl;
        cout << "5 英语成绩" << endl;
        int op;
        cin >> op;
        char cstr[1000];
        switch (op)
        {
        case 1: // id号
        {
            int newid;
            cout << "请输入新的id:" << endl;
            cin >> newid;
            sprintf_s(cstr, "update student set id = %d where id = %d", newid, id);
            if (mysql_query(this->m_conn, cstr))
            {
                cout << "更新失败" << endl;
                return;
            }
            else
            {
                cout << "更新成功" << endl;
                // 更新vstu
                this->v_stu[index].m_id = newid;
            }
            break;
        }
        case 2: // 姓名
        {
            string newName;
            cout << "请输入新的姓名:" << endl;
            cin >> newName;
            sprintf_s(cstr, "update student set name = '%s' where id = %d", newName.c_str(), id);
            if (mysql_query(this->m_conn, cstr))
            {
                cout << "更新失败" << endl;
                return;
            }
            else
            {
                cout << "更新成功" << endl;
                // 更新vstu
                this->v_stu[index].m_name = newName;
            }
            break;
        }
        case 3: // 语文成绩
        {
            int newChi;
            cout << "请输入新的语文成绩:" << endl;
            cin >> newChi;
            // 先修改vstr
            this->v_stu[index].m_chi = newChi;
            this->v_stu[index].cal_total();
            sprintf_s(cstr, "update student set chinese = %d, total = %d where id = %d", newChi, this->v_stu[index].m_total, id);
            if (mysql_query(this->m_conn, cstr))
            {
                cout << "更新失败" << endl;
                return;
            }
            else
            {
                cout << "更新成功" << endl;
            }
            break;
        }
        case 4: // 数学成绩
        {
            int newMath;
            cout << "请输入新的数学成绩:" << endl;
            cin >> newMath;
            // 先修改vstr
            this->v_stu[index].m_math = newMath;
            this->v_stu[index].cal_total();
            sprintf_s(cstr, "update student set math = %d, total = %d where id = %d", newMath, this->v_stu[index].m_total, id);
            if (mysql_query(this->m_conn, cstr))
            {
                cout << "更新失败" << endl;
                return;
            }
            else
            {
                cout << "更新成功" << endl;
            }
            break;
        }
        case 5: // 英语成绩
        {
            int newEng;
            cout << "请输入新的英语成绩:" << endl;
            cin >> newEng;
            // 先修改vstr
            this->v_stu[index].m_eng = newEng;
            this->v_stu[index].cal_total();
            sprintf_s(cstr, "update student set english = %d, total = %d where id = %d", newEng, this->v_stu[index].m_total, id);
            if (mysql_query(this->m_conn, cstr))
            {
                cout << "更新失败" << endl;
                return;
            }
            else
            {
                cout << "更新成功" << endl;
            }
            break;
        }
        }
    }
    else
    {
        cout << "查无此人" << endl;
        return;
    }
}
//查看学生信息
void Manager::searchStu()
{
    cout << "选择你要查找的方式:" << endl;
    cout << "1 学生id" << endl;
    cout << "2 学生姓名" << endl;
    int op;
    cin >> op;
    char cstr[1000];
    switch (op)
    {
    case 1:
    {
        // 根据id进行查找
        int id;
        cout << "请输入id号:" << endl;
        cin >> id;
        // 通过数据库进行查找
        sprintf_s(cstr, sizeof(cstr),  "select * from student where id = %d", id);
        if (mysql_query(this->m_conn, cstr))
        {
            cout << "查无此人" << endl;
        }
        else
        {
            this->res = mysql_store_result(this->m_conn);
            int findNum = mysql_num_rows(this->res);
            if (findNum == 0)
            {
                cout << "查无此人" << endl;
            }
            if (res)
            {
                while (this->row = mysql_fetch_row(res))
                {
                    printf("id:%4s\t姓名:%5s\t语文:%4s\t数学:%4s\t英语:%4s\t总分:%4s\n", 
                        row[0], row[1], row[2], row[3], row[4], row[5]);
                }
            }
            else
            {
                cout << "查无此人" << endl;
            }
        }
        break;
    }
    case 2:
    {
        // 根据姓名进行查找
        string name;
        cout << "请输入学生姓名:" << endl;
        cin >> name;
        // 通过数据库进行查找
        sprintf_s(cstr, sizeof(cstr), "select * from student where name = '%s'", name.c_str());
        if (mysql_query(this->m_conn, cstr))
        {
            cout << "查无此人" << endl;
        }
        else
        {
            this->res = mysql_store_result(this->m_conn);
            int findNum = mysql_num_rows(this->res);
            if (findNum == 0)
            {
                cout << "查无此人" << endl;
            }
            if (res)
            {
                while (this->row = mysql_fetch_row(res))
                {
                    printf("id:%4s\t姓名:%5s\t语文:%4s\t数学:%4s\t英语:%4s\t总分:%4s\n",
                        row[0], row[1], row[2], row[3], row[4], row[5]);
                }
            }
            else
            {
                cout << "查无此人" << endl;
            }
        }
        break;
    }
    default:
    {
        cout << "您的输入有误" << endl;
        break;
    }
    }
}
// 删除学生信息
void Manager::moveStu()
{
    if (this->is_empty)
    {
        cout << "学生表为空" << endl;
        return;
    }
    int id;
    cout << "请输入id号" << endl;
    cin >> id;
    int index = this->findStu(id);
    if (index != -1)
    {
        char cstr[1000];
        sprintf_s(cstr, "delete from student where id = %d", id);
        if (mysql_query(this->m_conn, cstr))
        {
            cout << "删除失败" << endl;
        }
        else
        {
            // 删除vstr中的
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
            cout << "删除成功" << endl;
        }
    }
    else
    {
        cout << "查无此人，删除失败" << endl;
    }
}
// 清空学生信息
void Manager::clearStu()
{
    cout << "将清空所有学生信息，请确认是否执行" << endl;
    cout << "1 确定" << endl;
    cout << "2 返回" << endl;
    int op;
    cin >> op;
    switch (op)
    {
    case 1:
    {
        if (mysql_query(this->m_conn, "delete from student"))
        {
            cout << "清空失败" << endl;
        }
        else
        {
            // 清空vstu
            while (this->m_stuNum > 0)
            {
                this->v_stu.pop_back();
                this->m_stuNum--;
            }
            this->is_empty = true;
            cout << "清空成功" << endl;
        }
        break;
    }
    default:
    {
        cout << "取消清空" << endl;
        return;
    }
    }
}
// 退出系统
void Manager::exitSys()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    system("cls");
    exit(0);
}

// 显示学生信息
void Manager::showStu()
{
    if (this->is_empty)
    {
        cout << "学生表为空" << endl;
    }
    for (int i = 0; i < this->m_stuNum; i++)
    {
        this->v_stu[i].printStu();
    }
}