#include <stdio.h>
#include <string.h>
#include "unit_test.h"

int main(int argc, char* argv[])
{
	Status (*tests[])(char*, int) =
	{
		test_init_default_returns_nonNULL,
 		test_get_size_on_init_default_returns_0,
		dbergero_test_get_capacity_on_init_default_returns_7,
		dbergero_test_data_allocation_on_init_default_returns_handle, 
		dbergero_test_my_string_destroy_sets_handle_to_NULL,
		dbergero_test_my_string_init_c_string_returns_valid_handle,
		dbergero_test_my_string_init_c_string_returns_size_of_string_TEST,
		dbergero_test_my_string_init_c_string_returns_capacity_of_string_TEST,
		dbergero_test_my_string_compare_returns_0_for_same_size,
		dbergero_test_my_string_compare_returns_greater_than_0_for_hleft_greater_than_hright,
		dbergero_test_my_string_compare_returns_less_than_0_for_hright_greater_than_hleft,
		dbergero_test_my_string_extraction_skips_leading_blanks,
		dbergero_test_my_string_extraction_expands_my_string_so_size_less_than_capacity,
		dbergero_test_my_string_extraction_fails_for_empty_string,
		dbergero_test_my_string_insertion_sets_size_to_0,
		dbergero_test_my_string_insertion_returns_SUCCESS,
		dbergero_test_my_string_push_back_resize_SUCCESS,
		dbergero_test_my_string_push_back_stores_char_value,
		dbergero_test_my_string_at_returns_NULL_at_invalid_index,
		dbergero_my_string_at_returns_valid_address,
		dbergero_my_string_c_str_returns_valid_address,
		dbergero_my_string_c_str_is_NULL_terminated,
		dbergero_my_string_c_is_empty_returns_true_for_empty,
		dbergero_my_string_c_is_empty_returns_false_for_nonempty,
		dbergero_my_string_concat_successfully_appends_word
	};
	
 	int number_of_functions = sizeof(tests) / sizeof(tests[0]);
	int i;
 	char buffer[500];
 	int success_count = 0;
 	int failure_count = 0;
	 
 	for(i=0; i<number_of_functions; i++)
	 {
		 if(tests[i](buffer, 500) == FAILURE)
	 	{
		 printf("FAILED: Test %d failed miserably\n", i);
	 	printf("\t%s\n", buffer);
	 	failure_count++;
	 	}
	 	else
	 	{
		// printf("PASS: Test %d passed\n", i);
		// printf("\t%s\n", buffer);
	 	success_count++;
 		}
 	}
 	
	printf("Total number of tests: %d\n", number_of_functions);
 	printf("%d/%d Pass, %d/%d Failure\n", success_count,
 	number_of_functions, failure_count, number_of_functions);
	
	return 0;
}
