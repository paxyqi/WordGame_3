#include "user.h"
#define MAX_REGISTER_NUMBER 200


user::user()
{
}
int user::LogIn_Check(string nm, string pw)//返回0为失败，返回1为成功
{
	bool accept_nm = 1;
	bool accept_pw = 1;
	
	if ((pw.length() < 6) || (pw.length() > 15)) accept_pw = 0;//判断该密码能否被接受
	for (string::size_type i = 0; i < pw.length(); i++)
	{
		if (!(isalpha(pw[i]) || isalnum(pw[i])))
			accept_pw = 0;
	}
	if (accept_pw == 0)
	{
		cout << "your password is too long or too short. Attention: you only can use digital or letter" << endl;
		return 0;
	}
	if ((nm.length()< 3) || (pw.length() > 10)) accept_nm = 0;//判断该注册名能否被接受
	for (string::size_type i = 0; i < nm.length(); i++)
	{
		if (!(isalpha(nm[i]) || isalnum(nm[i])))
			accept_nm = 0;
	}
	if (accept_nm == 0)
	{
		cout << "your name is too long or too short. Attention: you only can use digital or letter" << endl;
		return 0;
	}
	ifstream readRF("RegisterStore.txt");
	if (readRF.peek() == EOF)
	{
		cout << "you are the first register " << endl;
	}
	while (!readRF.eof())
	{
		string name, password;
		bool Role;
		int Rank;
		int Exp;
		while (accept_nm == 1 && (readRF.eof()==0))//eof为0时文件不到结束，accnm为1时改名尚可接受
		{
			readRF >> name >> password >> Role >> Rank >> Exp;
			if (name.compare(nm) == 0)//该名字已被注册
			{
				accept_nm = 0;
				cout << "this name has been used, plaese choose another one." << endl;
				//如果名字或者密码不被接受，则返回主函数，由主函数重新调度，直到被接受为止
			}
		}
	}
	readRF.close();
	if (accept_nm && accept_pw == 1)
	{
		return 1;
	}


}
void user::LogIn_Write(string nm, string pw)
{
	ofstream writeRF;
	writeRF.open("RegisterStore.txt", ios::app);
	cout << "please choose your role:teacher(0), student(1):" << endl;
	bool R;
	cin >> R;
	this->role = R;
	this->name = nm;
	writeRF << '\n' << nm << "            " << pw << "                  " << R << "                  0" << "                   0";
	writeRF.close();
	cout << "regist sucessfully!" << endl;
}
int user::Land_Check(string nm, string pw)//返回1为登陆成功，返回0为登陆失败
{
	bool had_nm = false;//暂未找到该用户
	bool right_pw = false;//该用户所对应的密码正确
	ifstream readRF("RegisterStore.txt");
	while (!readRF.eof())
	{
		string name;
		string password;
		bool Role;
		int Rank;
		int Exp;
		while (had_nm == 0 && readRF.eof() == 0)//eof为0时文件不到结束，had_nm=0即尚未找到对应名字
		{
			readRF >> name >> password >> Role >> Rank >> Exp;
			if (name.compare(nm) == 0)//该名字已被注册
			{
				had_nm = 1;
			//名字检验成功开始对照密码
				if (password.compare(pw)==0)//密码正确
				{
					right_pw = 1;
					this->role = Role;
					this->name = name;
					cout << endl;
					cout << "                         WELCOME!" << endl;
					return 1;
				}
				else
				{
					cout << "your password is wrong, please try it again!" << endl;
					return 0;
				}
			}
		}
	}
	if (had_nm == 0)
	{
		cout << "you had not regist, please regist first" << endl;
		return -1;
	}
	readRF.close();
}
void user::Mark_Change(int score)
{
	bool find_nm = false;//暂未找到该用户
	string Name, Password;
	string line;
	bool Role;
	int Rank, Exp;//以上为当前用户信息
	int New_rank, New_Exp;//为增加分数后的信息，name等其他信息不变
	ifstream readRF;//同时实现read和write
	readRF.open("RegisterStore.txt");
	ofstream temp;
	temp.open("temp.txt");
	while (readRF >> Name >> Password >> Role >> Rank >> Exp)//eof为0时文件不到结束readRF.peek()!=EOF
	{
		if (Name == this->name)
		{
			New_Exp = Exp + score;
			New_rank = New_Exp / 10;
		}
		else
		{
			New_Exp = Exp;
			New_rank = Rank;
		}
		temp << Name << "             " << Password << "                 " << Role << "                    " << New_rank << "               " << New_Exp << endl;
	}
	temp.close();
	readRF.close();
	remove("RegisterStore.txt");
	rename("temp.txt", "RegisterStore.txt");
}
void user::Ranking(bool role, char way)
{
	ifstream readRF;
	readRF.open("RegisterStore.txt");
	string Temp_Name[MAX_REGISTER_NUMBER];
	int Temp_Data[MAX_REGISTER_NUMBER] = { -1 };
	string name;
	string password;
	bool Role;
	int Rank;
	int Exp;
	int index = 0;
	while (readRF.eof() == 0)//eof为0时文件不到结束，had_nm=0即尚未找到对应名字
	{
		readRF >> name >> password >> Role >> Rank >> Exp;
		if (Role == role)
		{
			if (way == 'R'|| way == 'r')//按等级排序
			{
				Temp_Name[index] = name;
				Temp_Data[index] = Rank;
				index++;
			}
			else if (way == 'E'|| way == 'e')
			{
				Temp_Name[index] = name;
				Temp_Data[index] = Exp;
				index++;
			}
		}
	}
	for (int i = 0; i < (index-1); i++)
	{
		for (int j = 0; j < (index - 1); j++)
		{
			if (Temp_Data[j] > Temp_Data[j + 1])
			{
				int curr_Data;
				string curr_Name;
				curr_Data = Temp_Data[j];
				curr_Name = Temp_Name[j];
				Temp_Data[j] = Temp_Data[j + 1];
				Temp_Name[j] = Temp_Name[j + 1];
				Temp_Data[j + 1] = curr_Data;
				Temp_Name[j + 1] = curr_Name;
			}
		}
	}
	cout << "The rank is:" << endl;
	for (int i = 0; i < index; i++)
	{
		cout << Temp_Name[i] << "      " << Temp_Data[i] << endl;
	}
	readRF.close();

}
user::~user()
{
}
