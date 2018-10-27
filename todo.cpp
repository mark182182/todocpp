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

class writeToFile{
public:
  void writeFile(string lineToWrite, string fileToRead){
    fstream todoFile;
    todoFile.open(fileToRead);
    todoFile << lineToWrite << endl;
  }
};

int main(){
  readFromFile readFromFile;
  writeToFile writeToFile;
  string task;
  cout << "Please write in a task:" << endl;
  cin >> task;
  writeToFile.writeFile(task, "todo.txt");
  readFromFile.readFile("todo.txt");
  return 0;
}
