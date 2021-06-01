#include <stdio.h>
#include <stdlib.h>


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


// Инициализация дерева
void init(tree* t){
	t->root = NULL;
	t->count = 0;
}


struct node * minValueNode(struct node* node)
{
    struct node* current = node;
    while (current->left != NULL)
    current = current->left;
    return current;
}

node * rec_find(node* n, int value)
{
    if (n == NULL || n->value == value)
       return n;
    if (n->value < value)
       return rec_find(n->right, value);
 
    return rec_find(n->left, value);
}
// Поиск элемента по значению. Вернуть NULL если элемент не найден
node* find(tree* t, int value){
    return rec_find(t->root, value);
}


// Вставка значения в дерево:
// 0 - вставка выполнена успешно
// 1 - элемент существует
// 2 - не удалось выделить память для нового элемента
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


node* normaldelete_bez_inta(struct node* root, int value)
{
    if (root == NULL)
    return root;

    if (value < root->value)
    root->left = normaldelete_bez_inta(root->left, value);

    else if (value > root->value)
    root->right = normaldelete_bez_inta(root->right, value);
    else
    {

    if (root->left == NULL)
    {
    struct node *temp = root->right;
    free(root);
    return temp;
    }
    else if (root->right == NULL)
    {
    struct node *temp = root->left;
    free(root);
    return temp;
    }

    struct node* temp = minValueNode(root->right);

    root->value = temp->value;

    root->right = normaldelete_bez_inta(root->right, temp->value);
    }
    return root;
}
// Удалить элемент из дерева:
// 0 - удаление прошло успешно
// 1 - нет элемента с указанным значением
int remove_node(tree* t, int value){
    node * n = find(t, value);
    if (n == NULL){
        return 1;
    }
    t->root = normaldelete_bez_inta(t->root, value);
    t->count -= 1;
    return 0;
}



// Удалить минимальный элемент из поддерева, корнем которого является n
// Вернуть значение удаленного элемента
int remove_min(node* n){
    struct node *Temp = n, *Temp2;
    if (Temp->left != NULL)
    {
        while (Temp->left->left != NULL)
        Temp = Temp->left;
        Temp2 = Temp->left;
        Temp->left = Temp2->right;
        free(Temp2);
    }
    else
    {
        Temp = n->right;
        free(n);
        n = Temp;
    }
    return 0;
}

// Удалить все элементы из дерева
void clean(tree* t) {
    if (t->root == NULL) {
        return;
    }
    node *temp = t->root;
    while(1) {
        if (temp->left) {
            temp = temp->left;
        } else if (temp->right) {
            temp = temp->right;
        } else if (temp->left == NULL && temp->right == NULL && temp->parent != NULL) {
            node *temp2 = temp;
            temp = temp->parent;
            if (temp->left != NULL) {
                temp->left = NULL;
                free(temp2);
            } else {
                temp->right = NULL;
                free(temp2);
            }
        } else {
            t->root = NULL;
            t->count = 0;
            free(temp);
            return;
        }
    }
}
// Выполнить правое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно 
int rotate_right(tree * t, node* n){
  if (t->root == NULL) return 1;
    node * y = n->left;

  if ((y != NULL) && (n != NULL)){
    n->left = y->right; 

    if (y->right != NULL){
      y->right->parent = n; 
    }

    y->parent = n->parent; 

    if (n->parent != NULL){
      if (n->parent->left == n){
        n->parent->left = y;
      } else {
        n->parent->right = y;
      } 
    }

    t->root = y;
    y->right = n;
    n->parent = y; 

    return 0;
  } else {
    return 1;
  }
}

// Выполнить левое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_left(tree* t,node* n){
    if (t->root == NULL) return 1;
    node * y = n->right;

  if ((y != NULL) && (n != NULL)){

    n->right = y->left; 

    if (y->left != NULL){
      y->left->parent = n; 
    }

    y->parent = n->parent; 

    if (n->parent != NULL){

      if (n->parent->right == n){
        n->parent->right = y;
      } else {
        n->parent->left = y;
      } 

    }

    t->root = y;
    y->left = n;
    n->parent = y; 

    return 0;
  } else {
    return 1;
  }
}


int deepness(struct node * n, int deep){
  if (n == NULL){
    return deep;
  }
  int d1 = deepness(n->left, deep + 1);
  int d2 = deepness(n->right, deep + 1);

  return (d1 > d2) ? d1 : d2;
}

void printNode(struct node * n, int current, int deep, int first){
  if (current == deep){
      if (first > 0){
        printf(" ");
      }
    if (n == NULL){
      printf("_");
    } else{
      printf("%d", n->value);
    }
  } else if (n != NULL){
    printNode(n->left, current + 1, deep, first);
    printNode(n->right, current + 1, deep, first + 1);
  } else {
    printNode(n, current + 1, deep, first);
    printNode(n, current + 1, deep, first + 1);
  }
}
// Вывести все значения из поддерева, корнем которого является n
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке. 
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _. 
// Если дерево пусто, вывести -
void print(struct node * n)
{
  int m = deepness(n, 0);
  for (int i = 1; i <= m; i++){
    printNode(n, 1, i, 0);
    printf("\n");
  }
}
// Вывести все значения дерева t, аналогично функции print
void print_tree(struct tree * t)
{
    if (t->root == NULL) {printf("-"); return;}
    print(t->root);
}

int main() { // 2 раза \n\n помогает
	tree t;
    init(&t);

    for (int i = 0; i < 4; i++)
    {
        int a;
        scanf("%d", &a);
        insert(&t, a);
    }
    print_tree(&t);
    printf("\n");

    for (int i = 0; i < 3; i++)
    {
        int b;
        scanf("%d", &b);
        insert(&t, b);
    }
    print_tree(&t);
    printf("\n");
    // 2 как надо
  
    int m1;
    scanf("%d", &m1);
    struct node * n;
    n = find(&t, m1);
    if (n == NULL){
        printf("-");
    } else {
        if (n->parent != NULL) {
        printf("%d ", n->parent->value);
    } else {
        printf("_ ");
    }
    if (n->left != NULL){
        printf("%d ", n->left->value);
    } else {
        printf("_ ");
    }
    if (n->right != NULL){
        printf("%d", n->right->value);
    } else {
        printf("_");
    }
    }
    printf("\n\n");
    // 3 как надо
    
    int m2;
    scanf("%d", &m2);
    struct node * n2;
    n2 = find(&t, m2);
    if (n2 == NULL){
        printf("-");
        } else {
            if (n2->parent != NULL){
            printf("%d ", n2->parent->value);
        } else {
            printf("_ ");
        }
        if (n2->left != NULL){
            printf("%d ", n2->left->value);
        } else {
            printf("_ ");
        }
        if (n2->right != NULL){
            printf("%d", n2->right->value);
        } else {
            printf("_");
        }
    }
    printf("\n");
    printf("\n");
   
    int m3;
    scanf("%d", &m3);

    remove_node(&t, m3);
    print_tree(&t);
    printf("\n");
    printf("\n");
    while (rotate_left(&t, t.root) != 1);
    print_tree(&t);
    printf("\n");
    printf("\n");
    while (rotate_right(&t, t.root) != 1);
    print_tree(&t);
    printf("\n");
    printf("\n");
    printf("\n");
    printf("%d", t.count);
    printf("\n");
    printf("\n");
    clean(&t);
    printf("\n");
    print_tree(&t);
    printf("\n");
    printf("\n");
    return 0;

};
