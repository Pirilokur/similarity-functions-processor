#ifndef TERMS
#define TERMS

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct DictionaryEntry{
    std::string term;
    int document_freq;
    int offset;
    double weight_idf;
    double weight;
};

struct Posting{
    int document_id;
    int term_freq;
    double weight;
    
    double weight_tf;
};

struct Document{
    int number_of_terms;
    double cosine_similarity = 0.0;
    double okapi_similarity= 0.0;
    int document_id;
    vector<double> postings_weight;

};

class Terms{
    public: 
        void populate_data(std::string dictionary_filename, std::string postings_filename);
        void print_dictionary_entry(std::string term);
        void print_postings_entry(int offset);
        DictionaryEntry get_dictionary_entry(std::string term);
        Posting get_postings_entry(int offset);
        void calculate_term_weight();
        void calculate_overall_weight(double idf_weight);
        void calculate_idf_weight();
        Document documents[201];
        void print_postings();

    private:
        std::unordered_map<std::string, DictionaryEntry> dictionary;
        std::vector<Posting> postings;
        
        void update_dictionary(std::string filename);
        void update_postings(std::string filename);
        void calculate_docment_size();


};

#endif