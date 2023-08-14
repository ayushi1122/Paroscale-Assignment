/*2. c++ program to iterate a linux directory tree and count the number of files and number of subdirectories 
in each directory. Also, count the total number of files and directories in the directory tree. 
Implement the logic using multi-threading to improve the scanning of the directory*/

#include<bits/stdc++.h>
using namespace std;


mutex mtx; 
int tot_Files = 0;
int tot_Dirs = 0;

void countFilesAndDirs(const filesystem::path& dirPath) {
    int loc_Files = 0;
    int loc_Dirs = 0;
    
    for (const auto& entry : filesystem::directory_iterator(dirPath)) {
        if (entry.is_regular_file()) {
            loc_Files++;
        } else if (entry.is_directory()) {
            loc_Dirs++;
            countFilesAndDirs(entry.path()); // Recursive call for subdirectories
        }
    }
    
    lock_guard<mutex> lock(mtx);
    tot_Files += loc_Files;
    tot_Dirs += loc_Dirs;
    
    cout << "Directory: " << dirPath << "\n"
         << "Files: " << loc_Files << ", Subdirectories: " << loc_Dirs << "\n";
}

int main() {
    filesystem::path rootPath = "//path";
    
    thread t(countFilesAndDirs, rootPath);
    t.join();
    
    cout << "Total Files: " << tot_Files << "\n"
         << "Total SubDirectories: " << tot_Dirs << "\n";
    
    return 0;
}

