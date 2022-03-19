#include <iostream>
#include <fstream>
#include <limits>
#include "count.h"

using namespace std;

int* itr_data(int* count_arr, int arg_upper, int arg_lower, int input, string arg_0) {
	if (input <= arg_upper && input >= arg_lower) {
		for (int i = arg_lower; i <= arg_upper; i++) {
			if(i == input) {
				count_arr[i - arg_lower] += 1;
			}
		}
	} else {
		int err = errno;
		cerr << arg_0 << " ERROR: " << input << " is not within bounds " << arg_lower << " to " << arg_upper << "\n";
		exit (err);
	}
	return count_arr;
}

int* input_data(int* count_arr, string arg_0, int arg_lower, int arg_upper) {
	int input;
	//While user input exists increment indexes based on user input
	while (cin >> input) {
		if (cin.fail()) {
			int err = errno;
			cerr << arg_0 << " ERROR: Bad input. Expected integer\n";
			exit(err);
		} else {
			count_arr = itr_data(count_arr, arg_upper, arg_lower, input, arg_0);
		}
	}
	return count_arr;
}

int* file_data(int* count_arr, char* argv[], int argc, int arg_upper, int arg_lower) {
	int n;
	// reads in data from multiple files and iterates count_arr based on the data
	for (int i = 3; i < argc; i ++) {
		ifstream in(argv[i]);
		// check if file exists
		if (!in) {
			int err = errno;
			cerr << argv[0] << " ERROR: " << err << " " << argv[i] << " can't be opened \n";
			exit(err);
		}
		while(in >> n) {
			count_arr = itr_data(count_arr, arg_upper, arg_lower, n, argv[0]);
		}
		// check if end of file was reached
		if(!in.eof()) {
			int err = errno;
			cerr << argv[0] << " ERROR: " << err << " Bad data. Expected only ints\n";
			exit(err);
		}
	}
	return count_arr;
}

string input_freq (int* &count_arr, int arg_lower, int arg_upper, int max_freq) {
	//creation of the result string
	string result = "";
	//for loop to append frequency of user input values seperated by a comma
	for (int i = arg_lower; i <= arg_upper; i++) {
		count_arr[arg_lower - arg_upper] = max_freq;
		if (count_arr[i - arg_lower] > 0) {
			for (int k = 0; k < count_arr[i - arg_lower]; k++) {
				result += to_string(i);
				result += ",";
			}
		}
	}
	return result;
}

count::~count() {
	delete [] count_arr;
}

int main(int argc, char *argv[]) {
	// check if enough args exist to set the range
	if (argc < 3) {
		int err = errno;
		cerr << argv[0] << " ERROR: Missing arguments. "<< err << " argv[1] is lower bound, argv[2] is upper bound\n";
		exit(err);
	}
	try {
	//building initial array and input
	const string arg_0 = argv[0];
	const char* arg_1 = argv[1];
	const char* arg_2 = argv[2];
	char* arg_end = nullptr;
	int arg_lower = strtol(arg_1, &arg_end, 10);
	int arg_upper = strtol(arg_2, &arg_end, 10);
	int arr_size = arg_upper - arg_lower;
	int *count_arr = new int[arr_size];

	//Set all of the vector values to a tuple that holds all vlaues within the range and their frequencies starting at 0
	for (int i = arg_lower; i <= arg_upper; i++) {
		count_arr[i - arg_lower] = 0;
	}

	// check if arguments have file calls
	if (argc == 3) {
		count_arr = input_data(count_arr, arg_0, arg_lower, arg_upper);
	} else {
		count_arr = file_data(count_arr, argv, argc, arg_upper, arg_lower);
	}

	 //output array in "value"x"frequency" format
	for (int i = arg_lower; i <= arg_upper; i++) {
		if (count_arr[i - arg_lower] > 0) {
			cout << i << "x" << count_arr[i - arg_lower] << " ";
		}
	}
	cout << "\n";

	string result = input_freq(count_arr, arg_lower, arg_upper, count_arr[arg_upper - arg_lower]);
	//output of result string minus the ending ","
	cout << result.substr(0, result.size() - 1) << "\n";
	} catch (...) {
		char* arg_end = nullptr;
		int arg_lower = strtol(argv[1], &arg_end, 10);
		int arg_upper = strtol(argv[2], &arg_end, 10);
		// check if argv[1] > argv[2]
		if (arg_lower > arg_upper) {
			int err = errno;
			cerr << argv[0] << " ERROR: Improper arguments. Lower bound argv[1] is greater than upper bound argv[2]\n";
			exit(err);
		} else {
			int err = errno;
			cerr << argv[0] << " ERROR: Invalid Arguments. Expected integers as first two arguments\n";
			exit(err);
		}
	}
}
