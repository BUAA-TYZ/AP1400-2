#include <iostream>
#include <random>

using namespace std;
int main() {
	random_device r;
	default_random_engine e(r());
	uniform_int_distribution<int> u(1000, 9999);
	cout << u(e) << endl;
}
