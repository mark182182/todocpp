#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

class readFromFile{
public:
  void readFile(string fileToRead){
    ifstream todoFile;
    string line;
    todoFile.open(fileToRead);
    while(getline(todoFile, line)){
      cout << line << endl;
    }
    todoFile.close();
  }
};

int main(){
  readFromFile readFromFile;
  readFromFile.readFile("todo.txt");
  return 0;
}
