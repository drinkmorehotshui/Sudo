#include "pch.h"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <string>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <complex>
#include<stack>
#include <iomanip>
#include <stdlib.h>
#pragma warning(disable : 4996)
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i,a,b) for(int i = (a); i < (b); ++i)
#define per(i,b,a) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define mst(a,b) memset(a,b,sizeof(a));
#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int inf = 0x3f3f3f3f;
int s[111][111];//数独
int n, m;//个数 阶数
int flag = 0;//成功标记
FILE* fp1;
FILE* fp2;
bool check2(int x, int r, int c, int val)//第二个验证函数 判断宫 
{
	int a = x / m;
	int b = x % m;
	a = a / r * r;//行
	b = b / c * c;//列
	for (int i = a; i<a + r; i++)
	{
		for (int j = b; j<b + c; j++)
		{
			if (s[i][j] == val)
			{
				return 0;
			}
		}
	}
	return 1;
}
bool check(int x, int val)//第一个验证函数 验证行与列且 4 6 8 9时需要判断宫 
{
	int r = x / m;
	int c = x % m;
	for (int i = 0; i<m; i++)//行 
	{
		if (s[r][i] == val)
		{
			return 0;
		}
	}
	for (int i = 0; i<m; i++)//列 
	{
		if (s[i][c] == val)
		{
			return 0;
		}
	}
	if (m == 4)//4*4
	{
		if (check2(x, 2, 2, val))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (m == 6)//6*6
	{
		if (check2(x, 2, 3, val))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (m == 8)//8*8
	{
		if (check2(x, 4, 2, val))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (m == 9)//9*9
	{
		if (check2(x, 3, 3, val))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}
void output()//输出函数 
{
	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j<m; j++)
		{
			fprintf(fp2, "%d", s[i][j]);//输出至文件
			if (j < m - 1)
			{
				fprintf(fp2, " ");
			}
			
		}
		fprintf(fp2, "\n");
	}
}
void dfs(int x)//dfs函数 递归填数 
{
	if (flag)//如果已经完成 直接返回 
	{
		return;
	}
	if (x == m * m)//已经找完 
	{
		output();
		flag = 1;
		return;
	}
	int r = x / m;//行
	int c = x % m;//列
	if (!s[r][c])//没填过就填这个空 
	{
		for (int i = 1; i <= m; i++)
		{
			if (check(x, i))
			{
				s[r][c] = i;
				dfs(x + 1);
				s[r][c] = 0;//回溯 
			}
		}
	}
	else//已经有数就跳过 
	{
		dfs(x + 1);
	}
}
int main(int argc, char *argv[])
{
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);
	m = atoi(argv[2]);//读取参数
	n = atoi(argv[4]);
	char *inputname = argv[6];
	char *outputname= argv[8];
	fp1 = fopen(inputname, "r");//打开输入文件
	if (fp1 == NULL)
	{
		return -1;
	}
	fp2 = fopen(outputname, "w");//打开输出文件，清空文件
	if (fp2 == NULL) //
	{
		return -1;
	}
	fclose(fp2);
	while (n--)
	{
		mst(s, 0);//初始化 
		flag = 0;
		for (int i = 0; i<m; i++)//输入 
		{
			for (int j = 0; j<m; j++)
			{
				fscanf(fp1, "%d", &s[i][j]);//文件读入
			}
		}
		fp2 = fopen(outputname, "a");//打开输出文件
		dfs(0);	//开始填数 
		if (n > 0)
		{
			fprintf(fp2, "\n");//输出至文件

		}
		fclose(fp2);//关闭输出文件
	}
	fclose(fp1);//关闭输入文件
	return 0;
}
/*2 9
0 0 8 0 0 4 0 0 9
0 6 0 0 0 0 1 0 0
0 3 7 0 0 0 0 0 0
8 0 1 2 6 9 0 0 3
0 2 5 4 7 0 0 6 8
0 9 0 0 0 5 0 0 0
9 0 0 1 5 2 3 7 4
0 4 0 3 9 8 0 1 6
1 5 3 6 4 7 8 0 2

2 0 0 0 0 0 0 0 0
0 0 6 3 0 0 0 7 0
5 0 0 0 0 0 1 0 0
9 6 7 4 0 0 0 0 5
8 1 3 0 0 0 0 0 0
4 2 0 7 1 8 9 6 3
3 5 0 0 4 1 6 9 7
6 9 8 2 7 3 5 4 1
0 4 0 0 5 9 2 0 8
*/

