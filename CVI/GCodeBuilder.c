#include <ansi_c.h>
#include <math.h>;
#include <stdio.h>;
#include <stdlib.h>;
#include <string.h>
#include <time.h>

void relative_position(double pre_array[][3], int length);

void absolute_position(double pre_array[][3], int length);

void write_gcode(int coord_sys, double array[][3], int length);

double *z_slicer(double array[][3], int length, double slice_size, double slice_level);

int slice_counter(double array[][3], int length, double slice_size, double slice_level);

int main()
{
	//char *file_name = "metalclip1.xyz"; 
	//char *file_name = "inputtest.txt";
	//char *file_name;
	printf("Please enter file name with extension (.txt): ");	
	char file_name[40];
	scanf (" %[^\n]%*c", file_name);
	FILE *fp;
	fp = fopen(file_name, "r");
	char singleLine[40];
	char firstLine[150];
	fgets(firstLine, 150, fp);
	fgets(singleLine, 40, fp);
	int counter = 0;		// Gets the size of the xyz set
	double minx = 0;
	double miny = 0;
	double x1,y1,z1;
	while(!feof(fp))
	{
		fgets(singleLine, 40, fp);
		sscanf(singleLine,"%lf %lf %lf\r\n",&x1,&y1,&z1);
		if (x1 < minx)
		{
			minx = x1;		 
		}
		if (y1 < miny)
		{
			miny = y1;		 
		}
		fgets(singleLine,40,fp);
		counter += 1;
	}
	//printf("Xmin:%f  Ymin:%f\n",minx,miny);
	minx = -minx;
	miny = -miny;
	rewind(fp);
	double xyz[counter][3];
	int n = 0;
	fgets(singleLine, 40, fp); 
	fgets(singleLine, 40, fp);
	while(!feof(fp))
	{
		double x, y, z;
		fgets(singleLine, 40, fp);
		/*sscanf(singleLine,"%lf %lf %lf\n",&x,&y,&z);
		xyz[n][0] = x;
		xyz[n][1] = y;
		xyz[n][2] = z;*/
		sscanf(singleLine,"%lf %lf %lf\r\n",&x,&y,&z);
		xyz[n][0] = x + minx;
		xyz[n][1] = y + miny;
		xyz[n][2] = z;
		n += 1;
		fgets(singleLine, 40, fp); 
	}
	fclose(fp);
	//double slice_level = 0.18;
	//double slice_size = 0.006;
	//int z_count = slice_counter(xyz,counter,slice_size,slice_level);
	//printf("%d\n\n",z_count);
	//double *array_slice[][3] = z_slicer(xyz,z_count,slice_size,slice_level);
	/*for(int j = 0; j < z_count; j++)
	{
		printf("%f %f %f\n",*(array_slice[j]),*(array_slice[j]+1),*(array_slice[j]+2));
	}  */
	int input = 0;
	printf("\n\nPlease enter '1' for Absolute and '2' for Relative: ");	
	scanf(" %d", &input);
	if(input == 1)
	{
		absolute_position(xyz, counter);
	}
	else if(input == 2)
	{
		relative_position(xyz, counter); 
	}
	else
		printf("You did not enter a valid input!");
	printf("Press any key and enter to exit: ");
	scanf(" %d", &input);		// Wait for user to see input
	return 0;
}


void relative_position(double array[][3], int length)
{
	int coord_sys = 2;		// Sets coordinate system as relative positioning
	double xinit,xend,yinit,yend,zinit,zend;
	double new_array[length][3];
	double delx = *(array[0]);
	double dely = *(array[0]+1);
	double delz = *(array[0]+2);
	new_array[0][0] = delx;
	new_array[0][1] = dely;
	new_array[0][2] = delz;
	for (int i=1;i<(length);i++)
	{
		xinit = *(array[i-1]);
		xend  = *(array[i]);
		yinit = *(array[i-1]+1);
		yend  = *(array[i]+1);
		zinit = *(array[i-1]+2);
		zend  = *(array[i]+2);
		delx  = xend - xinit;
		dely  = yend - yinit;
		delz  = zend - zinit;
		new_array[i][0] = delx;
		new_array[i][1] = dely;
		new_array[i][2] = delz;
	}
	write_gcode(coord_sys, new_array, length);
	return;
}

