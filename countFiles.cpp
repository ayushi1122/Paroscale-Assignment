/*2. c++ program to iterate a linux directory tree and count the number of files and number of subdirectories 
in each directory. Also, count the total number of files and directories in the directory tree. 
Implement the logic using multi-threading to improve the scanning of the directory*/

#include<bits/stdc++.h>
//using namespace std;

mutex mtx;
int tot_files=0;
int tot_dirs=0;

void count(const filesystem::path& dirpath){
    int file=0;
    int dir=0;

    for(const auto& entry:)

}

