// the first project written by sy_han_ and her roommates.
饭卡管理系统


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 5
struct fanka{
	char number[20];
	char name[20];
	int zhuangtai;
	float yue;
}fanka[MAX];
int count=0;
void jianli();
void maifan();
void xuqian();
void tianjia();
void shanchu();
void guashi();
void tonggua();
void xianshi();

int main()
{int choose;
do {

    system("cls");
	printf("===================饭卡管理系统==================\n");
	printf("\t\t0.显示已建立的饭卡\n");
	printf("\t\t1.建立饭卡\n");
	printf("\t\t2.买饭\n");
	printf("\t\t3.续钱\n");
	printf("\t\t4.添加新饭卡\n");
	printf("\t\t5.注销旧饭卡\n");
	printf("\t\t6.设置与解除挂失\n");
	printf("\t\t7.统计挂失人数\n");
	printf("\t\t8.退出程序\n\n");

	fflush(stdin);

	printf("请输入功能选项:");
	scanf("%d",&choose);
	switch(choose)
	{
	case 0:xianshi();break;
	case 1:jianli();break;
	case 2:maifan();break;
	case 3:xuqian();break;
	case 4:tianjia();break;
	case 5:shanchu();break;
	case 6:guashi();break;
	case 7:tonggua();break;
	case 8:break;}
}while(choose!=8);
return 0;
}




void xianshi()
{
	int j;
	char x;
	do
	{
	printf("\t卡号\t姓名\t状态\t余额\n");
	for(j=0;j<count;j++)
		printf("\t%s\t%s\t%d\t%6.2f\n",fanka[j].number,fanka[j].name,fanka[j].zhuangtai,fanka[j].yue);
    fflush(stdin);
	printf("请输入回车以返回：");
		x=getchar();
	}while(x=='n');
}

void jianli()
{
	char a;
	do
	{
		fflush(stdin);
		printf("\n请输入卡号:");
		gets(fanka[count].number);
		fflush(stdin);
		printf("\n请输入姓名:");
		gets(fanka[count].name);
		fflush(stdin);
        fanka[count].zhuangtai=0;
		fflush(stdin);
		printf("\n请输入饭卡余额:");
		scanf("%f",&fanka[count].yue);
		fflush(stdin);
		printf("     建立完成    ");
		printf("是否继续建立新饭卡?(y/n)?");
		a=getchar();
		count++;
	}while((a=='y')&&(count<=MAX));

}





void guashi()
{
	char temp[20];
	int b,c;

		fflush(stdin);
	
	printf("请输入卡号:");
	gets(temp);
	for(c=0;c<count;c++)
	{
       if(strcmp(temp,fanka[c].number)==0)
	   break;

	}
    		fflush(stdin);
	printf("\n请选择功能：1.挂失 2.解除挂失 (1 or 2)?");
	scanf("%d",&b);

	if(b==1)
	{
		fanka[c].zhuangtai=1;
		printf("挂失已成功！\n");
	}
	if(b==2)
	{
		fanka[c].zhuangtai=0;
		printf("解除挂失已成功！");
	}
	xianshi();
		
}


void shanchu()
{ 

	char number[20],c;
	int a,b,i;
	do
	{
        fflush(stdin);
		printf("请输入要删除的卡号：");
		gets(number);
		for(a=0;a<count;a++)
		{	
			if(strcmp(number,fanka[a].number)==0)break;
		}
			for(b=a;b<count;b++)
				fanka[b]=fanka[b+1];
			if(a>count)printf("未找到!!!");
			else {count--;
			printf("剩余的饭卡为：\n");
			for(i=0;i<count;i++)
			
				printf("%s   %s\n",fanka[i].number,fanka[i].name);
			}
						  fflush(stdin);
			printf("是否继续删除?(y/n)");

             c=getchar();
	}      while(c=='y');
}

void tianjia()
{
	int i;
	char c;
	do
	{

	
		fflush(stdin);
		printf("\n请输入卡号:");
		gets(fanka[count].number);
		fflush(stdin);
		printf("\n请输入姓名:");
		gets(fanka[count].name);
		fflush(stdin);
		printf("\n请输入饭卡状态，已挂失输入1，未挂失输入0:");
		scanf("%d",&fanka[count].zhuangtai);
		fflush(stdin);
		printf("\n请输入饭卡余额:");
		scanf("%f",&fanka[count].yue);

        for(i=0;i<count;i++)
		     if(strcmp(fanka[count].number,fanka[i].number)==0)
			 {printf("该卡号已被注册，请重新输入!!!\n");
		    	break;
			 } 
	    if(i==count)
		{printf("您已注册成功!\n");
		count=count+1;
     	xianshi();
		}
        printf("是否继续添加？（y/n）\n");
        fflush(stdin);
		c=getchar();
	}while(c=='y');

		}

		




void maifan()
{
	
	int i;
	float m;
	char a;
	char num[20];
	do
	{
		system("cls");
        fflush(stdin);
        printf("\n请输入饭卡号:");
	    gets(num);
		fflush(stdin);
	    printf("\n请输入饭费:");
	    scanf("%f",&m);
		if(m<=0)
			printf("\n请输入正确的饭费!\n");
		else
		{

	     for(i=0;i<count;i++)
	
		    if(strcmp(num,fanka[i].number)==0)
			break;
		
         if(i==count)
			printf("没有找到该账户\n");
		 else if(fanka[i].zhuangtai==1)
			printf("本卡已冻结\n");
		 else if(fanka[i].yue<5)
			printf("金额不够，请续钱\n");
         else
		 {
			printf("\n消费前:%5.2f\n",fanka[i].yue);
            fanka[i].yue=fanka[i].yue-m;
			printf("\n消费后:%5.2f\n",fanka[i].yue);
		 }
		}
		printf("\n是否继续买饭?\n请输入y或n:");
        fflush(stdin);
		a=getchar();
	}while(a=='y');

}

void xuqian()
{
	int i;
	float m;
	char num[20];
	char a;
	do
	{
		system("cls");
        fflush(stdin);
        printf("\n请输入饭卡号:");
	    gets(num);
        fflush(stdin);
	    printf("\n请输入续钱额:");
	    scanf("%f",&m);
		if(m<=0)
			printf("\n请输入正确的饭费!\n");
		else
		{
	
	     for(i=0;i<count;i++)
		    if(strcmp(num,fanka[i].number)==0)
			break;

		 if(i==count)
			printf("没有找到该账户\n");
		 else if(fanka[i].zhuangtai==1)
			printf("本卡已冻结\n");
		 else
		 {
			printf("\n续费前:%5.2f\n",fanka[i].yue);
            fanka[i].yue=fanka[i].yue+m;
			printf("\n续费后:%5.2f\n",fanka[i].yue);
		 }
		}
		printf("\n是否继续续钱?\n请输入y或n:");
        fflush(stdin);
		a=getchar();
	}while(a=='y');
     	
}

void tonggua()
{
	int i,sum;
    for(i=0,sum=0;i<count;i++)
    if(fanka[i].zhuangtai==1)
	{sum=sum+1;
	 printf("\n饭卡号:%s\t姓名:%s\t余额:%5.2f\n",fanka[i].number,fanka[i].name,fanka[i].yue);
	}
	printf("\n挂失饭卡数:%d\n",sum);
	printf("\n按任意键继续:");
    fflush(stdin);
    getchar();
	
}
