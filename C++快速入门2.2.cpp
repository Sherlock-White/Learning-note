#include<fstream>
#include<iostream>
using namespace std;
int main() {
	ifstream in("test.txt");
	if (!in) {
		cerr << "���ļ�text.txtʧ��" << endl;
		return -1;
	}
	ofstream out("result.txt");
	if (!out) {
		cerr << "���ļ�result.txtʧ��" << endl;
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