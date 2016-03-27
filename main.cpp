#include<iostream>
#include<stdio.h>
#include<cstring>
#pragma warning(disable:4996)
using namespace std;


//数据结构
struct station
{
	char place[10];         //每站的名称
	int tickets;
	station *next;
};

struct Node
{
	char number[10];     //班次号
	int ticket;					 //余票数
	station *head;			 //经过的所有站
};


//全局变量
int tip = 0;                    //班次的数量


//函数声明
extern void welcome();
extern Node *leading_in();
extern station *input(station *head, char temp[10]);
extern void function1(Node *classes);
extern void function2(Node *classes);
extern void function3(Node *classes);
extern void function4(Node *classes);
extern Node *change(Node *classes);
extern Node *delete_it(Node *classes);
extern void search_number(Node *classes);
extern void search_station(Node *classes);
extern void sell_ticket(Node *classes);


//建立车站链表
station *input(station *head, char *temp)
{
	station *p = new station;
	strcpy(p->place, temp);
	p->tickets = 100;
	p->next = NULL;
	if (head == NULL)
		head = p;
	else
	{
		station *q = head;
		while (q->next != NULL)
			q = q->next;
		q->next = p;
	}
	return head;
}


//将班次信息从文件导入系统
Node *leading_in(Node *classes)
{
	FILE *fpA = fopen("info.txt", "r");
	if (fpA == NULL)
	{
		cout << "打开文件失败！" << endl;
		exit(1);
	}

	int t = 0;
	while (!feof(fpA))
	{
		char str[100];
		for (int x = 0; x < 100; x++)
			str[x] = '\0';
		fscanf(fpA, "%s", str);

		//录入班次号
		int j = 0;
		for (; str[j] != ','; j++)
			classes[t].number[j] = str[j];
		classes[t].number[j] = '\0';
		j = j++;
		//录入余票数
		classes[t].ticket = 0;
		for (; str[j] != '|'; j++)
		{
			classes[t].ticket += str[j] - '0';
			classes[t].ticket *= 10;
		}
		classes[t].ticket /= 10;
		j = j++;

		//录入车站信息
		classes[t].head = NULL;
		for (; str[j] != '\0'; j++)
		{
			char temp[10] = { '\0' };
			int k = j;
			for (; str[j] != '|'; j++)
				temp[j - k] = str[j];
			classes[t].head = input(classes[t].head, temp);
		}
		station *p = classes[t].head;
		while (p->next != NULL)
			p = p->next;
		p->tickets = 0;
		t++;
	}
	tip = t;

	return classes;
}


//显示欢迎界面，链接相应功能
void welcome(Node *classes)
{
	cout << " ****************************************" << endl;
	cout << "           欢迎登录12306购票系统！" << endl;
	cout << "  --------------------------------------" << endl;
	cout << " |           1. 录入班次信息     \t|" << endl;
	cout << " |           2. 操作班次信息     \t|" << endl; 
	cout << " |           3. 查询班次信息     \t|" << endl;
	cout << " |           4. 售票与退票系统     \t|" << endl;
	cout << " |           5. 导出票务信息     \t|" << endl;
	cout << " |           6. 退出系统            \t|" << endl;
	cout << "  --------------------------------------" << endl;
	cout << endl;

	cout << "请选择你所需的功能：";
	char choice;
	cin >> choice;

	while ((choice != '1') && (choice != '2') && (choice != '3') && (choice != '4') && (choice != '5') && (choice != '6'))
	{
		cout << "输入无效！请重新输入：";
		cin >> choice;
	}
	if (choice == '1')
		function1(classes);
	else if (choice == '2')
		function2(classes);
	else if (choice == '3')
		function3(classes);
	else if (choice == '4')
		function4(classes);
	else if (choice == '5')
		cout << "此功能在开发中，请稍候......" << endl;
	else
		cout << "此功能在开发中，请稍候......" << endl;
}


//welcome功能1实现
void function1(Node *classes)
{
	system("cls");
	cout << " ****************************************" << endl;
	cout << "           欢迎登录12306购票系统！" << endl;
	cout << "  --------------------------------------" << endl;
	cout << " |           1. 录入车次信息      \t|" << endl;
	cout << " |           2. 返回主菜单         \t|" << endl;
	cout << "  --------------------------------------" << endl;
	cout << endl;

	char choice;
	cout << "请选择你所需的功能：";
	cin >> choice;
	while ((choice != '1') && (choice != '2'))
	{
		cout << "输入无效！请重新输入：";
		cin >> choice;
	}
	if (choice == '1')
	{
		leading_in(classes);
		cout << "录入信息成功！" << endl;
		system("pause");
		system("cls");
		welcome(classes);
	}
	else
	{
		system("cls");
		welcome(classes);
	}
}


