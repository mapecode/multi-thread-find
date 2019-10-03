#include <string>
#include <iostream>

class StringTokenizer
{
  private:
    std::string str;
    std::string delim;
    int count;
    int begin;
    int end;

  public:
    StringTokenizer(std::string str, std::string delim);
    ~StringTokenizer();
    bool next_token(std::string &s);
    bool has_more_tokens();
};

StringTokenizer::StringTokenizer(std::string str, std::string delim)
{
    this->str = str;
    this->delim = delim;
    this->begin = str.find_first_not_of(delim);
    this->end = str.find_first_of(delim, begin);
}

StringTokenizer::~StringTokenizer() {}

bool StringTokenizer::next_token(std::string &s)
{
    if (has_more_tokens())
    {
        if (begin != std::string::npos && end != std::string::npos)
        {
            s = str.substr(begin, end - begin);
            begin = str.find_first_not_of(delim, end);
            end = str.find_first_of(delim, begin);
        }
        else if (begin != std::string::npos && end == std::string::npos)
        {
            s = str.substr(begin, str.length() - begin);
            begin = str.find_first_not_of(delim, end);
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool StringTokenizer::has_more_tokens()
{
    return begin != end;
}
