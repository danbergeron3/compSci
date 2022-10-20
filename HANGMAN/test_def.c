#include "unit_test.h"
#include <string.h>

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
 	MY_STRING hString = NULL;
 	hString = my_string_init_default();
 	
	if(hString == NULL)
 	{
		strncpy(buffer, "test_init_default_returns_nonNULL\n"
 			"my_string_init_default returns NULL", length);
 		
		return FAILURE;
 	}
 	else
	{
		my_string_destroy(&hString);
 			strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
 		
		return SUCCESS;
	}
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
 	
	MY_STRING hString = NULL;
 	Status status;
 	hString = my_string_init_default();
 	
	if(my_string_get_size(hString) != 0)
 	{	
 		status = FAILURE;
 		printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
 		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
 		"Did not receive 0 from get_size after init_default\n", length);
 	}	
 	else
 	{
 		status = SUCCESS;
 		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
 			, length);
 	}
 	
        my_string_destroy(&hString);
	return status;
}

Status dbergero_test_get_capacity_on_init_default_returns_7(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();

	if(my_string_get_capacity(hString)!= 7)
	{
		status = FAILURE;
		printf("Expected a capacity of 7 but got %d\n", my_string_get_capacity(hString));
		strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n"
		"Did not receive 7 from get size after init_default\n", length);
		return status;
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n"
				, length);
	}

	my_string_destroy(&hString);
	return status;
}

