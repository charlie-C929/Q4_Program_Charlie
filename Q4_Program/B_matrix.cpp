#include "shapeFuncAndDiff.hpp"
#include "ja.hpp"



double** BMatrix(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double s, double t)
{
	static double** B;							//			static			
	double J[2][2];
	double Ns[8];

	for (int i = 0; i < 8; i++)
	{
		Ns[i] = *(DiffShape(s, t) + i);
		//cout << Ns[i] << "  ";				//����
	}
	//cout << endl;							//����
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			J[i][j] = *(*(Jacobi(x1, y1, x2, y2, x3, y3, x4, y4, s, t) + i) + j);

			//cout << J[i][j] << endl;			//��������
		}
	}

	//			���ſɱȾ�������ʽ

	double detJ = 0;
	detJ = J[0][0] * J[1][1] - J[1][0] * J[0][1];
	//cout<<(detJ = J[0][0] * J[1][1] - J[1][0] * J[0][1])<<endl; //����



	//		��ʼ�����ξ���
	B = (double**)malloc(3 * sizeof(double));//������Էŵ���3��˫���ȸ��������ڴ�ռ䣬���ص��Ƕ���ָ������

	for (int i = 0; i < 3; i++)
	{
		B[i] = (double*)malloc(8 * sizeof(double));
		for (int j = 0; j < 8; j++)
		{
			B[i][j] = 0;
		}
	}



	//		�󼸺ξ���
	//		BΪ3x8����

	B[0][0] = (J[1][1] * Ns[0] - J[0][1] * Ns[4]) / detJ;
	B[0][2] = (J[1][1] * Ns[1] - J[0][1] * Ns[5]) / detJ;
	B[0][4] = (J[1][1] * Ns[2] - J[0][1] * Ns[6]) / detJ;
	B[0][6] = (J[1][1] * Ns[3] - J[0][1] * Ns[7]) / detJ;
	B[1][1] = (-J[1][0] * Ns[0] + J[0][0] * Ns[4]) / detJ;
	B[1][3] = (-J[1][0] * Ns[1] + J[0][0] * Ns[5]) / detJ;
	B[1][5] = (-J[1][0] * Ns[2] + J[0][0] * Ns[6]) / detJ;
	B[1][7] = (-J[1][0] * Ns[3] + J[0][0] * Ns[7]) / detJ;

	for (int i = 0; i < 8; i = i + 2)
	{
		B[2][i] = B[1][i + 1];
		B[2][i + 1] = B[0][i];

	}
	/*			//��������
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << B[i][j] << "  ";
		}
		cout << endl;
	}
	*/

	return B;



}