#ifndef TOKENIZER
#define TOKENIZER

#include <string>
#include <vector>


struct Document{
    int id;
    std::string contents;
};

struct TermPair{
    std::string term;
    int docID;
};

class Tokenizer{
    public:
        Tokenizer(std::string input_filename);
        std::vector<TermPair> tokenize();
    private:
        std::vector<TermPair> terms;
        std::string inp_file;
        std::vector<Document> docs;
        void case_fold(Document &d1);
        void remove_punct(Document &d1 , char symbols[]);
        std::vector<std::string> removeSpaces(std::string line);
        void add_to_term_list(std::string termIn, int docIDIn);
        void sort_terms();
        


};



#endif