#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<conio.h>
#include<windows.h>

#define Name_Max 20
#define Tele_Max 15
#define Company_Max 20
#define Addr_Max 20
#define Default_amount 5

//菜单函数
void menu()
{
	printf("**************通讯录**************\n");
	printf("*********1.增   加      2.删   除*********\n");
	printf("*********3.修   改      4.查   找*********\n");
	printf("*********5.显   示      6.排   序*********\n");
	printf("*********7.重置密码     0.退   出*********\n");
}

//定义结构体来表示联系人信息
struct infor
{
	char name[Name_Max];
	char sex[5];
	int  age;
	char tele[Tele_Max];
	char company[Company_Max];
	char addr[Addr_Max];
};

struct Contact
{
	struct infor* data;//联系人信息
	int num;//记录有了多少个联系人
	int capacity;//记录当前通讯录的容量以便进行空间的动态调整
};

//初始化通讯录
void Load_infor(char* pa, struct Contact* ps);
void Initcontact(char* pa,struct Contact* ps)
{
	ps->data = (struct infor*)malloc(Default_amount*sizeof(struct infor));
	if (ps->data == NULL)
	{
		return;
	}
	ps->num = 0;
	ps->capacity = Default_amount;
	Load_infor(pa,ps);
}

//从文件中上传联系人信息到通讯录
void Checkcap(struct Contact* ps);
void Load_infor(char* pa,struct Contact* ps)
{
	struct infor tmp = { 0 };
	FILE* pfWord = fopen("password.data", "rb");
	FILE* pfRead = fopen("infor.data", "rb");
	if (pfWord != NULL)
	{
		fread(pa, 7, 1, pfWord);
	}
	if (pfRead == NULL)
	{
		printf("Load_infor::%s\n", strerror(errno));
		return;
	}
	while (fread(&tmp, sizeof(struct infor), 1, pfRead))
	{                                                  
		Checkcap(ps);
		ps->data[ps->num] = tmp;
		ps->num++;
	}
	fclose(pfRead);
	pfRead = NULL;
}

//检测通讯录容量并增容
void Checkcap(struct Contact* ps)
{
	if (ps->num == ps->capacity)
	{
		ps->data = (struct infor*)realloc(ps->data, (ps->capacity + 2)*sizeof(struct infor));
		if (ps->data != NULL)
		 {
			ps->capacity += 2;
		 }
		else
			printf("增容失败\n");
	}
}

