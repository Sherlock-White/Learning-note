#include<fstream>
#include<iostream>
using namespace std;
int main() {
	ifstream in("test.txt");
	if (!in) {
		cerr << "打开文件text.txt失败" << endl;
		return -1;
	}
	ofstream out("result.txt");
	if (!out) {
		cerr << "打开文件result.txt失败" << endl;
		in.close();
		return -1;
	}

	char x;
	while (in >> x) {
		out << x;
	}
	out << endl;
	in.close();
	out.close();
	return 0;
}