#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

class readFromFile{
public:
  void readFile(std::string fileToRead){
    std::ifstream todoFile;
    std::string line;
    std::vector<std::string> todoArray;
    todoFile.open(fileToRead);
    while(getline(todoFile, line)){
      todoArray.push_back(line);
    }
    for (int i = 0; i < todoArray.size(); i++) {
      std::cout << todoArray[i] << "\n";
    }
    todoFile.close();
  }
};

class writeToFile{
public:
  void writeFile(std::string lineToWrite, std::string fileToRead){
    std::fstream todoFile;
    todoFile.open(fileToRead);
    todoFile << lineToWrite << "\n";
  }
};

int main(){
  readFromFile readFromFile;
  writeToFile writeToFile;
  std::string task;
  std::cout << "Please write in a task:" << "\n";
  std::cin >> task;
  writeToFile.writeFile(task, "todo.txt");
  readFromFile.readFile("todo.txt");
  return 0;
}
