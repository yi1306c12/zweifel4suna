
#ifndef USEFUL_UTILS_H
#define USEFUL_UTILS_H

#include"stdlib.h"
#include"stdio.h"
#include<assert.h>

#ifdef NOPRINTF

#define printf(x...)

#endif

inline double xrand(double min, double max);

inline void printMatrix(float** matrix, int size);
inline void printMatrix(int** matrix, int size);
inline void printMatrix(float** matrix, int lines, int columns);
inline void printMatrix(int** matrix, int lines, int columns);

inline void printArray(int* array, int size);
inline void printArray(float* array, int size);
inline void printArray(double* array, int size);
inline void printArrayAndIndex(float* array, int size); //print array together with an array of counters with index

//inline float fast_log2(float value);

inline int floor_log2(unsigned int x);

inline float fast_ln(const float &val);













/*log in base 2
inline float fast_log2(float value)
{
	int *const exp_ptr = reinterpret_cast <int * (&val);
	int x = *exp_ptr;
	const int log_2 = ((x 23) & 255) - 128;
	x &= ~(255 << 23);
	x += 127 << 23;
	*exp_ptr = x;

	val = ((-1.0f/3)*val + 2)*val - 2.0f/3;   // (1)

	return (val + log_2);

}
*/
//natural log
/*inline float fast_ln(const float &val)
{
	return (fast_log2(val)*0.69314718f);
}
*/

/*float fast_log2(float f) 
{
  //assert( sizeof(f) == sizeof(int) );
  //assert( sizeof(f) == 4 );
  //int i = (*(int *)&f);
  //return (((i&0x7f800000)>>23)-0x7f)+(i&0x007fffff)/(float)0x800000;
} 
*/

inline int floor_log2(unsigned int x) 
{
	int r = 0;
	while((x >> r) != 0) 
	{
		r++;
	}
	return r-1; // returns -1 for x==0, floor(log2(x)) otherwise
}


//return pseudo random number between min and max [min, max). The maximum value is not included.
inline double xrand(double min, double max)
{
	double random_number= ((double)rand()/((double)RAND_MAX + (double)1.0f))*(max-min) + min;

	return random_number;
}

//print a square matrix 
inline void printMatrix(float** matrix, int size)
{
	int i,j;

	printf("Matrix:\n");
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			printf("%4.2f ", matrix[i][j]);

		}
			
		printf("\n");
	}
		
	printf("\n");
}

//print a square matrix 
inline void printMatrix(int** matrix, int size)
{
	int i,j;

	printf("Matrix:\n");
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			printf("%d ", matrix[i][j]);

		}
			
		printf("\n");
	}
		
	printf("\n");
}

//print a matrix 
inline void printMatrix(float** matrix, int lines, int columns)
{
	int i,j;

	printf("Matrix:\n");
	for(i=0;i<lines;i++)
	{
		for(j=0;j<columns;j++)
		{
			printf("%.2f ", matrix[i][j]);

		}
			
		printf("\n");
	}
		
	printf("\n");
}

//print a matrix 
inline void printMatrix(int** matrix, int lines, int columns)
{
	int i,j;

	printf("Matrix:\n");
	for(i=0;i<lines;i++)
	{
		for(j=0;j<columns;j++)
		{
			printf("%.d ", matrix[i][j]);

		}
			
		printf("\n");
	}
		
	printf("\n");
}

inline void printArrayAndIndex(float* array, int size)
{
	int i;

	printf("Array:\n");
	for(i=0; i<size; i++)
	{
		printf("%d,%.1f ", i,array[i]);
		
	}
	
	printf("\n");
	printf("\n");
}

//print vector
inline void printArray(float* array, int size)
{
	int i;

	printf("Array:\n");
	for(i=0; i<size; i++)
	{
		printf("%.2f ", array[i]);
		
	}
	
	printf("\n");
	printf("\n");
}

//print vector
inline void printArray(double* array, int size)
{
	int i;

	printf("Array:\n");
	for(i=0; i<size; i++)
	{
		printf("%f ", array[i]);
		
	}
	
	printf("\n");
	printf("\n");
}

//print vector
inline void printArray(int* array, int size)
{
	int i;

	printf("Array:\n");
	for(i=0; i<size; i++)
	{
		printf("%d ", array[i]);
		
	}
	
	printf("\n");
	printf("\n");
}

#endif
