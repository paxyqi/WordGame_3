#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
using namespace std;
class user
{
public:
	int rank = 0;
	string name;//������Ӣ����ĸ��ɣ�����3���ַ����ܳ���10���ַ������ִ�Сд
	string password;//����Ҫ����Ӣ�ģ�������ɣ��������6λС��15λ ע�⣬�������м���password+=ch*ch;ÿ��ch��Ϊint
	/*******************************************
	registerStore ��ʽ
	           Name              PassWord             role       rank           exp
	          pixy               h19981229              0         3              30
	           gao               78900011               1         5             50
	********************************************/
	/********************************************
	wordStore ��ʽ
	           Rank���Ѷȵȼ���                Word  
			   1                                apple
			   2                                amazing
			   4                                beautiful
	*********************************************/
	bool role;//�û���ɫ��1Ϊ�����ߣ�student����0Ϊ�����ߣ�teacher��
	user() ;
	int LogIn_Check(string nm, string pw);//����0Ϊʧ�ܣ�����1Ϊ�ɹ�
	void LogIn_Write(string nm, string pw);
	int Land_Check(string nm, string pw);
	void Mark_Change(int score);
	void Ranking(bool role, char way);
	~user() ;
};

