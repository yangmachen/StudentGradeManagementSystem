#include "student.h"

Student::Student(int id, string name, int chi, int math, int eng)
{
	this->m_id = id;
	this->m_name = name;
	this->m_chi = chi;
	this->m_math = math;
	this->m_eng = eng;

	this->cal_total();

}	


void Student::cal_total()
{
	this->m_total = this->m_chi + this->m_math + this->m_eng;
}

void Student::printStu()
{
	/*
	cout << "id:" << this->m_id << "\t姓名:" << this->m_name << "\t语文:" <<
		this->m_chi << "\t数学:" << this->m_math << "\t英语:" << this->m_eng << "\t总分:" << this->m_total << endl;
	*/
	printf("id:%4d\t姓名:%5s\t语文:%4d\t数学:%4d\t英语:%4d\t总分:%4d\n", this->m_id, this->m_name.c_str(), this->m_chi, this->m_math, this->m_eng, this->m_total);
}
