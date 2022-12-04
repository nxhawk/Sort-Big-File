#pragma once

#include<Windows.h>
#include<cstring>
#include"Library.h"

typedef unsigned long long LL;

//Function get length file in bytes
LL GetFileLength(const string& filepath);

//split file => small file with blockSize KB (contain right line), return number of line data
int split(const string& filepath, LL blockSize);
