#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{
	//var section
	MY_STRING hMy_string = NULL;
	MY_STRING hAppend = NULL;
	FILE* fp;
	Status check;
	char* c;
	Boolean v;
	
	//initiates
	hMy_string = my_string_init_default();
	fp = fopen("simple.txt", "r");
	my_string_extraction(hMy_string, fp);
	c = my_string_c_str(hMy_string);
	printf("%s\n", c);

	//checks at func
	c = my_string_at(hMy_string, 2);
	printf("The third letter is %c\n\n", *c);
	
	//checks pop back func
	printf("size: %d\n", my_string_get_size(hMy_string));
	check = my_string_pop_back(hMy_string);
	printf("size after pop back: %d, status: %d\n\n", my_string_get_size(hMy_string), check);

	//checks str funct
	c = my_string_c_str(hMy_string);
	printf("C-String: %s\n", c);

	//show push funct
	my_string_push_back(hMy_string, 'e');
	c = my_string_c_str(hMy_string);
	printf("C-String: %s\n\n", c);

	//concat test
	hAppend = my_string_init_c_string("hello");
	c = my_string_c_str(hAppend);
	printf("C-String: %s\n", c);
	my_string_concat(hMy_string, hAppend);
	c = my_string_c_str(hMy_string);
	printf("New C-String: %s\n", c);
	c = my_string_c_str(hAppend);
	printf("String before append C-String: %s\n", c);
	
	//checks empty func
	printf("Checks to see if is empty function & pop back are working\n");
	do{
		check = my_string_pop_back(hMy_string);
		v = my_string_is_empty(hMy_string);
		printf("check value: %d, Boolean Value: %d\n\n", check, v);
	} while (check == 1 || v == 0);

	my_string_destroy(&hMy_string);
	my_string_destroy(&hAppend);
	fclose(fp);
	
	return 0;
}






