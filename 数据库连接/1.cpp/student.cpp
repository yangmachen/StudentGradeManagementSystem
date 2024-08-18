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
	cout << "id:" << this->m_id << "\t����:" << this->m_name << "\t����:" <<
		this->m_chi << "\t��ѧ:" << this->m_math << "\tӢ��:" << this->m_eng << "\t�ܷ�:" << this->m_total << endl;
	*/
	printf("id:%4d\t����:%5s\t����:%4d\t��ѧ:%4d\tӢ��:%4d\t�ܷ�:%4d\n", this->m_id, this->m_name.c_str(), this->m_chi, this->m_math, this->m_eng, this->m_total);
}
