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
	// ���ݿ�����
	MYSQL *m_conn;
	// ���ݿ�������
	MYSQL_RES *res;
	// ���ݿ�һ�н���
	MYSQL_ROW row;
	// ѧ������
	int m_stuNum;
	// ѧ������
	vector<Student> v_stu;
	// �Ƿ����ѧ��
	bool is_empty;
	// ���ݿ������Ƿ�ɹ�
	bool is_conn;


	// ���캯��
	Manager();
	// ��������
	~Manager();
	// ��ʾ����
	void showMenu();
	// ���ѧ����Ϣ
	void addStu();
	// �޸�ѧ����Ϣ
	void alterStu();
	// ����ѧ���Ƿ����(�����±�)
	int findStu(int id);
	//�鿴ѧ����Ϣ
	void searchStu();
	// ɾ��ѧ����Ϣ
	void moveStu();
	// ���ѧ����Ϣ
	void clearStu();
	// �˳�ϵͳ
	void exitSys();
	// ��ʾѧ����Ϣ
	void showStu();
};