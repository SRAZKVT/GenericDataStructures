#ifndef LinkedList_h_INCLUDED
	#define LinkedList_h_INCLUDED
	#include "../macro.h"
	#ifdef TYPE
		#include <stdlib.h>
		#include "../monads/Maybe.h"

		#define MAYBE_TYPE CAT(Maybe_, TYPE)
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

		// LinkedList_<type>_new
		struct LIST_TYPE *CAT(LIST_TYPE, _new)() {
			struct LIST_TYPE *ret = malloc(sizeof(LIST_TYPE));
			ret->fst = NULL;
			return ret;
		}

		// LinkedList_<type>_insert
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

		// LinkedList<type>_copy
		struct LIST_TYPE *CAT(LIST_TYPE, _copy)(struct LIST_TYPE *list) {
			struct LIST_TYPE *cpy = CAT(LIST_TYPE, _new)();
			NODE_TYPE *node = list->fst;
			while (node) {
				CAT(LIST_TYPE, _insert)(cpy, node->value);
				node = node->next;
			}
			return cpy;
		}

		// LinkedList_<type>_removeList
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

		// LinkedList_<type>_remove
		int CAT(LIST_TYPE, _remove)(LIST_TYPE *list,
		                            TYPE element) {
			NODE_TYPE *node = list->fst;
			while (node) {
				if (node->value == element) {
					if (node->next) node->next->prev = node->prev;
					if (node->prev) node->prev->next = node->next;
					else list->fst = node->next;
					free(node);
					return 1;
				}
				node = node->next;
			}
			return 0;
		}

		// LinkedList_<type>_removeAll
		int CAT(LIST_TYPE, _removeAll)(LIST_TYPE *list,
		                               TYPE element) {
			int cnt = 0;
			NODE_TYPE *node = list->fst;
			while (node) {
				if (node->value == element) {
					if (node->next) node->next->prev = node->prev;
					if (node->prev) node->prev->next = node->next;
					else list->fst = node->next;
					NODE_TYPE *toFree = node;
					node = node->next;
					free(toFree);
					cnt += 1;
				} else node = node->next;
			}
			return cnt;
		}

		// LinkedList_<type>_removeIf
		int CAT(LIST_TYPE, _removeIf)(LIST_TYPE *list,
		                              int (*func)(TYPE)) {
			int cnt = 0;
			NODE_TYPE *node = list->fst;
			while (node) {
				if (func(node->value)) {
					if (node->next) node->next->prev = node->prev;
					if (node->prev) node->prev->next = node->next;
					else list->fst = node->next;
					NODE_TYPE *toFree = node;
					node = node->next;
					free(toFree);
					cnt += 1;
				} else node = node->next;
			}
			return cnt;
		}

		// LinkedList_<type>_removeIfNot
		int CAT(LIST_TYPE, _removeIfNot)(LIST_TYPE *list,
		                              int (*func)(TYPE)) {
			int cnt = 0;
			NODE_TYPE *node = list->fst;
			while (node) {
				if (!func(node->value)) {
					if (node->next) node->next->prev = node->prev;
					if (node->prev) node->prev->next = node->next;
					else list->fst = node->next;
					NODE_TYPE *toFree = node;
					node = node->next;
					free(toFree);
					cnt += 1;
				} else node = node->next;
			}
			return cnt;
		}

		// LinkedList_<type>_get
		MAYBE_TYPE *CAT(LIST_TYPE, _get)(LIST_TYPE *list,
		                                 int index) {
			NODE_TYPE *node = list->fst;
			while (node) {
				index--;
				if (index < 0)
					return CAT(MAYBE_TYPE, _of)(node->value);
				else node = node->next;
			}
			// If we end up here, index is out of bounds
			return CAT(MAYBE_TYPE, _empty)();
		}

		// LinkedList_<type>_size
		int CAT(LIST_TYPE, _size)(LIST_TYPE *list) {
			NODE_TYPE *node = list->fst;
			int cnt = 0;
			while (node) {
				cnt++;
				node = node->next;
			}
			return cnt;
		}

		// LinkedList_<type>_print
		void CAT(LIST_TYPE, _print)(LIST_TYPE *list,
		                            void (*print_func)(TYPE)) {
			printf("[");
			NODE_TYPE *node = list->fst;
			while (node) {
				print_func(node->value);
				if (node->next) printf(", ");
				node = node->next;
			}
			printf("]\n");
		}

		#undef MAYBE_TYPE
		#undef NODE_TYPE
		#undef LIST_TYPE
	#endif
#endif // LinkedList_h_INCLUDED
