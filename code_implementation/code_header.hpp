#ifndef CODE_HEADER_H
#define CODE_HEADER_H

#include <dlfcn.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <random>
#include <unistd.h>
#include <string.h>
#include <algorithm>
#include <typeinfo>


struct MyClass {
    int id;
    char name[10];
};

bool
MyClass_less_by_id(const MyClass &o1, const MyClass &o2) {
    return o1.id < o2.id;
}

bool
MyClass_less_by_name(const MyClass &o1, const MyClass &o2) {
    return strcmp(o1.name, o2.name) < 0;
}

void
MyClass_print(const MyClass *o) {
    printf("%d\n", o->id);
    printf("%s\n", o->name);
}

struct Deque_MyClass_Iterator; // forward decl;

// define DEQUE_Myclass


const char MyClass_type_name[] = "Deque_MyClass";

struct Deque_MyClass {
	char type_name[sizeof(MyClass_type_name)]; /* how to set*/						
	int head;												
	int tail;												
	size_t sz; /* TODO should i have this */				
	size_t (*size)(Deque_MyClass *de); /* size fp */			
	bool (*empty)(Deque_MyClass *de); /* true if empty */ 		
	void (*push_back)(Deque_MyClass *de, MyClass item);				
	void (*push_front)(Deque_MyClass *de, MyClass item);				
	MyClass& (*back)(Deque_MyClass *de); /* TODO return const reference?*/	
	MyClass& (*front)(Deque_MyClass *de);						
	MyClass& (*at)(Deque_MyClass *de, int idx);					
	void (*pop_back)(Deque_MyClass *de);						
	void (*pop_front)(Deque_MyClass *de);						
	void (*clear)(Deque_MyClass *de);							
	void (*dtor)(Deque_MyClass *de);
	bool (*comparator)(const MyClass& o1, const MyClass &o2);
	Deque_MyClass_Iterator (*begin)(Deque_MyClass *de);
	Deque_MyClass_Iterator (*end)(Deque_MyClass *de);
};

	/* Iterator struct-------------------------------------------------*/
struct Deque_MyClass_Iterator {								
	void (*inc)(Deque_MyClass_Iterator *it);	
	void (*dec)(Deque_MyClass_Iterator *it);
	MyClass& (*deref)(Deque_MyClass_Iterator *it);
};

/* DEQ member fns------------------------------------------------ */
size_t Deque_MyClass_size(Deque_MyClass *de) {					
															
}															

bool Deque_MyClass_empty(Deque_MyClass *de) {

}
			
void Deque_MyClass_push_back(Deque_MyClass *de, MyClass item) {
	
}
				
void Deque_MyClass_push_front(Deque_MyClass *de, MyClass item) {
	
}

MyClass& Deque_MyClass_back(Deque_MyClass *de) {

}

MyClass& Deque_MyClass_front(Deque_MyClass *de){

}
					
MyClass& Deque_MyClass_at(Deque_MyClass *de, int idx) {

}
				
void Deque_MyClass_pop_back(Deque_MyClass *de){
	
}
					
void Deque_MyClass_pop_front(Deque_MyClass *de){

}		
				
void Deque_MyClass_clear(Deque_MyClass *de){

}
						
void Deque_MyClass_dtor(Deque_MyClass *de){

}

Deque_MyClass_Iterator Deque_MyClass_begin(Deque_MyClass *de){

}

Deque_MyClass_Iterator Deque_MyClass_end(Deque_MyClass *de){

}



	
/* Iterator member fns------------------------------------------------ */
bool Deque_MyClass_Iterator_equal(Deque_MyClass_Iterator it, 
													Deque_MyClass_Iterator end){

}
	
/* ctor and other fns ------------------------------------------s----- */	
bool Deque_MyClass_equal(Deque_MyClass& de1, Deque_MyClass& de2){		
																
}														
void Deque_MyClass_ctor(Deque_MyClass *de, 
							bool (*cmp)(const MyClass &o1, const MyClass &o2)){
	strcpy(de->type_name, MyClass_type_name);				
	de->head = 0;												
	de->tail = 0;											
	de->sz = 0;				
	de->size = Deque_MyClass_size;
	de->empty = Deque_MyClass_empty;
	de->push_back = Deque_MyClass_push_back;
	de->push_front = Deque_MyClass_push_front;
	de->back = Deque_MyClass_back;
	de->front	= Deque_MyClass_front;	
	de->at = Deque_MyClass_at;
	de->pop_back = Deque_MyClass_pop_back;
	de->pop_front	= Deque_MyClass_pop_front;
	de->clear	= Deque_MyClass_clear;			
	de->dtor = Deque_MyClass_dtor;
	de->comparator = cmp;	
	de->begin = Deque_MyClass_begin;	// currently returns new iterators
	de->end = Deque_MyClass_end;			// should they return member iterators
}	


#endif
