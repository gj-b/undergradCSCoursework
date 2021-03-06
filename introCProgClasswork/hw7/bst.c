#include<stdio.h>
#include<stdlib.h>
#include "bst.h"

/* malloc a new node and assign the data
 * pointer to its data field
 */
node* node_new(void* data){
  node* new_node = (node *)malloc(sizeof(node));
  new_node->data = data;
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

/* create a new bst, initialize its root to be NULL
 */
bst* bst_new(int (*cmp)(const void* x, const void* y))
{
  bst* new_bst = (bst *)malloc(sizeof(bst));
  new_bst->root = NULL;
  new_bst->cmp = cmp;
  return new_bst;
}

/* Insert a node to to a subtree with a root node as parameter
 * Insertion is in sorted order. 
 * Return the new root of the modified subtree.  
 */
node* node_insert(node* root, void* data, 
    int (*cmp)(const void* x, const void* y))
{
  if(root == NULL)
  {
    return node_new(data);
  }
  if(cmp(root->data,data) == 1)
  {
    root->left = node_insert(root->left,data,cmp);
  }
  if(cmp(data,root->data) == 1)
  {
    root->right = node_insert(root->right,data,cmp);
  }
  return root;
}

/* Insert a new node to the bst
 */
void bst_insert(bst* b, void* data)
{
  b->root = node_insert(b->root,data, b->cmp);
}

/*Finds the minimum value in the left subtree. 
Used as a helper function for node_delete as I then replace the deleted node 
with this minimum value of left branch.*/
node* leftmost_val(node* root) 
{ 
    node *val = root; 
    if(val->left != NULL)
    {
      val = leftmost_val(val->left);
    }
    return val;
} 
  
/* delete a node from a subtree with a given root node
 * use the comparison function to search the node and delete 
 * it when a matching node is found. This function only
 * deletes the first occurrence of the node, i.e, if multiple 
 * nodes contain the data we are looking for, only the first node 
 * we found is deleted. 
 * Return the new root node after deletion.
 */
  node* node_delete(node* root, void* data, 
    int (*cmp)(const void* x, const void* y))
{ 
    if (root == NULL)
    {
      return root;
    }  
    if (cmp(data,root->data) == 1)
    {
      root->right = node_delete(root->right,data,cmp); 
    }
    else if (cmp(root->data,data) == 1) 
    {
      root->left = node_delete(root->left,data,cmp); 
    }
    else
    { 
        if (root->left == NULL) 
        { 
            node *bypass_right = root->right; 
            free(root); 
            return bypass_right; 
        } 
        else if (root->right == NULL) 
        { 
            node *bypass_left = root->left; 
            free(root); 
            return bypass_left; 
        } 
        else
        {
          node *bypass = leftmost_val(root->right); 
          root->data = bypass->data; 
          root->right = node_delete(root->right,bypass->data,cmp); 
        }
    } 
    return root; 
} 

/* delete a node containing data from the bst
 */
void bst_delete(bst* b, void* data)
{
  b->root = node_delete(b->root,data,b->cmp);
}

/* Search for a node containing data in a subtree with
 * a given root node. Use recursion to search that node. 
 * Return the first occurrence of node. 
 */
void* node_search(node* root, void* data, 
    int (*cmp)(const void* x, const void* y))
{
  if(root == NULL)
  {
    printf("Value not part of BST.\n");
    return NULL;
  }
  else if(cmp(root->data,data) == 0)
  {
    return root;
  }
  else if(cmp(root->data,data) == 1)
  {
    root = root->left;
    return node_search(root,data,cmp);
  }
  else if(cmp(data,root->data) == 1)
  {
    root = root->right;
    return node_search(root,data,cmp);
  }
}

/* Search a node with data in a bst. 
 */
void* bst_search(bst* b, void* data)
{
  node *node_found;
  node_found = node_search(b->root,data,b->cmp);
  return node_found;
}

/* traverse a subtree with root in ascending order. 
 * Apply func to the data of each node. 
 */
void inorder_traversal(node* root, void(*func)(void* data)){
  if(root==NULL)
  {
    return;
  }
  inorder_traversal(root->left,func);
  func(root->data);
  inorder_traversal(root->right,func);
}

/* traverse a bst in ascending order. 
 * Apply func to the data of each node. 
 */
void bst_inorder_traversal(bst* b, void(*func)(void* data))
{
  inorder_traversal(b->root,func);
}

/* Helper function that like all previous helpers,
tales a BST and performs the needed task for its node 
struct before returning it back to the BST struct*/
void node_free(node* root)
{
  if(root->left == NULL && root->right == NULL)
  {
    free(root);
    return;
  }
  node_free(root->left);
  node_free(root->right);

  free(root);
}

/* free the bst with 
 */
void bst_free(bst* b)
{
  node_free(b->root);
}





