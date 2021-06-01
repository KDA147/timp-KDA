#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int value;
	struct node *parent;
	struct node *left;
	struct node *right;
} node;


typedef struct tree {
	int count;
	node *root;
} tree;



void init(tree* t){
	t->root = NULL;
	t->count = 0;
}


int insert(tree* t, int value){
	if (t->root == NULL) { 
        node *temp_root = (node*)malloc(sizeof(node));
        t->count++;
        t->root = temp_root;
        temp_root->left = NULL;
        temp_root->right = NULL;
        temp_root->value = value;
        temp_root->parent = NULL;
        return 0;
    } else { 
        node *temp = t->root;
        for (int i = 0; i < t->count; i++) {
            if (value == temp->value) {
                return 1;
            } else if (value < temp->value && temp->left != NULL) {
                temp = temp->left;
            } else if (value > temp->value && temp->right != NULL) {
                temp = temp->right;
            } else {
                break;
            }
        }
        node *new_node = (node*)malloc(sizeof(node));
        t->count++;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->value = value;
        new_node->parent = temp;
        if (value < temp->value) {
            temp->left = new_node;
            return 0;
        } else {
            temp->right = new_node;
            return 0;
        }
        return 2;
    }
}

void print(node * n){
    if ( n != NULL) { 
    
    print(n->left); 
    print(n->right);
    printf("%d ", n->value); 
    
  }
}

void print_tree(tree * t){
    print(t->root);
}


int main() { 
	tree t;
    init(&t);

    for (int i = 0; i < 7; i++)
    {
        int a;
        scanf("%d", &a);
        insert(&t, a);
    }
    print_tree(&t);
    return 0;
};
