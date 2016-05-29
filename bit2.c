/*
 * filename: bit2.c
 * purpose: implementation of 2D bit array
 * 
 * created by: Taylor Ampatiellos and Isaac Rothschild
 * modified on: February 11th, 2016
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "bit2.h"
#include "mem.h"

#define T Bit2_T

struct Bit2_T {
	int width;
	int height;
	
	Bit_T arr;
};

/* Returns a pointer to new two-dimensional array of bits, 
 *      all initialized to 0.
 *      
 * Exits with CRE if memory cannot be allocated or if width or height is <= 0.
 */
T Bit2_new(int width, int height)
{  
	T bit2 = ALLOC(sizeof(*bit2));
	
	bit2 -> width = width;
	bit2 -> height = height;
	
	bit2 -> arr = Bit_new(width * height);
	
	return bit2;
}

/* Deallocates and clears *bit_arr.
 * 
 * Exits with CRE if *bit_arr or bit_arr are NULL.
 */
void Bit2_free(T *bit_arr)
{
	Bit_free(&((*bit_arr) -> arr));
	FREE(*bit_arr);
}

/* Returns the number of ‘ON’ bits in bit_array. */
int Bit2_count(T bit_arr)
{
	return Bit_count(bit_arr -> arr);
}

/* Returns the number of columns of the two-dimensional bit array. */
int Bit2_width(T bit_arr)
{
	return bit_arr -> width;
}

/* Returns the number of rows of the two-dimensional bit array. */
int Bit2_height(T bit_arr)
{
	return bit_arr -> height;
}

/* Returns the status of bit n.
 * 
 * Exits with CRE if col and/or row are out of bounds.
 */
int Bit2_get(T bit_arr, int col, int row)
{
	int index = (bit_arr -> width * row) + col;
	return Bit_get(bit_arr -> arr, index);
}

/* Sets the status of the bit at location n. Bit can only be 0 or 1.
 *
 * Exits with CRE if bit is not 0 or 1, or if col and/or row are out of bounds.
 */
int Bit2_put(T bit_arr, int col, int row, int bit)
{
	int index = (bit_arr -> width * row) + col;
	return Bit_put(bit_arr -> arr, index, bit);
}

/* Applies function 'map' to elements of bit_arr in row-major order. 
 * Function ‘map’ is allowed to change elements of the array.
 */
void Bit2_map_row_major(T bit_arr, 
			void map(int c, int r, T bit_arr, int val, void* cl),
                        void* cl)
{
	for (int r = 0; r < bit_arr -> height; r++) {
		for (int c = 0; c < bit_arr -> width; c++) {
			map(c, r, bit_arr, Bit2_get(bit_arr, c, r), cl);
		}
	}
}
/* Applies function 'map' to elements of bit_arr in column-major order.
 * Function ‘map’ is allowed to change elements of the array.
 */
void Bit2_map_col_major(T bit_arr,
                        void map(int c, int r, T bit_arr, int val, void* cl),
			void* cl)
{
	for (int c = 0; c < bit_arr -> width; c++) {
		for (int r = 0; r < bit_arr -> height; r++) {
			map(c, r, bit_arr, Bit2_get(bit_arr, c, r), cl);
		}
	}
}