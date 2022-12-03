#include"MergeAllFileSorted.h"

struct Book
{
    string id, context;
};

class FileHandler
{
private:
    ifstream fileHandle;
    int totalBufferCapacity;
    int iterator;
    int bufferSize;
    vector<Book> buffer;

    /*  Loads next batch of lines from Disk to Memory */
    void loadDataFromDisk()
    {
        int i = 0;
        string line;
        for (; i < totalBufferCapacity && getline(fileHandle, line); i++)
        {
            buffer[i].id = line.substr(0, 10);
            buffer[i].context = line;
        }
        bufferSize = i;
        iterator = 0;
    }

public:
    FileHandler(int capacity)
    {
        totalBufferCapacity = capacity;
        iterator = 0;
        bufferSize = 0;
        buffer.resize(capacity);
    }

    /*Finds and Opens file in read only mode*/
    void loadFile(string fileName)
    {
        fileHandle.open(fileName, ios_base::in | ios_base::binary);
        if (!fileHandle.is_open()) {
            cout << "Failed\n";
            return;
        }
    }

    /*Checks if file has any more line left*/
    bool hasNext()
    {
        return (iterator < bufferSize || !fileHandle.eof());
    }

    /*Returns next line*/
    Book next()
    {
        if (!hasNext()) return { "", "" };
        if (iterator >= bufferSize) loadDataFromDisk();
        return buffer[iterator++];
    }

    ~FileHandler()
    {
        fileHandle.close();
    }
};


class FileMerger
{
private:

    /*Comparator for constructing min-heap*/
    struct Comp
    {
        bool operator()(const pair<Book, int>& first, const pair<Book, int>& second)
        {
            return first.first.id > second.first.id;
        }
    };

    static const int CHUNK_SIZE = 100; /* Loads 100 lines of input from File in a batch*/
    int numberOfFiles;
    vector<FileHandler*> fileHandles;
    string outputFileName;
    priority_queue<pair<Book, int>, vector<pair<Book, int>>, Comp> queue;

public:

    FileMerger()
    {
        numberOfFiles = 0;
        outputFileName = "sorted_books_rating.csv";
    }

    /*Read the list of files to merge in sorted order*/
    void loadFiles(vector<string> fileNames)
    {
        numberOfFiles = fileNames.size();
        for (string file : fileNames)
        {
            FileHandler* handler = new FileHandler(CHUNK_SIZE);
            handler->loadFile(file);
            fileHandles.push_back(handler);
        }
    }

    void setOutputFileName(string fileName)
    {
        outputFileName = fileName;
    }

    void generateSortedFile()
    {
        ofstream outputFile;
        outputFile.open(outputFileName, ios_base::out | ios_base::binary);
        if (!outputFile.is_open())
        {
            cout << "open " << outputFileName << " failed." << endl;
            return;
        }
        cout << "Writing...\n";
        outputFile << "Id,Title,Price,User_id,profileName,review/helpfulness,review/score,review/time,review/summary,review/text" << endl;
        for (int i = 0; i < numberOfFiles; i++)
        {
            if (fileHandles[i]->hasNext())
            {
                queue.push(make_pair(fileHandles[i]->next(), i));
            }
        }
        while (!queue.empty())
        {
            auto lineHandlePair = queue.top(); queue.pop();
            outputFile << lineHandlePair.first.context << endl;
            if (fileHandles[lineHandlePair.second]->hasNext())
            {
                queue.push(make_pair(fileHandles[lineHandlePair.second]->next(), lineHandlePair.second));
            }
        }
        cout << "Done!\n";
        outputFile.close();
    }

    ~FileMerger()
    {
        for (int i = 0; i < numberOfFiles; i++)
                  delete fileHandles[i];        
    }
};

void run_main(int lenghtFile)
{
    FileMerger* merger = new FileMerger();
    vector<string> files;
    for (int i = 0; i < lenghtFile; i++) 
        files.push_back(to_string(i) + "_sorted.csv");
    merger->loadFiles(files);
    merger->setOutputFileName("../sorted_books_rating.csv");
    cout << "Sorting files" << endl;
    merger->generateSortedFile();
    cout << "Sorting ended" << endl;    
}
