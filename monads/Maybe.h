#ifndef Maybe_h_INCLUDED
	#ifdef TYPE
		#include "../macro.h"
		#include <stdlib.h>
		#include <stdbool.h>
		#define MAYBE_TYPE CAT(Maybe_, TYPE)

		typedef struct MAYBE_TYPE {
			TYPE value;
			bool present;
		} MAYBE_TYPE;

		MAYBE_TYPE *CAT(MAYBE_TYPE, _of)(TYPE a) {
			MAYBE_TYPE *m = malloc(sizeof(MAYBE_TYPE));
			m->value = a;
			m->present = true;
			return m;
		}

		MAYBE_TYPE *CAT(MAYBE_TYPE, _empty)() {
			MAYBE_TYPE *m = malloc(sizeof(MAYBE_TYPE));
			m->present = false;
			return m;
		}

		#undef MAYBE_TYPE
	#endif
#endif // Maybe_h_INCLUDED

