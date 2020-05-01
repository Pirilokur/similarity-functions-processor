#include <string>
#include <iostream>
#include <cstring>

#include "terms.hpp"
#include "stemmer.h"
#include "queryHandler.hpp"

using namespace std;

/**
 * To make life easier for the TA, I have opted to hardcode in the input files 
 * so that they don't need to add them manually on the cmd line
 */ 
int main(){
    string dictionary_filename = "dictionary.txt";
    string postings_filename = "postings.txt";
    Terms t1;
    int x;
    string chosen_query;

   /*string query1 = "europe";
    string query2 = "stock rally";
    string query3 = "debt crisis";
    string query4 = "stock future higher";

    cout << "Please choose one of the queries below by entering the query number" << endl <<"1: europe " << endl;
    cout << "2: stock rally" << endl << "3: debt crisis" << endl << "4: stock future higher" << endl;
    cin >> x;
    if (x==1) chosen_query=query1;
    else if (x==2) chosen_query=query2;
    else if (x==3) chosen_query=query3;
    else if (x==4) chosen_query=query4;*/


    t1.populate_data(dictionary_filename, postings_filename);
    //t1.print_dictionary_entry("ahead");
    //t1.print_postings_entry(1395);
    t1.calculate_term_weight();
    //t1.print_postings_entry(1395);
    //the queries are hard coded in as well for now...

    
    //QueryHandler q1(chosen_query, t1);

    string query1 = "europe";
    string query2 = "stock rally";
    string query3 = "debt crisis";
    string query4 = "stock future higher";
    
    //QueryHandler q1(query1, t1);
    //QueryHandler q2(query2, t1);
    //QueryHandler q3(query3, t1);
    QueryHandler q4(query4, t1);

    string output1 = "query1result.txt";
    string output2 = "query2result.txt";
    string output3 = "query3result.txt";
    string output4 = "query4result.txt";

    //q1.tokenize();
    //q1.process_query();
    //q1.print_results(output1);

    
    //q2.tokenize();
    //q2.process_query();
    //q2.print_results(output2);

    //q3.tokenize();
    //q3.process_query();
    //q3.print_results(output3);

    q4.tokenize();
    q4.process_query();
    q4.print_results(output4);
    t1.print_postings();
    
}