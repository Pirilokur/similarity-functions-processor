#include <iostream>
#include <unistd.h> //required for getopt()
#include <string>
#include <vector>

#include <cstdlib>
#include "main.hpp"
#include "terms.hpp"
#include "stemmer.h"
#include "queryHandler.hpp"


int main(int argc, char * argv[]){
	
	string dictionary_filename = "dictionary.txt";
    string postings_filename = "postings.txt";
    Terms t1, t2, t3, t4;
    string chosen_query;



    t1.populate_data(dictionary_filename, postings_filename);
    t1.calculate_term_weight();
    t2.populate_data(dictionary_filename, postings_filename);
    t2.calculate_term_weight();
    t3.populate_data(dictionary_filename, postings_filename);
    t3.calculate_term_weight();
    t4.populate_data(dictionary_filename, postings_filename);
    t4.calculate_term_weight();


    
    //QueryHandler q1(chosen_query, t1);

    string query1 = "europe";
    string query2 = "stock rally";
    string query3 = "debt crisis";
    string query4 = "stock future higher";
    
    QueryHandler q1(query1, t1);
    QueryHandler q2(query2, t2);
    QueryHandler q3(query3, t3);
    QueryHandler q4(query4, t4);

    string output1 = "query1result-okapi.txt";
    string output2 = "query2result-okapi.txt";
    string output3 = "query3result-okapi.txt";
    string output4 = "query4result-okapi.txt";

    q1.tokenize();
    q1.process_query();
    q1.print_results(output1);

    
    q2.tokenize();
    q2.process_query();
    q2.print_results(output2);

    q3.tokenize();
    q3.process_query();
    q3.print_results(output3);

    q4.tokenize();
    q4.process_query();
    q4.print_results(output4);
    
    t1.print_postings();
    t2.print_postings();
    t3.print_postings();
    t4.print_postings();

	//std::string cmd = "./dictionary -i 200_content.txt";
	//std::system(cmd.c_str());
	//sleep(2); //ensure the files are done being created
	//cmd = "./cosin";
	//std::system(cmd.c_str());
}
