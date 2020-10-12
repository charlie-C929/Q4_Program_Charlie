
/*
        程序作者：Max_Zhang
        程序功能：等参单元四节点，Q4_Program 主程序
*/

#include <iostream>
#include <vector>
#include "readData.hpp"

using namespace std;

//int main(int argc, char* argv[])
//{
//    
//    vector<vector<double>> a;  // a是应力
//
//    a = readData_4();
//    for (int i = 0; i < a.size(); i++)
//    {
//        cout << a[i][0] << " " << a[i][1] << endl;
//    }
//
//  
//    system("pause");
//
//
//    return 0;
//
//}



/*
				解方程组,用Cholesky分解法
				有精力的话就改成改进型的cholesky分解法
	*/

	//			定义L

double** L;
L = (double**)malloc(2 * countGrid * sizeof(double));
for (i = 0; i < 2 * countGrid; i++)
{
	L[i] = (double*)malloc(2 * countGrid * sizeof(double));
	for (j = 0; j < 2 * countGrid; j++)
	{
		L[i][j] = 0;
	}
}

/*
			cholesky分解法,经过验证，此分解法已经没有问题，此方法弃用。总刚矩阵还是不对，依然是非正定
			使用改进的cholesky分解法
			（1）求 K 的Cholesky分解，得到 L*Lt = K
			（2）求解 L*Y = F，得到 Y
			（3）求解 Lt* X = Y，得到 X
*/

L[0][0] = pow(K[0][0], 0.5);



//			第一列的元素
//			i 是行

double sum = 0, sum1 = 0;

for (i = 1; i < 2 * countGrid; i++)
{
	L[i][0] = K[i][0] / L[0][0];

}

//			已知第一列，求余下的列,第一列求对了
//			j是列



for (j = 1; j < 2 * countGrid; j++)
{

	sum = 0;
	//		先求sum
	for (i = 0; i < j; i++)
	{
		sum = sum + L[j][i] * L[j][i];
	}

	L[j][j] = pow((K[j][j] - sum), 0.5);


	for (k = j + 1; k < 2 * countGrid; k++)
	{
		sum1 = 0;
		for (i = 0; i < j; i++)
		{
			sum1 = sum1 + L[k][i] * L[j][i];
		}

		L[k][j] = (K[k][j] - sum1) / L[j][j];

	}
}

/*
			转置 L 得到 Lt
*/


double** Lt;
Lt = (double**)malloc(2 * countGrid * sizeof(double));
for (i = 0; i < 2 * countGrid; i++)
{
	Lt[i] = (double*)malloc(2 * countGrid * sizeof(double));
	for (j = 0; j < 2 * countGrid; j++)
	{
		Lt[i][j] = 0;
	}
}

for (i = 0; i < 2 * countGrid; i++)
{
	for (j = 0; j < 2 * countGrid; j++)
	{
		Lt[i][j] = L[j][i];
	}
}

/*
			输出 L 文件做检查
*/
/*
ofstream fLout;
fLout.open("E:\\text1.txt", ios::out);
if (!fLout)
{
	cout << "不能创建L输出文件" << endl;
}
for (i = 0; i < countGrid * 2; i++)
{
	for (j = 0; j < countGrid * 2; j++)
	{
		fLout << L[i][j] << "\t";
	}
	fLout << endl;
}
*/
/*
			L 已经求出了，下面开始求 Y
*/

double* Y;
Y = (double*)malloc(2 * countGrid * sizeof(double));
for (i = 0; i < 2 * countGrid; i++)
{
	Y[i] = 0;
}

for (i = 0; i < 2 * countGrid; i++)
{
	sum = 0;
	for (j = 0; j < i; j++)
	{
		sum = sum + L[i][j] * Y[j];
	}
	Y[i] = (F[i] - sum) / L[i][i];
	//cout << Y[i] << endl;
}

/*
				求X
*/

long double* X;
X = (long double*)malloc(2 * countGrid * sizeof(long double));
for (i = 0; i < 2 * countGrid; i++)
{
	X[i] = 0;
}

for (i = 2 * countGrid - 1; i >= 0; i--)
{
	sum = 0;
	for (j = 2 * countGrid - 1; j > i; j--)
	{
		sum = sum + Lt[i][j] * X[j];
	}
	X[i] = (Y[i] - sum) / Lt[i][i];
	//cout << X[i] << endl;
}


/*

			至此，位移矩阵X求出，但是还有很多问题
			上面的方法不够精确，已弃用，数据已经被下面改进型的cholesky分解法代替
*/

/*

			使用改进型的cholesky算法
			因为在计算过程中有比较大的误差，所以需要后边误差处理
			但是刚度矩阵是qi

*/

double** D;				//		D 是正对角矩阵

//						初始化D

