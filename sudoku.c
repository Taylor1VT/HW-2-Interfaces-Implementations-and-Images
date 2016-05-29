/*
 * filename: sudoku.c
 * purpose: check if a given sudoku solution is valid
 * 
 * created by: Taylor Ampatiellos and Isaac Rothschild
 * modified on: February 16th, 2016
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "except.h"
#include "uarray2.h"
#include "bit.h"
#include "pnmrdr.h"

Except_T Invalid_Data_Type = { "invalid data type" };
Except_T Invalid_Width = { "invalid width" };
Except_T Invalid_Height = { "invalid height" };
Except_T Invalid_Denominator = { "invalid maximum pixel value" };

bool check_row(UArray2_T board, Bit_T status, int row);
bool check_col(UArray2_T board, Bit_T status, int col);
bool check_square(UArray2_T board, Bit_T status, int row, int col);
void read_board(UArray2_T board, Pnmrdr_T reader);
bool check_board(UArray2_T board, Bit_T status);
void check_for_CRE(Pnmrdr_mapdata data);

int main(int argc, char *argv[])
{
        FILE *file;
	int result;
	
	file = (argc == 1) ? stdin : fopen(argv[1], "rb");

        Pnmrdr_T reader = Pnmrdr_new(file); /* Raises CRE if file is NULL */
        Pnmrdr_mapdata data = Pnmrdr_data(reader);
	
	check_for_CRE(data);
	
	UArray2_T board = UArray2_new(9, 9, sizeof(int));
	Bit_T status = Bit_new(10);
	
	/* Read Board */
	read_board(board, reader); /* Store reader data in 2D uarray */
	
	/* Check Board */
	result = (check_board(board, status)) ? 0 : 1; /* Valid board gets 0,
							  otherwise gets 1. */
	/* Free all memory. */
	Bit_free(&status);
	UArray2_free(&board);
	Pnmrdr_free(&reader);
        fclose(file);
	
	return result;
}

/* Raises Hanson CREs for any violations of the spec. */
void check_for_CRE(Pnmrdr_mapdata data)
{
	if (data.type != Pnmrdr_gray)
		RAISE(Invalid_Data_Type);
	if (data.width != 9)
		RAISE(Invalid_Width);
	if (data.height != 9)
		RAISE(Invalid_Height);
	if (data.denominator != 9)
		RAISE(Invalid_Denominator);
}

/* Reads a 9x9 grid from reader into board. */
void read_board(UArray2_T board, Pnmrdr_T reader)
{
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++)
			*((int *)UArray2_at(board, col, row)) = 
							    Pnmrdr_get(reader);
	}
}

/* Checks for board validity */
bool check_board(UArray2_T board, Bit_T status)
{
	/* Check Rows */
	for (int row = 0; row < 9; row++) {
		if (check_row(board, status, row) == false)
			return false;
		Bit_clear(status, 0, 9);
	}
		
	/* Check Cols */
	for (int col = 0; col < 9; col++) {
		if (check_col(board, status, col) == false)
			return false;
		Bit_clear(status, 0, 9);
	} 
	
	/* Check Squares */
	for (int row = 0; row < 9; row += 3) {
		for (int col = 0; col < 9; col += 3)
		if (check_square(board, status, row, col) == false)
			return false;
		Bit_clear(status, 0, 9);
	}
	
	return true;
}

/* Checks one row of the Sudoku board, using a bit array to keep track
 * of seen values. If not all numbers 1-9 found in row, returns false.
 * 
 * Exits on CRE if a seen value is less than 0 or greater than 9.
 */
bool check_row(UArray2_T board, Bit_T status, int row)
{
	for (int i = 0; i < 9; i++)
		Bit_put(status, *((int *)UArray2_at(board, row, i)), 1);
	if (Bit_get(status, 0))
		return false;
	if (Bit_count(status) != 9)
		return false;
	return true;
}

/* Checks one column of the Sudoku board, using a bit array to keep track
 * of seen values. If not all numbers 1-9 found in column, returns false.
 * 
 * Exits on CRE if a seen value is less than 0 or greater than 9.
 */
bool check_col(UArray2_T board, Bit_T status, int col)
{
	for (int i = 0; i < 9; i++)
		Bit_put(status, *((int *)UArray2_at(board, i, col)), 1);
	if (Bit_get(status, 0))
		return false;
	if (Bit_count(status) != 9)
		return false;
	return true;
}

/* Checks one 3x3 square of the Sudoku board, using a bit array to keep track
 * of seen values. If not all numbers 1-9 found in square, returns false.
 * 
 * Exits on CRE if a seen value is less than 0 or greater than 9.
 */
bool check_square(UArray2_T board, Bit_T status, int row, int col)
{
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) 
		        Bit_put(status, 
				*((int *)UArray2_at(board, row+r, col+c)), 1);
	}
	if (Bit_get(status, 0))
		return false;
	if (Bit_count(status) != 9)
		return false;
	
	return true;
}