/*
 * filename: bit2.h
 * 
 * created by: Taylor Ampatiellos and Isaac Rothschild
 * modified on: February 9th, 2016
 * 
 */

#ifndef BIT2_INCLUDED
#define BIT2_INCLUDED

#include "bit.h"

#define T Bit2_T
typedef struct T *T;

/* Returns a pointer to new two-dimensional array of bits, 
 *      all initialized to 0.
 *      
 * Exits with CRE if memory cannot be allocated or if width or height is <= 0.
 */
T Bit2_new(int width, int height);

/* Deallocates and clears *bit_arr.
 * 
 * Exits with CRE if *bit_arr or bit_arr are NULL.
 */
void Bit2_free(T *bit_arr);

/* Returns the number of ‘ON’ bits in bit_array. */
int Bit2_count(T bit_arr);

/* Returns the number of columns of the two-dimensional bit array. */
int Bit2_width(T bit_arr);

/* Returns the number of rows of the two-dimensional bit array. */
int Bit2_height(T bit_arr);

/* Returns the status of bit n.
 * 
 * Exits with CRE if col and/or row are out of bounds.
 */
int Bit2_get(T bit_arr, int col, int row);

/* Sets the status of the bit at location n. Bit can only be 0 or 1.
 *
 * Exits with CRE if bit is not 0 or 1, or if col and/or row are out of bounds.
 */
int Bit2_put(T bit_arr, int col, int row, int bit);

/* Applies function 'map' to elements of bit_arr in row-major order. 
 * Function ‘map’ is allowed to change elements of the array.
 */
void Bit2_map_row_major(T bit_arr, 
			void map(int col, int row, T bit_arr, 
				 int val, void* cl), void* cl);
			
/* Applies function 'map' to elements of bit_arr in column-major order.
 * Function ‘map’ is allowed to change elements of the array.
 */
void Bit2_map_col_major(T bit_arr,
                           void map(int col, int row, T bit_arr, 
			            int val, void* cl), void* cl);

#undef T
#endif /*BIT2*/