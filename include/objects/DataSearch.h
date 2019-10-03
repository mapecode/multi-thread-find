#include <iostream>
#include <list>
#include <definitions.h>

class DataSearch
{
private:
  int n_thread;
  int start_line;
  int end_line;
  std::list<WordFinded> searches_list;
  int color;
  std::string build_search_string(WordFinded wf);
  void color_print(std::string str);

public:
  DataSearch(int color, int n_thread, int start_line, int end_line);
  ~DataSearch();
  void add_word(int line, std::string word_, std::string antecesor, std::string sucesor);
  int getStart_line();
  int getEnd_line();
  void print();
};

DataSearch::DataSearch(int color,int n_thread, int start_line, int end_line)
{
  this->color=color;
  this->n_thread = n_thread;
  this->start_line = start_line;
  this->end_line = end_line;
}

DataSearch::~DataSearch() {}

void DataSearch::add_word(int line, std::string word_, std::string predecessor, std::string successor)
{
  WordFinded *wf = new WordFinded;
  wf->line = line;
  wf->word_ = word_;
  wf->predecessor = predecessor;
  wf->successor = successor;
  searches_list.push_back(*wf);
}

int DataSearch::getStart_line()
{
  return start_line;
}

int DataSearch::getEnd_line()
{
  return end_line;
}

std::string DataSearch::build_search_string(WordFinded wf)
{
  char s[MAX_CHAR];
  sprintf(s, "[Thread %d start:%d - end:%d] :: line %d :: ", n_thread, start_line, end_line, wf.line);
  return s + ("..." + wf.predecessor + " " + wf.word_ + " " + wf.successor + "...");
}

void DataSearch::print()
{
  int searches_list_length = searches_list.size();
  std::string str;
  for (int i = 0; i <searches_list_length; i++)
  {
    str = build_search_string(searches_list.front());
    searches_list.pop_front();
    color_print(str);
  }
}

void DataSearch::color_print(std::string str){
  switch (color)
  {
  case RED:
    print_red(str);
    break;
  case GREEN:
    print_green(str);
    break;
  case YELLOW:
    print_yellow(str);
    break;
  case BLUE:
    print_blue(str);
    break;
  case MAGENTA:
    print_magenta(str);
    break;
  case CYAN:
    print_cyan(str);
    break;
  case WHITE:
    print_white(str);
    break;
  }
}