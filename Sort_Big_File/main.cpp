#include"SplitBigFile.h"
#include"SortSmallFile.h"
#include"MergeAllFileSorted.h"
#include<time.h>

//clear screen
void cls()
{
	system("cls");
}

int files_length = 559;
 
int main()
{
	//Change this value to split file you want 
	int K_bytes = 20000;
	double time_split = 0, time_sort_small = 0, time_merge = 0;

	
	//First step: split big file into small files 
	cout << "The first We will split the 'Books_rating.csv' file into several small files.\n";
	
	clock_t start = clock();
	files_length = split("../Books_rating.csv", K_bytes);
	clock_t end = clock();
	time_split = double(end - start) / CLOCKS_PER_SEC;
	cls();
	
	cout << "Time split: " << time_split / 60 << " minutes\n";
	cout << "Number of file: " << files_length << endl;

	//Second step: Sort all small files
	cout << "The second We will sort all these split data files in ascending ID order.\n";
	start = clock();
	readData(files_length);
	end = clock();
	time_sort_small = double(end - start) / CLOCKS_PER_SEC;
	cls();

	cout << "Time split: " << time_split / 60 << " minutes\n";
	cout << "Time sort all small files: " << time_sort_small / 60 << " minutes\n\n";
	
	//Third step: Merger small files => file result
	cout << "Finally We will merge the sorted files into the result file and save the name as 'sorted_books_rating.csv'.\n";
	start = clock();
	run_main(files_length);
	end = clock();
	time_merge = double(end - start) / CLOCKS_PER_SEC;
	//cout << GetFileLength("Books_rating_sorted.csv") << endl;

	cout << "\nTime split: " << time_split / 60 <<" minutes\n";
	cout << "Time sort all small files: " << time_sort_small / 60 << " minutes\n";
	cout << "Time merge all small files: " << time_merge / 60 << " minutes\n\n";
	cout << "Total time: " << double(time_split + time_sort_small + time_merge) / 60 << " minutes\n";
	return 0;
}
