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
#include <limits.h>


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
void Deque_MyClass_Iterator_ctor(Deque_MyClass_Iterator * it, unsigned int idx, 
							size_t at_element, MyClass *data, size_t capacity);

// define DEQUE_Myclass


const char MyClass_type_name[] = "Deque_MyClass";

struct Deque_MyClass {
	MyClass *data;	
	char type_name[sizeof(MyClass_type_name)]; /* how to set*/						
	unsigned int head;												
	unsigned int tail;												
	size_t sz; /* TODO should i have this */	
	size_t capacity;			
	size_t (*size)(Deque_MyClass *de); /* size fp */			
	bool (*empty)(Deque_MyClass *de); /* true if empty */ 		
	void (*push_back)(Deque_MyClass *de, MyClass item);				
	void (*push_front)(Deque_MyClass *de, MyClass item);				
	MyClass& (*back)(Deque_MyClass *de); /* TODO return const reference?*/	
	MyClass& (*front)(Deque_MyClass *de);						
	MyClass& (*at)(Deque_MyClass *de, int idx);					
	bool (*pop_back)(Deque_MyClass *de);						
	bool (*pop_front)(Deque_MyClass *de);						
	void (*clear)(Deque_MyClass *de);							
	void (*dtor)(Deque_MyClass *de);
	bool (*comparator)(const MyClass& o1, const MyClass &o2);
	Deque_MyClass_Iterator (*begin)(Deque_MyClass *de);
	Deque_MyClass_Iterator (*end)(Deque_MyClass *de);
};

	/* Iterator struct-------------------------------------------------*/
struct Deque_MyClass_Iterator {								
	unsigned int idx;
	size_t at_element;
	size_t capacity;	
	void (*inc)(Deque_MyClass_Iterator *it);	
	void (*dec)(Deque_MyClass_Iterator *it);
	MyClass& (*deref)(Deque_MyClass_Iterator *it);
	MyClass * data;
};

/* DEQ member fns------------------------------------------------ */
size_t Deque_MyClass_size(Deque_MyClass *de) {					
	return de->sz;													
}															

bool Deque_MyClass_empty(Deque_MyClass *de) {
	if(!de->sz) return true;
	return false;
}

			
void Deque_MyClass_push_back(Deque_MyClass *de, MyClass item) {
	if(de->sz < de->capacity){
		de->data[de->tail] = item;
		//printf("push_back de->tail before %u\n", de->tail);
		de->tail = (de->tail < (de->capacity-1)) ? de->tail + 1 : 0; 
		//printf("push_back de->tail after %u\n", de->tail);
	}													//  increment tail
	else{
		//TODO resize
	}
	
	de->sz++;
}	
				
void Deque_MyClass_push_front(Deque_MyClass *de, MyClass item) {
	if(de->sz < de->capacity){
		de->data[de->head] = item;		
		//printf("push_front de->head before %u\n", de->head);	
		de->head = (de->head > 0) ? de->head - 1 : de->capacity - 1;
		//printf("push_front de->head after %u\n", de->head);	
	}
	else{
		//TODO resize
	}
	de->sz++;
}

MyClass& Deque_MyClass_back(Deque_MyClass *de) {
	unsigned int idx = (de->tail > 0) ? de->tail - 1 : de->capacity - 1;	
	return de->data[idx];
}

MyClass& Deque_MyClass_front(Deque_MyClass *de){	
	unsigned int idx = (de->head < (de->capacity - 1)) ? de->head + 1 : 0;
	return de->data[idx];						
}
					
MyClass& Deque_MyClass_at(Deque_MyClass *de, int idx) {
	unsigned int idx_of_elem = (de->head + idx+ 1) % de->capacity;
	return de->data[idx_of_elem];
	
}
				
bool Deque_MyClass_pop_back(Deque_MyClass *de){
	if(!de->empty(de)){ 
		//printf("pop_back de->tail before %u\n", de->tail);		
		de->tail = (de->tail > 0) ? de->tail - 1 : de->capacity - 1;		
		//printf("pop_back de->tail after %u\n", de->tail);
		de->sz--;								
			
		return true;							
	}
	return false;
}
					
