#include <iostream>
#include <fstream>



#include "fileparser.hpp"

using namespace std;

FileParser::FileParser(std::string filename_in){
    filename = filename_in;
}

string FileParser::poll(){
    string ret_val = "";
    if(!file.eof()){
        getline(file, ret_val);
    }
    return ret_val;
}

std::vector<string> FileParser::poll_lines(int num_lines){
    int k = 0;
    vector<string> ret_val;
    string line = "";
    while(!file.eof() && k < num_lines){
        getline(file, line);
        ret_val.push_back(line);
    }
    return ret_val;
}

void FileParser::open(){
    file.open(filename);
}

void FileParser::close(){
    file.close();
}