// WordGame.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "user.h"
#include "load.h"
#include "student.h"
#include "teacher.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	char haveAccount;//是否已经注册过帐户
	cout << "                          WELCOME TO THE GAME" << endl;
	cout << "Do you have account? (Y/N):";
	cin >> haveAccount;
	load NewLoad = load(haveAccount);
	cout << "Do you want to play the game or check the ranking? (G/R):" << endl;
	char function;
	cin >> function;
	if (function == 'G' || function == 'g')
	{
		if (NewLoad.Role == true)//role为1是学生
		{
			student Student = student();
			Student.GameTime(NewLoad.Name);
		}
		if (NewLoad.Role == false)
		{
			teacher Teacher = teacher();
			Teacher.AddWord(NewLoad.Name);
		}

	}
	else if (function == 'R' || function == 'r')
	{
		bool R;
		char W;
		cout << "the role you want to see: (0/1) (1 for student, 0 for teacher)" << endl;
		cin >> R;
		cout << "the way of ranking: (R/E) (R for rank, E for experience)" << endl;
		cin >> W;
		user Rank = user();
		Rank.Ranking(R, W);
	}
	
	cout << "Have a good day!" << endl;
	return 0;
	
}
