#include <array>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include <string>

using namespace std;

string exec(const char* cmd) 
{
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void searchFile(string filePath, string searchString)
{
    ifstream in(filePath);
    char c;

    if(in.is_open()) {
        int occurences = 0;

        while(in.good()) {
            in.get(c);
            if (searchString[0] == c) {
                bool matchFound = true;
                for(char& sc : searchString) {
                    if (sc == c) {
                        in.get(c);
                    }
                    else {
                        matchFound = false;
                        break;
                    }
                }
                if (matchFound) {
                    occurences += 1;
                }
            }
        }

        cout << filePath << ": " << occurences << endl;
    }

    if(!in.eof() && in.fail()) {
        cout << "error reading " << filePath << endl;
    }

    in.close();
}

int main(int argc, char** argv) 
{
    auto bookNames = exec("./scripts_get_books.sh");
    
    istringstream f(bookNames);
    string bookName;    
    while (getline(f, bookName)) {
        string filePath = "./Books/" + bookName;
        searchFile(filePath, "Test");
    }
}