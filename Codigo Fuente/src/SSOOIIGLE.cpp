#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <string>
#include <mutex>

#include <objects/DataSearch.h>
#include <objects/StringTokenizer.h>
#include <definitions.h>


void parse_argv(int argc, char *argv[], std::string &file, std::string &word_, int &n_threads);
void count_lines(std::string file, int &lines);
void assign_lines(int n_threads, int lines, int &lines_per_thread, int &rest_lines);
void launch_threads(int n_threads, int lines_per_thread, int rest_lines, std::string file_name, std::string word_);
void wait_threads();
void print_result();
void search(int pos, std::string file_name, std::string word_);
bool equals(std::string word_, std::string word_to_compare);
void build_search(int posi, int line, std::vector<int> words_finded_positions, std::vector<std::string> line_words);

std::vector<DataSearch> searches_vector;
std::vector<std::thread> threads_vector;
int n_occurrences=0;

int main(int argc, char *argv[])
{
    std::string file_name;
    std::string word_;
    int n_threads;
    int lines;
    int lines_per_thread;
    int rest_lines;

    parse_argv(argc, argv, file_name, word_, n_threads);
    count_lines(file_name, lines);
    assign_lines(n_threads, lines, lines_per_thread, rest_lines);
    launch_threads(n_threads, lines_per_thread, rest_lines, file_name, word_);
    wait_threads();
    print_result();
    reset_color();
}

void parse_argv(int argc, char *argv[], std::string &file, std::string &word_, int &n_threads)
{
    std::fstream fs;

    if (argc != 4)
    {
        fprintf(stderr, "Error in the command line\n");
        exit(EXIT_FAILURE);
    }

    file = argv[1];

    fs.open(file);
    if (!fs.is_open())
    {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    fs.close();

    word_ = argv[2];
    upper_to_lower(word_);
    n_threads = atoi(argv[3]);
}

void count_lines(std::string file, int &lines)
{
    lines = 0;
    std::string line;
    std::fstream fs;

    fs.open(file, std::ios::in);

    while (getline(fs, line))
        lines++;

    fs.close();
}

void assign_lines(int n_threads, int lines, int &lines_per_thread, int &rest_lines)
{
    lines_per_thread = lines / n_threads;
    rest_lines = lines - (lines_per_thread * n_threads);
}

void launch_threads(int n_threads, int lines_per_thread, int rest_lines, std::string file_name, std::string word_)
{
    int start_line, end_line;
    int colors[N_COLORS] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

    for (int i = 0, c = 0; i < n_threads; i++, c++)
    {
        start_line = lines_per_thread * i + 1;
        i == n_threads - 1 ? end_line = lines_per_thread * (i + 1) + rest_lines : end_line = lines_per_thread * (i + 1);
        c < N_COLORS ? c : c = 0; //Position in array of colors
        searches_vector.push_back(DataSearch(colors[c], i + 1, start_line, end_line));
        threads_vector.push_back(std::thread(search, i, file_name, word_));
    }
}

void wait_threads()
{
    std::for_each(threads_vector.begin(), threads_vector.end(), std::mem_fn(&std::thread::join));
}

void print_result()
{
    std::cout << "Number of occurrences: \n" << n_occurrences << std::endl;
    for (int i = 0; i < searches_vector.size(); i++)
    {
        searches_vector[i].print();
    }
}

void search(int search, std::string file_name, std::string word_)
{
    std::string line, token, antecesor, sucesor;
    std::fstream fs;
    std::vector<int> words_finded_positions;
    std::vector<std::string> line_words;
    int lines_count = 1;

    fs.open(file_name, std::ios::in);

    while (getline(fs, line))
    {
        if (lines_count >= searches_vector[search].getStart_line() && lines_count <= searches_vector[search].getEnd_line())
        {
            StringTokenizer st(line, " ");
            for (int i = 0; st.next_token(token); i++)
            {
                line_words.push_back(token);
                if (equals(word_, token))
                {
                    words_finded_positions.push_back(i);
                }
            }
            if (words_finded_positions.size() >= 0)
            {
                build_search(search, lines_count, words_finded_positions, line_words);
                words_finded_positions.clear();
            }
            line_words.clear();
        }

        lines_count++;
    }

    fs.close();
}

bool equals(std::string word_, std::string word_to_compare)
{
    int n_equals = 0; //number of consecutive equal characters

    upper_to_lower(word_to_compare);

    for (int i = 0, j = 0; i < word_to_compare.length(); i++)
    {
        if (word_to_compare[i] == word_[j])
        {
            n_equals++;
            j++;
        }
        else
        {
            n_equals = 0;
            j = 0;
        }

        if (n_equals == word_.length())
            return true;
    }

    return false;
}

void build_search(int search, int line, std::vector<int> words_finded_positions, std::vector<std::string> line_words)
{
    std::mutex sem1,sem2;
    std::string predecessor, successor;

    for (int i = 0, pos; i < words_finded_positions.size(); i++)
    {
        pos = words_finded_positions[i];

        if (pos == 0 && line_words.size() > 1) //Without predecessor
        {
            predecessor = "";
            successor = line_words[pos + 1];
        }
        else if (pos == line_words.size() - 1 && line_words.size() > 1) //Without successor
        {
            predecessor = line_words[pos - 1];
            successor = "";
        }
        else if (pos == 0 && line_words.size() == 1) //Without predecessor and successor
        {
            predecessor = successor = "";
        }
        else //With predecessor and successor
        {
            predecessor = line_words[pos - 1];
            successor = line_words[pos + 1];
        }

        std::unique_lock<std::mutex> lock(sem1);
        {
            n_occurrences++;
        }
        lock.unlock();

        std::lock_guard<std::mutex> guard(sem2);
        {
            searches_vector[search].add_word(line, line_words[pos], predecessor, successor);
        }    
    }
}
