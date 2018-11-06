#include <stdio.h>
#include <malloc.h>

typedef struct MATRIX {
	int rows, cols;
	double** mat;
}ma;
int n;
ma mat,check;
void input() {
	printf("n원일차연립 방정식 근 계산기\n");
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
		printf("%d 번째 열 : a1x1+a2x2+a3x3+...an+xn = b\n",i+1);
		printf("a1부터 an, b까지 순서대로 입력 : ");
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
		printf("%d 번째 미지수의 값 : %lf\n", i+1, mat.mat[i][mat.cols]==-0.0 ? 0 : mat.mat[i][mat.cols]);
	}
}

int gausSoge() {
	for (int i = 0; i < n; i++) {
		printf("소거법 %2d번 진행후 행렬 상황\n",i);
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
			printf("Error! : 구한 근이 방정식 만족하지 않음 : %lf , %lf\n",check.mat[i][check.rows-1],sum);
			return;
		}
	}
	printf("구한근이 방정식을 만족시킴\n");
}

int main() {
	input();
	printf("=============================================================================================\n");
	int k = gausSoge();
	printf("소거법 종료 후 행렬 상황\n");
	printMatrix(mat);
	printf("=============================================================================================\n");
	switch (k) {
	case 0:checkSolve(); printResultFromMatrix(); break;
	//case 1:printf("불능\n");break;
	//case 2:printf("부정\n");break;
	default:
		printf("근이 2개 이상 혹은 0개\n"); break;
	}
}