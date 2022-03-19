/*
  TODO: error check for file name before arguments. check max nums of args if an arg exists that isnt a file name after the first filename throw
  TODO: Test
*/

#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <unistd.h>
#include <cstring>
//#include "count.h"


using namespace std;

//increment the data in count_arr
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

int* input_data(int* count_arr, string arg_0, int arg_lower, int arg_upper, bool vbool) {
	int input;
	if (vbool)
		cout << "Reading from standard input \n";
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

int* file_data(int* count_arr, char* argv[], int argc, int arg_upper, int arg_lower, bool vbool, const char* cdata, const char* rdata) {
	int n;
	vector<int> file_collection;
	for(int i = 1; i < argc; i++) {
		string arg(argv[i]);
		if(argv[i] != rdata && argv[i] != cdata && arg.find('-') == string::npos) {
			file_collection.push_back(i);
		}
	}

	if (file_collection.size() > 0) {
	// reads in data from multiple files and iterates count_arr based on the data
		if (file_collection[file_collection.size() - 1] != argc - 1) {
			cerr << argv[0] << " ERROR: arguments called after file name\n";
			exit(1);
		}
		if (vbool) {
			for (size_t i = 0; i < file_collection.size(); i++) {
				cout << "Reading from " << argv[file_collection[i]] << "\n";
			}
		}

		for (size_t k = 0; k < file_collection.size(); k++) {
			ifstream in(argv[file_collection[k]]);
			// check if file exists
			if (!in) {
				int err = errno;
				cerr << argv[0] << " ERROR: " << err << " " << argv[file_collection[k]] << " can't be opened \n";
				exit(err);
			}
			while(in >> n) {
				count_arr = itr_data(count_arr, arg_upper, arg_lower, n, argv[0]);
			}
			// check if end of file was reached
			if(!in.eof()) {
				int err = errno;
				cerr << argv[0] << " ERROR:  Bad data. Expected only ints\n";
				exit(err);
			}

		}
	} else {
		count_arr = input_data(count_arr, argv[0], arg_lower, arg_upper, vbool);
	}
	return count_arr;
}

string input_freq (int* count_arr, int arg_lower, int arg_upper, int max_freq, const char *cdata) {
	//creation of the result string
	string result = "";
	//for loop to append frequency of user input values seperated by a comma
	for (int i = arg_lower; i <= arg_upper; i++) {
		count_arr[arg_lower - arg_upper] = max_freq;
		if (count_arr[i - arg_lower] > 0) {
			for (int k = 0; k < count_arr[i - arg_lower]; k++) {
				result += to_string(i);
				result += cdata;
			}
		}
	}
	return result;
}

void val_x_freq(int* count_arr, int arg_lower, int arg_upper) {
	 //output array in "value"x"frequency" format
        for (int i = arg_lower; i <= arg_upper; i++) {
                if (count_arr[i - arg_lower] > 0) {
                        cout << i << "x" << count_arr[i - arg_lower] << " ";
                }
        }
	cout << "\n";
}

int main(int argc, char *argv[]) {
	const string arg_0 = argv[0];
	bool rbool = false;
	const char* rdata = "";
	int r_count = 0;
	bool fbool = false;
	bool sbool = false;
	const char* cdata = ",";
	int c_count = 0;
	bool vbool = false;
	int c;
	char **unordered_argv = new char*[argc];
	for(int i = 0; i < argc; i++) {
		unordered_argv[i] = argv[i];
	}

	while((c = getopt(argc, argv, "r:fsc:v")) != -1) {
		switch(c) {
			case 'r':
				if(r_count == 0) {
					rbool = true;
					rdata = optarg;
					r_count++;
					break;
				} else {
					cerr << arg_0 <<" Illegal use of arguments, can't have multiple r's\n";
					exit(1);
				}
			case 'f':
				fbool = true;
				break;
			case 's':
				sbool = true;
				break;
			case 'c':
				if(c_count == 0) {
					cdata = optarg;
					c_count++;
					break;
				} else {
					cerr << arg_0 << " Illegal use of arguments: can't have multiple c's/n";
					exit(1);
				}
			case 'v':
				vbool = true;
				break;
			default:
				exit(1);
		}
	}

	//building initial array and input
	int arg_lower = 0;
	int arg_upper = 99;

	if (rbool) {
		//parse rdata
		string s(rdata);
		string delimeter = "-";
		int count = 0;
		for(size_t i = 0; i < strlen(rdata); i++) {
			if (rdata[i] == '-') {
			count++;
			}
		}
		string sarg_lower;
		string sarg_upper;
		if (count == 1) {
		//	cout << "inside if count == 1\n";
			sarg_lower = s.substr(0, s.find(delimeter));
			sarg_upper = s.substr(s.find(delimeter) + 1);
		} else if (count == 2) {
		//	cout << "inside else if count == 2\n";
			sarg_lower = s.substr(0, s.rfind(delimeter));
			sarg_upper = s.substr(s.rfind(delimeter) + 1);
		} else if (count == 3) {
		//	cout << "inside else if count == 3\n";
			sarg_lower = s.substr(s.find(delimeter), s.rfind(delimeter));
			sarg_upper = s.substr(s.rfind(delimeter));
		}
		try {
		arg_lower = stoi(sarg_lower);
		arg_upper = stoi(sarg_upper);
		} catch (...) {
			cerr << argv[0] << " ERROR: Invalid Arguments. Expected integers as first two arguments\n";
			exit(1);
		}
		//cout << "arg_lower = " << arg_lower << "\n";
		//cout << "arg_upper = " << arg_upper << "\n";
	}
	if (arg_lower > arg_upper) {
		cerr << argv[0] << " ERROR: Improper arguments. Lower bound is greater than upper bound\n";
		exit(2);
	}

	int arr_size = arg_upper - arg_lower;
	int *count_arr = new int[arr_size];

	//Set all of the vector values to a tuple that holds all vlaues within the range and their frequencies starting at 0
	for (int i = arg_lower; i < arg_upper; i++) {
		count_arr[i - arg_lower] = 0;
	}

	// gather the data from file or stream
	count_arr = file_data(count_arr, unordered_argv, argc, arg_upper, arg_lower, vbool, rdata, cdata);

	// check if f, s, or neither arguments were used
	string str_cdata(cdata);
	if(fbool && !sbool) {
		if (sbool) {
			cerr << arg_0 << "Invalid arguments: can't use c without use of s\n";
			exit(1);
		}
	 	//output array in "value"x"frequency" format
		val_x_freq(count_arr, arg_lower, arg_upper);
	} else if (sbool && !fbool) {
		string result = input_freq(count_arr, arg_lower, arg_upper, count_arr[arg_upper - arg_lower], cdata);
		//output of result string minus the ending ","
		cout << result.substr(0, result.size() - str_cdata.size()) << "\n";
	} else {
                //output array in "value"x"frequency" format
                val_x_freq(count_arr, arg_lower, arg_upper);
                string result = input_freq(count_arr, arg_lower, arg_upper, count_arr[arg_upper - arg_lower], cdata);
                //output of result string minus the ending ","
                cout << result.substr(0, result.size() - str_cdata.size()) << "\n";
	}
	delete[] count_arr;
	delete[] unordered_argv;
}
