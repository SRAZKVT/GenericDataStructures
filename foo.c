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
	printf("Size of list is: [%d]\n", LinkedList_int_size(list));
	LinkedList_int_removeList(list);
}