//welcome功能2实现
void function2(Node *classes)
{
	system("cls");
	cout << " ****************************************" << endl;
	cout << "           欢迎登录12306购票系统！" << endl;
	cout << "  --------------------------------------" << endl;
	cout << " |           1. 添加/修改班次    \t|" << endl;
	cout << " |           2. 删除班次            \t|" << endl;
	cout << " |           3. 返回主菜单         \t|" << endl;
	cout << "  --------------------------------------" << endl;
	cout << endl;

	cout << "请选择你所需的功能：";
	char choice;
	cin >> choice;

	while ((choice != '1') && (choice != '2') && (choice != '3'))
	{
		cout << "输入无效！请重新输入：";
		cin >> choice;
	}
	while ((choice == '1') || (choice == '2'))
	{
		if ((choice == '1'))
			change(classes);
		else if (choice == '2')
			delete_it(classes);
		cout << endl;

		cout << "请选择你所需的功能：";
		cin >> choice;
		while ((choice != '1') && (choice != '2') && (choice != '3'))
		{
			cout << "输入无效！请重新输入：";
			cin >> choice;
		}
	}
	system("cls");
	welcome(classes);
}


//用户输入班次信息，若系统中无此班次，则添加；
//若有，则将原信息替换为当前信息。
Node *change(Node *classes)
{
	char str[100];
	str[0] = '\0';
	cout << "请输入班次信息：" << endl;
	cin >> str;
	int x = strlen(str);
	str[x] = '|';
	str[x + 1] = '\0';

	int i = 0;
	char temp1[10];
	temp1[0] = '\0';
	for (; str[i] != ','; i++)
		temp1[i] = str[i];
	temp1[i] = '\0';
	i++;

	int j = 0;
	for (; j < tip; j++)
	{
		if (strcmp(temp1, classes[j].number) == 0)
			break;
	}

	if (j == tip)		//原有系统中无此班次
	{
		strcpy(classes[j].number, temp1);
		tip++;
	}
	//录入余票数
	classes[j].ticket = 0;
	for (; str[i] != '|'; i++)
	{
		classes[j].ticket += str[i] - '0';
		classes[j].ticket *= 10;
	}
	classes[j].ticket /= 10;
	i++;

	//录入车站信息		
	classes[j].head = NULL;
	for (; str[i] != '\0'; i++)
	{
		char temp[10] = { '\0' };
		int k = i;
		for (; str[i] != '|'; i++)
			temp[i - k] = str[i];
		classes[j].head = input(classes[j].head, temp);
	}
	cout << "添加成功！" << endl;
	return classes;
}

//用户输入班次号，在系统中搜索此班次并删除。
Node *delete_it(Node *classes)
{
	cout << "请输入班次号：";
	char temp[10];
	cin >> temp;

	int i = 0;
	for (; i < tip; i++)
	{
		if (strcmp(classes[i].number, temp) == 0)
			break;
	}
	
	if (i == tip)
		cout << "不存在此班次列车！" << endl;
	else
	{
		if (i == tip - 1)
			tip--;
		if (i < tip - 1)
		{
			for (int j = i; j < tip - 1; j++)
				classes[j] = classes[j + 1];
			tip--;
		}
		cout << "删除成功！" << endl;
	}
	return classes;
}


//welcome功能3实现
void function3(Node *classes)
{
	system("cls");
	cout << " ****************************************" << endl;
	cout << "           欢迎登录12306购票系统！" << endl;
	cout << "  --------------------------------------" << endl;
	cout << " |           1. 按班次查询      \t|" << endl;
	cout << " |           2. 按出发/到达站查询  \t|" << endl;
	cout << " |           3. 返回主菜单      \t|" << endl;
	cout << "  --------------------------------------" << endl;
	cout << endl;

	cout << "请选择你所需的功能：";
	char choice;
	cin >> choice;

	while ((choice != '1') && (choice != '2') && (choice != '3'))
	{
		cout << "输入无效！请重新输入：";
		cin >> choice;
	}
	while ((choice == '1') || (choice == '2'))
	{
		if (choice == '1')
			search_number(classes);
		else if (choice == '2')
			search_station(classes);
		cout << endl;

		cout << "请选择你所需的功能：";
		cin >> choice;
		while ((choice != '1') && (choice != '2') && (choice != '3'))
		{
			cout << "输入无效！请重新输入：";
			cin >> choice;
		}
	}
	system("cls");
	welcome(classes);
}


//根据用户输入的班次号查询车次信息并在控制台输出。
void search_number(Node *classes)
{
	cout << "请输入班次号：";
	char temp[10];
	cin >> temp;
	int i = 0;
	for (; i < tip; i++)
	{
		if (strcmp(classes[i].number, temp) == 0)
			break;
	}
	if (i == tip)
		cout << "查询信息不存在！" << endl;
	else
	{
		cout << classes[i].number << "," << classes[i].ticket;
		station *p = classes[i].head;
		while (p != NULL)
		{
			cout << "|" << p->place << "," << p->tickets;
			p = p->next;
		}
		cout << "|" << endl;
	}
}


