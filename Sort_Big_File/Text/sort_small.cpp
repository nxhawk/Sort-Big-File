//{}[]

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

struct Book {
	string id, context;
};

Book book[100000];
int n;
int file = 0;
int length_file = 140;

void writeData();
void qSort(int left, int right);

void parseData(string line)
{
	string s;
	int vt = line.find(",");
	s = line.substr(0, vt);
	line.erase(0, vt + 1);
	if (s == "") return;
	book[n] = { s, line };
	n++;
}

void readData() {

	for (int i = 0; i < length_file; i++) 
	{
		n = 0;
		file = i;
		string dirfile = "D:/archive/test/" + to_string(i) + ".txt";
		ifstream f;
		f.open(dirfile, ios_base::in | ios_base::binary);
		if (!f.is_open()) {
			cout << "Failed";
			return;
		}
		
		string line;
		if (i == 0) getline(f, line);
		while (f) {
			getline(f, line);
			
			parseData(line);
		}
		qSort(0, n - 1);
		writeData();
	}
}

void qSort(int left, int right)
{
	int i = left, j = right;
	Book x = book[(left + right) / 2];
	while(i < j) {
		while (book[i].id < x.id) i++;
		while (book[j].id > x.id) j--;
		if (!(i > j)) {
			Book tmp = book[i];
			book[i] = book[j];
			book[j] = tmp;
			i++; j--;
		}
	} 
	if (i < right) qSort(i, right);
	if (left < j) qSort(left, j);
}

void writeData()
{
	string dirfile;
	dirfile = to_string(file) + "_sort.txt";
	ofstream f;
	f.open(dirfile, ios_base::out | ios_base::binary);
	if (!f.is_open())
	{
		cout << "open " << dirfile << " failed." << endl;
		return;
	}
	cout << "writing " + dirfile + "...\n";
	for (int i = 0; i < n; i++)
		f << book[i].id << "," << book[i].context << endl;
	f.close();
	cout << "Done\n";
}

int main()
{
	readData();
	return 0;
}