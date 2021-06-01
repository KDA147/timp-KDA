#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Структура для хранения узла дерева.
// Необходимо хранить ссылки на потомков, предка и некоторое значение
typedef struct node {
	int value;
	struct node *parent;
	struct node *left;
	struct node *right;
} node;

// Структура для хранения дерева.
// Хранит ссылку на корень дерева и количество элементов в дереве
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

void print_tree(tree * t)
{
    node * rights[SHRT_MAX];
    int r_i = 0;
    node * write[SHRT_MAX];
    int w_i = 0;
    node * n = t->root; // раз рекурсию нельзя...

    while (w_i < t->count){ // Проходим пока все не пройдем
        while (n != NULL){ // Пока звено есть
            w_i++; // Увеличиваем счетчик на вывод
            if (n->right != NULL){ // Если правое звено есть
                r_i++;
                rights[r_i] = n->right; // Заносим его в а
            }
            write[w_i] = n; // Заносим звено на вывод
            n = n->left; // Идем влево
        }
        n = rights[r_i]; // Идем вправо
        r_i -= 1; // и назад
    }
    for (int i = 1; i <= w_i; i++)
        printf("%d ", write[i]->value);
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

};
