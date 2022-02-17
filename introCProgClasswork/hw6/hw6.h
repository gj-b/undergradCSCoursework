#ifndef HW6_H
#define HW6_H

typedef unsigned int uint;

enum Category { GROCERY=0, OFFICE, PHARMACY, HOBBY};
#define NUM_CATEGORIES 4

typedef struct {
 enum Category category;
 char name[40];
 uint productID;
 uint current_stock;
 uint min_for_restock;
 uint max_after_restock;
} product_info;

// for the linked list, we will use the following struct
typedef struct _node node;

struct _node{
 product_info *product;
 node *next;
};

extern char *category_strings[];

//Provided function. Prints product info. to given file.
void print_product(product_info *g, FILE *fp);

//Provided function. Prints linked list of product info. to given file.
void print_list(node *head, FILE *fp);

//Helper function that returns enum category if the 2 strings match. 
int enum_value(char *category);

/*allocates memory and fills in the fields for a product. 
It returns a pointer to the newly allocated and initialized memory.*/
product_info *create_product(char *name, char *category, uint id,
				uint current, uint mn, uint mx);

/*Adds a product to the "head" or beginning of a list. 
The new first node of the list will point to pinfo. 
It returns a pointer to the first node in the modified list.*/
node* insert_head(node *head, product_info *pinfo);

/*Given a productID, finds the record for the product and 
	returns the pointer to that record.*/
product_info *find(node *head, uint pID);

/*Replaces the current number of items with 
	the max number of items after restocking.*/
void record_restocked_single(node *head, uint pID);

/*Given a productID, finds the record for the product and 
	decrements the number of items currently in stock for that item.*/
void product_sold(node *head, uint pID);

/*Given a new product, places it in the current list based on its product ID.
The earlier the productID, the earlier it goes in list*/
node *add_sorted_productID(product_info *pinfo, node *head);

/*Given a new product, places it in the current list based on its product ID and category.
Category ranking goes: Grocery -> Office -> Pharmacy -> Hobby.
The earlier the productID and category, the earlier it goes in list*/
node *add_sorted_category_ID(product_info *pinfo, node *head);

/*Creates a linked list of product_info records that need to be restocked 
(current_stock < max_for_restock) and returns the head of this new linked list.*/
node *make_restock_list(node *head);

/*Given a list of restocked items, go through the original list and record 
	the current_stock value to be equal to max_after_restock.*/
void record_restocked_list(node *restocked_list, node *head);





















#endif