#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string convertToLower(string str) 
{
    for(int i=0; i < str.length(); i++) {
        if(str[i] != ' ')
        {
            str[i] = tolower(str[i]);
        }
    }
    return str;
}

void readCharFile(string filePath)
{
    ifstream in(filePath);
    char c;
    string searchString = "Scrooge";

    if(in.is_open()) {
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
                    cout << "FOUND!" << endl;
                }
            }
        }
    }

    if(!in.eof() && in.fail()) {
        cout << "error reading " << filePath << endl;
    }

    in.close();
}

int main(int argc, char** argv) 
{
    readCharFile("./Books/A Christmas Carol");
}