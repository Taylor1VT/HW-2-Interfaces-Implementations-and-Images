/*
 * filename: uarray2.h
 * 
 * created by: Taylor Ampatiellos and Isaac Rothschild
 * modified on: February 16th, 2016
 * 
 */

#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED

#include "uarray.h"

#define T UArray2_T
typedef struct T *T;

/* Allocates, initializes, and returns a new array of size elements with
 * bounds zero through (width * height) - 1 (unless this value is zero,
 * in which case the array has no elements). 
 * 
 * Exits with CRE if memory cannot be allocated, width or height is < 0,
 * or size is <= 0.
 */
T UArray2_new(int width, int height, int size);

/* Deallocates and clears *arr.
 * 
 * Exits with CRE if *arr or arr is NULL.
 */
void UArray2_free(T *arr);

/* Returns the number of columns of the two-dimensional uarray. */
int UArray2_width(T arr);

/* Returns the number of rows of the two-dimensional uarray. */
int UArray2_height(T arr);

/* Returns the size of the elements in the array. */
int UArray2_size(T arr);
  
/* Returns a pointer to the element in [col,row]. 
 * 
 * Exits with CRE if col and/or row are out of bounds.
 */
void* UArray2_at(T arr, int col, int row);

/* Applies function 'map' to elements of uarray in row-major order. 
 * Function ‘map’ is allowed to change elements of the array.
 */
void UArray2_map_row_major(T arr, 
			   void map(int col, int row, T arr, 
				    void* val, void* cl), void* cl);

/* Applies function 'map' to elements of uarray in column-major order.
 * Function ‘map’ is allowed to change elements of the array.
 */
void UArray2_map_col_major(T arr, 
			   void map(int col, int row, T arr, 
				    void* val, void* cl), void* cl);
        
#undef T
#endif /*UARRAY2*/