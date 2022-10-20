#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{

	MY_STRING hMy_string = NULL;
	FILE* fp;
        int size;	
        
	hMy_string = my_string_init_default();
	fp = fopen("dictionary.txt", "r");

	
	//driver
	while (my_string_extraction(hMy_string, fp)) {

		//gets ride of white space when file stream is moved back one
		
		//gets size and adjusts for whites space
		size = my_string_get_size(hMy_string);
		
		if (size == 5)
		{
			my_string_insertion(hMy_string, stdout);
			fprintf(stdout, "\n");
		}
				
	}

	my_string_destroy(&hMy_string);
	fclose(fp);

	return 0;
}






