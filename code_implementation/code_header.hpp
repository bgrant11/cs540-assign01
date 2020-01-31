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
	//unsigned int (*dec_idx)(Deque_MyClass *de, unsigned int idx, 
	//									unsigned int amount, size_t capacity);
	//unsigned int (*inc_idx)(Deque_MyClass *de, unsigned int idx, 
	//									unsigned int amount, size_t capacity);
	//unsigned int (*real_idx)(Deque_MyClass *de, unsigned int idx);
	//bool (*has_open_spot)(Deque_MyClass *de);
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
	/*if(de->sz < de->capacity){
		de->data[de->tail % de->capacity] = item;
		de->tail = ( de->tail+1 < 4*de->capacity ) ? de->tail + 1 : 
																2*de->capacity;
	}
	else{
		//TODO resize
	}
	de->sz++; */
	if(de->sz < de->capacity){
		//de->data[de->real_idx(de, de->tail)] = item;
		de->data[de->tail] = item;
		//de->tail = de->inc_idx(de, de->tail, 1, de->capacity);
		de->tail = (de->tail < (de->capacity-1)) ? de->tail + 1 : 0; 
	}													//  increment tail
	else{
		//TODO resize
	}
	de->sz++;
}	
				
void Deque_MyClass_push_front(Deque_MyClass *de, MyClass item) {
	/*if(de->sz < de->capacity){
		de->data[de->head % de->capacity] = item;
		de->head = ( de->head-1 != UINT_MAX ) ? de->head - 1 : 2*de->capacity-1;
	}
	else{
		//TODO resize
	}
	de->sz++; */
	if(de->sz < de->capacity){
		//de->data[de->real_idx(de, de->head)] = item;
		de->data[de->head] = item;		
		//de->head = de->dec_idx(de, de->head, 1, de->capacity);
		de->head = (de->head > 0) ? de->head - 1 : de->capacity - 1;
	}
	else{
		//TODO resize
	}
	de->sz++;
}

MyClass& Deque_MyClass_back(Deque_MyClass *de) {
	//unsigned int idx = de->dec_idx(de, de->tail, 1, de->capacity);
	//unsigned int true_idx = de->real_idx(de, idx);
	unsigned int idx = (de->tail > 0) ? de->tail - 1 : de->capacity - 1;	
	return de->data[idx];
}

MyClass& Deque_MyClass_front(Deque_MyClass *de){
	//unsigned int idx = de->inc_idx(de, de->head, 1, de->capacity);
	//unsigned int true_idx = de->real_idx(de, idx); 	
	unsigned int idx = (de->head < (de->capacity - 1)) ? de->head + 1 : 0;
	return de->data[idx];						
}
					
MyClass& Deque_MyClass_at(Deque_MyClass *de, int idx) {
	//unsigned int idx_of_elem = de->real_idx(de, de->head+idx+1);
	unsigned int idx_of_elem = (de->head + idx) % de->capacity;
	return de->data[idx_of_elem];
	
}
				
bool Deque_MyClass_pop_back(Deque_MyClass *de){
	if(!de->empty(de)){
		//de->tail = de->dec_idx(de, de->tail, 1, de->capacity); 
		de->tail = (de->tail > 0) ? de->tail - 1 : de->capacity - 1;		
		de->sz--;								
			
		return true;							
	}
	return false;
}
					
bool Deque_MyClass_pop_front(Deque_MyClass *de){
	if(!de->empty(de)){
		//de->head = de->inc_idx(de, de->head, 1, de->capacity);
		de->head = (de->head < (de->capacity -1)) ? de->head + 1 : 0;
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
	Deque_MyClass_Iterator it;
	//unsigned int idx = de->inc_idx(de, de->head, 1, de->capacity);
	unsigned int idx = (de->head < (de->capacity -1)) ? de->head + 1 : 0;
	size_t at = 0;
	Deque_MyClass_Iterator_ctor(&it, idx, at, de->data, de->capacity);
	return it;
}

Deque_MyClass_Iterator Deque_MyClass_end(Deque_MyClass *de){
	Deque_MyClass_Iterator it;
	unsigned int idx = de->tail; 
	size_t at = (size_t)de->size;	
	Deque_MyClass_Iterator_ctor(&it, idx, at, de->data, de->capacity);
	return it;
}

//unsigned int Deque_MyClass_dec_idx(Deque_MyClass *de, unsigned int idx, 
//										unsigned int amount, size_t capacity){
//	unsigned int ret = idx;
//	for(unsigned int i = 0; i < amount; i++){
//		ret = ( ret-1 != UINT_MAX ) ? ret - 1 : 2*capacity-1;
//	}
//	return ret;

//}

//unsigned int Deque_MyClass_inc_idx(Deque_MyClass *de, unsigned int idx, 
//										unsigned int amount, size_t capacity){
//	unsigned int ret = idx;
//	for(unsigned int i = 0; i < amount; i++){	
//		ret = ( ret+1 < 4*capacity ) ? ret + 1 : 2*capacity;
//	}
//	return ret;

//}



//unsigned int Deque_MyClass_real_idx(Deque_MyClass *de, unsigned int idx){
//	return idx%de->capacity;
//}

//bool Deque_MyClass_has_open_spot(Deque_MyClass *de){
//	return de->sz < de->capacity;
//}


	
/* Iterator member fns------------------------------------------------ */
void Deque_MyClass_Iterator_inc(Deque_MyClass_Iterator *it){
	//it->idx = ( it->idx+1 < 4*it->capacity ) ? it->idx + 1 : 2*it->capacity;
	//it->idx = it->idx % it->capacity;
	it->idx = (it->idx < (it->capacity - 1)) ? it->idx + 1 : 0;	
	it->at_element++;
	
}


	
void Deque_MyClass_Iterator_dec(Deque_MyClass_Iterator *it){
	//it->idx = ( it->idx-1 != UINT_MAX ) ? it->idx - 1 : 2*it->capacity-1;
	//it->idx = it->idx % it->capacity;
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
	//end1 = de1.end();
	//end2 = de2.end();
	for(unsigned int i = 0; i < de1.sz; i++){
		bool less = de1.comparator(it1.deref(&it1), it2.deref(&it2));
		bool greater = de1.comparator(it2.deref(&it2), it1.deref(&it1));	
		if(less || greater) return false;
	}
	return true;	
																
}

bool Deque_MyClass_Iterator_equal(Deque_MyClass_Iterator it, 
													Deque_MyClass_Iterator end){
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
	de->head = 0;												
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
	//de->inc_idx = Deque_MyClass_inc_idx;
	//de->dec_idx = Deque_MyClass_dec_idx;
	//de->real_idx = Deque_MyClass_real_idx;
	//de->has_open_spot = Deque_MyClass_has_open_spot;	
	//TODO sort
}	


#endif
