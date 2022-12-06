//file contains main.c functions and 

#include "my_string.h"

struct my_string
{
	int size;
	int capacity;
	char *data;
};

typedef struct my_string My_string;


Status my_string_assignment(ITEM *phLeft, ITEM hRight)
{
	int i;
	char *temp;
	My_string *pLeft = (My_string *)*phLeft;
	My_string *pRight = (My_string *)hRight;

	if (pLeft == NULL)
	{
		//we need to create the left my_string

		pLeft = (My_string *)malloc(sizeof(My_string));
		if (pLeft == NULL)
		{
			printf("Failed to create object.\n");
			return FAILURE;
		}
		*phLeft = pLeft;

		pLeft->size = pRight->size;
		pLeft->capacity = pRight->capacity;
		pLeft->data = (char *)malloc(sizeof(char) * pRight->capacity);
		if (pLeft->data == NULL) {

			free(pLeft);
			return FAILURE;

		}
		for (i = 0; i < pLeft->size; i++)
		{
			pLeft->data[i] = pRight->data[i];
		}
		//printf("%s\n", pLeft->data);//delete
	}
	else if (pRight->size >= pLeft->capacity)
	{
		//we need to resize the left my_string

		pLeft->size = pRight->size;
		pLeft->capacity = pRight->capacity;
		temp = (char *)malloc(sizeof(char) * pRight->capacity);
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i < pRight->size; i++)
		{
			temp[i] = pRight->data[i];
		}
		free(pLeft->data);
		pLeft->data = temp;
	}
	else
	{
		//just copy the data and members
		
		pLeft->size = pRight->size;

		for (i = 0; i < pRight->size; i++)
		{
			pLeft->data[i] = pRight->data[i];
		}
	}

	return SUCCESS;
}

MY_STRING my_string_init_default(void)
{
	//allocates space for the structure if it fails null returned exit code 1
	My_string *pstring = (My_string *)malloc(sizeof(My_string));
	if (pstring != NULL)
	{
		//assigns default behavior of My_string 
		pstring->size = 0;
		pstring->capacity = 7;
		pstring->data = (char *)malloc(sizeof(char) * pstring->capacity);//allocates space for char string and stores the address in data pointer
		if (pstring->data == NULL)
		{
			//if allocation failed then the programs frees up allocated space and returns null
			free(pstring);
			return NULL;

		}
	}
	return (MY_STRING)pstring;

}

void my_string_destroy(ITEM *phMy_string)
{
	//function is past a void* holding the address of the structure, then its casted to know type so adress can be acessesd
	My_string *pString = (My_string *)*phMy_string;
	if (pString == NULL) {
		return;
	}

	//gets rid of dynamicaly allocated arrray for data
	free(pString->data);
	free(pString);
	*phMy_string = NULL;

	//printf("Process complete\n");//confirmation statement


}

//Precondtion: c_string is a valid null terminated c-string.
//Postcondition: Allocate space for a string object that represents a string
// with the same value as the given c-string. The capacity of the string
// object will be set to be one greater than is required to hold the string.
// As an example, the string "the" would set capacity at 4 instead of 3. A
// copy of the address of the opaque object will be returned on success and
// NULL on failure.
MY_STRING my_string_init_c_string(const char *c_string)
{
	int i = 0;
	//allocates space for object
	My_string *p_string = (My_string *)malloc(sizeof(My_string));
	if (p_string != NULL)
	{
		while (c_string[i] != '\0')
		{
			i++;
		}
		//size starts as given 
		p_string->size = i;
		p_string->capacity = i + 1;//capacity is one larger than size
		p_string->data = (char *)malloc(sizeof(char) * p_string->capacity);//mallocs a dynamic array for the string 
		if (p_string->data == NULL)//safty net
		{
			free(p_string->data);
			return NULL;
		}
		//copy loop
		for (i = 0; i < p_string->size; i++)
		{
			(*p_string).data[i] = c_string[i];
		}


	}
	//printf("copy complete\n");//confirmation 
	return p_string;

}

//Precondition: hMy_string is the handle of a valid My_string object.
//Postcondtion: Returns a copy of the integer value of the object's capacity.
int my_string_get_capacity(MY_STRING hMy_string)
{
	My_string *p_string = (My_string *)hMy_string;//cast to the known type
	//return an integer value
	return p_string->capacity;

}

//Precondition: hMy_string is the handle of a valid My_string object.
//Postcondtion: Returns a copy of the integer value of the object's size.
int my_string_get_size(MY_STRING hMy_string)
{
	My_string *p_string = (My_string *)hMy_string;//cast to the known type
	//return an integer value
	return p_string->size;
}


