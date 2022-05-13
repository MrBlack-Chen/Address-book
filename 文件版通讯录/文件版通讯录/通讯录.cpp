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

//�˵�����
void menu()
{
	printf("**************ͨѶ¼**************\n");
	printf("*********1.��   ��      2.ɾ   ��*********\n");
	printf("*********3.��   ��      4.��   ��*********\n");
	printf("*********5.��   ʾ      6.��   ��*********\n");
	printf("*********7.��������     0.��   ��*********\n");
}

//����ṹ������ʾ��ϵ����Ϣ
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
	struct infor* data;//��ϵ����Ϣ
	int num;//��¼���˶��ٸ���ϵ��
	int capacity;//��¼��ǰͨѶ¼�������Ա���пռ�Ķ�̬����
};

//��ʼ��ͨѶ¼
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

//���ļ����ϴ���ϵ����Ϣ��ͨѶ¼
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

//���ͨѶ¼����������
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
			printf("����ʧ��\n");
	}
}

//���ù��λ��
void GotoXY(int x, int y)
{
	COORD pos = { x, y };
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//��ʾͨѶ¼��ʼ����
void Print()
{
	int x =20, y = 10;
	system("color F0");
	GotoXY(x, y);
	printf("************************************************\n");
	GotoXY(x, y + 1);
	printf("************************************************\n");
	GotoXY(x, y + 2);
	printf("***************      ͨѶ¼      ***************\n");
	GotoXY(x, y + 3);
	printf("************************************************\n");
	GotoXY(x, y + 4);
	printf("************************************************\n");
}

//������ϵ��
void Addcontact(struct Contact* ps)
{
	Checkcap(ps);
	printf("������������>");
	scanf("%s", ps->data[ps->num].name);
	printf("�������Ա�>");
	scanf("%s", ps->data[ps->num].sex);
	printf("���������䣺>");
	scanf("%d", &ps->data[ps->num].age);
	printf("������绰��>");
	scanf("%s", ps->data[ps->num].tele);
	printf("�����빫˾��>");
	scanf("%s", ps->data[ps->num].company);
	printf("�������ַ��>");
	scanf("%s", ps->data[ps->num].addr);
	printf("��ӳɹ�\n");
	ps->num++;
}

//��װ����ϵ�˺���
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

//ɾ����ϵ��
void Delcontact(struct Contact* ps)
{
	char arr[15]; int i = 0;
	if (ps->num == 0)
	{
		printf("ͨѶ¼Ϊ��\n");
	}
	else
	{
		printf("������Ҫɾ����ϵ�˵�������>");
		scanf("%s", arr);
		int ret = Find(ps, arr);
		if (ret == -1)
		{
			printf("����ϵ�˲�����\n");
		}
		else
		{
			for (i = ret; i <= ps->num; i++)
			{
				ps->data[i] = ps->data[i + 1];
			}
			ps->num--;
			printf("ɾ���ɹ�\n");
		}
	}
}

//�޸���ϵ��
void Modcontact(struct Contact* ps)
{
	char arr[15]; 
	int input;
	if (ps->num == 0)
	{
		printf("ͨѶ¼Ϊ��\n");
	}
	else
	{
		printf("������Ҫ�޸���ϵ�˵�������>");
		scanf("%s", arr);
		int ret = Find(ps, arr);
		if (ret == -1)
		{
			printf("����ϵ�˲�����\n");
		}
		else
		{ 
			printf("*********1.����     2.�Ա�*********\n");
			printf("*********3.����     4.�绰*********\n");
			printf("*********5.��˾     6.��ַ*********\n");
			printf("*********7.ȫѡ     0.�˳�*********\n");
			do
			{
				printf("��ѡ����Ҫ�޸ĵ����ݣ�>");
				scanf("%d", &input);
				switch (input)
				{
				 case 1:
					printf("������������>");
					scanf("%s", ps->data[ret].name);
					printf("�޸ĳɹ�\n");
					break;
				 case 2:
					 printf("�������Ա�>");
					 scanf("%s", ps->data[ret].sex);
					 printf("�޸ĳɹ�\n");
					 break;
				 case 3:
					 printf("���������䣺>");
					 scanf("%d", &ps->data[ret].age);
					 printf("�޸ĳɹ�\n");
					 break;
				 case 4:
					 printf("������绰��>");
					 scanf("%s", ps->data[ret].tele);
					 printf("�޸ĳɹ�\n");
					 break;
				 case 5:
					 printf("�����빫˾��>");
					 scanf("%s", ps->data[ret].company);
					 printf("�޸ĳɹ�\n");
					 break;
				 case 6:
					 printf("�������ַ��>");
					 scanf("%s", ps->data[ret].addr);
					 printf("�޸ĳɹ�\n");
					 break;
				 case 7:
					 printf("������������>");
					 scanf("%s", ps->data[ret].name);
					 printf("�������Ա�>");
					 scanf("%s", ps->data[ret].sex);
					 printf("���������䣺>");
					 scanf("%d", &ps->data[ret].age);
					 printf("������绰��>");
					 scanf("%s", ps->data[ret].tele);
					 printf("�����빫˾��>");
					 scanf("%s", ps->data[ret].company);
					 printf("�������ַ��>");
					 scanf("%s", ps->data[ret].addr);
					 printf("�޸ĳɹ�\n");
					 break;
				 case 0:
					 printf("�˳��޸�\n");
					 break;
				 default:
					 printf("ѡ�����������ѡ��\n");
					 break;
				}
			} while (input);
		}
	}
}

//������ϵ��
void Searcontact(const struct Contact* ps)
{
	char arr[15];
	if (ps->num == 0)
	{
		printf("ͨѶ¼Ϊ��\n");
	}
	else
	{
		printf("������Ҫ������ϵ�˵�������>");
		scanf("%s", arr);
		int ret = Find(ps, arr);
		if (ret == -1)
		{
			printf("����ϵ�˲�����\n");
		}
		else
		{
			printf("%-4s\t%-2s\t%-3s\t%-12s\t%-13s\t%-15s\n",
				"����", "�Ա�", "����", "�绰", "��˾", "��ַ");
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

//��ʾ��ϵ����Ϣ
void Showcontact(const struct Contact* ps)
{
	int i = 0;
	if (ps->num == 0)
		printf("ͨѶ¼Ϊ��\n");
	else
	{      //Ҫ��������ȥ����
		printf("%-4s\t%-2s\t%-3s\t%-12s\t%-13s\t%-15s\n",
			"����", "�Ա�", "����", "�绰", "��˾", "��ַ");
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

//������ϵ��
void Sortcontact(struct Contact* ps)
{
	int flag = 0; int n = 0; int i = 0;
	struct infor tmp;
	if (ps->num == 0)
	{
		printf("ͨѶ¼Ϊ��\n");
	}
	else
	{
		printf("�������������ݣ�>");
		printf("****1.����    2.����****\n");
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
		printf("�������\n");
	}
}

//����ͨѶ¼(�ͷŶ�̬�����ڴ�ռ�)
void Destroycontact(struct Contact* ps)
{
	free(ps->data);
	ps->data = NULL;
}

//������ϵ����Ϣ
void Preserve_infor(struct Contact* ps)
{
	int input;
	int i = 0;
	printf("**********1.����    0.������*********\n");
	printf("��ѡ���Ƿ񱣴棺>");
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
		printf("����ɹ�\n");
		fclose(pfWrite);
		pfWrite = NULL;
	}
}

//��������
void ResetPassword(char* pa)
{
	int i, input;
	printf("�������µ����룺>");
	for (i = 0; i < 6; i++)
	{
		pa[i] = _getch();
		printf("*");
	}
	printf("\n**********1.����    0.������*********\n");
	printf("��ѡ���Ƿ񱣴棺>");
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
			printf("����ɹ�\n");
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
	printf("���������룺>");
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
				printf("��ѡ����ʹ�õĹ��ܣ�>");
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
					printf("�˳�ͨѶ¼\n");
					break;
				default:
					printf("ѡ�����,������ѡ��\n");
					break;
				}
			} while (input);
			break;
		}
		printf("\n��������������������룺>");
	}	
	return 0;
}



