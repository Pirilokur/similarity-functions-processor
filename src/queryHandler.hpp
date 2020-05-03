#ifndef QUERY_H
#define QUERY_H

#include "terms.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
 


struct Query{
    std::string original_query;
    std::vector<std::string> terms;
};

class QueryHandler{
    public:
        QueryHandler(std::string query_in, Terms terms_in);
        void tokenize();
        void print_terms();
        std::vector<std::string> get_terms();
        void process_query();
        void print_results(string filename);
        std::ofstream outFile;
    private:
        Query query;
        Terms terms;
        std::vector<std::string> removeSpaces(std::string line);
        const int NUMBER_OF_DOCUMENTS = 201;
        double calculate_okapi_similarity(vector<double> p_weights, vector<double> q_weights, vector <double> dl, int avdl);
        double calculate_cosine_similarity(vector<double> p_weights, vector<double> q_weights);
};





#endif