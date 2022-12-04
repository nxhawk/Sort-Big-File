#include"SortSmallFile.h"

typedef unsigned long long LL;

//value
Book book[100000];
int n;
int file = 0;

int length_file = 140;


//function to parse line of file => data Book Info 
void parseData(string line)
{
	string s;
	int vt = line.find(",");
	s = line.substr(0, vt);
	if (s == "") return;
	book[n].id = s;
	book[n].context = line;
	n++;
}

//function get length file 
LL GetFileLength(string filepath)
{
	LL len = -1;
	ifstream in;
	in.open(filepath, ios_base::in);
	if (in.is_open())
	{
		in.seekg(0, ios::end);
		len = in.tellg();
		in.close();
	}
	return len;
}

//read Data of file with char array
void readData(int lengthFile) {
	length_file = lengthFile;
	
	for (int i = 0; i < length_file; i++)
	{
		n = 0;
		file = i;
		string dirfile = to_string(i) + ".csv";
		ifstream f;
		f.open(dirfile, ios_base::in | ios_base::binary);
		if (!f.is_open()) {
			cout << "Failed open " << dirfile << " to read data\n";
			return;
		}
		cout << "Read data from " << dirfile << endl;

		//Read data
		LL ori_size = GetFileLength(dirfile);
		char buff[1024];
		memset(buff, 0, 1024);
		LL read_count = 0;
		LL cur_count = 0;
		string line = "";
		int k = 0;
		while (read_count < ori_size)
		{
			memset(buff, 0, 1024);
			f.read(buff, 1024);
			cur_count = f.gcount();
			read_count += cur_count;
			for (int j = 0; j < 1024; j++)
				if (!buff[j]) break;
				else if (buff[j] == '\n') {
					if (i == 0 && k == 0) k = 1;
					else parseData(line);
					line = "";
				}
				else line += buff[j];
		}

		cout << "Sort data from file\n";
		qSort(0, n - 1);//sort data
		writeData();//write data after sort
	}
}

//Quick sort
void qSort(int left, int right)
{
	int i = left, j = right;
	Book x = book[(left + right) / 2];
	while (i < j) {
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

//write data into new file with name sorted
void writeData()
{
	string dirfile;
	dirfile = to_string(file) + "_sorted.csv";
	ofstream f;
	f.open(dirfile, ios_base::out | ios_base::binary);
	if (!f.is_open())//error open file
	{
		cout << "open " << dirfile << " failed to write data." << endl;
		return;
	}
	cout << "writing " + dirfile + "...\n";
	for (int i = 0; i < n; i++)
		f << book[i].context << endl;
	f.close();
	
	//successfully
	cout << "Done!!!\n\n";
}
