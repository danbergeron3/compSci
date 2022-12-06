#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"

	Status test_init_default_returns_nonNULL(char* buffer, int length);
	Status test_get_size_on_init_default_returns_0(char* buffer, int length);
	Status dbergero_test_get_capacity_on_init_default_returns_7(char* buffer, int length);
	Status dbergero_test_data_allocation_on_init_default_returns_handle(char* buffer, int length);
	Status dbergero_test_my_string_destroy_sets_handle_to_NULL(char* buffer, int length);
	Status dbergero_test_my_string_init_c_string_returns_valid_handle(char* buffer, int length);
	Status dbergero_test_my_string_init_c_string_returns_size_of_string_TEST(char* buffer, int length);
	Status dbergero_test_my_string_init_c_string_returns_capacity_of_string_TEST(char* buffer, int length);
	Status dbergero_test_my_string_compare_returns_0_for_same_size(char* buffer, int length);
	Status dbergero_test_my_string_compare_returns_greater_than_0_for_hleft_greater_than_hright(char* buffer, int length);
	Status dbergero_test_my_string_compare_returns_less_than_0_for_hright_greater_than_hleft(char* buffer, int length);
	Status dbergero_test_my_string_extraction_skips_leading_blanks(char* buffer, int length);
	Status dbergero_test_my_string_extraction_expands_my_string_so_size_less_than_capacity(char* buffer, int length);
	Status dbergero_test_my_string_extraction_fails_for_empty_string(char* buffer, int length);
	Status dbergero_test_my_string_insertion_sets_size_to_0(char* buffer, int length);
	Status dbergero_test_my_string_insertion_returns_SUCCESS(char* buffer, int length);
	Status dbergero_test_my_string_push_back_resize_SUCCESS(char* buffer, int length);
	Status dbergero_test_my_string_push_back_stores_char_value(char* buffer, int length);
	Status dbergero_test_my_string_at_returns_NULL_at_invalid_index(char* buffer, int length);
	Status dbergero_my_string_at_returns_valid_address(char* buffer, int length);
	Status dbergero_my_string_c_str_returns_valid_address(char* buffer, int length);
        Status dbergero_my_string_c_str_is_NULL_terminated(char* buffer, int length);
	Status dbergero_my_string_c_is_empty_returns_true_for_empty(char* buffer, int length);
	Status dbergero_my_string_c_is_empty_returns_false_for_nonempty(char* buffer, int length);
	Status dbergero_my_string_concat_successfully_appends_word(char* buffer, int length);

#endif
