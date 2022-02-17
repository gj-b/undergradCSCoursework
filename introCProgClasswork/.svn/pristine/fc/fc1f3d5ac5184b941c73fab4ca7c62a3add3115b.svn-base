#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw6.h"

int main(int argc, char *argv[])
{
	
	product_info *new_product;
	char *outfile = "products2.txt";
	FILE *fp_test_outfile = fopen(outfile, "w");
	// make sure there are two arguments - hw5 and filename
	if (argc < 2)
	{
		printf("Usage: ./hw6 filename. Missing filename\n");
		exit(1);
	}
	char *filename = argv[1];

	// open file for reading
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Could not open file %s for reading\n",filename);
		exit(2);
	}

	node *test_insert_head = NULL;
	node *test_sorted_by_ID = NULL;
	node *test_sorted_by_ID_and_Cat = NULL;

	fprintf(fp_test_outfile, "Printed all products first to test (create_product):\n");

	// read in each record from the file
	char buffer[BUFSIZ];
	while (!feof(fp) && (fgets(buffer,500,fp) != NULL))
	{
		

		// parse the line to split up the fields
		char *category;
		char *name;
		uint pID;
		uint current_stock;
		uint min_stock;
		uint max_stock;
		char *tmp_s;

		// first field is category
		category = strtok(buffer," ,\n\r");
		// second field is name
		name = strtok(NULL," ,\n\r");
		// third is pID;
		tmp_s = strtok(NULL," ,\n\r");
		pID = atoi(tmp_s);
		// fourth is current
		tmp_s = strtok(NULL," ,\n\r");
		current_stock = atoi(tmp_s);
		// fifth is min
		tmp_s = strtok(NULL," ,\n\r");
		min_stock = atoi(tmp_s);
		// sixth is max
		tmp_s = strtok(NULL," ,\n\r");
		max_stock = atoi(tmp_s);

		printf("Read in record: %s, %s, %u, %u, %u, %u\n",
			category, name, pID, current_stock, min_stock,
			max_stock);

		//Creates and prints the procut out.
		new_product = 
			create_product(name,category,pID,current_stock,min_stock,max_stock);
		print_product(new_product,fp_test_outfile);

		test_insert_head = insert_head(test_insert_head,new_product);

		test_sorted_by_ID = 
			add_sorted_productID(new_product,test_sorted_by_ID);

		test_sorted_by_ID_and_Cat = 
			add_sorted_category_ID(new_product,test_sorted_by_ID_and_Cat);
		}

	fprintf(fp_test_outfile, "\n \n Printing insert_head function linked list. "
		"Should be all products in reverse order.:\n");
	print_list(test_insert_head,fp_test_outfile);

	fprintf(fp_test_outfile, "\n Testing find function. Looking for 92656." 
		"Should return Grocery, Flour, 92656, 9, 8, 12. \n");
	product_info *find_test_1;
	find_test_1 = find(test_insert_head,92656);
	print_product(find_test_1,fp_test_outfile);

	fprintf(fp_test_outfile, "\n Testing find function. Looking for 12345." 
		"Should return error message to terminal. \n");
	product_info *find_test_2;
	find_test_2 = find(test_insert_head,12345);

	fprintf(fp_test_outfile, "\n Testing record_restock function."
		" Restocking (92656) from 9 to 12.\n");
	record_restocked_single(test_insert_head,92656);
	print_list(test_insert_head,fp_test_outfile);

	fprintf(fp_test_outfile, "\n Testing record_restock function."
		" Restocking (12345) should return a terminal error.\n");
	record_restocked_single(test_insert_head,12345);
	print_list(test_insert_head,fp_test_outfile);

	fprintf(fp_test_outfile, "\n Testing product_sold function."
		" Selling one (92656). Dec from 12 to 11.\n");
	product_sold(test_insert_head,92656);
	print_list(test_insert_head,fp_test_outfile);

	fprintf(fp_test_outfile, "\n Testing product_sold function."
		" Selling one (23765). Should stay at 0.\n");
	product_sold(test_insert_head,23765);
	print_list(test_insert_head,fp_test_outfile);

	fprintf(fp_test_outfile, "\n Testing record_restock function."
		" Restocking (12345) should return a terminal error.\n");
	product_sold(test_insert_head,12345);
	print_list(test_insert_head,fp_test_outfile);

	fprintf(fp_test_outfile, "\n \n Printing sorted_by_id function linked list. "
		"Should be all products in order of inc. pID:\n");
	print_list(test_sorted_by_ID,fp_test_outfile);

	node *needs_restocking = make_restock_list(test_sorted_by_ID);
	fprintf(fp_test_outfile, "\n \n Printing items that need restocking.\n.");
	print_list(needs_restocking,fp_test_outfile);

	record_restocked_list(needs_restocking,test_sorted_by_ID);
	fprintf(fp_test_outfile, "\n \n Printing items which should now be restocked."
		"all items should be at their max # of items.\n");
	print_list(test_sorted_by_ID,fp_test_outfile);

	fprintf(fp_test_outfile, "\n \n Printing sorted_by_id_and_cat function linked list. "
		"Should be all products in order of category and inc. pID:\n"
		"Had issues with last item in list.");
	print_list(test_sorted_by_ID_and_Cat,fp_test_outfile);

}