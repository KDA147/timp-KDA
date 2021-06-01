#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#define foreach(item, list) \
    for(node * item = list->head; item != NULL; item = item->next)
#define back_foreach(item, list) \
    for(node * item = list->tail; item != NULL; item = item->prev)

// Структура для хранения узла дерева.
// Необходимо хранить ссылки на потомков, предка и некоторое значение
typedef struct nodet {
	int value;
	struct nodet *parent;
	struct nodet *left;
	struct nodet *right;
} nodet;

// Структура для хранения дерева.
// Хранит ссылку на корень дерева и количество элементов в дереве
typedef struct tree {
	int count;
	nodet *root;
} tree;



void init_tree(tree* t){
	t->root = NULL;
	t->count = 0;
}


int insert(tree* t, int value){
	if (t->root == NULL) { 
        nodet *temp_root = (nodet*)malloc(sizeof(nodet));
        t->count++;
        t->root = temp_root;
        temp_root->left = NULL;
        temp_root->right = NULL;
        temp_root->value = value;
        temp_root->parent = NULL;
        return 0;
    } else { 
        nodet *temp = t->root;
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
        nodet *new_node = (nodet*)malloc(sizeof(nodet));
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
typedef struct list {
	struct node *head;  // начало списка
    int size;
} list;

typedef struct node {
	long value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
} node;

// * инициализация пустого списка
void init(list *l){
    l->head = NULL;
    l->size = 0;
}

// * удалить все элементы из списка
void clean(list *l){
    node* tmp1;
    node* tmp2;
    tmp1 = l->head;
    while (tmp1->next != NULL)
    {
        tmp2 = tmp1;
        tmp1 = tmp1->next;
        free(tmp2);
    }
    free(tmp1);
    init(l);
}

// * проверка на пустоту списка
bool is_empty(list *l){
    if (l->head == NULL) return true;
    return false;
}

// * поиск элемента по значению. вернуть NULL если эжемент не найден
node *find(list *l, long value){
    foreach(item, l){
        if (item->value == value) return item;
    }
    return NULL;
}
//  вставка значения в конец списка, вернуть 0 если успешно
// ? брак
int push_back(list *l, long value){
    node* Node;
        Node = (node*)malloc(sizeof(node));
        Node->value = value;
        Node->next = NULL;
    if (is_empty(l))
        l->head = Node;
    else{
        node* p = l->head;
        while (p->next != NULL){
            p = p->next;
        }
        p->next = Node;
    }
    l->size +=1;
    return 0;
}

//  вставка значения в начало списка, вернуть 0 если успешно
// ? брак
int push_front(list *l, long value){
    node* Nnode;
    Nnode = (node*)malloc(sizeof(node));
    Nnode->value = value;
    if (is_empty(l)){
        l->head = Nnode;
        Nnode->next = NULL;
    }
    else{
        Nnode->next = l->head;
        l->head = Nnode;
    }
    l->size +=1;
    return 0;
}

// удалить первый элемент из списка с указанным значением, 
// * вернуть 0 если успешно
int remove_node(list *l, long value){
    if (l->head == NULL) {
		return 1;
	} else if (l->head->value == value) {
		node *temp = l->head;
		l->head = l->head->next;
		free(temp);
		return 0;
	} else {
		node *prev = l->head;
		foreach(i, l) {
			if (i->value == value) {	
				node *temp = i;
				prev->next = i->next;
				free(temp);
				return 0;
			}
			prev = i;
		}
		return 1;
	}

    return 0;
}

nodet * pop_front(list *l){
    if (l->size == 0) return;
    long t = l->head->value;
    remove_node(l, t);
    l->size = l->size - 1;
    return t;
}

void print_tree(nodet* root) {
    list l;
    init(&l);

    push_back(&l, (long)root);
     
    while (l.size != 0) {
        nodet *tmp = (nodet*) pop_front(&l);
        printf("%d ", tmp->value);
        if (tmp->left) {
            push_back(&l, tmp->left);
        } 
        if (tmp->right) {
            push_back(&l, tmp->right);
        }
    }

}


int main() { // 2 раза \n\n помогает
	tree t;
    init_tree(&t);

    for (int i = 0; i < 7; i++)
    {
        int a;
        scanf("%d", &a);
        insert(&t, a);
    }
    print_tree(t.root);

};
