#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#define foreach(item, list) \
    for(node * item = list->head; item != NULL; item = item->next)

typedef struct list {
	struct node *head;  // начало списка
} list;

typedef struct node {
	int value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
} node;

// * инициализация пустого списка
void init(list *l){
    l->head = NULL;
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
    init(&l);
}

// * проверка на пустоту списка
bool is_empty(list *l){
    if (l->head == NULL) return true;
    return false;
}

// * поиск элемента по значению. вернуть NULL если эжемент не найден
node *find(list *l, int value){
    foreach(item, l){
        if (item->value == value) return item;
    }
    return NULL;
}
//  вставка значения в конец списка, вернуть 0 если успешно
// ? брак
int push_back(list *l, int value){
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
    return 0;
}

//  вставка значения в начало списка, вернуть 0 если успешно
// ? брак
int push_front(list *l, int value){
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
    return 0;
}

// * вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(node *n, int value){
    node* Node;
    Node = (node*)malloc(sizeof(node));
    Node->next = n->next;
    Node->value = value;
    n->next = Node;
    return 0;
}

// удалить первый элемент из списка с указанным значением, 
// * вернуть 0 если успешно
int remove_node(list *l, int value){
    node* p1 = l->head;
    node* p2;
    while ((p1->value != value)&&(p1->next != NULL)){
        p2 = p1;
        p1 = p1->next;
    }
    if ((p1->next == NULL)&&(p1->value != value))
        return 1;
    else if ((p1->next == NULL)&&(p1->value == value))
        p2->next = NULL;
    else if (p1 == l->head)
        l->head = p1->next;
    else{
        p2->next = p1->next;
    }
    free(p1);
    return 0;
}

// вывести все значения из списка в прямом порядке через пробел,
// * после окончания вывода перейти на новую строку
void print(list *l){
    foreach(item, l){
        printf("%d ", item->value);
    }
    printf("\n");
}

int main(void)
{
    int n;
    scanf("%d", &n);
    struct list l;
    init(&l);
    int a;
    for (int i = 0; i != n; i++){
        scanf("%d", &a);
        push_back(&l, a);
    }
    print(&l);
    int k1,k2,k3;
    scanf("%d %d %d", &k1, &k2, &k3);
    find(&l, k1) == NULL ? printf("%d", 0) : printf("%d", 1);
    printf(" ");
    find(&l, k2) == NULL ? printf("%d", 0) : printf("%d", 1);
    printf(" ");
    find(&l, k3) == NULL ? printf("%d", 0) : printf("%d", 1);
    printf("\n");
    int m;
    scanf("%d", &m);
    push_back(&l, m);
    print(&l);
    int t;
    scanf("%d", &t);
    push_front(&l, t);
    print(&l);
    int j, x;
    scanf("%d", &j);
    scanf("%d", &x);
    node * no = l.head;
    for(int k = 0; k != j; k++){
        if (k != j - 1 ) { no = no->next;}
        else break;
    }
    insert_after(no, x);
    print(&l); 
    int z;
    scanf("%d", &z);
    remove_node(&l, z);
    print(&l);
    clean(&l);
    return 0;
    
}
