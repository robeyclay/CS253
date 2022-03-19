#include "bar.h"
#include <iostream>

using namespace std;

void bar() {
	cout << "Hi from " << __func__ << " at " << __FILE__ ":" << __LINE__ << '\n';
} 
