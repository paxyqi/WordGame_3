#include "teacher.h"



teacher::teacher()
{
}
void teacher::AddWord(string nm)
{
	char stillAdd = 'Y';
	ofstream addWordFile;
	addWordFile.open("WordStore.txt", ios::app);
	ifstream checkFile;
	checkFile.open("WordStore.txt");
	this->name = nm;
	char addWord;
	string R_had, W_had;
	while (stillAdd == 'Y' || stillAdd == 'y')
	{
		cout << "Please add word:(rank              new word)" << endl;
		int New_rank;
		string New_word;
		cin >> New_rank >> New_word;
		//���õ����Ƿ��ظ�����
		while (checkFile.peek()!=EOF)
		{
			checkFile >> R_had >> W_had;
			if (W_had == New_word)
			{
				cout << "This word is exist, please add another one." << endl;
				cout << "Please add word:(rank              new word)" << endl;
				cin >> New_rank >> New_word;
				checkFile.clear();
				checkFile.seekg(0, ios::beg);
			}
		}
		addWordFile << New_rank << "		" << New_word << endl;
		/*����wordstore ����Ķ�Ӧ��Rstore*/
		this->Mark_Change(New_rank);
		cout << "Continue to add word? (Y/N): ";
		cin >> stillAdd;
	}

	addWordFile.close();
	checkFile.close();
}
teacher::~teacher()
{
}
