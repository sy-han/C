//医院选址问题完整程序如下：
//hospital.cpp
//EDIT with Microsoft Visual C++ 6.0 
#include<stdio.h>
#include<stdlib.h>
#define MAX 32767//定义一个很大的数当作是不存在直接路径的标志
#define N 6//图的顶点数量
typedef struct AM_Graph//图的邻接矩阵类型
{
	int AdjMatrix[N][N];//邻接矩阵存放各点之间的距离
	int VexNum,ArcNum;//存放顶点数量和弧的数量
  char VexName[N];//顶点名称
}AM_Graph;

void printGraph(AM_Graph g)
{
	int i,j;
	printf("该图的顶点个数为:%d\n",g.VexNum);
	printf("该图的边的条数为:%d\n",g.ArcNum);//输出图的顶点和边的总体信息；
	printf("图已经定义完毕！\n初始各点的距离为:\n(这里我们用∞表示两点之间没有直接路径):\n");//用一个很大的数代表不存在直接路径
	for(i=0;i<g.VexNum;i++)
	{
		for(j=0;j<g.VexNum;j++)
		{
			if(g.AdjMatrix[i][j]>=MAX)
				printf("∞\t");
			else
				printf("%d\t",g.AdjMatrix[i][j]);
		}
		printf("\n");//输出图的各个顶点的距离信息
		
	}
}

void Floyd(AM_Graph g,int Dist[N][N])//Floyd算法求解各顶点之间的最短路径，传递的参数为存放有直接路径长度的矩阵
{
	printf("==============图的赋值准备===============\n");
	int i,j,k;
	int count=0;//记录边的数量，方法是初始的矩阵所有不是0也不是MAX的元素个数可视为一条边

	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
		{
			if((Dist[i][j]!=0)&&(Dist[i][j]!=MAX))
				count++;//记录边的个数
			g.AdjMatrix[i][j]=Dist[i][j];//用传递的二维数组为图的邻接矩阵赋值
		}
	g.VexNum=N;//为图的各项元素赋值
	g.ArcNum=count;

	printGraph(g);//输出图的各项信息，以检验是否赋值成功
	printf("==============Floyd算法求解==================\n");


	for(k=0;k<N;k++)//用图中的每一点作为中间点遍历dist矩阵
	{
		for(i=0;i<N;i++)
		{
			for(j=0;j<N;j++)
			{
				if(Dist[i][j]>(Dist[i][k]+Dist[k][j]))//如果把k作为中间点会让距离变小
				{
					Dist[i][j]=Dist[i][k]+Dist[k][j];//修改顶点之间的距离
				}
			}
		}
	}
}

void BuildEc(int Dist[N][N],int Ec[N])
{
	int i,j;
	int temp;//方便比较以便找出每一列的最大元素即为对应顶点的偏心度
	for(i=0;i<N;i++)
	{
		temp=Dist[0][i];//对每一列的偏心度取初始值
		for(j=0;j<N;j++)
		{
			if(temp<Dist[j][i])
				temp=Dist[j][i];//找到每一列的最大元素
		}
		Ec[i]=temp;
	}
	printf("各顶点偏心度建立成功！\n");
}

					
int minEc(int Ec[N])//取得最小偏心度的顶点下标
{
	int i,temp,k;
	k=0;//下标赋初始值

	for(i=1;i<N;i++)
	{
		temp=Ec[k];//寻找最小偏心度元素
		if(temp>Ec[i])
		{
			k=i;//用k表示当前找到的偏心度最小元素的下标
		}
	}
	printf("已取得最小下标的元素!\n");

	return k;//循环结束，返回遍历整个数组后偏心度最小的元素下标
}


void print(int Dist[N][N],int Ec[N],char VexName[N])//输出最终结果
{
	int i,j,k;

	printf("================输出最终结果=================\n");
	printf("经过Floyd算法求得了每对顶点之间的最短路径\n");
	printf("其中∞代表两点之间不存在直接路径\n");
	printf("=============================================\n");

	for(i=0;i<N;i++)//输出每对顶点之间的最短路径
	{
		for(j=0;j<N;j++)
		{
			if(i==j)
				continue;
			if(Dist[i][j]>=MAX)
				printf("%c到%c点的最短路径长度为:∞ ",VexName[i],VexName[j]);
			else
				printf("%c到%c点的最短路径长度为:%d ",VexName[i],VexName[j],Dist[i][j]);//输出每一点到其他点的最短路径的长度
		}
		printf("\n");
	}
	printf("============================================\n");
	printf("各个顶点的偏心度为:\n");
	printf("其中∞代表偏心度为无穷大\n");
	for(i=0;i<N;i++)//输出各个顶点的偏心度
	{
		if(Ec[i]>=MAX)
			printf("%c点的偏心度为：∞\n",VexName[i]);
		else
			printf("%c点的偏心度为：%d\n",VexName[i],Ec[i]);
	}
	k=minEc(Ec);//取得偏心度最小元素的下标

	printf("==================最终结果=================\n");
	printf("医院最佳选址即偏心度最小的顶点是%c点\n",VexName[k]);//输出结果
}
	


int main()
{ 
	int i,j;
	int dist[N][N];
	int EC[N];
	AM_Graph g;
	printf("请输入各个顶点的名称(中间没有空格,请以回车键结束):");
	for(i=0;i<N;i++)
		scanf("%c",&g.VexName[i]);//为顶点名称赋值，实际上在顶点个数不是5的情况可以顺延到下一位ASCII码对应的字符，也可作一定改进让用户自行输入
//	char VexName[N]={'a','b','c','d','e','f'};

	for(i=0;i<N;i++)//为各个顶点的直接距离赋值
	{
	    for(j=0;j<N;j++)
		{
			if(i==j)
				continue;
			printf("请输入第%d点到第%d点的距离(如果没有直接路径请输入-1):",i+1,j+1);
			scanf("%d",&dist[i][j]);		
		}
	}
	for(i=0;i<N;i++)//没有直接距离的时候赋值为MAX
	{
		dist[i][i]=0;
		for(j=0;j<N;j++)
		{
			if(dist[i][j]<0)
				dist[i][j]=MAX;
		}
	}

	system("cls");
/*	int dist[N][N]={
	{0,1,MAX,MAX,MAX},
	{MAX,0,2,MAX,MAX},
	{MAX,MAX,0,2,4},
	{MAX,1,3,0,MAX},
	{MAX,MAX,MAX,5,0}
	};//初始设计，初始的dist矩阵存放的是直接路径长度*/




	Floyd(g,dist);//为图赋值并且完成Floyd算法求解各顶点之间的最短路径
	BuildEc(dist,EC);//求解各点的偏心度并存放在一维数组里
	print(dist,EC,g.VexName);//输出最终结果

	printf("================程序结束==================\n");

	return 0;
}
