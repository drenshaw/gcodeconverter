#include <math.h>;
#include <stdio.h>;
#include <stdlib.h>;

void relative_position(double pre_array[], double post_array[], int length);

void absolute_position(double pre_array[], double post_array[], int length);



//FILE *fp;

int main()
{
	//fp = fopen("textfile.txt");
	//double array_from_file[] = {1, 5, 2, 8, 3, 7, 4, 8, 3, 7}; 
	//int a[3][4] = {0,1,2,3,4,5,6,7,8,9,10,11};
	double pre_array[10][2]={
								{1,0},
								{2,6},
								{4,0},
								{5,5},
								{8,8},
								{3,2},
								{1,2},
								{8,7},
								{3,7},
								{4,4}
								};
	int lenarray  = sizeof(pre_array)/sizeof(double)/2;
	double new_array[lenarray][2]; 
	//relative_position(array_from_file, new_array, lenarray);
	double xinit = 0;
	double xend  = 0;
	double yinit = 0;
	double yend  = 0;
	double delx = pre_array[0][0];
	double dely = pre_array[0][1]; 
	new_array[0][0] = delx;
	new_array[0][1] = dely;
	printf("[%f\t,\t%f] \n",delx,dely);
	for (int i=1;i<(lenarray);i++)
	{
		xinit = pre_array[i-1][0];
		xend  = pre_array[i][0];
		yinit = pre_array[i-1][1];
		yend  = pre_array[i][1];
		delx  = xend - xinit;
		dely  = yend - yinit;
		new_array[i][0] = delx;
		new_array[i][1] = dely; 
		printf("[%f\t,\t%f] \n",delx,dely); 
	}
	getchar();
	return 0;
}


void relative_position(double pre_array[10], double post_array[10], int length)
{
	return;
}

void absolute_position(double pre_array[], double post_array[], int length)
{
	return;
}
