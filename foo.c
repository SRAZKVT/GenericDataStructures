#include <stdio.h>

void print_int(int i) {
	printf("%d", i);
}

#define TYPE int
#include "structures/LinkedList.h"
#undef TYPE

int main(void) {
	struct LinkedList_int *list = LinkedList_int_new();
	LinkedList_int_print(list, print_int);
	LinkedList_int_insert(list, 1);
	LinkedList_int_insert(list, 2);
	LinkedList_int_insert(list, 3);
	LinkedList_int_print(list, print_int);
	if (LinkedList_int_remove(list, 1)) printf("1 removed\n");
	LinkedList_int_print(list, print_int);
	printf("Size of list is: [%d]\n", LinkedList_int_size(list));
	for (int i = 0; i < 10; i++) LinkedList_int_insert(list, 10);
	LinkedList_int_print(list, print_int);
	printf("%d\n", LinkedList_int_removeAll(list, 10));
	printf("%d\n", LinkedList_int_removeAll(list, 11));
	LinkedList_int_print(list, print_int);
	LinkedList_int_removeList(list);
}
