#include "load.h"
#include "user.h"
#include <conio.h>
load::load(char ch)
{
	user User = user();
	if (ch == 'Y'||ch=='y')//已有帐户，1、需要确认是否存在该用户，若没有直接报错；2、确认密码是否吻合，若错误直接报错
	{
		string Name, Password;
		char password[15] = "";
		char ch;
		int index;
		cout << "please input your name:" << endl;
		cin >> Name;
		cout << "please input your password:" << endl;
		index = 0;
		while ((ch = _getch())!= '\r') 
		{
			if (ch != '\b')
			{
				password[index++] = ch;
				cout << "*";
			}
			else
			{
				index--;
				cout << '\b'  << ' '<< '\b';
			}
		}
		password[index] = '\0';
		cout << endl;
		Password = password;
		int flag = User.Land_Check(Name, Password);
		while (flag != 1)
		{
			if (flag == -1)
			{
				cin >> Name >> Password;
				flag = User.LogIn_Check(Name, Password);
				while (flag == 0)
				{
					cin >> Name >> Password;
					flag = User.LogIn_Check(Name, Password);
				}
				User.LogIn_Write(Name, Password);
				Role = User.role;
				this->Name = User.name;
				break;
			}
			index = 0;
			while ((ch = _getch()) != '\r')
			{
				if (ch != '\b')
				{
					password[index++] = ch;
					cout << "*";
				}
				else
				{
					index--;
					cout << '\b' << ' ' << '\b';
				}
			}
			password[index] = '\0';
			cout << endl;
			Password = password;
			flag = User.Land_Check(Name, Password);
		}
		Role = User.role;
		this->Name = User.name;
	}
	else if (ch == 'N' || ch=='n')
	{
		cout << "please input your name and password:" << endl;
		cout << "ATTENTION:" << endl;
		cout << "the name length need to less than 10 char, more than 3 char." << endl;
		cout << "please input your name:" << endl;
		cout << "the password length need to less than 15 char, more than 6 char." << endl;
		cout << "Both name and password is made by letter(a-z,A-Z) and digital(0-9)." << endl;
		string Name, Password;
		cin >> Name >> Password;//新用户的Name和Password均用string形式读入，为判别是否符合规定
		int flag = User.LogIn_Check(Name, Password);
		while (flag == 0)
		{
			cin >> Name >> Password;
			flag = User.LogIn_Check(Name, Password);
		}
		User.LogIn_Write(Name, Password);
		Role = User.role;
		this->Name = User.name;
	}
	else
		cout << "you only can type Y or N";
}


load::~load()
{
}
