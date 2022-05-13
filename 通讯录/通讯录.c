#include<stdio.h>
#include<memory.h>
#include<string.h>
#define Max 1000
#define Name_Max 15
#define Tele_Max 11
#define Company_Max 15
#define Addr_Max 15

//创建菜单函数
void menu()
{
 printf("*********通讯录*********\n");
 printf("****1.增加    2.删除****\n");
 printf("****3.修改    4.查找****\n");
 printf("****5.显示    6.排序****\n");
 printf("*********0.退出*********\n");
}

//创建描述联系人信息的结构体变量
struct infor
{
 char name[Name_Max];
 char sex[5];
 int  age;
 char tele[Tele_Max];
 char company[Company_Max];
 char addr[Addr_Max];
};

//创建存放联系人信息的结构体变量
struct Contact
{
 struct infor date[Max];//联系人信息
 int num;//记录有了多少个联系人（因为联系人存放在数组中有多个位置可以放,无法确定放在哪
};            //则通过联系人数量num来确定存放位置,使联系人信息一个接着一个放）

//初始化通讯录
void Initcontact(struct Contact* ps)
{
 memset(ps->date,0,sizeof(ps->date));
 ps->num=0;
}

//增加联系人
void Addcontact(struct Contact* ps)
{
 if(ps->num==Max)
  {
   printf("添加失败,通讯录已满\n");
  }
 else
 {
  printf("请输入姓名：>\n");
  scanf("%s",ps->date[ps->num].name);
  printf("请输入性别：>\n");
  scanf("%s",ps->date[ps->num].sex);
  printf("请输入年龄：>\n");
  scanf("%d",&ps->date[ps->num].age);
  printf("请输入电话：>\n");
  scanf("%s",ps->date[ps->num].tele);
  printf("请输入公司：>\n");
  scanf("%s",ps->date[ps->num].company);
  printf("请输入地址：>\n");
  scanf("%s",ps->date[ps->num].addr);
 printf("添加成功\n");
 ps->num++;
 }
}

//分装找联系人的函数（因为后面多个功能的实现都需要这个函数,会出现代码的重叠）
int Find(const struct Contact* ps,char arr[15])
{
 int i=0;
 for(i=0;i<=ps->num-1; i++)
  {
   if(0==strcmp(ps->date[i].name,arr))
     return i;
  }
 return -1;
}

//删除联系人
void Delcontact(struct Contact* ps)
{
 char arr[15]; int i=0;
 if(ps->num==0)
  {
   printf("通讯录为空\n");
  }
 else
 {
  printf("请输入要删除联系人的姓名：>\n");
  scanf("%s",arr);
  int ret=Find(ps,arr);
  if(ret==-1)
   {
    printf("该联系人不存在\n");
   }
  else
  {
   for(i=ret;i<=ps->num;i++)
    {
     ps->date[i]=ps->date[i+1];
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
 if(ps->num==0)
  {
   printf("通讯录为空\n");
  }
 else
 {
  printf("请输入要修改联系人的姓名：>\n");
  scanf("%s",arr);
  int ret=Find(ps,arr);
  if(ret==-1)
   {
    printf("该联系人不存在\n");
   }
  else
   {
    printf("请输入姓名：>\n");
    scanf("%s",ps->date[ret].name);
    printf("请输入性别：>\n");
    scanf("%s",ps->date[ret].sex);
    printf("请输入年龄：>\n");
    scanf("%d",&ps->date[ret].age);
    printf("请输入电话：>\n");
    scanf("%s",ps->date[ret].tele);
    printf("请输入公司：>\n");
    scanf("%s",ps->date[ret].company);
    printf("请输入地址：>\n");
    scanf("%s",ps->date[ret].addr);
   printf("修改成功\n");
   }
  }
} 

//查找联系人
void Searcontact(const struct Contact* ps)
{
char arr[15];
 if(ps->num==0)
  {
   printf("通讯录为空\n");
  }
 else
 {
  printf("请输入要查找联系人的姓名：>\n");
  scanf("%s",arr);
  int ret=Find(ps,arr);
  if(ret==-1)
   {
    printf("该联系人不存在\n");
   }
  else
   {
    printf("%-3s\t%-s\t%-d\t%-10s\t%-13s\t%-13s\n",
          ps->date[ret].name,
          ps->date[ret].sex,
          ps->date[ret].age,
          ps->date[ret].tele,
          ps->date[ret].company,
          ps->date[ret].addr);
   }
  }
}

//显示联系人信息
void Showcontact(const struct Contact* ps)
{
 int i=0;
 if(ps->num==0)
  printf("通讯录为空\n");
 else
 {      //要根据类型去对齐
  printf("%-3s\t%-s\t%-s\t%-10s\t%-13s\t%-13s\n",
       "姓名","性别","年龄","电话","公司","地址");
  for(i=0;i<ps->num;i++)
  {
   printf("%-3s\t%-s\t%-d\t%-10s\t%-13s\t%-13s\n",
          ps->date[i].name,
          ps->date[i].sex,
          ps->date[i].age,
          ps->date[i].tele,
          ps->date[i].company,
          ps->date[i].addr);
  }
 }
}

//排序联系人
void Sortcontact(struct Contact* ps)
{
 int flag=0; int n=0; int i=0;
 struct infor tmp;
 if(ps->num==0)
  {
   printf("通讯录为空\n");
  }
 else
 {
  printf("请输入排列依据：>\n");
  printf("****1.姓名    2.年龄****\n");
  scanf("%d",&n);
  if(n==2)
  {
   for(i=0;i<ps->num;i++)
   {
    int j=0;
    for(j=0;j<ps->num-i-1;j++)
     {
       if(ps->date[j].age>ps->date[j+1].age)
       {
         tmp=ps->date[j];
         ps->date[j]=ps->date[j+1];
         ps->date[j+1]=tmp;
         flag=1;
       }
      }
    }
  }
 else 
 {
  for(i=0;i<ps->num;i++)
   {
    int j=0;
    for(j=0;j<ps->num-i-1;j++)
     {
      char bubb[15];
      if(strcmp(ps->date[j].name,ps->date[j+1].name)<0)
       {
       tmp=ps->date[j];
       ps->date[j]=ps->date[j+1];
       ps->date[j+1]=tmp;
       flag=1;
       }
     }
    if(flag==0)
     break;
    }
  }
 printf("排序完毕\n");
 }
}

//通过创建枚举来增加代码的可读性,使后面的switch语句更加可读
enum function
{
 Exit,
 Add,
 Del,
 Mod,
 Sear,
 Show,
 Sort
};

int main()
{
 int input=0;
 struct Contact con;
 Initcontact(&con);
 do
 {
  menu();
  printf("请选择想使用的功能：>\n");
  scanf("%d",&input);
  switch(input)
   { 
    case Add:
     Addcontact(&con); 
     break;
    case Del:
     Delcontact(&con);
     break;
    case Mod:
     Modcontact(&con);
     break;
    case Sear:
     Searcontact(&con);
     break;
    case Show:
     Showcontact(&con);
     break;
    case Sort:
     Sortcontact(&con);
     break;
    case Exit:
     printf("退出通讯录\n");
     break;
    default:
     printf("选择错误,请重新选择\n");
     break;
   }
 }while(input);
 return 0;
}


    