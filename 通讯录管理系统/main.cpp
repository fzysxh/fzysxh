#include <iostream>
#include <string>
using namespace std;
#define �� 1
#define Ů 2
#define MAX 100
struct person
{
	string name;
	int sex;
	string phone;
	string address;
};
struct book
{
	struct person love[MAX];
	uint16_t size;
};
void menu()
{
	cout << "***********************" << endl;
	cout << "*****1�������ϵ��*****" << endl;
	cout << "*****2����ʾ��ϵ��*****" << endl;
	cout << "*****3��ɾ����ϵ��*****" << endl;
	cout << "*****4��������ϵ��*****" << endl;
	cout << "*****5���޸���ϵ��*****" << endl;
	cout << "*****6�������ϵ��*****" << endl;
	cout << "*****0���˳�ͨѶ¼*****" << endl;
	cout << "***********************" << endl;
}
void add_love(book *adr)
{
	int temp;
	if (adr->size < 1000)
	{
		cout << "����������" << endl;
		cin >> adr->love[adr->size].name;

		cout << "�������Ա�" << endl << "1Ϊ���ԣ�2ΪŮ��"<<endl;
		while (1)
		{
			cin >> temp;
			if (temp == 1 || temp == 2)
			{
				adr->love[adr->size].sex = temp;
				break;
			}
			else cout << "������֧�ֵ����Ա�" << endl;
		}

		cout << "������绰����" << endl;
		cin >> adr->love[adr->size].phone;

		cout << "�������ַ" << endl;
		cin >> adr->love[adr->size].address;
		adr->size ++;
		system("cls");
		menu();
		cout << "��ӳɹ�!" << endl;
	}
	else cout << "������Ա��" << endl;
}
void show_love(book const* adr)
{
	uint8_t i;
	for (i = 0; i < adr->size; i++)
	{
		cout << "����:" << adr->love[i].name << "\t\t";
		cout << "�Ա�:" << (adr->love[i].sex == 1 ? "����":"Ů��") << "\t\t";
		cout << "�绰����:" << adr->love[i].phone << "\t\t";
		cout << "��ַ:" << adr->love[i].address << endl;
	}
}
uint8_t find_love(book const* adr,string name,int * del)
{
	uint8_t temp=0;
	for (uint8_t i = 0; i < adr->size; i++)
	{
		if (adr->love[i].name == name)
		{
			cout << "����:" << adr->love[i].name << "\t\t";
			cout << "�Ա�:" << (adr->love[i].sex == 1 ? "����" : "Ů��") << "\t\t";
			cout << "�绰����:" << adr->love[i].phone << "\t\t";
			cout << "��ַ:" << adr->love[i].address << endl;
			del[temp] = i;
			temp++;
		}
	}
	if (temp == 0)
	{
		return -1;
	}
	if (temp == 1)
	{
		return 0;
	}
	if(temp>1)
	{
		return 1;
	}
	return 2;
}
void delete_love(book *adr,uint16_t i)
{
	adr->love[i].name=adr->love[adr->size-1].name;
	adr->love[i].address = adr->love[adr->size-1].address;
	adr->love[i].sex= adr->love[adr->size-1].sex;
	adr->love[i].phone = adr->love[adr->size-1].phone;
	adr->size--;
}
void change_love(book* adr,int  del)
{
	cout << "����������" << endl;
	cin >> adr->love[del].name;

	cout << "�������Ա�" << endl << "1Ϊ���ԣ�2ΪŮ��" << endl;
	while (1)
	{
		int temp;
		cin >> temp;
		if (temp == 1 || temp == 2)
		{
			adr->love[del].sex = temp;
			break;
		}
		else cout << "������֧�ֵ����Ա�" << endl;
	}

	cout << "������绰����" << endl;
	cin >> adr->love[del].phone;

	cout << "�������ַ" << endl;
	cin >> adr->love[del].address;
	cout << "�޸ĳɹ�" << endl;
}
void clear_love(book* adr)
{
	int temp;
	cout << "ȷ�������ϵ�ˣ�����1ȷ����2ȡ��" << endl;
	cin >> temp;
	if (temp == 1)
	{
		adr->size = 0;
		cout << "�����"<<endl;
	}
	else
	{
		return;
	}
	
}
int main()
{
	int select = 0,del[100];
	menu();
	struct book My_book;
	My_book.size = 0;
	while (1)
	{
		cin >> select;
		switch (select)
		{

			case 0:
			{
				cout << "��ӭ�´�ʹ�ã���Ű�" << endl;
				system("pause");
				return 0;
				break;
			}
			case 1:
			{
				add_love(&My_book);
				system("pause");
				system("cls");
				menu();
				break;
			}		
			case 2:
			{
				show_love(&My_book);
				system("pause");
				system("cls");
				menu();
				break;
			}	
			case 3:
			{
				string name;
				int j=0;
				cout << "����������" << endl;
				cin >> name;
				uint8_t re = find_love(&My_book, name,del);
				if (re == -1)
				{
					cout << "���޴���" << endl;
				}
			    if (re == 0)
				{
					delete_love(&My_book, del[0]);
					cout << "ɾ���ɹ�" << endl;
				}
			    if (re == 1)
				{
					cout << "Ҫɾ���ڼ�λ" << name << "?"<<endl;
					cin >> j;
					delete_love(&My_book,del[j-1]);
					cout << "ɾ���ɹ�" << endl;
				}
				system("pause");
				system("cls");
				menu();
				break; 
			}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
			case 4:
			{
				string name;
				cout << "����������" << endl;
				cin >> name;
				find_love(&My_book, name, del);
				system("pause");
				system("cls");
				menu();
				break;
			}
			case 5:
			{
				string name;
				int j = 0;
				cout << "����������" << endl;
				cin >> name;
				uint8_t re = find_love(&My_book, name, del);
				if (re == -1)
				{
					cout << "���޴���" << endl;
				}
				if (re == 0)
				{
					change_love(&My_book, del[0]);
				}
				if (re == 1)
				{
					cout << "Ҫ�޸ĵڼ�λ" << name << "?" << endl;
					cin >> j;
					change_love(&My_book, del[j - 1]);
				}
				system("pause");
				system("cls");
				menu();
				break;
			}
			case 6:
			{
				clear_love(&My_book);
				system("pause");
				system("cls");
				menu();
				break;
			}		
			default: system("cls");  menu();
				break;
		}
	}
	system("pause");
	return 0;
}
