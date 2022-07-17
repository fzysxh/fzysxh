#include <iostream>
#include <string>
using namespace std;
#define 男 1
#define 女 2
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
	cout << "*****1、添加联系人*****" << endl;
	cout << "*****2、显示联系人*****" << endl;
	cout << "*****3、删除联系人*****" << endl;
	cout << "*****4、查找联系人*****" << endl;
	cout << "*****5、修改联系人*****" << endl;
	cout << "*****6、清空联系人*****" << endl;
	cout << "*****0、退出通讯录*****" << endl;
	cout << "***********************" << endl;
}
void add_love(book *adr)
{
	int temp;
	if (adr->size < 1000)
	{
		cout << "请输入姓名" << endl;
		cin >> adr->love[adr->size].name;

		cout << "请输入性别" << endl << "1为男性，2为女性"<<endl; 
		while (1)
		{
			cin >> temp;
			if (temp == 1 || temp == 2)
			{
				adr->love[adr->size].sex = temp;
				break;
			}
			else cout << "本程序不支持第三性别" << endl;
		}

		cout << "请输入电话号码" << endl;
		cin >> adr->love[adr->size].phone;

		cout << "请输入地址" << endl;
		cin >> adr->love[adr->size].address;
		adr->size ++;
		system("cls");
		menu();
		cout << "添加成功!" << endl;
	}
	else cout << "这里满员了" << endl;
}
void show_love(book const* adr)
{
	uint8_t i;
	for (i = 0; i < adr->size; i++)
	{
		cout << "姓名:" << adr->love[i].name << "\t\t";
		cout << "性别:" << (adr->love[i].sex == 1 ? "男性":"女性") << "\t\t";
		cout << "电话号码:" << adr->love[i].phone << "\t\t";
		cout << "地址:" << adr->love[i].address << endl;
	}
}
uint8_t find_love(book const* adr,string name,int * del)
{
	uint8_t temp=0;
	for (uint8_t i = 0; i < adr->size; i++)
	{
		if (adr->love[i].name == name)
		{
			cout << "姓名:" << adr->love[i].name << "\t\t";
			cout << "性别:" << (adr->love[i].sex == 1 ? "男性" : "女性") << "\t\t";
			cout << "电话号码:" << adr->love[i].phone << "\t\t";
			cout << "地址:" << adr->love[i].address << endl;
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
	cout << "请输入姓名" << endl;
	cin >> adr->love[del].name;

	cout << "请输入性别" << endl << "1为男性，2为女性" << endl;
	while (1)
	{
		int temp;
		cin >> temp;
		if (temp == 1 || temp == 2)
		{
			adr->love[del].sex = temp;
			break;
		}
		else cout << "本程序不支持第三性别" << endl;
	}

	cout << "请输入电话号码" << endl;
	cin >> adr->love[del].phone;

	cout << "请输入地址" << endl;
	cin >> adr->love[del].address;
	cout << "修改成功" << endl;
}
void clear_love(book* adr)
{
	int temp;
	cout << "确定清空联系人？输入1确定，2取消" << endl;
	cin >> temp;
	if (temp == 1)
	{
		adr->size = 0;
		cout << "已清空"<<endl;
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
				cout << "欢迎下次使用，大概吧" << endl;
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
				cout << "请输入姓名" << endl;
				cin >> name;
				uint8_t re = find_love(&My_book, name,del);
				if (re == -1)
				{
					cout << "查无此人" << endl;
				}
			    if (re == 0)
				{
					delete_love(&My_book, del[0]);
					cout << "删除成功" << endl;
				}
			    if (re == 1)
				{
					cout << "要删除第几位" << name << "?"<<endl;
					cin >> j;
					delete_love(&My_book,del[j-1]);
					cout << "删除成功" << endl;
				}
				system("pause");
				system("cls");
				menu();
				break; 
			}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
			case 4:
			{
				string name;
				cout << "请输入姓名" << endl;
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
				cout << "请输入姓名" << endl;
				cin >> name;
				uint8_t re = find_love(&My_book, name, del);
				if (re == -1)
				{
					cout << "查无此人" << endl;
				}
				if (re == 0)
				{
					change_love(&My_book, del[0]);
				}
				if (re == 1)
				{
					cout << "要修改第几位" << name << "?" << endl;
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
