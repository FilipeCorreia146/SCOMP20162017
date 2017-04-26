#include <stdio.h>
#include <stdlib.h>

int countlines(char * filename){

	FILE * fp = fopen(filename, "r");

	int ch=0, lines=0;

	if(fp == NULL) return 0;

	lines++;

	while((ch = fgetc(fp)) != EOF) {

		if( ch == '\n')
			lines++;
	}

	fclose(fp);

	return lines;

}