D = (double**)malloc(2 * countGrid * sizeof(double));
for (i = 0; i < 2 * countGrid; i++)
{
	D[i] = (double*)malloc(2 * countGrid * sizeof(double));
	for (j = 0; j < 2 * countGrid; j++)
	{
		D[i][j] = 0;
	}

}
//					初始化 L
for (i = 0; i < 2 * countGrid; i++)
{
	for (j = 0; j < 2 * countGrid; j++)
	{
		L[i][j] = 0;
	}
}
//					初始化 Lt
for (i = 0; i < 2 * countGrid; i++)
{
	for (j = 0; j < 2 * countGrid; j++)
	{
		Lt[i][j] = 0;
	}
}


//			k 是列 , j 是行

for (k = 0; k < 2 * countGrid; k++)
{
	sum = 0;
	for (int m = 0; m <= k - 1; m++)
	{
		sum = sum + L[k][m] * L[k][m] * D[m][m];
	}

	D[k][k] = K[k][k] - sum;

	for (j = k; j < 2 * countGrid; j++)
	{
		sum1 = 0;
		for (int m = 0; m < k - 1; m++)
		{
			sum1 = sum1 + L[j][m] * L[k][m] * D[m][m];
		}

		L[j][k] = (K[j][k] - sum1) / D[k][k];

	}
	//cout <<D[k][k]<< endl;
}



for (k = 0; k < 2 * countGrid; k++)
{
	L[k][k] = 1;
}

for (i = 0; i < 2 * countGrid; i++)
{
	for (j = 0; j < 2 * countGrid; j++)
	{
		Lt[i][j] = L[j][i];
		//cout << Lt[i][j] << "  ";
	}
	//cout << endl;
}


/*
		求Y
*/

for (i = 0; i < 2 * countGrid; i++)
{
	Y[i] = 0;
}

for (i = 0; i < 2 * countGrid; i++)
{
	sum = 0;
	for (j = 0; j < i; j++)
	{
		sum = sum + L[i][j] * Y[j];
	}
	Y[i] = (F[i] - sum) / L[i][i];
	//cout << Y[i] << endl;
}

double** DLt;				//		D 是正对角矩阵

//						初始化D

DLt = (double**)malloc(2 * countGrid * sizeof(double));
for (i = 0; i < 2 * countGrid; i++)
{
	DLt[i] = (double*)malloc(2 * countGrid * sizeof(double));
	for (j = 0; j < 2 * countGrid; j++)
	{
		DLt[i][j] = 0;
	}

}

for (i = 0; i < 2 * countGrid; i++)
{
	for (j = 0; j < 2 * countGrid; j++)
	{
		for (k = 0; k < 2 * countGrid; k++)
		{
			DLt[i][j] = DLt[i][j] + D[i][k] * Lt[k][j];

		}
		//cout << DLt[i][j] << "  ";

	}
	//cout << endl;
}



for (i = 0; i < 2 * countGrid; i++)
{
	X[i] = 0;
}

for (i = 2 * countGrid - 1; i >= 0; i--)
{
	sum = 0;
	for (j = 2 * countGrid - 1; j > i; j--)
	{
		sum = sum + DLt[i][j] * X[j];
	}
	X[i] = (Y[i] - sum) / DLt[i][i];

}
for (i = 0; i < 2 * countGrid; i++)
{
	cout << X[i] << endl;
}

/*
			将结果输出到文件中，输出单元节点坐标和节点位移，好画图
*/


ofstream fLout;
fLout.open("E:\\text1.txt", ios::out);
if (!fLout)
{
	cout << "不能创建L输出文件" << endl;
}
fLout << "weiyi" << endl;
for (i = 0; i < countGrid * 2; i++)
{
	fLout << X[i] << endl;
}

fLout << "输出力以验证结果正确性" << endl;

for (i = 0; i < 2 * countGrid; i++)
{
	fLout << i << "\t" << F[i] << endl;
}


for (i = 0; i < 2 * countGrid; i++)
{
	cout << F[i] << endl;
}


/*

			老师给的umfpack文件已经包含进来了，现在探索怎么用
			失败了

*/
/*

			用jacobi迭代法

*/


double s1, s2;
k = 0;

for (i = 0; i < 2 * countGrid; i++)
{
	X[i] = 0;
}
do
{
	s2 = 0;
	k = k + 1;
	for (i = 0; i < 2 * countGrid; i++)
	{
		s1 = 0;
		for (j = 0; j < 2 * countGrid; j++)
		{
			if (i == j)
				continue;
			s1 += K[i][j] * X[j];
		}
		Y[i] = (F[i] - s1) / K[i][i];
		s2 += fabs(X[i] - Y[i]);
	}
	if (s2 < 1e-20)
		cout << "迭代次数K=" << k << endl;
	if (k > 10000)
	{
		cout << "不收敛" << endl;
	}
	for (i = 0; i < 2 * countGrid; i++)
	{
		X[i] = Y[i];
	}
	/*
	for (i = 0; i < 2*countGrid; i++)
	{
		cout << X[i] << "  ";
	}
	*/
} while (s2 > 1e-20);


for (i = 0; i < 2 * countGrid; i++)
{
	cout << X[i] << "  ";
}





infile.close();
infile1.close();
fLout.close();
fout.close();
return 0;

