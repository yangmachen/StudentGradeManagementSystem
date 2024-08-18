#pragma once
#include <string>
#include <mysql.h>
#include <vector>
#include <tchar.h>
#include <Windows.h>
#include "student.h"

using namespace std;

class Manager
{
public:
	// 数据库连接
	MYSQL *m_conn;
	// 数据库结果接受
	MYSQL_RES *res;
	// 数据库一行接受
	MYSQL_ROW row;
	// 学生数量
	int m_stuNum;
	// 学生容器
	vector<Student> v_stu;
	// 是否存在学生
	bool is_empty;
	// 数据库连接是否成功
	bool is_conn;


	// 构造函数
	Manager();
	// 析构函数
	~Manager();
	// 显示界面
	void showMenu();
	// 添加学生信息
	void addStu();
	// 修改学生信息
	void alterStu();
	// 查找学生是否存在(返回下标)
	int findStu(int id);
	//查看学生信息
	void searchStu();
	// 删除学生信息
	void moveStu();
	// 清空学生信息
	void clearStu();
	// 退出系统
	void exitSys();
	// 显示学生信息
	void showStu();
};