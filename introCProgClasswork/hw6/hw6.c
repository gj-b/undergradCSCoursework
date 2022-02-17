#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw6.h"

char *category_strings[] = { "Grocery", "Office", "Pharmacy", "Hobby"};

//Provided function. Prints product info. to given file.
void print_product(product_info *p, FILE *fp)
{
	fprintf(fp,"%s (%u) %s:",p->name, p->productID,
		category_strings[p->category]);
	fprintf(fp, "current: %u, min: %u, max: %u \n",
		p->current_stock, p->min_for_restock, p->max_after_restock);
}

//Provided function. Prints linked list of product info. to given file.
void print_list(node *head, FILE *fp)
{
	node *tmp;
	fprintf(fp, "Product Status:\n");
	//fprintf(fp, "%d\n",*head);
	for(tmp = head; tmp != NULL; tmp = tmp->next)
	{
		print_product(tmp->product,fp);
		//fprintf(fp,"\n");
	}
}

//Helper function that returns enum category if the 2 strings match. 
int enum_value(char *category)
{
	int i;
	for(i = 0; i < NUM_CATEGORIES; i++)
	{
		if(strcmp(category,category_strings[i]) == 0) //means they're same.
			return i;
	}
	//If not returned above:
	fprintf(stderr,"error (enum_value) : %s " 
		"Not one of the given categories. "
		"Will give it category Grocery as default. \n", category);
	return 0;
}

/*allocates memory and fills in the fields for a product. 
It returns a pointer to the newly allocated and initialized memory.*/
product_info *create_product(char *name, char *category, uint id,
				uint current, uint mn, uint mx)
{
	product_info *ini_item = malloc(sizeof(product_info));
	ini_item->category =  enum_value(category);
	strcpy(ini_item->name,name);
	ini_item->productID = id;
	ini_item->current_stock = current;
	ini_item->min_for_restock = mn;
	ini_item->max_after_restock = mx; 
	return ini_item;
}

/*Adds a product to the "head" or beginning of a list. 
The new first node of the list will point to pinfo. 
It returns a pointer to the first node in the modified list.*/
node* insert_head(node *head, product_info *pinfo)
{
	node *new_node = (node*)malloc(sizeof(node));
	new_node->product = pinfo;
	new_node->next = head;
	head = new_node;
	return head;
}

/*Given a productID, finds the record for the product and 
	returns the pointer to that record.*/
product_info *find(node *head, uint pID)
{
	node *current = head;
	while(current != NULL)
	{
		if(current->product->productID == pID)
		{
			return current->product;
		}
		current = current->next;
	}
	fprintf(stderr,"error (find) : (%d) " 
		"not found in our records. \n", pID);
}

/*Replaces the current number of items with 
	the max number of items after restocking.*/
void record_restocked_single(node *head, uint pID)
{
	product_info *prdct_in_quest = find(head,pID);
		prdct_in_quest->current_stock = prdct_in_quest->max_after_restock;
}

/*Given a productID, finds the record for the product and 
	decrements the number of items currently in stock for that item.*/
void product_sold(node *head, uint pID)
{
	product_info *prdct_in_quest = find(head,pID);
		if(prdct_in_quest->current_stock > 0)
			prdct_in_quest->current_stock = prdct_in_quest->current_stock - 1;
}

/*Given a new product, places it in the current list based on its product ID.
The earlier the productID, the earlier it goes in list*/
node *add_sorted_productID(product_info *pinfo, node *head)
{
	node *current;
	node *temp;
	current = head;
	//Fills in an empty linked list or inserts new product at head if it
	//has smalled productID.
	if((head == NULL) || (head->product->productID >= pinfo->productID))
	{
		head = insert_head(head,pinfo);
		return head;
	}
	else
	{
		while((current->next != NULL) && 
			(current->next->product->productID < pinfo->productID))
		{ 
			current = current->next;
		}
		
		temp = (node*) malloc(sizeof(node));
		temp->product = pinfo;
		temp->next = current->next;
		current->next = temp;
		return head;
	}	
}

/*Given a new product, places it in the current list based on its product ID and category.
Category ranking goes: Grocery -> Office -> Pharmacy -> Hobby.
The earlier the productID and category, the earlier it goes in list*/
node *add_sorted_category_ID(product_info *pinfo, node *head)
{
	node *current;
	node *temp;
	current = head;
	if((head == NULL) || 
		((head->product->productID >= pinfo->productID) 
			&& (current->product->category == pinfo->category)))
	{
		head = insert_head(head,pinfo);
		return head;
	}
	else
	{
		while((current->next != NULL)
			&& (current->next->product->category < pinfo->category))
			//&& (current->next->product->productID < pinfo->productID)) 
		{
			current = current->next;
		}
		while((current->next != NULL) 
			&& (current->next->product->productID < pinfo->productID)) 
		{ 
			current = current->next;
		}
	}
		temp = (node*) malloc(sizeof(node));
		temp->product = pinfo;
		temp->next = current->next;
		current->next = temp;
		return head;
}	

/*Creates a linked list of product_info records that need to be restocked 
(current_stock < max_for_restock) and returns the head of this new linked list.*/
node *make_restock_list(node *head)
{
	node *current;
	current = head;
	node *head_restock;
	head_restock = NULL;
	while(current != NULL)
	{
		if(current->product->current_stock < current->product->max_after_restock)
		{
			head_restock = insert_head(head_restock,current->product);
		}
		current = current->next;
	}
	return head_restock;
}

/*Given a list of restocked items, go through the original list and record 
	the current_stock value to be equal to max_after_restock.*/
void record_restocked_list(node *restocked_list, node *head)
{
	node *current_restocked;
	current_restocked = restocked_list;
	while(current_restocked != NULL)
	{
		record_restocked_single(head,current_restocked->product->productID);
		current_restocked = current_restocked->next;
	}
}	

