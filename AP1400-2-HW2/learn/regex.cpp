#include <iostream>
#include <regex>

using namespace std;
int main() {
	// The first \ is meant to convert \ in C++
	std::regex base_regex("(\\w+)-(\\w+)-(\\d+\\.\\d+)");
	std::smatch base_match;
	string fname;
	cin >> fname;
	if (std::regex_match(fname, base_match, base_regex)) {
		for (int i = 0; i < base_match.size(); ++i) {
			cout << i + 1 << " " << base_match[i].str() << endl;
		}
	} else {
		cout << "False" << endl;
	}
}
