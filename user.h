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
	string name;//名字由英文字母组成，大于3个字符不能超过10个字符，区分大小写
	string password;//密码要求由英文，数字组成，必须大于6位小于15位 注意，输入后进行加密password+=ch*ch;每个ch均为int
	/*******************************************
	registerStore 格式
	           Name              PassWord             role       rank           exp
	          pixy               h19981229              0         3              30
	           gao               78900011               1         5             50
	********************************************/
	/********************************************
	wordStore 格式
	           Rank（难度等级）                Word  
			   1                                apple
			   2                                amazing
			   4                                beautiful
	*********************************************/
	bool role;//用户角色，1为闯关者（student），0为出题者（teacher）
	user() ;
	int LogIn_Check(string nm, string pw);//返回0为失败，返回1为成功
	void LogIn_Write(string nm, string pw);
	int Land_Check(string nm, string pw);
	void Mark_Change(int score);
	void Ranking(bool role, char way);
	~user() ;
};

