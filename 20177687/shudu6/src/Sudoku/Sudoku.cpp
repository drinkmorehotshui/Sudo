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
int s[111][111];//����
int n, m;//���� ����
int flag = 0;//�ɹ����
FILE* fp1;
FILE* fp2;
bool check2(int x, int r, int c, int val)//�ڶ�����֤���� �жϹ� 
{
	int a = x / m;
	int b = x % m;
	a = a / r * r;//��
	b = b / c * c;//��
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
bool check(int x, int val)//��һ����֤���� ��֤�������� 4 6 8 9ʱ��Ҫ�жϹ� 
{
	int r = x / m;
	int c = x % m;
	for (int i = 0; i<m; i++)//�� 
	{
		if (s[r][i] == val)
		{
			return 0;
		}
	}
	for (int i = 0; i<m; i++)//�� 
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
void output()//������� 
{
	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j<m; j++)
		{
			fprintf(fp2, "%d", s[i][j]);//������ļ�
			if (j < m - 1)
			{
				fprintf(fp2, " ");
			}
			
		}
		fprintf(fp2, "\n");
	}
}
void dfs(int x)//dfs���� �ݹ����� 
{
	if (flag)//����Ѿ���� ֱ�ӷ��� 
	{
		return;
	}
	if (x == m * m)//�Ѿ����� 
	{
		output();
		flag = 1;
		return;
	}
	int r = x / m;//��
	int c = x % m;//��
	if (!s[r][c])//û������������ 
	{
		for (int i = 1; i <= m; i++)
		{
			if (check(x, i))
			{
				s[r][c] = i;
				dfs(x + 1);
				s[r][c] = 0;//���� 
			}
		}
	}
	else//�Ѿ����������� 
	{
		dfs(x + 1);
	}
}
int main(int argc, char *argv[])
{
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);
	m = atoi(argv[2]);//��ȡ����
	n = atoi(argv[4]);
	char *inputname = argv[6];
	char *outputname= argv[8];
	fp1 = fopen(inputname, "r");//�������ļ�
	if (fp1 == NULL)
	{
		return -1;
	}
	fp2 = fopen(outputname, "w");//������ļ�������ļ�
	if (fp2 == NULL) //
	{
		return -1;
	}
	fclose(fp2);
	while (n--)
	{
		mst(s, 0);//��ʼ�� 
		flag = 0;
		for (int i = 0; i<m; i++)//���� 
		{
			for (int j = 0; j<m; j++)
			{
				fscanf(fp1, "%d", &s[i][j]);//�ļ�����
			}
		}
		fp2 = fopen(outputname, "a");//������ļ�
		dfs(0);	//��ʼ���� 
		if (n > 0)
		{
			fprintf(fp2, "\n");//������ļ�

		}
		fclose(fp2);//�ر�����ļ�
	}
	fclose(fp1);//�ر������ļ�
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

