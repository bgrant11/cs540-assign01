#ifndef DEQUE_H
#define DEQUE_H





#define Deque_DEFINE(t)														\
	struct Deque_##t {														\
		size_t	(*size)(Deque_##t *de);										\
	};																		\
																			\
	struct Deque_##t##_iterator {											\
																			\
	};																		\
																			\

//TODO what to do with Deque_##t##_ctor() 

#endif
