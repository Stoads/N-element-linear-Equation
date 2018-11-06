#include <stdio.h>
#include <malloc.h>

typedef struct MATRIX {
	int rows, cols;
	double** mat;
}ma;
int n;
ma mat,check;
void input() {
	printf("n���������� ������ �� ����\n");
	printf("n? >>");
	scanf("%d", &n);
	check.cols=mat.cols = n;
	check.rows=mat.rows = n + 1;
	mat.mat = (double**)malloc(sizeof(double*)*mat.cols);
	check.mat = (double**)malloc(sizeof(double*)*mat.cols);
	for (int i = 0; i < n; i++) {
		mat.mat[i] = (double*)malloc(sizeof(double)*mat.rows);
		check.mat[i] = (double*)malloc(sizeof(double)*mat.rows);
	}
	for (int i = 0; i < n; i++) {
		printf("%d ��° �� : a1x1+a2x2+a3x3+...an+xn = b\n",i+1);
		printf("a1���� an, b���� ������� �Է� : ");
		for (int j = 0; j <= n; j++) {
			scanf("%lf", &mat.mat[i][j]);
			check.mat[i][j] = mat.mat[i][j];
		}
	}
}



void printMatrix(ma m) {
	for (int i = 0; i < m.cols; i++) {
		for (int j = 0; j < m.rows; j++) {
			printf("%.2lf ", m.mat[i][j]);
		}
		printf("\n");
	}
}

void printResultFromMatrix() {
	for (int i = 0; i < n; i++) {
		printf("%d ��° �������� �� : %lf\n", i+1, mat.mat[i][mat.cols]==-0.0 ? 0 : mat.mat[i][mat.cols]);
	}
}

int gausSoge() {
	for (int i = 0; i < n; i++) {
		printf("�ҰŹ� %2d�� ������ ��� ��Ȳ\n",i);
		printMatrix(mat);
		printf("\n");
		int t = 0;
		for (; i + t < n&&mat.mat[i + t][i] == 0; t++);
		if (i+t==n) 
			return (int)mat.mat[i][mat.cols] ? 1 : 2;
		for (int k = 0; k < n + 1; k++) {
			double tmp = mat.mat[i + t][k];
			mat.mat[i + t][k] = mat.mat[i][k];
			mat.mat[i][k] = tmp;
		}
		for (int k = i + 1; k < n+1; k++) 
			mat.mat[i][k] /= mat.mat[i][i];
		mat.mat[i][i] = 1;
		for (int j = i+1; j < n; mat.mat[j++][i] = 0) 
			for (int k = i + 1; k < n + 1; k++) 
				mat.mat[j][k] = (mat.mat[j][i]*mat.mat[i][k])-mat.mat[j][k];
		for (int j = 0; j < i; mat.mat[j++][i] = 0) 
			for (int k = i + 1; k < n + 1; k++) 
				mat.mat[j][k] = mat.mat[j][k]-(mat.mat[j][i]*mat.mat[i][k]);
			
	}
	return 0;
}

void checkSolve() {
	for (int i = 0; i < mat.cols; i++) {
		double sum=0;
		for (int j = 0; j < mat.rows - 1; j++) {
			sum += check.mat[i][j] * mat.mat[j][mat.rows - 1];
			printf("%lf + ", check.mat[i][j] * mat.mat[j][mat.rows - 1]);
		}
		printf("\b\b= %lf // sum : %lf\n", check.mat[i][check.rows - 1], sum);
		if (sum - 0.000001 > check.mat[i][check.rows - 1]&&check.mat[i][check.rows-1]>sum + 0.000001) {
			printf("Error! : ���� ���� ������ �������� ���� : %lf , %lf\n",check.mat[i][check.rows-1],sum);
			return;
		}
	}
	printf("���ѱ��� �������� ������Ŵ\n");
}

int main() {
	input();
	printf("=============================================================================================\n");
	int k = gausSoge();
	printf("�ҰŹ� ���� �� ��� ��Ȳ\n");
	printMatrix(mat);
	printf("=============================================================================================\n");
	switch (k) {
	case 0:checkSolve(); printResultFromMatrix(); break;
	//case 1:printf("�Ҵ�\n");break;
	//case 2:printf("����\n");break;
	default:
		printf("���� 2�� �̻� Ȥ�� 0��\n"); break;
	}
}