//设置光标位置
void GotoXY(int x, int y)
{
	COORD pos = { x, y };
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//显示通讯录初始界面
void Print()
{
	int x =20, y = 10;
	system("color F0");
	GotoXY(x, y);
	printf("************************************************\n");
	GotoXY(x, y + 1);
	printf("************************************************\n");
	GotoXY(x, y + 2);
	printf("***************      通讯录      ***************\n");
	GotoXY(x, y + 3);
	printf("************************************************\n");
	GotoXY(x, y + 4);
	printf("************************************************\n");
}

//增加联系人
void Addcontact(struct Contact* ps)
{
	Checkcap(ps);
	printf("请输入姓名：>");
	scanf("%s", ps->data[ps->num].name);
	printf("请输入性别：>");
	scanf("%s", ps->data[ps->num].sex);
	printf("请输入年龄：>");
	scanf("%d", &ps->data[ps->num].age);
	printf("请输入电话：>");
	scanf("%s", ps->data[ps->num].tele);
	printf("请输入公司：>");
	scanf("%s", ps->data[ps->num].company);
	printf("请输入地址：>");
	scanf("%s", ps->data[ps->num].addr);
	printf("添加成功\n");
	ps->num++;
}

//分装找联系人函数
static int Find(const struct Contact* ps, char arr[15])
{
	int i = 0;
	for (i = 0; i <= ps->num - 1; i++)
	{
		if (0 == strcmp(ps->data[i].name, arr))
			return i;
	}
	return -1;
}

//删除联系人
void Delcontact(struct Contact* ps)
{
	char arr[15]; int i = 0;
	if (ps->num == 0)
	{
		printf("通讯录为空\n");
	}
	else
	{
		printf("请输入要删除联系人的姓名：>");
		scanf("%s", arr);
		int ret = Find(ps, arr);
		if (ret == -1)
		{
			printf("该联系人不存在\n");
		}
		else
		{
			for (i = ret; i <= ps->num; i++)
			{
				ps->data[i] = ps->data[i + 1];
			}
			ps->num--;
			printf("删除成功\n");
		}
	}
}

//修改联系人
void Modcontact(struct Contact* ps)
{
	char arr[15]; 
	int input;
	if (ps->num == 0)
	{
		printf("通讯录为空\n");
	}
	else
	{
		printf("请输入要修改联系人的姓名：>");
		scanf("%s", arr);
		int ret = Find(ps, arr);
		if (ret == -1)
		{
			printf("该联系人不存在\n");
		}
		else
		{ 
			printf("*********1.姓名     2.性别*********\n");
			printf("*********3.年龄     4.电话*********\n");
			printf("*********5.公司     6.地址*********\n");
			printf("*********7.全选     0.退出*********\n");
			do
			{
				printf("请选择想要修改的内容：>");
				scanf("%d", &input);
				switch (input)
				{
				 case 1:
					printf("请输入姓名：>");
					scanf("%s", ps->data[ret].name);
					printf("修改成功\n");
					break;
				 case 2:
					 printf("请输入性别：>");
					 scanf("%s", ps->data[ret].sex);
					 printf("修改成功\n");
					 break;
				 case 3:
					 printf("请输入年龄：>");
					 scanf("%d", &ps->data[ret].age);
					 printf("修改成功\n");
					 break;
				 case 4:
					 printf("请输入电话：>");
					 scanf("%s", ps->data[ret].tele);
					 printf("修改成功\n");
					 break;
				 case 5:
					 printf("请输入公司：>");
					 scanf("%s", ps->data[ret].company);
					 printf("修改成功\n");
					 break;
				 case 6:
					 printf("请输入地址：>");
					 scanf("%s", ps->data[ret].addr);
					 printf("修改成功\n");
					 break;
				 case 7:
					 printf("请输入姓名：>");
					 scanf("%s", ps->data[ret].name);
					 printf("请输入性别：>");
					 scanf("%s", ps->data[ret].sex);
					 printf("请输入年龄：>");
					 scanf("%d", &ps->data[ret].age);
					 printf("请输入电话：>");
					 scanf("%s", ps->data[ret].tele);
					 printf("请输入公司：>");
					 scanf("%s", ps->data[ret].company);
					 printf("请输入地址：>");
					 scanf("%s", ps->data[ret].addr);
					 printf("修改成功\n");
					 break;
				 case 0:
					 printf("退出修改\n");
					 break;
				 default:
					 printf("选择错误，请重新选择\n");
					 break;
				}
			} while (input);
		}
	}
}

//查找联系人
void Searcontact(const struct Contact* ps)
{
	char arr[15];
	if (ps->num == 0)
	{
		printf("通讯录为空\n");
	}
	else
	{
		printf("请输入要查找联系人的姓名：>");
		scanf("%s", arr);
		int ret = Find(ps, arr);
		if (ret == -1)
		{
			printf("该联系人不存在\n");
		}
		else
		{
			printf("%-4s\t%-2s\t%-3s\t%-12s\t%-13s\t%-15s\n",
				"姓名", "性别", "年龄", "电话", "公司", "地址");
			printf("%-3s\t%-s\t%-d\t%-10s\t%-13s\t%-13s\n",
				ps->data[ret].name,
				ps->data[ret].sex,
				ps->data[ret].age,
				ps->data[ret].tele,
				ps->data[ret].company,
				ps->data[ret].addr);
		}
	}
}

//显示联系人信息
void Showcontact(const struct Contact* ps)
{
	int i = 0;
	if (ps->num == 0)
		printf("通讯录为空\n");
	else
	{      //要根据类型去对齐
		printf("%-4s\t%-2s\t%-3s\t%-12s\t%-13s\t%-15s\n",
			"姓名", "性别", "年龄", "电话", "公司", "地址");
		for (i = 0; i<ps->num; i++)
		{
			printf("%-4s\t%-2s\t%-d\t%-12s\t%-13s\t%-15s\n",
				ps->data[i].name,
				ps->data[i].sex,
				ps->data[i].age,
				ps->data[i].tele,
				ps->data[i].company,
				ps->data[i].addr);
		}
	}
}

//排序联系人
void Sortcontact(struct Contact* ps)
{
	int flag = 0; int n = 0; int i = 0;
	struct infor tmp;
	if (ps->num == 0)
	{
		printf("通讯录为空\n");
	}
	else
	{
		printf("请输入排列依据：>");
		printf("****1.姓名    2.年龄****\n");
		scanf("%d", &n);
		if (n == 2)
		{
			for (i = 0; i<ps->num; i++)
			{
				int j = 0;
				for (j = 0; j<ps->num - i - 1; j++)
				{
					if (ps->data[j].age>ps->data[j + 1].age)
					{
						tmp = ps->data[j];
						ps->data[j] = ps->data[j + 1];
						ps->data[j + 1] = tmp;
						flag = 1;
					}
				}
			}
		}
		else
		{
			for (i = 0; i<ps->num; i++)
			{
				int j = 0;
				for (j = 0; j<ps->num - i - 1; j++)
				{
					if (strcmp(ps->data[j].name, ps->data[j + 1].name)>0)
					{
						tmp = ps->data[j];
						ps->data[j] = ps->data[j + 1];
						ps->data[j + 1] = tmp;
						flag = 1;
					}
				}
				if (flag == 0)
					break;
			}
		}
		printf("排序完毕\n");
	}
}

//销毁通讯录(释放动态开辟内存空间)
void Destroycontact(struct Contact* ps)
{
	free(ps->data);
	ps->data = NULL;
}

//保存联系人信息
void Preserve_infor(struct Contact* ps)
{
	int input;
	int i = 0;
	printf("**********1.保存    0.不保存*********\n");
	printf("请选择是否保存：>");
	scanf("%d", &input);
	if (input == 1)
	{
		FILE* pfWrite = fopen("infor.data","wb");
		if (pfWrite == NULL)
		{
			printf("Preserve_infor::%s\n", strerror(errno));
			return;
		}
		for (i = 0; i< ps->num; i++)
		{
			fwrite(&(ps->data[i]), sizeof(struct infor), 1, pfWrite);
		}
		printf("保存成功\n");
		fclose(pfWrite);
		pfWrite = NULL;
	}
}

//重设密码
void ResetPassword(char* pa)
{
	int i, input;
	printf("请输入新的密码：>");
	for (i = 0; i < 6; i++)
	{
		pa[i] = _getch();
		printf("*");
	}
	printf("\n**********1.保存    0.不保存*********\n");
	printf("请选择是否保存：>");
	scanf("%d", &input);
	if (input == 1)
	{
		FILE* pfWord = fopen("password.data", "wb");
		if (pfWord == NULL)
		{
			printf("Preserve_infor::%s\n", strerror(errno));
			return;
		}
		else
		{
			fwrite(pa, 7, 1, pfWord);
			printf("保存成功\n");
			fclose(pfWord);
			pfWord = NULL;
		}
	}
}

void Pause()
{
	if (_kbhit() == 0)
		system("pause");
}

enum function
{
	Exit,
	Add,
	Del,
	Mod,
	Sear,
	Show,
	Sort,
	Reset
};

int main()
{
	int i,input = 0;
	char arr[7] = { 0 };
	char password[7] = "su58i6";
	struct Contact con;
	Initcontact(password,&con);
	Print();
	printf("请输入密码：>");
	for (i = 1; i <= 3; i++)
	{
		int j = 0;
		for (j = 0; j < 6; j++)
		{
			arr[j] = _getch();
			printf("*");
		}
		if (strcmp(arr, password) == 0)
		{
			do
			{
				system("cls");
				menu();
				printf("请选择想使用的功能：>");
				scanf("%d", &input);
				switch (input)
				{
				case Add:
					Addcontact(&con);
					Pause();
					break;
				case Del:
					Delcontact(&con);
					Pause();
					break;
				case Mod:
					Modcontact(&con);
					Pause();
					break;
				case Sear:
					Searcontact(&con);
					Pause();
					break;
				case Show:
					Showcontact(&con);
					Pause();
					break;
				case Sort:
					Sortcontact(&con);
					Pause();
					break;
				case Reset:
					ResetPassword(password);
					Pause();
					break;
				case Exit:
					Preserve_infor(&con);
					Destroycontact(&con);
					printf("退出通讯录\n");
					break;
				default:
					printf("选择错误,请重新选择\n");
					break;
				}
			} while (input);
			break;
		}
		printf("\n密码输入错误，请重新输入：>");
	}	
	return 0;
}



