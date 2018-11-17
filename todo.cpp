#include <iostream>
#include <fstream>
#include <vector>
#include <ncurses.h>
#define WIDTH 30
#define HEIGHT 20

int main(int argc, char ** argv){
  initscr();
  noecho();
  cbreak();
  int start_y, start_x;
  start_y = start_x = 5;

  WINDOW * menuwin = newwin(HEIGHT, WIDTH, start_y, start_x + 40);
  refresh();

  box(menuwin, (int)'/', (int)'-');

  keypad(menuwin, true);

  std::string choices[5] = {"View tasks", "Add new task", "Edit a task", "Remove a task", "Exit"};

  int choice;
  int highlight = 0;

  while(1) {
    wresize(menuwin, HEIGHT, WIDTH);
    clear();
    wclear(menuwin);
    refresh();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    wattron(menuwin, COLOR_PAIR(1));
    box(menuwin, (int)'/', (int)'-');
    wattroff(menuwin, COLOR_PAIR(1));
    wrefresh(menuwin);
    for (int i = 0; i < 5; i++) {
      if(i == highlight){
        start_color();
        init_pair(2, COLOR_RED, COLOR_BLACK);
        wattron(menuwin, COLOR_PAIR(2));
        wattron(menuwin, A_REVERSE);
      }
      mvwprintw(menuwin, (HEIGHT/5)+i+1, WIDTH/3, choices[i].c_str());
      wattroff(menuwin, A_REVERSE);
      wattroff(menuwin, COLOR_PAIR(2));
    }
    choice = wgetch(menuwin);

    switch (choice) {
      case KEY_UP:
      highlight--;
      if(highlight == -1){
        highlight = 0;
      }
      break;
      case KEY_DOWN:
      highlight++;
      if(highlight == 5){
        highlight = 4;
      }
      break;
      default:
      break;
    }
    if (highlight == 0 && choice == 10) {
      std::ifstream todoFile;
      std::string line;
      std::vector<std::string> taskChoices;
      todoFile.open("todo.txt");
      taskChoices.push_back("Back to the menu");
      while(getline(todoFile, line)){
        taskChoices.push_back(line);
      }
      todoFile.close();

      wresize(menuwin, HEIGHT, WIDTH + 5 + taskChoices.size());

      int taskChoice;
      int taskHighlight = 0;

      clear();
      wclear(menuwin);
      refresh();
      start_color();
      init_pair(1, COLOR_WHITE, COLOR_RED);
      wattron(menuwin, COLOR_PAIR(1));
      box(menuwin, (int)'/', (int)'-');
      wattroff(menuwin, COLOR_PAIR(1));
      wrefresh(menuwin);
      while(1) {
        for (int i = 0; i < taskChoices.size(); i++) {
          if(i == taskHighlight){
            wattron(menuwin, A_REVERSE);
          }
          mvwprintw(menuwin, (HEIGHT/5)+i+1, WIDTH/3, taskChoices[i].c_str());
          wattroff(menuwin, A_REVERSE);
        }
        taskChoice = wgetch(menuwin);

        switch (taskChoice) {
          case KEY_UP:
          taskHighlight--;
          if(taskHighlight == -1){
            taskHighlight = 0;
          }
          break;
          case KEY_DOWN:
          taskHighlight++;
          if(taskHighlight == taskChoices.size()) {
            taskHighlight = taskChoices.size()-1;
          }
          break;
          default:
          break;
        }
        if(taskHighlight == 0 && taskChoice == 10) {
          break;
        }
      }
    }
    else if (highlight == 1 && choice == 10) {
      std::vector<std::string> menuChoices;
      menuChoices.push_back("Back to the menu");
      menuChoices.push_back("Add new task");

      int taskChoice;
      int taskHighlight = 0;

      clear();
      wclear(menuwin);
      refresh();
      start_color();
      init_pair(1, COLOR_WHITE, COLOR_RED);
      wattron(menuwin, COLOR_PAIR(1));
      box(menuwin, (int)'/', (int)'-');
      wattroff(menuwin, COLOR_PAIR(1));
      wrefresh(menuwin);

      while(1){
        for (int i = 0; i < menuChoices.size(); i++) {
          if(i == taskHighlight){
            wattron(menuwin, A_REVERSE);
          }
          mvwprintw(menuwin, (HEIGHT/5)+i+1, WIDTH/3, menuChoices[i].c_str());
          wattroff(menuwin, A_REVERSE);
        }
        taskChoice = wgetch(menuwin);

        switch (taskChoice) {
          case KEY_UP:
          taskHighlight--;
          if(taskHighlight == -1){
            taskHighlight = 0;
          }
          break;
          case KEY_DOWN:
          taskHighlight++;
          if(taskHighlight == menuChoices.size()) {
            taskHighlight = menuChoices.size() - 1;
          }
          break;
          default:
          break;
        }
        if(taskHighlight == 0 && taskChoice == 10) {
          break;
        }
        else if(taskHighlight > 0 && taskChoice == 10){
          mvprintw(2, 50, "Please specify the task name:");
          wrefresh(menuwin);
          move(4, 50);
          echo();
          char newTask[30];
          getstr(newTask);
          noecho();
          menuChoices.push_back(newTask);
          std::ofstream writeNewTasks ("todo.txt");
          for (int i = 2; i < menuChoices.size(); i++) {
            writeNewTasks << menuChoices[i] << "\n";
          }
          writeNewTasks.close();
          break;
        }
      }
    }
    else if (highlight == 2 && choice == 10) {
      std::fstream modifyTaskInFile;
      std::string line;
      std::vector<std::string> taskChoices;
      modifyTaskInFile.open("todo.txt");
      taskChoices.push_back("Back to the menu");
      while(getline(modifyTaskInFile, line)) {
        taskChoices.push_back(line);
      }
      modifyTaskInFile.close();
      mvwprintw(menuwin, HEIGHT/3, 0, "Which task would you like to edit?");
      wrefresh(menuwin);

      int taskChoice;
      int taskHighlight = 0;

      clear();
      wclear(menuwin);
      refresh();
      start_color();
      init_pair(1, COLOR_WHITE, COLOR_RED);
      wattron(menuwin, COLOR_PAIR(1));
      box(menuwin, (int)'/', (int)'-');
      wattroff(menuwin, COLOR_PAIR(1));
      wrefresh(menuwin);

      mvwprintw(menuwin, 1, 4, "Select task to edit.");
      wrefresh(menuwin);

      while(1){
        for (int i = 0; i < taskChoices.size(); i++) {
          if(i == taskHighlight){
            wattron(menuwin, A_REVERSE);
          }
          mvwprintw(menuwin, (HEIGHT/5)+i+1, WIDTH/3, taskChoices[i].c_str());
          wattroff(menuwin, A_REVERSE);
        }
        taskChoice = wgetch(menuwin);

        switch (taskChoice) {
          case KEY_UP:
          taskHighlight--;
          if(taskHighlight == -1){
            taskHighlight = 0;
          }
          break;
          case KEY_DOWN:
          taskHighlight++;
          if(taskHighlight == taskChoices.size()) {
            taskHighlight = taskChoices.size()-1;
          }
          break;
          default:
          break;
        }
        if(taskHighlight == 0 && taskChoice == 10) {
          break;
        }
        else if(taskHighlight > 0 && taskChoice == 10){
          mvprintw(2, 50, "New task name:");
          wrefresh(menuwin);
          move(4, 50);
          echo();
          char newTask[30];
          getstr(newTask);
          noecho();
          taskChoices.erase(taskChoices.begin() + taskHighlight);
          taskChoices.push_back(newTask);
          std::ofstream writeNewTasks ("todo.txt");
          for (int i = 1; i < taskChoices.size(); i++) {
            writeNewTasks << taskChoices[i] << "\n";
          }
          modifyTaskInFile.close();
          break;
        }
      }
    }
    else if (highlight == 3 && choice == 10) {
      std::ifstream deleteFromFile ("todo.txt");
      std::string line;
      std::vector<std::string> taskChoices;
      taskChoices.push_back("Back to the menu");
      while(getline(deleteFromFile, line)) {
        taskChoices.push_back(line);
      }

      int taskChoice;
      int taskHighlight = 0;

      clear();
      wclear(menuwin);
      refresh();
      start_color();
      init_pair(1, COLOR_WHITE, COLOR_RED);
      wattron(menuwin, COLOR_PAIR(1));
      box(menuwin, (int)'/', (int)'-');
      wattroff(menuwin, COLOR_PAIR(1));
      wrefresh(menuwin);

      mvwprintw(menuwin, 1, 4, "Select task to remove.");
      wrefresh(menuwin);

      while(1) {
        for (int i = 0; i < taskChoices.size(); i++) {
          if(i == taskHighlight){
            wattron(menuwin, A_REVERSE);
          }
          mvwprintw(menuwin, (HEIGHT/5)+i+1, WIDTH/3, taskChoices[i].c_str());
          wattroff(menuwin, A_REVERSE);
        }
        taskChoice = wgetch(menuwin);

        switch (taskChoice) {
          case KEY_UP:
          taskHighlight--;
          if(taskHighlight == -1){
            taskHighlight = 0;
          }
          break;
          case KEY_DOWN:
          taskHighlight++;
          if(taskHighlight == taskChoices.size()) {
            taskHighlight = taskChoices.size() - 1;
          }
          break;
          default:
          break;
        }
        if(taskHighlight == 0 && taskChoice == 10) {
          break;
        }
        else if(taskHighlight > 0 && taskChoice == 10){
          taskChoices.erase(taskChoices.begin() + taskHighlight);
          std::ofstream writeNewTasks ("todo.txt");
          for (int i = 1; i < taskChoices.size(); i++) {
            writeNewTasks << taskChoices[i] << "\n";
          }
          deleteFromFile.close();
          break;
        }
      }
    }
    else if (highlight == 4 && choice == 10) {
      break;
    }
  }

  endwin();
  return 0;
}
