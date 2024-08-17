#include <iostream>
using namespace std;
const int N = 2;
double f1(double x, double y)
{
	return (x * x + y * y * y - 4);
}
double derXf1(double x, double y)
{
	return (2 * x);
}
double derYf1(double x, double y)
{
	return (3 * y * y);
}
double f2(double x, double y)
{
	return (x / y - 2);
}
double derXf2(double x, double y)
{
	return 1 / y;
}
double derYf2(double x, double y)
{
	return (-x / (y * y));
}
void Gauss(double A[N][N + 1], double X[N])
{
	int i, j, k, ind;
	double f, max, obm;
	for (i = 0; i < N - 1; i++)
	{
		ind = i;
		for (j = i + 1; j < N; j++)
		{
			max = abs(A[i][i]);
			if (max < abs(A[j][i]))
			{
				max = abs(A[j][i]);
				ind = j;
			}
		}
		if (ind != i)
		{
			for (j = 0; j < N + 1; j++)
			{
				obm = A[i][j];
				A[i][j] = A[ind][j];
				A[ind][j] = obm;
			}
			for (j = 0; j < N; j++)
			{
				for (k = 0; k < N + 1; k++)
					cout << " " << A[j][k] << "\t";
				cout << endl;
			}
		}
		cout << endl;

		for (j = i + 1; j < N; j++)
		{
			f = A[j][i] / A[i][i];
			for (k = 0; k < N + 1; k++)
				A[j][k] = -(f * A[i][k]) + A[j][k];
		}
	}

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N + 1; j++)
			cout << " " << A[i][j] << "\t";
		cout << endl;
	}

	for (i = N - 1; i >= 0; i--)
	{
		f = A[i][N];
		for (j = i + 1; j < N; j++)
			f -= A[i][j] * X[j];
		X[i] = f / A[i][i];
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int a = 1, i, j, k;
	double eps = pow(10, -8), x0[N] = { 2, 1 }, x1[N], y[N], W[N][N], F[N], max, f, A[N][N + 1];
	cout << " eps = " << eps << endl;
	do
	{
		cout << endl << " Шаг " << a << ":\n F(x" << a - 1 << "):" << endl;
		F[0] = f1(x0[0], x0[1]);
		F[1] = f2(x0[0], x0[1]);

		for (i = 0; i < N; i++)
			cout << " " << F[i] << endl;
		cout << endl << " W(x" << a - 1 << "):" << endl;

		W[0][0] = derXf1(x0[0], x0[1]);
		W[0][1] = derYf1(x0[0], x0[1]);
		W[1][0] = derXf2(x0[0], x0[1]);
		W[1][1] = derYf2(x0[0], x0[1]);

		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
				cout << " " << W[i][j] << "\t";
			cout << endl;
		}
		cout << endl << " СЛАУ:" << endl;
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				A[i][j] = W[i][j];
				cout << " " << A[i][j] << "\t";
			}
			cout << " | ";
			A[i][N] = F[i];
			cout << A[i][N] << endl;
		}

		Gauss(A, y);
		cout << endl << " y[" << a << "]:" << endl;
		for (i = 0; i < N; i++)
			cout << " " << y[i] << endl;

		cout << endl << " x[" << a << "]:" << endl;
		for (i = 0; i < N; i++)
		{
			x1[i] = x0[i] - y[i];
			cout << " " << x1[i] << endl;
		}

		max = 0;
		for (i = 0; i < N; i++)
		{
			x0[i] = abs(x1[i] - x0[i]);
			if (max < x0[i])
				max = x0[i];
			x0[i] = x1[i];
		}
		cout << "_______________" << endl;
		a++;
	} while (!(max < eps));
	return 0;
}