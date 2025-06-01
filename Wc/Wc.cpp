// challenge: https://codingchallenges.fyi/challenges/challenge-wc

// libraries
#include <iostream> // std io
#include <string> // string
#include <fstream> // file io
#include <filesystem> // size
#include <sstream> // read string as if it is from a stream (cin)

// define ansi color codes
#define RESET "\033[0m"
#define RED "\033[31m"

// methods
int c(std::string file_name){ // file_size [step 1]
    return std::filesystem::file_size(file_name); // return size of file_name
}

int l(std::string file_name){ // file_lines [step 2]
    std::ifstream file(file_name);
    std::string temp = "";
    int file_lines = 0;
    while(std::getline(file, temp))
    {
        ++file_lines;
    }
    file.close(); // close file
    return file_lines; // return # of lines in file_name
}

int w(std::string file_name){ // file_words [step 3] [idk slightly larger but idk y]
    std::ifstream file(file_name);
    std::string temp;
    int file_words = 0;
    while(getline(file, temp))
    {
        std::stringstream ss(temp); // lets read temp like cin
        while(ss >> temp) // read a string from ss into temp
        {
            ++file_words;
        }
    }
    file.close();
    return file_words; // return # of words in file_name
}

int m(std::string file_name){ // file_chars [step 4]
    std::ifstream file(file_name, std::ios::binary);
    int file_chars = 0;
    char temp;
    while(file.get(temp))
    {
        if(temp != '\r' && temp != '\n'){
            ++file_chars;
        }
    }
    file.close();
    return file_chars; // return # of chars in file_name
}

int main(void)
{
    while(true)
    {
        std::string input = "", cmd = "", file_name = ""; // declare vars
        // initialize vars
        getline(std::cin, input); // get input
        int input_length = input.length(); // get input's length
        // interpret input [step 6]
        for(int i = 0; i < input_length; ++i)
        {
            if(input[i] == '.'){ // get file_name
                int file_name_index_end; // get the ending index of file name;
                for(int j = i+1; j < input_length; ++j)
                {
                    if(input[j] == ' '){
                        file_name_index_end = j-1;
                        break;
                    }else if(j == input_length-1){
                        file_name_index_end = j;
                        break;
                    }
                }
                
                int file_name_index_begin; // get the starting index of file name;
                for(int j = file_name_index_end; j >= 0; --j)
                {
                    if(input[j] == ' '){
                        file_name_index_begin = j+1;
                        break;
                    }else if(j == 0){
                        file_name_index_begin = 0;
                        break;
                    }
                }
    
                file_name = input.substr(file_name_index_begin, file_name_index_end - file_name_index_begin + 1); // get file_name
            }else if(input[i] == '-'){ // get cmd
                cmd += input[i];
                cmd += input[i+1];
            }
        }
    
        if(std::filesystem::exists(file_name) && std::filesystem::is_regular_file(file_name)){ // if file exists and is regular
            if(cmd == "-c"){ // if count file size
                std::cout << c(file_name) << ' ' << file_name << '\n';
            }else if(cmd == "-l"){ // if count # of lines in file
                std::cout << l(file_name) << ' ' << file_name << '\n';
            }else if(cmd == "-w"){ // if count # of words in file
                std::cout << w(file_name) << ' ' << file_name << '\n';
            }else if(cmd == "-m"){ // if count # of chars in file
                std::cout << m(file_name) << ' ' << file_name << '\n';
            }else{ // step 5
                std::cout << l(file_name) << ' ' << w(file_name) << ' ' << c(file_name) << ' ' << file_name << '\n';
            }
        }else{
            std::cout << RED << "Error: " << file_name << " not found / is irregular" << RESET << '\n';
        }
    }
    return 0;
}