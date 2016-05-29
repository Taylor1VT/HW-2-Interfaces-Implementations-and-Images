/*
 * filename: unblackedges.c
 * purpose: remove black edges from pbm image
 * 
 * created by: Taylor Ampatiellos and Isaac Rothschild
 * modified on: February 12th, 2016
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "except.h"
#include "bit2.h"
#include "pnmrdr.h"

/* Hanson Exceptions */
Except_T Too_Many_Arguments = { "too many files specified" };
Except_T Data_Type_Invalid = { "invalid data type" };

void clear_black_edges(Bit2_T image, Pnmrdr_mapdata data, int col, int row);
void pbmwrite(FILE *outputfp, Bit2_T image, int col, int row);
void read_image(Bit2_T image, Pnmrdr_T reader, Pnmrdr_mapdata data);
void search_perimeter(Bit2_T image, Pnmrdr_mapdata data);


int main(int argc, char *argv[])
{
        FILE *inputfp;
	FILE *outputfp = stdout;

	/* Raises CRE if more than 1 file specified */
        if (argc >= 3)
		RAISE(Too_Many_Arguments);
	
        inputfp = (argc == 1) ? stdin : fopen(argv[1], "rb");

        Pnmrdr_T reader = Pnmrdr_new(inputfp); /* Raises CRE if file is NULL */
        Pnmrdr_mapdata data = Pnmrdr_data(reader);
	
	if (data.type != Pnmrdr_bit)
		RAISE(Data_Type_Invalid);
	
	Bit2_T image = Bit2_new(data.width, data.height);	
	
	/* Read Image */
	read_image(image, reader, data);
	
	/* Check all edges */	
	search_perimeter(image, data);
	
	/* Write unblacked board to outputfp. */
	pbmwrite(outputfp, image, data.width, data.height);
	
	/* Free all memory. */
	Bit2_free(&image);
	Pnmrdr_free(&reader);
        fclose(inputfp);
	
	return 0;
}

/* Reads PBM image from 'reader' into 'image' */
void read_image(Bit2_T image, Pnmrdr_T reader, Pnmrdr_mapdata data)
{
  	for (size_t row = 0; row < data.height; row++) {
		for (size_t col = 0; col < data.width; col++)
			Bit2_put(image, col, row, Pnmrdr_get(reader));
	}
}

/* Calls clear_black_edges on each perimeter pixel */
void search_perimeter(Bit2_T image, Pnmrdr_mapdata data)
{
	/* Check Top/Bottom */
	for (size_t row = 0; row < data.height; row += data.height-1) {
		for (size_t col = 0; col < data.width; col++) {
			  clear_black_edges(image, data, col, row);
		}
	}
	
	/* Check Left/Right */
	for (size_t col = 0; col < data.width; col += data.width - 1) {
		for (size_t row = 0; row < data.height; row++) {
			clear_black_edges(image, data, col, row);
		}
	}
}

/* Recursive function that removes black edge pixels according to the spec. */
void clear_black_edges(Bit2_T image, Pnmrdr_mapdata data, int col, int row)
{
	/* Quit if not valid location. */
	if ((col < 0) || (col >= (int)data.width))
		return;
	if ((row < 0) || (row >= (int)data.height))
		return;
	
	/* Quit if white pixel. */
	if (Bit2_get(image, col, row) == 0)
		return;
	
	/* Removes black pixel by setting to white. */
	Bit2_put(image, col, row, 0);
	
	/* Recurse into 4 cardinally adjacent pixels. */
	clear_black_edges(image, data, col, row + 1);
	clear_black_edges(image, data, col, row - 1);
	clear_black_edges(image, data, col + 1, row);
	clear_black_edges(image, data, col - 1, row);
}

/* Writes a Plain PBM to outputfp. */
void pbmwrite(FILE *outputfp, Bit2_T image, int width, int height)
{
	int count = 0;
	fprintf(outputfp, "P1\n%d %d\n", width, height);
	
	for (int row = 0; row < height; row++) {
		count = 0;
		for (int col = 0; col < width; col++) {
			if (count % 70 == 0 && count > 0)
				fprintf(outputfp, "\n");	
			fprintf(outputfp, "%d", Bit2_get(image, col, row));
			count++;
		}
		
		fprintf(outputfp, "\n");
	}
}

