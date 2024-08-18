#pragma once
#include <iostream>
#include <string>

using namespace std;

class Student
{
public:
	int m_id;
	string m_name;
	int m_chi;
	int m_math;
	int m_eng;
	int m_total;

	// 构造函数
	Student(int id, string name, int chi ,int math, int eng);
	// 计算总分
	void cal_total();
	// 打印信息
	void printStu();
};