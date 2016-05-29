/*
 * filename: uarray2.c
 * purpose: implementation for a 2D uarray
 * 
 * created by: Taylor Ampatiellos and Isaac Rothschild
 * modified on: February 16th, 2016
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "uarray2.h"
#include "mem.h"

struct UArray2_T {
        int width;
        int height;
        int size;
        
        UArray_T array;
};

#define T UArray2_T

/* Allocates, initializes, and returns a new array of size elements with
 * bounds zero through (width * height) - 1 (unless this value is zero,
 * in which case the array has no elements). 
 * 
 * Exits with CRE if memory cannot be allocated, width or height is < 0,
 * or size is <= 0.
 */
T UArray2_new(int width, int height, int size) 
{
	T uarray2 = ALLOC(sizeof(*uarray2));
	
	uarray2 -> width = width;
	uarray2 -> height = height;
	uarray2 -> size = size;
	
	uarray2 -> array = UArray_new(width * height, size);
	
	return uarray2;
}

/* Deallocates and clears *arr.
 * 
 * Exits with CRE if *arr or arr is NULL.
 */
void UArray2_free(T *arr)
{
	UArray_free(&((*arr) -> array));
	FREE(*arr);
}

/* Returns the number of columns of the two-dimensional uarray. */
int UArray2_width(T arr)
{
	return arr -> width;
}

/* Returns the number of rows of the two-dimensional uarray. */
int UArray2_height(T arr)
{
	return arr -> height;
}

/* Returns the size of the elements in the array. */
int UArray2_size(T arr)
{
	return arr -> size;
}
  
/* Returns a pointer to the element in [col,row]. 
 * 
 * Exits with CRE if col and/or row are out of bounds.
 */
void* UArray2_at(T arr, int col, int row)
{
	int index = (arr -> width * row) + col;
	return UArray_at(arr -> array, index);
}

/* Applies function 'map' to elements of uarray in row-major order. 
 * Function ‘map’ is allowed to change elements of the array.
 */
void UArray2_map_row_major(T arr, 
			   void map(int col, int row, T arr, 
				    void* val, void* cl), void* cl)
{
	for (int r = 0; r < arr -> height; r++) {
		for (int c = 0; c < arr -> width; c++) {
			map(c, r, arr, UArray2_at(arr, c, r), cl);
		}
	}
}

/* Applies function 'map' to elements of uarray in column-major order.
 * Function ‘map’ is allowed to change elements of the array.
 */
void UArray2_map_col_major(T arr, 
			   void map(int col, int row, T arr, 
				    void* val, void* cl), void* cl)
{
	for (int c = 0; c < arr ->  width; c++) {
		for (int r = 0; r < arr -> height; r++) {
			map(c, r, arr, UArray2_at(arr, c, r), cl);
		}
	}
}