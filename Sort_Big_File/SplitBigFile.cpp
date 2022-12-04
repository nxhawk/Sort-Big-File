#include"SplitBigFile.h"

//Function get length file in bytes
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
    }else {
        //open file error
        cout << "Failed open Big File Data to get length\n";
        exit(0);
    }

    return len;
}



//split file => small file with blockSize KB (contain right line), return number of line data
int  split(const string& filepath, LL blockSize)
{
    LL ori_size = GetFileLength(filepath);
    blockSize *= 1024; //KB -> B
    
    //get length file error
    if (ori_size == -1)
    {
        cout << "Get file length failed." << endl;
        exit(0);
    }

    ifstream in;
    in.open(filepath, ios_base::in | ios_base::binary);
    if (!in.is_open())
    {
        cout << "Open file big data failed to split file" << endl;
        exit(0);
    }

    char buff[1024];
    memset(buff, 0, 1024);
    LL read_count = 0;
    LL cur_count = 0;
    int i;
    for (i = 0; read_count < ori_size; ++i)
    {
        int thisTimesRead = 0;
        string divfile = to_string(i) + ".csv";
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
        if (int(buff[1023]) != 10) {
            char ch[1];
            ch[0] = buff[1023];
            while (int(ch[0]) != 10 && read_count < ori_size) {
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
    return i;
}
//end
