#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

int increment (int i) { return (i + 1); }

int main() {
    vector<short> pi = {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4};
    string alpha="abcdefghijklmnopqrstuvwxyz", digits="0123456789";
    char cbuf[100] = { };	// contains 100 '\0' chars
    list<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    [[maybe_unused]] short powers[] = {1,2,4,8,16,32,64};
    [[maybe_unused]] int ibuf[100];		// contains unknown values

    cout << "Exercise 0\n";
    copy(alpha.begin(), alpha.end(), cbuf);
    cout << cbuf << '\n';

    cout << "Exercise 1\n";
    reverse(begin(cbuf), end(cbuf));
    for (auto e : cbuf) {
	cout << e;
    }
    cout << '\n';

    cout << "Exercise 2\n";
    transform(primes.begin(), primes.end(), ibuf, [](auto c) { return c + 1; });
    for (size_t i = 0; i < size(primes); i++) {
	cout << ibuf[i] << ' ';
    }
    cout << '\n';

    cout << "Exercise 3\n";
    if (any_of(primes.begin(), primes.end(), [](auto c) bool { return (c % 2) == 0; }))
	cout << "div 2\n";
    if (any_of(primes.begin(), primes.end(), [](auto c) bool { return (c % 42) == 0; }))
	cout << "div 42\n";

    cout << "Exercise 4\n";
    list<int>::iterator result = find(primes.begin(), primes.end(), 13);
    cout << *++result << '\n';

    cout << "Exercise 5\n";
    int three_count = count(pi.begin(), pi.end(), 3);
    cout << three_count << '\n';

    cout << "Exercise 6\n";
    int lt_five_count = count_if(pi.begin(), pi.end(), [](auto c) { return c < 5; });
    cout << lt_five_count << '\n';

    cout << "Exercise 7\n";
    auto great_value = max_element(pi.begin(), pi.end());
    cout << *great_value << '\n';

    cout << "Exercise 8\n";
    sort(pi.begin(), pi.end());
    for (auto p : pi) {
	cout << p << ' ';
    }
    cout << '\n';

    cout << "Exercise 9\n";
    auto seven_bound = lower_bound(pi.begin(), pi.end(), 7);
    cout << (seven_bound - pi.begin()) << '\n';

    cout << "Exercise 10\n";
    auto last_index = set_intersection(pi.begin(), pi.end(), begin(powers), end(powers), begin(ibuf));
    for (auto i = &ibuf[0]; i < last_index; i++) {
	cout << *i << ' ';
    }
    cout << '\n';
}
