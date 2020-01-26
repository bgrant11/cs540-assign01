#ifndef DEQUE_H
#define DEQUE_H





#define Deque_DEFINE(t)											\
	/* DEQ struct ------------------------------------- */	\
    struct Deque_##t {											\
		char *type_name; /* how to set*/						\
		int head;												\
		int tail;												\
		size_t sz; /* TODO should i have this */				\
		size_t (*size)(Deque_##t *de); /* size fp */			\
		bool (*empty)(Deque_##t *de); /* true if empty */ 		\
		void (*push_back)(Deque_##t *de, t item);				\
		void (*push_front)(Deque_##t *de, t item);				\
		t& (*back)(Deque_##t *de); /* TODO return const reference?*/	\
		t& (*front)(Deque_##t *de);						\
		t& (*at)(Deque_##t *de, int idx);					\
		void (*pop_back)(Deque_##t *de);						\
		void (*pop_front)(Deque_##t *de);						\
		void (*clear)(Deque_##t *de);							\
		void (*dtor)(Deque_##t *de);							\
	};															\
																\
														\
	/* DEQ member fns------------------------------------------------ */
	size_t Deque_##t##_size(Deque_##t *de) {					\
																\
	}															\
	
	bool empty(Deque_##t *de) {

	}
			
	void push_back(Deque_##t *de, t item) {
	
	}
				
	void push_front(Deque_##t *de, t item) {
	
	}

	t& back(Deque_##t *de) {

	}

	t& front(Deque_##t *de){

	}
					
	t& at(Deque_##t *de, int idx) {

	}
				
	void pop_back(Deque_##t *de){
	
	}
					
	void pop_front(Deque_##t *de){

	}		
				
	void clear(Deque_##t *de){

	}
						
	void dtor(Deque_##t *de){

	}
	/* Iterator struct-------------------------------------------------*/
	struct Deque_##t##_iterator {								\
																\
	};	
	
	/* Iterator member fns------------------------------------------------ */
	
	/* ctor and other fns ------------------------------------------s----- */	
	bool Deque_##t##_equal(Deque_##t *de1, Deque_##t *de2){		
																
	}														
	void Deque_##t##_ctor(Deque_##t *de, void(*cmp)()){			
		de->													\
	}															\

//TODO 
#endif
