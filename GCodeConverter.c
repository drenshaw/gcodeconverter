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
	int a[3][4] = {0,1,2,3,4,5,6,7,8,9,10,11};
	double array_from_file[10][2]={
								{1,0},
								{2,0},
								{4,0},
								{5,0},
								{8,0},
								{3,0},
								{1,0},
								{8,0},
								{3,0},
								{4,0}
								};
	int lenarray  = sizeof(array_from_file)/sizeof(double);
	double new_array[lenarray][2]; 
	relative_position(array_from_file, new_array, lenarray);
	getchar();
	return 0;
}


void relative_position(double pre_array[10][2], double post_array[10][2], int length)
{
	int xinit = 0;
	int xend  = 0;
	int yinit = 0;
	int yend  = 0;
	double delx = pre_array[0][0];
	double dely = pre_array[0][1]; 
	post_array[0][0] = delx;
	post_array[0][1] = dely;
	printf("%f \n",delx);
	for (int i=1;i<(length);i++)
	{
		xinit = pre_array[i-1];
		xend  = pre_array[i];
		yinit = pre_array[i-1];
		yend  = pre_array[i];
		delx  = xend - xinit;
		dely  = yend - yinit;
		post_array[i][0] = delx;
		post_array[i][1] = dely; 
		printf("[%f,\t%f] \n",delx,dely); 
	}
}

void absolute_position(double pre_array[], double post_array[], int length)
{
	  return;
}
