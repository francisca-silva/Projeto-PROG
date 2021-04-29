#include <iostream>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <climits>

using namespace std;

int main() {
	
    char c;
    string s;

    getline(cin, s);

    if (cin.eof()) cout << "Fail" << endl;
    else cout << "|" << s << "|" << endl;

    return 0;
}