//Precondition: hLeft_string and hRight_string are valid My_string objects.
//Postcondition: returns an integer less than zero if the string represented
// by hLeft_string is lexicographically smaller than hRight_string. If
// one string is a prefix of the other string then the shorter string is
// considered to be the smaller one. (app is less than apple). Returns
// 0 if the strings are the same and returns a number greater than zero
// if the string represented by hLeft_string is bigger than hRight_string.
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	int i, asciiSizeLeft = 0, asciiSizeRight = 0;
	char diff_char;
	//cast to known type in order to access object data
	My_string *pLeft_string = (My_string *)hLeft_string;
	My_string *pRight_string = (My_string *)hRight_string;

	if (pRight_string->size == pLeft_string->size)
	{
		//compares each value
		for (i = 0; i < pRight_string->size; i++)
		{
			diff_char = pLeft_string->data[i] - pRight_string->data[i];
			if (diff_char != 0)
			{
				return diff_char;
			}
		}
		return 0;
	}
	else
	{
		if (pRight_string->size > pLeft_string->size)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}


}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: hMy_string will be the handle of a string object that contains
// the next string from the file stream fp according to the following rules.
// 1) Leading whitespace will be ignored.
// 2) All characters (after the first non-whitespace character is obtained
// and included) will be added to the string until a stopping condition
// is met. The capacity of the string will continue to grow as needed
// until all characters are stored.
// 3) A stopping condition is met if we read a whitespace character after
// we have read at least one non-whitespace character or if we reach
// the end of the file.
// Function will return SUCCESS if a non-empty string is read successfully.
// and failure otherwise. Remember that the incoming string may aleady
// contain some data and this function should replace the data but not
// necessarily resize the array unless needed.
Status my_string_extraction(MY_STRING hMy_string, FILE *fp)
{
	int noc;
	char c;

	//cast
	My_string *pstring = (My_string *)hMy_string;
	//set string size to zeroe size to 0 and writes over old content
	pstring->size = 0;

	/*gets first char without white space then checks then
	it has guard in case eof is reached and c is corrupted
	in which case function fails*/
	noc = fscanf(fp, " %c", &c);
	if (noc == EOF)
	{
		return FAILURE;
	}
	if (my_string_push_back(hMy_string, c) == FAILURE)
	{
		printf("ERROR: Failed to allocate space");
		return FAILURE;
	}

	//reads all spaces after first non white space ends if eOf is reached or a white space
	while (noc == 1 && c != ' ' && noc != EOF && c != '\n')
	{
		/*assumes noc has a healthy value and c is not a white space
		gets a new value checks if the program is at Eof, or picked up another white space or newline and should return
		if it makes it past that exit condition then it puts the element in the
		array. */
		noc = fscanf(fp, "%c", &c);
		if (noc == EOF)
		{
			return SUCCESS;
		}
		if (c == '\n' || c == ' ')
		{
			break;
		}
		if (my_string_push_back(hMy_string, c) == FAILURE)
		{
			printf("ERROR: Failed to allocate space");
			return FAILURE;
		}
	}

	//moves file pointer back a position so white space is readable 
	fseek(fp, -1, SEEK_CUR);
	//makes it here it has should have run succesfuly
	return SUCCESS;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Writes the characters contained in the string object indicated
// by the handle hMy_string to the file stream fp.
// Function will return SUCCESS if it successfully writes the string and
// FAILURE otherwise.
Status my_string_insertion(MY_STRING hMy_string, FILE *fp)
{
	My_string *pstring = (My_string *)hMy_string;

	int noc = fprintf(fp, "%.*s", pstring->size, pstring->data);
	return noc >= 0 ? SUCCESS : FAILURE;
}

//Pre-condition: gets a handle to a string and value to add to the string
//Post-condition: item will be added to the string and string->data will be double if
//the data is not within the capacity
Status my_string_push_back(MY_STRING hMy_string, char value)
{
	//casts to known type
	My_string *pstring = (My_string *)hMy_string;
	//creates a temp for data which is a dynamically allocated array for chars
	//char* temp;

	//if there isn't enough space we will make space
	if (my_string_resize_up(hMy_string) == FAILURE)
	{
		return FAILURE;
	}

	//puts char value at the next index then increaeses size
	/*Note: This works because size when no items are in is
	* '0' and when one item is in size is '1' but mind the one
	* item is in index '0' not one so size is already one place
	* ahead as far as indexes are concerend.
	*/
	pstring->data[pstring->size] = value;
	pstring->size++;

	// the program made it to here it had to have run correctly.
	return SUCCESS;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Removes the last character of a string in constant time.
// Guaranteed to not cause a resize operation of the internal data. Returns
// SUCCESS on success and FAILURE if the string is empty.
Status my_string_pop_back(MY_STRING hMy_string)
{
	My_string *pstring = (My_string *)hMy_string;
	if (pstring->size > 0 && pstring != NULL)
	{
		pstring->size--;
		return SUCCESS;
	}

	return FAILURE;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Returns the address of the character located at the given
// index if the index is in bounds but otherwise returns NULL. This address
// is not usable as a c-string since the data is not NULL terminated and is
// intended to just provide access to the element at that index.
char *my_string_at(MY_STRING hMy_string, int index)
{
	My_string *pstring = (My_string *)hMy_string;
	//guard against inproper bounds
	if (index < 0 || index >= pstring->size)
	{
		return NULL;
	}
	//does address aritmitic fo find nth index
	return pstring->data + index;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Returns the address of the first element of the string object
// for use as a c-string. The resulting c-string is guaranteed to be NULL
// terminated and the memory is still maintained by the string object though
// the NULL is not actually counted as part of the string (in size).
char *my_string_c_str(MY_STRING hMy_string)
{
	My_string *pstring = (My_string *)hMy_string;
	if (pstring == NULL)
	{
		return NULL;
	}

	//resizes if neccasary
	if (pstring->size >= pstring->capacity)
	{
		if (my_string_resize_up(hMy_string) == FAILURE)
		{
			return NULL;
		}
	}

	pstring->data[pstring->size] = '\0';
	return pstring->data;
}

//precondition: hMystring is a valid object handle
//postcondtion: the memory footprint of hMystring data will be doubled 
Status my_string_resize_up(MY_STRING hMy_string)
{
	My_string *pstring = (My_string *)hMy_string;
	char *temp;
	int i;

	if (pstring->size >= pstring->capacity)
	{
		//says take size of char multiply it with the current size of capacity to get
		// current capacity then multiply that by 2 to double size
		temp = (char *)malloc(sizeof(char) * pstring->capacity * 2);
		if (temp == NULL)
		{
			return FAILURE;
		}
		//compy data into temporary 
		for (i = 0; i < pstring->size; i++)
		{
			temp[i] = pstring->data[i];
		}
		//frees old array at data but gives us space to add new one 
		free(pstring->data);
		pstring->data = temp;
		//doubles capacity to match the new size
		pstring->capacity *= 2;

		return SUCCESS;
	}

	return SUCCESS;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Returns an enumerated type with value TRUE if the string
// is empty and FALSE otherwise.
Boolean my_string_is_empty(MY_STRING hMy_string)
{
	My_string *pstring = (My_string *)hMy_string;
	if (pstring->size == 0)
	{
		return TRUE;
	}
	return FALSE;

}

//Precondition: hResult and hAppend are handles to valid My_string objects.
//Postcondition: hResult is the handle of a string that contains the original
// hResult object followed by the hAppend object concatenated together. This
// function should guarantee no change to the hAppend object and return
// SUCCESS if they operation is successful and FAILURE if the hResult object
// is unable to accomodate the characters in the hAppend string perhaps
// because of a failed resize operation. On FAILURE, no change to either
// string should be made.
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	My_string *pstring1 = (My_string *)hResult;
	My_string *pstring2 = (My_string *)hAppend;
	Status critical_error;
	int i, size;
	char c;

	//gets size of hresult
	size = pstring1->size;

	//checks for a valid input
	if (pstring1 == NULL || pstring2 == NULL)
	{
		return FAILURE;
	}

	for (i = 0; i < pstring2->size; i++)
	{
		c = pstring2->data[i];

		//segement inserts new letters into the result string
		if (my_string_push_back((MY_STRING)pstring1, c) != SUCCESS)
		{
			while (i > size)//if it failed to push then run if statment till i = original size
			{
				critical_error = my_string_pop_back(hResult);//removes elments form size till it reaches orginal content
				if (critical_error == FAILURE)//if it failed to pop back all the way then...
				{
					printf("CRITICAL ERROR: STRING CORRUPTED\n");//there was a critical error and string is corrupted
					return FAILURE;
				}
				i--;
			}
			return FAILURE;
		}
	}
	return SUCCESS;
}


//Precondition:current_word_family, new_key and word are all handles to valid
// MY_STRING opaque objects. guess is an alphabetical character that can be either
// upper or lower case.
//Postcondition: Returns SUCCESS after replacing the string in new_key with the key
// value formed by considering the current word family, the word and the guess.
// Returns failure in the case of a resizing problem with the new_key string.
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
	int i;
	My_string *pString_current_word_family = (My_string *)current_word_family;
	My_string *pString_word = (My_string *)word;

	my_string_assignment(&new_key, current_word_family);
	My_string *pString_new_key = (My_string *)new_key;

	for (i = 0; i < my_string_get_size(word); i++)
	{
		if (*(my_string_at(word, i)) == guess)
		{
			pString_new_key->data[i] = guess;
		}
	}

	return SUCCESS;
}

