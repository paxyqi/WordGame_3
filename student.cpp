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
	int rankIn = 1;//rankֵ��1����5�������Ѷ��ɵ͵���
	int rank_need_pass[5] = { 1,2,3,4,5 };//Ϊ������n����Ҫ��Եĵ�����Ŀ
	int Rank;
	int flag = 1;//�ù�Ϊͨ��״̬
	int p = 0;//������
	string Word;
	string word[WORD_NO];
	ifstream readWF("WordStore.txt");
	while (continue_the_game == 'Y' || continue_the_game == 'y')
	{
		cout << "			         This is the " << rankIn << " rank." << endl;
		flag = 1;
		while(readWF.peek() != EOF)//���ļ�û�ж���eofʱ
		{
			readWF >> Rank >> Word;
			if (Rank == rankIn)//������Ҫ�ĵ��ʵȼ�
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
				cout << "				Wrong answer! Ready to try again?(Y/N)��" << endl;
				cin >> continue_the_game;
				i = 0;//����һ��ʧ�ܣ���Ϊ������Ҫ���¿�ʼ
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
