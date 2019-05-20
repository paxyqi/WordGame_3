#include "user.h"
#define MAX_REGISTER_NUMBER 200


user::user()
{
}
int user::LogIn_Check(string nm, string pw)//����0Ϊʧ�ܣ�����1Ϊ�ɹ�
{
	bool accept_nm = 1;
	bool accept_pw = 1;
	
	if ((pw.length() < 6) || (pw.length() > 15)) accept_pw = 0;//�жϸ������ܷ񱻽���
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
	if ((nm.length()< 3) || (pw.length() > 10)) accept_nm = 0;//�жϸ�ע�����ܷ񱻽���
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
		while (accept_nm == 1 && (readRF.eof()==0))//eofΪ0ʱ�ļ�����������accnmΪ1ʱ�����пɽ���
		{
			readRF >> name >> password >> Role >> Rank >> Exp;
			if (name.compare(nm) == 0)//�������ѱ�ע��
			{
				accept_nm = 0;
				cout << "this name has been used, plaese choose another one." << endl;
				//������ֻ������벻�����ܣ��򷵻��������������������µ��ȣ�ֱ��������Ϊֹ
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
int user::Land_Check(string nm, string pw)//����1Ϊ��½�ɹ�������0Ϊ��½ʧ��
{
	bool had_nm = false;//��δ�ҵ����û�
	bool right_pw = false;//���û�����Ӧ��������ȷ
	ifstream readRF("RegisterStore.txt");
	while (!readRF.eof())
	{
		string name;
		string password;
		bool Role;
		int Rank;
		int Exp;
		while (had_nm == 0 && readRF.eof() == 0)//eofΪ0ʱ�ļ�����������had_nm=0����δ�ҵ���Ӧ����
		{
			readRF >> name >> password >> Role >> Rank >> Exp;
			if (name.compare(nm) == 0)//�������ѱ�ע��
			{
				had_nm = 1;
			//���ּ���ɹ���ʼ��������
				if (password.compare(pw)==0)//������ȷ
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
	bool find_nm = false;//��δ�ҵ����û�
	string Name, Password;
	string line;
	bool Role;
	int Rank, Exp;//����Ϊ��ǰ�û���Ϣ
	int New_rank, New_Exp;//Ϊ���ӷ��������Ϣ��name��������Ϣ����
	ifstream readRF;//ͬʱʵ��read��write
	readRF.open("RegisterStore.txt");
	ofstream temp;
	temp.open("temp.txt");
	while (readRF >> Name >> Password >> Role >> Rank >> Exp)//eofΪ0ʱ�ļ���������readRF.peek()!=EOF
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
	while (readRF.eof() == 0)//eofΪ0ʱ�ļ�����������had_nm=0����δ�ҵ���Ӧ����
	{
		readRF >> name >> password >> Role >> Rank >> Exp;
		if (Role == role)
		{
			if (way == 'R'|| way == 'r')//���ȼ�����
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