//根据用户输入的出发和到达站查询车次信息并在控制台输出。
void search_station(Node *classes)
{
	char temp1[10], temp2[10];
	cout << "出发站：";
	cin >> temp1;
	cout << "到达站：";
	cin >> temp2;

	int k = 0;
	char numbers[100][10];
	int ticket[100];

	int i = 0,x = 0,y = 0;
	for (; i < tip; i++)
	{
		station *p = classes[i].head;
		while (p->next != NULL)
		{
			if (strcmp(p->place, temp1) == 0)
				break;
			else
				p = p->next;
		}
		if (p->next != NULL)
		{
			station *q = p->next;
			while (q != NULL)
			{
				if (strcmp(q->place, temp2) == 0)
				{
					x++;
					break;
				}
				else
					q = q->next;
			}
			if (q != NULL)
			{
				station *r = p;
				int tickets = r->tickets;
				while (r->next != q)
				{
					if (r->tickets < tickets)
						tickets = r->tickets;
					r = r->next;
				}
				if (tickets != 0)
				{
					y++;
					strcpy(numbers[k], classes[i].number);
					ticket[k] = tickets;
					k++;
				}
			}
		}
	}

	if (x == 0)
		cout << "不存在此班次列车！" << endl;
	if (x != 0 && y == 0)
		cout << "该班次列车票已售完！" << endl;
	if (x != 0 && y != 0)
	{
		
		//升序排序
		for (int m = 0; m < k-1; m++)
		{
			for (int n = 0; n < k - 1; n++)
			{
				if (numbers[n][0] != numbers[n + 1][0])
				{
					if (numbers[n][0] > numbers[n + 1][0])
					{
						char temp[10];
						strcpy(temp, numbers[n]);
						strcpy(numbers[n], numbers[n + 1]);
						strcpy(numbers[n + 1], temp);
						int temps = ticket[n];
						ticket[n] = ticket[n + 1];
						ticket[n + 1] = temps;
					}
				}
				else
				{
					int s1 = strlen(numbers[n]);
					int s2 = strlen(numbers[n + 1]);
					if (s1 != s2)
					{
						if (s1 > s2)
						{
							char temp[10];
							strcpy(temp, numbers[n]);
							strcpy(numbers[n], numbers[n + 1]);
							strcpy(numbers[n + 1], temp);
							int temps = ticket[n];
							ticket[n] = ticket[n + 1];
							ticket[n + 1] = temps;
						}
					}
					else
					{
						for (int x = 1; x < s1; x++)
						{
							if (numbers[n][x] > numbers[n + 1][x])
							{
								char temp[10];
								strcpy(temp, numbers[n]);
								strcpy(numbers[n], numbers[n + 1]);
								strcpy(numbers[n + 1], temp);
								int temps = ticket[n];
								ticket[n] = ticket[n + 1];
								ticket[n + 1] = temps;
								break;
							}
						}
					}
				}
			}
		}

		cout << "车次     余票" << endl;
		for (int j = 0; j < k; j++)
		{
			cout << numbers[j] << "      ";
			cout << ticket[j] << endl;
		}
	}
}


//welcome功能4实现
void function4(Node *classes)
{
	system("cls");
	cout << " ****************************************" << endl;
	cout << "           欢迎登录12306购票系统！" << endl;
	cout << "  --------------------------------------" << endl;
	cout << " |             1. 售票                 \t|" << endl;
	cout << " |             2. 订单浏览          \t|" << endl;
	cout << " |             3. 退票                 \t|" << endl;
	cout << " |             4. 返回主菜单       \t|" << endl;
	cout << "  --------------------------------------" << endl;
	cout << endl;

	cout << "请选择你所需的功能：";
	char choice;
	cin >> choice;
	while ((choice != '1') && (choice != '2') && (choice != '3')&&(choice != '4'))
	{
		cout << "输入无效！请重新输入：";
		cin >> choice;
	}
	while ((choice == '1') || (choice == '2')||(choice == '3'))
	{
		if ((choice == '1'))
			sell_ticket(classes);
		else if (choice == '2')
			cout << "此功能在开发中，请稍候......" << endl;
		else
			cout << "此功能在开发中，请稍候......" << endl;
		cout << endl;

		cout << "请选择你所需的功能：";
		cin >> choice;
		while ((choice != '1') && (choice != '2') && (choice != '3')&&(choice != '4'))
		{
			cout << "输入无效！请重新输入：";
			cin >> choice;
		}
	}
	system("cls");
	welcome(classes);
}


//完成购票功能，修改系统中余票数量。
void sell_ticket(Node *classes)
{

}


int main()
{
	Node classes[100];
	welcome(classes);

	//输出classes的信息
	for (int i = 0; i < tip; i++)
	{
		cout << classes[i].number << " * ";
		cout << classes[i].ticket << " * ";
		station *p = classes[i].head;
		while (p != NULL)
		{
			cout << p->place << " * ";
			p = p->next;
		}
		cout << endl;
	}
	//
	return 0;
}