#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char st2[] = "123456";


struct MyClass {
    int id;
    char name[20];
	char name2[sizeof(st2)];
};

int
main(){
	printf("%s\n", "Playground");
	const char st[] = "Ssss";
	
	printf("%s\n", st);
	printf("size %lu\n", sizeof(st));
	

	MyClass str;
	strcpy(str.name, st);
	printf("myclass.name %s size %lu\n", str.name, sizeof(str.name));
	
	printf("size st2 %lu\n", sizeof(st2));	
	
	
	strcpy(str.name2, st2);
	printf("str.name2 %s str.name2 size %lu\n", str.name2, sizeof(str.name2));
	
}
