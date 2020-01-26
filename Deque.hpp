#ifndef DEQUE_H
#define DEQUE_H





#define Deque_DEFINE(t)											\
	/* container struct */										\
    struct Deque_##t {											\
		char *type_name; /* how to set*/						\
		int head;												\
		int tail;												\
		size_t sz; /* TODO should i have this */				\
		size_t (*size)(Deque_##t *de); /* size fp */			\
		bool (*empty)(Deque_##t *de); /* true if empty */ 		\
		void (*push_back)(Deque_##t *de, t item);				\
		void (*push_front)(Deque_##t *de, t item);				\
		const t& (*back)(Deque_##t *de); /* TODO return const reference?*/	\
		const t& (*front)(Deque_##t *de);						\
		const t& (*at)(Deque_##t *de, int idx);					\
		void (*pop_back)(Deque_##t *de);						\
		void (*pop_front)(Deque_##t *de);						\
		void (*clear)(Deque_##t *de);							\
		void (*dtor)(Deque_##t *de);							\
	};															\
																\
	struct Deque_##t##_iterator {								\
																\
	};															\
																\
	size_t Deque_##t##_size(Deque_##t *de) {					\
																\
	}															\
																\
	bool Deque_##t##_equal(Deque_##t *de1, Deque_##t *de2){		\
																\
	}															\
	void Deque_##t##_ctor(Deque_##t *de, void(*cmp)()){			\
		de->													\
	}															\

//TODO 
#endif
