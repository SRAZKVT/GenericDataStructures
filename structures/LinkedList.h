#ifndef LinkedList_h_INCLUDED
	#define LinkedList_h_INCLUDED
	#include "../macro.h"
	#ifdef TYPE
		#include <stdlib.h>
		#define LIST_TYPE CAT(LinkedList_, TYPE)
		#define NODE_TYPE CAT(Node, LIST_TYPE)

		typedef struct NODE_TYPE {
			TYPE value;
			struct NODE_TYPE *prev;
			struct NODE_TYPE *next;
		} NODE_TYPE;

		typedef struct LIST_TYPE {
			struct NODE_TYPE *fst;
		} LIST_TYPE;

		struct LIST_TYPE *CAT(LIST_TYPE, _new)() {
			struct LIST_TYPE *ret = malloc(sizeof(LIST_TYPE));
			ret->fst = NULL;
			return ret;
		}

		void CAT(LIST_TYPE, _removeList)(struct LIST_TYPE *list) {
			struct NODE_TYPE *node = list->fst;
			while (node) {
				if (node->prev) free(node->prev);
				if (!node->next) {
					free(node);
					break;
				}
				else node = node->next;
			}
			free(list);
		}

		void CAT(LIST_TYPE, _insert)(LIST_TYPE *list,
		                             TYPE element) {
			if (list->fst) {
				struct NODE_TYPE *node = list->fst;
				while (node->next) node = node->next;
				node->next = malloc(sizeof(NODE_TYPE));
				node->next->value = element;
				node->next->next = NULL;
				node->next->prev = node;
			} else {
				list->fst = malloc(sizeof(NODE_TYPE));
				list->fst->value = element;
				list->fst->next = NULL;
				list->fst->prev = NULL;
			}
		}

		int CAT(LIST_TYPE, _remove)(LIST_TYPE *list,
		                            TYPE element) {
			NODE_TYPE *node = list->fst;
			while (node) {
				if (node->value == element) {
					if (node->next) node->next->prev = node->prev;
					if (node->prev) node->prev->next = node->next;
					else list->fst = node->next;
					return 1;
				}
				node = node->next;
			}
			return 0;
		}

		int CAT(LIST_TYPE, _removeAll)(LIST_TYPE *list,
		                               TYPE element) {
			int cnt = 0;
			NODE_TYPE *node = list->fst;
			while (node) {
				if (node->value == element) {
					if (node->next) node->next->prev = node->prev;
					if (node->prev) node->prev->next = node->next;
					else list->fst = node->next;
					cnt += 1;
				}
				node = node->next;
			}
			return cnt;
		}

		int CAT(LIST_TYPE, _size)(LIST_TYPE *list) {
			NODE_TYPE *node = list->fst;
			int cnt = 0;
			while (node) {
				cnt++;
				node = node->next;
			}
			return cnt;
		}

		void CAT(LIST_TYPE, _print)(LIST_TYPE *list,
		                            void (*print_func)()) {
			printf("[");
			NODE_TYPE *node = list->fst;
			while (node) {
				print_func(node->value);
				if (node->next) printf(", ");
				node = node->next;
			}
			printf("]\n");
		}

		#undef NODE_TYPE
		#undef LIST_TYPE
		#undef TYPE
	#endif
#endif // LinkedList_h_INCLUDED
