#include <iostream>

class count {
   public:
        ~count();
        int* input_data(int* count_arr, std::string arg_0, int arg_lower, int arg_upper);
        std::string input_freq (int arr_size, int* count_arr);
        int* itr_data(int* count_arr, int arg_upper, int arg_lower, int input, std::string arg_0);
        const std::string arg_0;
	const char* arg_1;
	const char* arg_2;
	char* arg_end;
	int arg_lower;
	int arg_upper;
	int arr_size;
	int *count_arr;
};
