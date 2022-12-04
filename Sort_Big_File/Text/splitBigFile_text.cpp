#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <Windows.h>

using namespace std;

typedef unsigned long long LL;

LL GetFileLength(const string& filepath)
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

void cls()
{
    system("cls");
}

//blockSize -> KB
void split(const string& filepath, LL blockSize)
{
    LL ori_size = GetFileLength(filepath);
    blockSize *= 1024; //KB -> B
    if (ori_size == -1)
    {
        cout << "get file length failed." << endl;
        return;
    }
    ifstream in;
    in.open(filepath, ios_base::in | ios_base::binary);
    if (!in.is_open())
    {
        cout << "ifstream open failed" << endl;
        return;
    }

    char buff[1024];
    memset(buff, 0, 1024);
    LL read_count = 0;
    LL cur_count = 0;
    int i;
    for (i = 0; read_count < ori_size; ++i)
    {
        int thisTimesRead = 0;
        string divfile = to_string(i) + ".txt";
        cout << "spliting file: " << divfile << ".." << endl;
        ofstream out;
        out.open(divfile, ios_base::out | ios_base::binary);
        if (!out.is_open())
        {
            cout << "open " << divfile << " failed." << endl;
            break;
        }
        while (thisTimesRead < blockSize && read_count < ori_size)
        {
            memset(buff, 0, 1024);
            in.read(buff, 1024);
            cur_count = in.gcount();
            read_count += cur_count;
            thisTimesRead += cur_count;
            out.write(buff, cur_count);
        }
        if (int(buff[1023])!=10) {
            char ch[1];
            ch[0] = buff[1023];
            while(int (ch[0])!=10 && read_count < ori_size) {
                in.read(ch, 1);
                cur_count = in.gcount();
                read_count += cur_count;
                out.write(ch, cur_count);
            }
        }

        out.close();
    }

    in.close();
    cout << "Split " << i << " files, original file size: " << ori_size << "Bytes." << endl;
}


int main(int argc, char** argv)
{
    //cout << GetFileLength("1.jpg") << endl;
    //split("2.jpg", 128);
    cls();
    string curDir(argv[0]);
    curDir = curDir.substr(0, curDir.find_last_of('\\'));
    //merge(curDir);

    int opt;
    cout << "What do you want to do:" << endl
        << "1. Split file." << endl
        << "2. Merge file." << endl
        << "3. Exit." << endl
        << "Your option: " << endl;
    cin >> opt;
    string path;
    int blockSize = 0;
    cls();
    switch (opt)
    {
    case 1:
        cout << "Input the path of file you want to split and the size of each part (KB):" << endl;
        cin >> path >> blockSize;
        split(path, blockSize);
        break;
    case 2:
        cout << "Merging in current directory." << endl;
        merge("D:/archive/sort_small");
        break;
    default:

        break;
    }
    cout << "Exit." << endl;
    return 0;
}