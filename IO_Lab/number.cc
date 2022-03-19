#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Number {
  public:
    Number() = default;
    Number(const Number &) = default;
    Number(int v) : value(v) {}
    Number &operator=(int n) { value = n; return *this; }
    operator int() const { return value; }
  private:
    int value = 0;			// default value unless otherwise given
};

istream &operator>>(istream &is, Number &rhs) {
    string n;
    is >> n;
    if (n == "one") {
	rhs = 1;
    }
    else if (n == "two") {
	rhs = 2;
    }
    else if (n == "three") {
	rhs = 3;
    }
    else if (n == "four") {
	rhs = 4;
    }
    else if (n == "five") {
        rhs = 5;
    } else if (n != "") {
	rhs = stoi(n,nullptr,0);
    }
    return is;
}


int main() {
    Number n = 666;
    istringstream ss("12 34 three 789 five");

    while (ss >> n)
	cout << n << ' ';
    cout << '\n';
}
