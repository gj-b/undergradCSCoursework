#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "hw7.h"

bst* read_memory_blocks(char *filename, 
  int (*cmp)(const void* x, const void* y))
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Could not open file %s for reading\n",filename);
		exit(1);
	}
	bst *fresh = bst_new(cmp);

	char buffer[BUFSIZ];
	while (!feof(fp) && (fgets(buffer,500,fp) != NULL))
	{
		char *tmp_val;
		unsigned int addr;
		unsigned int size;

		tmp_val = strtok(buffer," ,\n\r");
		addr = atoi(tmp_val);
		tmp_val = strtok(NULL," ,\n\r");
		size = atoi(tmp_val);
		memory *new_mem = memory_new(addr,size);
		bst_insert(fresh,new_mem);
	}
	return fresh;
}
