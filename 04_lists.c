#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#define foreach(item, list) \
    for(node * item = list->head; item != NULL; item = item->next)
#define back_foreach(item, list) \
    for(node * item = list->tail; item != NULL; item = item->prev)

typedef struct node {
	int value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
	struct node *prev;  // ссылка на предыдущий элемент списка
} node;

typedef struct list {
	struct node *head;  // начало списка
	struct node *tail;  // конец списка
} list;


// инициализация пустого списка
void init(list *l){
    l->head = NULL;
    l->tail = NULL;
}

// удалить все элементы из списка
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



// проверка на пустоту списка
bool is_empty(list *l){
    if (l->head == NULL) return true;
    return false;
}

// поиск элемента по значению. вернуть NULL если элемент не найден
node *find(list *l, int value){
    foreach(item, l){
        if (item->value == value) return item;
    }
    return NULL;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value){
    node* Node;
    Node = (node*)malloc(sizeof(node));
    Node->value = value;
    Node->next = NULL;
    if (is_empty(l)){
        l->head = Node;
        l->tail = Node;
        Node->prev = NULL;
    }
    else
    {
        Node->prev = l->tail;
        l->tail->next = Node;
        l->tail = Node;
    }
    return 0;
}


// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value){
    node* Node;
    Node = (node*)malloc(sizeof(node));
    Node->value = value;
    Node->prev = NULL;
    if (is_empty(l)){
        l->head = Node;
        l->tail = Node;
        Node->next = NULL;
    }
    else{
        Node->next = l->head;
        l->head->prev = Node;
        l->head = Node;
    }
    return 0;
}


// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list *l, node *n, int value){
    node* Node;
    Node = (node*)malloc(sizeof(node));
    Node->value = value;
    Node->prev = n;
    if (n->next == NULL){
        Node->next = NULL;
        n->next = Node;
        l->tail = Node;
    }
    else{
        Node->next = n->next;
        Node->next->prev = Node;
        n->next = Node;
    }
    return 0;
}

// вставка значения перед указанным узлом, вернуть 0 если успешно
int insert_before(list *l, node *n, int value){
    if (n->prev == NULL){
        push_front(l, value);
        return 0;
    }
    node* Node;
    Node = (node*)malloc(sizeof(node));
    Node->next = n;
    Node->prev = n->prev;
    Node->prev->next = Node;
    n->prev = Node;
    Node->value = value;
    return 0;
}

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_first(list *l, int value){
    node* p1 = l->head;
    node* p2;
    while ((p1->value != value)&&(p1->next != NULL)){
        p2 = p1;
        p1 = p1->next;
    }
    if ((p1->next == NULL)&&(p1->value != value))
        return 1;
    else if ((p1->next == NULL)&&(p1->value == value)){
        p2->next = NULL;
        l->tail = p2;
    }
    else if (p1 == l->head) {
        l->head = p1->next;
        p1->next->prev = NULL;
    }
    else{
        p2->next = p1->next;
        p1->next->prev = p2;
    }
    free(p1);
    return 0;
}

// удалить последний элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_last(list *l, int value){
    node *p1 = l->tail;
    node *p2;
    while ((p1->value != value) && (p1->prev != NULL)) {
        p2 = p1;
        p1 = p1->prev;
    }
    if ((p1->prev == NULL) && (p1->value != value))
        return 1;
    else if ((p1->prev == NULL) && (p1->value == value)){
        p2->prev = NULL;
        l->head = p2;
    }
    else if (p1 == l->tail){
        l->tail = p1->prev;
        p1->prev->next = NULL;

    }
    else {
        p2->prev = p1->prev;
        p1->prev->next = p2;
    }
    free(p1);
    return 0;
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l){
    foreach(item, l){
        printf("%d ", item->value);
    }
    printf("\n");
}

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void print_invers(list *l){
    back_foreach(item, l){
        printf("%d ", item->value);
    }
    printf("\n");
}

int main() {
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
    print_invers(&l);
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
    insert_after(&l,no, x);
    print_invers(&l); 
    int u, y;
    scanf("%d", &u);
    scanf("%d", &y);
    no = l.head;
    for(int k = 0; k != u; k++){
        if (k != u - 1) { no = no->next;}
        else break;
    }
    insert_before(&l,no, y);
    print(&l);
    int z;
    scanf("%d", &z);
    remove_first(&l, z);
    print_invers(&l);
    int r;
    scanf("%d", &r);
    remove_last(&l, r);
    print(&l);
    clean(&l);
    return 0;

};
