#include "terms.hpp"
#include "fileparser.hpp"

#include <bits/stdc++.h> 
#include <cmath>
#include <fstream>

using namespace std;

void Terms::populate_data(string dictionary_filename, string postings_filename){
    update_dictionary(dictionary_filename);
    update_postings(postings_filename);
}
/**
 * Adds entries to the dictionary
 */ 
void Terms::update_dictionary(std::string filename){
    FileParser fp(filename);
    fp.open();
    string line = "none";
    while(line != ""){
        line = fp.poll();
        istringstream par(line);
        DictionaryEntry temp;
        par >> temp.term;
        par >> temp.document_freq;
        par >> temp.offset;
        temp.weight_idf = 0.0;
        dictionary.insert({temp.term, temp});
    }
}

/**
 * Updates the postings list
 */ 
void Terms::update_postings(std::string filename){
    FileParser fp(filename);
    fp.open();
    string line = "none";
    while(line != ""){
        line = fp.poll();
        istringstream par(line);
        Posting temp;
        par >> temp.document_id;
        par >> temp.term_freq;
        temp.weight_tf = 0.0;
        postings.push_back(temp);
    }
    calculate_docment_size();
}
/**
 * Prints the specified dictionary entry
 */ 
void Terms::print_dictionary_entry(std::string term){
    auto ret = dictionary.find(term);
    cout << ret->first << " " << ret->second.document_freq << " " << ret->second.offset <<endl;
}

/**
 * prints a single posting entry at the offset
 */ 
void Terms::print_postings_entry(int offset){
    Posting temp;
    temp = postings.at(offset);
    cout << temp.document_id << " " << temp.term_freq << " " << temp.weight_tf <<endl;
}
/**
 * returns a single dictionary entry corresponding to the term
 */
DictionaryEntry Terms::get_dictionary_entry(std::string term){
    auto itr = dictionary.find(term);
    return itr->second;
}
/**
 * Returns a single Posting entry at location offset
 */ 
Posting Terms::get_postings_entry(int offset){
    return postings.at(offset);
}
/**
 * Modifies the term_freq in the postings list to represent
 * the weight of the term. The weight is calculated using
 * weight = log10(term_frequency)
 */ 
void Terms::calculate_term_weight(){
    for(auto post = postings.begin(); post != postings.end(); ++post){
        post->weight_tf = 1 + log10(post->term_freq);
    }
}

void Terms::calculate_idf_weight(){
    for(auto post = postings.begin(); post != postings.end(); ++post){
        //this needs to be changed to be calculated on a document entry, not a posting list
        //post->weight_idf = log10( 200 / (post->document_freq));
    }
}

/**
 * This method should be called after the idf weight has already been calculated for each term
 * @param idf_weight    the idf weight of the term.
 */ 
void Terms::calculate_overall_weight(double idf_weight){
    //My modification-
    //calculate_idf_weight();
   // calculate_term_weight();
    // weight=0.0;   not needed
    //for(auto post = postings.begin(); post != postings.end(); ++post){
        //post->weight = post->weight_tf * idf_weight;
    //}
}

void Terms::calculate_docment_size(){
    for(auto i = postings.begin(); i != postings.end(); ++i){
        documents[i->document_id].number_of_terms = documents[i->document_id].number_of_terms + i->term_freq;
        documents[i->document_id].document_id = i->document_id + 1;
    }
}

void Terms::print_postings(){
    ofstream outFile;
    outFile.open("revised_postings.txt");
    for(auto i = postings.begin(); i != postings.end(); ++i){
        outFile << i->document_id << " " << i->weight_tf << endl;
    }
    outFile.close();
}