bool Deque_MyClass_pop_front(Deque_MyClass *de){
	if(!de->empty(de)){
		//printf("pop_front de->head before %u\n", de->head);		
		de->head = (de->head < (de->capacity -1)) ? de->head + 1 : 0;
		//printf("pop_front de->head after %u\n", de->head);	
		de->sz--;		
		return true;							
	}
	return false;
}		
				
void Deque_MyClass_clear(Deque_MyClass *de){ 
	de->head = 0;
	de->tail = 0;
	de->sz = 0;
}
						
void Deque_MyClass_dtor(Deque_MyClass *de){
	free(de->data); //TODO set to null?
	de->data = NULL;
}

Deque_MyClass_Iterator Deque_MyClass_begin(Deque_MyClass *de){
	//printf("in iterator begin\n");	
	Deque_MyClass_Iterator it;
	unsigned int idx = (de->head < (de->capacity -1)) ? de->head + 1 : 0;
	//printf("de->head %u\n", de->head);	
	//printf("idx %u\n", idx);	
	size_t at = (size_t)0;
	Deque_MyClass_Iterator_ctor(&it, idx, at, de->data, de->capacity);
	//printf("it.idx %u it.at_element %lu it->capacity %lu\n", it.idx, it.at_element, it.capacity);
	return it;
}

Deque_MyClass_Iterator Deque_MyClass_end(Deque_MyClass *de){
	//printf("in iterator end\n");	
	Deque_MyClass_Iterator it;
	unsigned int idx = de->tail; 
	size_t at = (size_t)de->sz;	
	Deque_MyClass_Iterator_ctor(&it, idx, at, de->data, de->capacity);
	//printf("it.idx %u it.at_element %lu it->capacity %lu\n", it.idx, it.at_element, it.capacity);
	return it;
}


	
/* Iterator member fns------------------------------------------------ */
void Deque_MyClass_Iterator_inc(Deque_MyClass_Iterator *it){
	it->idx = (it->idx < (it->capacity - 1)) ? it->idx + 1 : 0;	
	it->at_element++;
	
}


	
void Deque_MyClass_Iterator_dec(Deque_MyClass_Iterator *it){
	it->idx = (it->idx > 0) ? it->idx - 1 : it->capacity - 1;
	it->at_element--;
	
}


MyClass& Deque_MyClass_Iterator_deref(Deque_MyClass_Iterator *it){
	return it->data[it->idx];
}
	
/* ctor and other fns ------------------------------------------s----- */	
bool Deque_MyClass_equal(Deque_MyClass& de1, Deque_MyClass& de2){		
	if(de1.sz != de2.sz) return false;
	Deque_MyClass_Iterator it1, it2; //end1, end2;
	it1 = de1.begin(&de1);
	it2 = de2.begin(&de2);
	for(unsigned int i = 0; i < de1.sz; i++){
		bool less = de1.comparator(it1.deref(&it1), it2.deref(&it2));
		bool greater = de1.comparator(it2.deref(&it2), it1.deref(&it1));	
		if(less || greater) return false;
		it1.inc(&it1);
		it2.inc(&it2);
	}
	return true;	
																
}

bool Deque_MyClass_Iterator_equal(Deque_MyClass_Iterator it, 
													Deque_MyClass_Iterator end){
	//printf("in iterator equal\n");
	//printf("it.idx %u end.idx %u it.at_element %lu end.at_element %lu\n",
			//it.idx, end.idx, it.at_element, end.at_element);
	return (it.idx == end.idx) && (it.at_element == end.at_element);
}

void Deque_MyClass_Iterator_ctor(Deque_MyClass_Iterator * it, unsigned int idx, 
							size_t at_element, MyClass *data, size_t capacity){
	it->idx = idx;
	it->at_element = at_element;
	it->inc = Deque_MyClass_Iterator_inc;
	it->dec = Deque_MyClass_Iterator_dec;
	it->deref = Deque_MyClass_Iterator_deref;
	it->data = data;
	it->capacity = capacity;
}
														
void Deque_MyClass_ctor(Deque_MyClass *de, 
							bool (*cmp)(const MyClass &o1, const MyClass &o2)){
	de->data = (MyClass*)malloc(sizeof(MyClass)*5);	
	strcpy(de->type_name, MyClass_type_name);				
	de->head = 5-1;												
	de->tail = 0;										
	de->sz = 0;	
	de->capacity = 5;			
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
	//TODO sort
}	


#endif
