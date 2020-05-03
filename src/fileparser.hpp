#ifndef FILEPARSER
#define FILEPARSER

#include <string>
#include <vector>
#include <fstream>

class FileParser{
    public:
        FileParser(std::string filename_in);
        std::string poll();
        std::vector<std::string> poll_lines(int num_lines);
        void open();
        void close();
    private:
        std::string filename;
        std::fstream file;
};




#endif