Status dbergero_test_data_allocation_on_init_default_returns_handle(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();

	if(hString ==  NULL)
	{
		status = FAILURE;
		printf("EXPECTED VOID* ADDRESS GOT NULL\n");
		strncpy(buffer, "dbergero_test_data_allocation_on_init_default_returns_address\n"
		"Did not receive a void* address from the init_default\n", length);
		return status;	
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "dbergero_test_data_allocation_on_init_default_returns_address\n", length);
	}
	my_string_destroy(&hString);
	return status;
}
Status dbergero_test_my_string_destroy_sets_handle_to_NULL(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();

	if(hString != NULL)
	{
		my_string_destroy(&hString);
		if(hString != NULL)
		{
			status = FAILURE;
			printf("Expected hString to be set to NULL");
			strncpy(buffer, "dbergero_test_my_string_destroy_sets_handle_to_NULL\n"
			"was not set to NULL from my_string_destroy\n", length);
		}
		else
		{
			status = SUCCESS;
			strncpy(buffer,"dbergero_test_my_string_destroy_sets_handle_to_NULL\n ", length);
		}
	}
	else
	{
		status = FAILURE;
	}

	return status;
}
Status dbergero_test_my_string_init_c_string_returns_valid_handle(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("TEST");
	if(hString == NULL)
	{
		status = FAILURE;
		printf("Expected hString to be valid handle");
		strncpy(buffer, "dbergero_my_string_init_c_string_returns_vaild_handle\n"
		"was not given a valid handle\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer,"dbergero_my_string_init_c_string_returns_valid_handle\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status dbergero_test_my_string_init_c_string_returns_size_of_string_TEST(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("TEST");
	if(hString != NULL)
	{
		if(my_string_get_size(hString) != 4)
		{
			status = FAILURE;
		        printf("Expected to receive integer 4 instead received %d\n", my_string_get_size(hString));
			strncpy(buffer, "dbergero_test_my_string_init_c_string_returns_size_of_string_TEST\n"
			"did not receive integer 4 from object size\n", length);
		}
		else
		{	
			status = SUCCESS;
			strncpy(buffer, "dbergero_test_my_string_init_c_string_returns_size_of_string_TEST\n", length);
		}
	}
	else
	{
		status = FAILURE;
	}
	my_string_destroy(&hString);
	return status;	
}

Status dbergero_test_my_string_init_c_string_returns_capacity_of_string_TEST(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("TEST");
	if(hString != NULL)
	{
		if(my_string_get_capacity(hString) != 5)
		{
			status = FAILURE;
			printf("Expected a capacity of 5 instead received a capacity of %d\n", my_string_get_capacity(hString));
			strncpy(buffer, "dbergero_test_my_string_init_c_string_returns_capacity_of_string_TEST\n"
			"did not receive string capacity of TEST\n", length);
		}
		else
		{
			status = SUCCESS;
			strncpy(buffer, "dbergero_test_my_string_init_c_string_returns_size_of_string_TEST\n", length);
		}
	}
	else
	{
		status = FAILURE;
	}
	my_string_destroy(&hString);
	return status;
}

Status dbergero_test_my_string_compare_returns_0_for_same_size(char* buffer, int length)
{
	MY_STRING hString1, hString2 = NULL;
	Status status;
	hString1 = my_string_init_c_string("TEST");
	hString2 = my_string_init_c_string("TEST");
	if(hString1 != NULL && hString2 != NULL)
	{
		if(my_string_compare(hString1, hString2)!= 0)
		{
			status = FAILURE;
			printf("Expected a 0 instead received %d\n", my_string_compare(hString1, hString2));
			strncpy(buffer, "dbergero_test_my_string_compare_returns_0_for_same_size\n"
			"did not receive 0 from string comparison\n", length);
		}	
		else
		{
			status = SUCCESS;
		        strncpy(buffer, "dbergero_test_my_string_compare_returns_0_for_same_size\n", length);	
		}

	}
	else
	{
		status = FAILURE;
	}
	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;

}

Status dbergero_test_my_string_compare_returns_greater_than_0_for_hleft_greater_than_hright(char* buffer, int length)
{
	MY_STRING hString1, hString2 = NULL;
	Status status;
	hString1 = my_string_init_c_string("GREATER");
	hString2 = my_string_init_c_string("LESS");
	if(hString1 != NULL && hString2 != NULL)
	{
		if(my_string_compare(hString1, hString2) < 0)
		{
			status = FAILURE;
			printf("Expeceted to return greater than 0 instead returned %d\n", my_string_compare(hString1, hString2));
			strncpy(buffer, "dbergero_test_my_string_compare_returns_greater_than_0_for_hleft_greater_than_hright\n"
			"did not receive integer > 0 from string comparison\n", length);
		}
		else
		{
			status = SUCCESS;
			strncpy(buffer, "dbergero_test_my_string_compare_returns_greater_than_0_for_hleft_greater_than_hright\n", length);
		}
	}
	else
	{
		status = FAILURE;
	}
	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;

}
	
Status dbergero_test_my_string_compare_returns_less_than_0_for_hright_greater_than_hleft(char* buffer, int length)
{
	MY_STRING hString1, hString2 = NULL;
	Status status;	
	hString1 = my_string_init_c_string("LESS");
	hString2 = my_string_init_c_string("GREATER");
	if(hString1 != NULL && hString2 != NULL)
	{
		if(my_string_compare(hString1, hString2) > 0)
		{
			status = FAILURE;
			printf("Expected to return < 0 instead returned %d\n", my_string_compare(hString1, hString2));
			strncpy(buffer, "dbergero_test_my_string_compare_returns_less_than_0_for_hright_greater_than_hleft\n"
			"did not receive integer < 0 from string comparison\n", length);
		}
		else
		{
			status = SUCCESS;
			strncpy(buffer, "dbergero_test_my_string_compare_returns_less_than_0_for_hright_greater_than_hleft\n", length);
		}
	}
	else
	{
		status = FAILURE;
	}
	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;
}

Status dbergero_test_my_string_extraction_skips_leading_blanks(char* buffer, int length)
{
	MY_STRING hString = NULL;
	FILE* fp;
	Status status = FAILURE;
	char *str;
	char c;

	fp = fopen("simple.txt", "r");
	hString = my_string_init_default();
	if(hString != NULL)
	{
		if(my_string_extraction(hString, fp))
		{
			str  = my_string_c_str(hString);
			c = str[0];
			if(c == ' ')
			{
				status = FAILURE;
				printf("Expected to receive a non-whitespace character\n");
				strncpy(buffer, "dbergero_test_my_string_extraction_skips_leading_blanks\n"
				"received a leading white space from extraction\n", length);
			}
			else
			{
				status = SUCCESS;
				strncpy(buffer, "dbergero_test_my_string_extraction_skips_leading_blanks\n", length);
			}
		}		
	}
	fclose(fp);
	my_string_destroy(&hString);
	return status;
}

Status dbergero_test_my_string_extraction_expands_my_string_so_size_less_than_capacity(char* buffer, int length)
{
	MY_STRING hString = NULL;
	FILE* fp;
	Status status = FAILURE;
	int size1, size2, cap1, cap2;
	
	fp = fopen("test.txt", "r");  
	hString = my_string_init_c_string("hello");
	if(hString != NULL)
	{
		size1 = my_string_get_size(hString);
		cap1 = my_string_get_capacity(hString);
		if(my_string_extraction(hString, fp))
		{
			size2 = my_string_get_size(hString);
			cap2 = my_string_get_capacity(hString);
			//second part of if statement is to just see if the string grew and
			//the capacity > size test will even be possible
			//remember: this function is just testing if a string that already exists
			//will grow if my_string_extraction is called using it as a parmeter
			if(cap2 > size2 && (cap2 > cap1 && size2 > size1))
			{
				status = SUCCESS;
				strncpy(buffer, "dbergero_test_my_string_extraction_expands_my_string_so_size_less_than_capacity\n", length);
			}
			else
			{
				printf("Expected capcity to be greater than size and both to be greater than former string\n");
				strncpy(buffer, "dbergero_test_my_string_extraction_expands_my_string_so_size_less_than_capacity\n"
				"size was not less than capcity or string failed to compund\n", length);
			}
		}
		else
		{
			return status;
		}
	}
	fclose(fp);
	my_string_destroy(&hString);
	return status;

}

Status dbergero_test_my_string_extraction_fails_for_empty_string(char* buffer, int length)
{
	MY_STRING hString = NULL;
	FILE *fp;
	Status status = FAILURE;
	
	fp = fopen("empty.txt", "r");
	hString = my_string_init_default();
	
	if(hString != NULL)
	{
		if(my_string_extraction(hString, fp)){
			printf("expeceted to return failure instead received a non-empty string\n");
			strncpy(buffer, "dbergero_test_my_string_extraction_fails_for_empty_string\n"
			"string was not empty contained valid chars\n", length);
		}
		else
		{
			status = SUCCESS;
			strncpy(buffer,"dbergero_test_my_string_extraction_fails_for_empty_string\n", length);
		}
	}
	fclose(fp);
	my_string_destroy(&hString);
	return status;

}

Status dbergero_test_my_string_insertion_sets_size_to_0(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status = FAILURE;

	hString = my_string_init_c_string("size");
	if(hString != NULL || my_string_get_size(hString) != 0)
	{
		my_string_insertion(hString, stdout);
		if(my_string_get_size(hString)!= 0)
		{
			printf("expected 0 instead received %d\n", my_string_get_size(hString));
			strncpy(buffer, "dbergero_test_my_string_sets_size_to_0\n"
			"string insertion did not set a proper size to 0\n", length);
		}
		else
		{
			status = SUCCESS;
			strncpy(buffer, "dbergero_test_my_string_insertion_sets_size_to_0\n", length);
		}
	}
	my_string_destroy(&hString);
	return status;

}

Status dbergero_test_my_string_insertion_returns_SUCCESS(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status = FAILURE;

	hString = my_string_init_c_string("word");
	if(hString != NULL)
	{
		if(my_string_insertion(hString, stdout))
		{
			status = SUCCESS;
			strncpy(buffer, "dbergero_test_my_string_insertion_returns_SUCCESS\n", length);
		}
		else
		{
			printf("expected to receive a SUCCESS\n");
			strncpy(buffer,"dbergero_test_my_string_insertion_returns_SUCCESS\n"
			"did not returns SUCCESS string insertion FAILURE\n", length);
		}
		my_string_destroy(&hString);
	}
	return status;

}

Status dbergero_test_my_string_push_back_resize_SUCCESS(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status = FAILURE;
	int cap1, cap2;
	hString = my_string_init_c_string("cat");
	cap1 = my_string_get_capacity(hString);
	
	if(hString != NULL)
	{
		my_string_push_back(hString, 'i');
		cap2 = my_string_get_capacity(hString);
	
		if(cap1 >= cap2)
		{
			printf("Expeceted cap1 < cap2 instead %d >= %d\n", cap1, cap2 );
			strncpy(buffer, "dbergero_test_my_string_push_back_resize_SUCCESS\n"
			"resize failed\n", length);
		}
		else
		{
			status = SUCCESS;
			strncpy(buffer, "dbergero_test_my_string_push_back_resize_SUCCESS\n", length);
		}
		my_string_destroy(&hString);
	}
	
	return status;
}

Status dbergero_test_my_string_push_back_stores_char_value(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status = FAILURE;
	char* c;
	hString = my_string_init_c_string("mat");
	if(hString != NULL)
	{
		my_string_push_back(hString, 'h');
		c = my_string_at(hString, 3);
		if(*c != 'h')
		{
			printf("Expected char h instead received %c\n", *c);
			strncpy(buffer, "dbergero_test_my_string_push_back_stores_char_value\n"
			"Failed to store value or stored at invalid index\n", length);
		}
		else
		{
			status = SUCCESS;
			strncpy(buffer, "dbergero_test_my_string_push_back_stores_char_value\n",length);
		}
		my_string_destroy(&hString);
	}	
	return status;
}

Status dbergero_test_my_string_at_returns_NULL_at_invalid_index(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status = FAILURE;	
	char* c1,* c2;

	hString = my_string_init_c_string("at");
	c1 = my_string_at(hString, -1);
	c2 = my_string_at(hString, 2);	
	if(hString != NULL)
	{
		if(c1 != NULL || c2 != NULL)
		{
		
	
			printf("falied to return null at invalid index instead returned %c & %c\n",*c1, *c2);
			strncpy(buffer, "dbergero_test_my_string_at_returns_NULL_at_invalid_index\n"
			"failed to return null at invalid index\n", length);
		}	
		else
		{
			status = SUCCESS;
			strncpy(buffer,"dbergero_test_my_string_at_returns_NULL_at_invalid_index\n", length);
		}
		my_string_destroy(&hString);
	}	
	return status; 
}

Status dbergero_my_string_at_returns_valid_address(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status = FAILURE;
	
	hString = my_string_init_c_string("dog");
       	if(hString != NULL)
	{
		if(my_string_at(hString, 0) == NULL)
		{
			printf("return null is invalid address\n");
                        strncpy(buffer, "dbergero_test_my_string_at_returns_valid_address\n"
                        "failed to return valid address\n", length);

		}
		else
		{
			status = SUCCESS;
	            	strncpy(buffer, "dbergero_test_my_string_at_returns_valid_address\n", length);

		}
		my_string_destroy(&hString);
	}	
	return status;


}
Status dbergero_my_string_c_str_returns_valid_address(char* buffer, int length)
{
	MY_STRING hString = NULL;
        Status status = FAILURE;
	
	hString = my_string_init_c_string("c-string");
	if(hString != NULL)
        {
                if(my_string_c_str(hString) == NULL)
                {
                        printf("return null is invalid address\n");
                        strncpy(buffer, "dbergero_test_my_string_c_str_returns_valid_address\n"
                        "failed to return valid address\n", length);

                }
                else
                {
                        status = SUCCESS;
                        strncpy(buffer, "dbergero_test_my_string_c_str__returns_valid_address\n", length);

                }
                my_string_destroy(&hString);
        }
        return status;	

}

Status dbergero_my_string_c_str_is_NULL_terminated(char* buffer, int length)
{
	MY_STRING hString = NULL;
        Status status = FAILURE;
	char* c;
	int i = 0;

	hString = my_string_init_c_string("c-string");
	c = my_string_c_str(hString);
	for(i; i < my_string_get_size(hString); i++)
	{}	
	
	if(c[i] == '\0')
	{
		 status = SUCCESS;
                 strncpy(buffer, "dbergero_test_my_string_c_str_is_NULL_terminated\n", length);

	}
	else
	{
		printf("return null is not null terminated\n");
		strncpy(buffer, "dbergero_test_my_string_c_str_is_NULL_terminated\n"
		 "failed to null terminate\n", length);

	}
	my_string_destroy(&hString);
	return status;

}

Status dbergero_my_string_c_is_empty_returns_true_for_empty(char* buffer, int length)
{
	MY_STRING hString = NULL;
        Status status = FAILURE;

	hString = my_string_init_default();

	if(my_string_is_empty(hString))
	{
		 status = SUCCESS;
                 strncpy(buffer,"dbergero_my_string_c_is_empty_returns_true_for_empty\n", length);
	}
	else
	{
		printf("string was empty function returned false\n");
                strncpy(buffer, "dbergero_my_string_c_is_empty_returns_true_for_empty\n"
                "returned false instead of true\n", length);
	}
	my_string_destroy(&hString);
        return status;
}

Status dbergero_my_string_c_is_empty_returns_false_for_nonempty(char* buffer, int length)
{
        MY_STRING hString = NULL;
        Status status = FAILURE;

        hString = my_string_init_c_string("nonempty");

        if(!(my_string_is_empty(hString)))
        {
                 status = SUCCESS;
                 strncpy(buffer,"dbergero_my_string_c_is_empty_returns_false_for_nonempty\n", length);
        }
        else
        {
                printf("string was full function returned true\n");
                strncpy(buffer, "dbergero_my_string_c_is_empty_returns_false_for_nonempty\n"
                "returned true instead of false\n", length);
        }
        my_string_destroy(&hString);
        return status;
}

Status dbergero_my_string_concat_successfully_appends_word(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status = FAILURE;

	hString1 = my_string_init_default();

	hString2 = my_string_init_c_string("rd");
	if(hString2 == NULL)
	{
		return status;
	}
	if(my_string_concat(hString1, hString2))
	{
		status = SUCCESS;
		strncpy(buffer,"dbergero_my_string_concat_successfully_appends_word\n", length);
	}	
	else
	{
		printf("did not append\n");
		strncpy(buffer,"dbergero_my_string_concat_successfully_appends_word\n"
		"func fail\n", length);

	}
	

	my_string_destroy(&hString1);
        my_string_destroy(&hString2);
        return status;
}








