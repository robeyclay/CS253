#include <iostream>

using namespace std;

int * input_data(int count_arr[], string arg_0) {
	int input;
	//While user input exists increment indexes based on user input
	while (cin >> input) {	
		if (input < 100 && input > -1) {
 			count_arr[input] += 1;
		}
		
		else {
			cout << arg_0 << " ERROR: " << input << " is not within bounds 0 to 99\n";
			exit (1);
		}
	}
	return count_arr;
}

string input_freq (int arr_size, int count_arr[]) {
	//creation of the result string
	string result = "";
	//for loop to append frequency of user input values seperated by a comma
	for (int i = 0; i < arr_size; i++) {
		if (count_arr[i] > 0) {
			for (int k = 0; k < count_arr[i]; k++) {
				result += to_string(i);
				result += ",";
			}
		}
	}
	return result;
}

int main(int /*argc*/, char *argv[]) {
	//building initial array and input
	int count_arr [100];
	string arg_0 = argv[0];
	//sizeof finds the number of bits total, so dividing by the starter element produces correct size of array
	int arr_size = sizeof(count_arr)/sizeof(count_arr[0]);
	//Set all of the array values to 0
	for (int i = 0; i < arr_size; i++) {
		count_arr[i] = 0;
	}


	input_data(count_arr, arg_0);
	//output array in "value"x"frequency" format
	for (int i = 0; i < arr_size; i++) {
		if (count_arr[i] > 0) {
			cout << i << "x" << count_arr[i] << " ";
		}
	}
	cout << "\n";
	

	string result = input_freq(arr_size, count_arr);
	//output of result string minus the ending ","
	cout << result.substr(0, result.size() - 1) << "\n";

}
