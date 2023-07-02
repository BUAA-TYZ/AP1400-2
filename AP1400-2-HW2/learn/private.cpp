#include <iostream>

using namespace std;

class Student {
public:
	explicit Student(int age_) : age(age_) {}
private:
	int age;
};

int main() {
	Student tyz(21);
	// cout << tyz.age << endl;
	cout << *((int*)&tyz) << endl;
}