void absolute_position(double array[][3], int length)
{
	int coord_sys = 1;		// Sets coordinate system as absolute positioning  
	write_gcode(coord_sys, array, length);
	return;
}

void write_gcode(int coord_sys, double array[][3], int length)
{
	FILE *fpointer;
	int g;					// Int for storing G90 or G91
	int spacing = 5;		// Spacing variable for line numbers
	int spacing_val = 0;	// Line number initialization
	double f =	40.00;		// Char for storing feed rate 
	int d = 1;			// Integer for storing dwell time after each step
	int dwell = 04;
	time_t t = time(NULL);  // Time setup
	struct tm tm = *localtime(&t);	// Get time		
	if(coord_sys == 1)		// Absolute coordinate system GCode
	{
		g = 90;				// G90 is code for absolute positioning
	}
	else					// Relative coordinate system Gcode
	{
		g = 91;				// G91 is code for relative positioning
	}
	fpointer = fopen("outfile.txt", "w");
	fprintf(fpointer,"(Time Created: %d-%d-%d %d:%02d:%02d)\n",
								tm.tm_mon+1,
								tm.tm_mday,
								tm.tm_year+1900,
								tm.tm_hour,
								tm.tm_min,
								tm.tm_sec);
	fprintf(fpointer,"(Post: Sandia Object GCode Generator)\n");  
	fprintf(fpointer,"(5-Axis CNC Scanning Machine)\n");  
	fprintf(fpointer,"N%05d G90\t\t\t\t;\tG90 -> Abs; G91-> Rel\n",spacing_val+1);	// First line and setup function
	fprintf(fpointer,"N%05d G00 X0.000 Y0.000 Z0.000\t\t;\tMove to Initial Position\n",spacing_val+2);		// Filler line for user readability 
	fprintf(fpointer,"N%05d G%02d P%d\t\t\t\t;\tDwell %d (milli)seconds\n",spacing_val+3,dwell,d,d);
	fprintf(fpointer,"N%05d G%d\t\t\t\t;\tBegin Operation\n",spacing_val+4,g);		// Filler line for user readability  
	for(int i = 0; i < length; i++)
	{
		spacing_val  = (i+1)*spacing;
		fprintf(fpointer,"N%05d G01 X%f Y%f F%f\n",spacing_val,*(array[i]),*(array[i]+1),f);
		fprintf(fpointer,"N%05d G%02d P%d\t\t\t\t;\tDwell %d (milli)seconds\n",spacing_val+2,dwell,d,d);
	}
	spacing_val += 5;
	fprintf(fpointer,"N%05d G00 X0.000 Y0.000 Z0.000\t\t;\tMove back to Initial Position\n",spacing_val);
	fprintf(fpointer,"N%05d\n",spacing_val+1);
	fprintf(fpointer,"N%05d M30\t\t\t\t;\tEnd of GCode file",spacing_val+2);
	fclose(fpointer);
	printf("\n\nSee file 'outfile.txt' to view GCode generated.\n\n\n");
	return;
}

int slice_counter(double array[][3], int length, double slice_size, double slice_level)
{
	/*
input:
	array - nx3 matrix containing full set of coordinates
	length - size of array
	slice_size - width of z coordinate slice
	slice_level - center of level to compare to z coordinate in each element's z coordinate
output:
	count - the number of z coordinates in array that fall within specified z range to z depth
	*/
	int count = 0;
	//double z, value;
	for(int i = 0; i < length; i++)
	{
		if(fabs(*(array[i]+2) - slice_level)< (slice_size/2))
		{
			//z = *(array[i]+2);
			//value = fabs(z - slice_level);
			count += 1;
		}
	}
	return count;
}

double *z_slicer(double array[][3], int length, double slice_size, double slice_level)
{
	double array_slice[length][3];
	int count = 0;
	for(int i = 0; i < length; i++)
	{
		if(fabs(*(array[i]+2) - slice_level)< (slice_size/2))
		{
			array_slice[count][0] = *(array[i]);
			array_slice[count][1] = *(array[i]+1);
			array_slice[count][2] = *(array[i]+2);
			count += 1;
		}
	}
	return *array_slice;
}
