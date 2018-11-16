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
  start_y = start_x = 10;

  WINDOW * menuwin = newwin(HEIGHT, WIDTH, start_y, start_x);
  refresh();

  box(menuwin, (int)'/', (int)'/');
  wrefresh(menuwin);

  keypad(menuwin, true);

  std::string choices[5] = {"View tasks", "Complete a task", "Edit a task", "Remove a task", "Exit"};

  int choice;
  int highlight = 0;

  while(1){
    box(menuwin, (int)'/', (int)'/');
    for (int i = 0; i < 5; i++) {
      if(i == highlight)
      wattron(menuwin, A_REVERSE);
      mvwprintw(menuwin, (HEIGHT/5)+i+1, WIDTH/3, choices[i].c_str());
      wattroff(menuwin, A_REVERSE);
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
      clear();
      refresh();
      std::ifstream todoFile;
      std::string line;
      std::vector<std::string> taskChoices;
      todoFile.open("todo.txt");
      taskChoices.push_back("Back to the menu");
      while(getline(todoFile, line)){
        taskChoices.push_back(line);
      }
      todoFile.close();

      WINDOW * taskwin = newwin(taskChoices.size() * 1.48, WIDTH + 10, start_y, start_x);

      system("clear");

      box(taskwin, (int)'/', (int)'/');
      wrefresh(taskwin);

      keypad(taskwin, true);

      int taskChoice;
      int taskHighlight = 0;

      while(1){
        for (int i = 0; i < taskChoices.size(); i++) {
          if(i == taskHighlight)
          {
            wattron(taskwin, A_REVERSE);
            mvwprintw(taskwin, (HEIGHT/5)+i+1, WIDTH/3, taskChoices[i].c_str());
            wattroff(taskwin, A_REVERSE);
          }
        }

        taskChoice = wgetch(taskwin);
        refresh();
        wrefresh(menuwin);

        switch (taskChoice) {
          case KEY_UP:
          taskHighlight--;
          if(taskHighlight == -1){
            taskHighlight = 0;
          }
          break;
          case KEY_DOWN:
          taskHighlight++;
          if(taskHighlight == taskChoices.size()){
            taskHighlight = taskChoices.size()-1;
          }
          break;
          default:
          break;
        }
        if(taskHighlight == 0 && taskChoice == 10) {
          endwin();
          break;
        }
      }
    }
    else if (highlight == 1 && choice == 10) {
      break;
    }
    else if (highlight == 2 && choice == 10) {
      break;
    }
    else if (highlight == 3 && choice == 10) {
      break;
    }
    else if (highlight == 4 && choice == 10) {
      break;
    }
  }

  endwin();
  return 0;
}
