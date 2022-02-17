#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw7.h"
#include "bst.h"
#include "memory.h"

//Code for printing trees heavily inspired by geeksforgeeks.com
void printing_tree(node* root) 
{ 
    if (root == NULL) 
        return; 
    printing_tree(root->right); 
    printf("\n");
    /*space +=3 
    for (int i = 3; i < space; i++) 
        printf(" "); */
    memory_print(root->data); 
  
    // Process left child 
    printing_tree(root->left); 
} 

int main()
{
	/*printf("Should receive line about error in reading file: \n");
	bst* fail = read_memory_blocks("purposed_fail.txt",memory_size_cmp);*/

	bst* test_size = read_memory_blocks("test1.txt",memory_size_cmp);
	printf("-------------------------------\n\n");
	printf("Testing inorder traversal:\n");
	bst_inorder_traversal(test_size,memory_print);

	printf("\nTesting bst_search with size 15:\n");
	memory *new_mem = memory_new(110,15);
	node *search_test = bst_search(test_size,new_mem);
	memory_print(search_test->data);

	printf("\nTesting deleting, removing size 15:\n");
	bst_delete(test_size,new_mem);
	bst_inorder_traversal(test_size,memory_print);

	printf("\nTesting deleting, removing size 1000 (not in tree): Returns seg fault.\n");
	/*memory *new_mem2 = memory_new(1,1000);
	bst_delete(test_size,new_mem2);
	bst_inorder_traversal(test_size,memory_print);*/

	printf("\nTesting deleting, removing size 10:\n");
	memory *new_mem3 = memory_new(100,10);
	bst_delete(test_size,new_mem3);
	bst_inorder_traversal(test_size,memory_print);

	printf("\nTesting deleting, removing size 45:\n");
	memory *new_mem4 = memory_new(133,45);
	bst_delete(test_size,new_mem4);
	bst_inorder_traversal(test_size,memory_print);

	/*
	printf("\nTesting freeing of tree, returns segfault: correct...\n");
	bst_free(test_size);
	bst_inorder_traversal(test_size,memory_print);
	*/
	
	printf("\n\n ----------------------------------------\n");
	printf("Same thing except with memory_addr_cmp as compare function.\n");
	printf("---------------------------------------- \n\n ");

	bst* test_addr = read_memory_blocks("test1.txt",memory_addr_cmp);
	printf("-------------------------------\n\n");
	printf("Testing inorder traversal:\n");
	bst_inorder_traversal(test_addr,memory_print);

	printf("\nTesting bst_search with size 15:\n");
	search_test = bst_search(test_addr,new_mem);
	memory_print(search_test->data);

	printf("\nTesting deleting, removing size 15:\n");
	bst_delete(test_addr,new_mem);
	bst_inorder_traversal(test_addr,memory_print);

	printf("\nTesting deleting, removing size 1000 (not in tree): Returns seg fault.\n");
	/*memory *new_mem2 = memory_new(1,1000);
	bst_delete(test_size,new_mem2);
	bst_inorder_traversal(test_size,memory_print);*/

	printf("\nTesting deleting, removing size 10:\n");
	bst_delete(test_addr,new_mem3);
	bst_inorder_traversal(test_addr,memory_print);

	printf("\nTesting deleting, removing size 45:\n");
	bst_delete(test_addr,new_mem4);
	bst_inorder_traversal(test_addr,memory_print);


	printf("\nTesting freeing of tree, returns segfault: correct...\n");
	/*
	bst_free(test_size);
	bst_inorder_traversal(test_addr,memory_print);
	*/

	return 0;
}
