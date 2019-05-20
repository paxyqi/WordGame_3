#include "student.h"

#define WORD_NO 100


student::student()
{
}
void student::GameTime(string nm)
{
	this->name = nm;
	char continue_the_game;
	cout << "Are you ready?(Y/N)" << endl;
	cin >> continue_the_game;
	int choose = 0;
	int rankIn = 1;//rank值由1升至5，代表难度由低到高
	int rank_need_pass[5] = { 1,2,3,4,5 };//为闯过第n关需要答对的单词数目
	int Rank;
	int flag = 1;//该关为通过状态
	int p = 0;//计数器
	string Word;
	string word[WORD_NO];
	ifstream readWF("WordStore.txt");
	while (continue_the_game == 'Y' || continue_the_game == 'y')
	{
		cout << "			         This is the " << rankIn << " rank." << endl;
		flag = 1;
		while(readWF.peek() != EOF)//当文件没有读到eof时
		{
			readWF >> Rank >> Word;
			if (Rank == rankIn)//符合想要的单词等级
			{
				word[p++] = Word;
			}
		}
		for (int i = 0 ; ( i < rank_need_pass[rankIn]) && (continue_the_game == 'Y') ;  i++)
		{
			srand((unsigned)time(NULL));
			choose = rand() % p;
			cout << word[choose];
			Sleep(500);
			system("cls");
			string answer;
			cout << "the word is:" << endl;
			cin >> answer;
			if (word[choose].compare(answer) == 0)
			{
				this->Mark_Change(rankIn);
				//cout << "Congratulation! Ready to next word?(Y/N)" << endl;
				//cin >> continue_the_game;
			}
			else
			{
				flag = 0;
				cout << "				Wrong answer! Ready to try again?(Y/N)：" << endl;
				cin >> continue_the_game;
				i = 0;//若有一次失败，则为闯关需要重新开始
			}
		}
		if (flag == 1)
		{
			cout << "				Congratulations! You had pass the " << rankIn << " level!" << endl;
			cout << "				Ready to next level?(Y/N): " << endl;
			cin >> continue_the_game;
		}
		if (continue_the_game == 'Y' || continue_the_game == 'y')
		{
			readWF.clear();
			readWF.seekg(0, ios::beg);
		}
		rankIn++;
		p = 0;
	}
	readWF.close();
}

student::~student()
{
}
