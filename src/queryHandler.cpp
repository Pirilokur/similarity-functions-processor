#include "queryHandler.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include<cstring>
#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>
#include <fstream>
#include "stemmer.h"
#include "fileparser.hpp"

using namespace std;



QueryHandler::QueryHandler(std::string query_in, Terms terms_in){
    query.original_query = query_in;
    terms = terms_in;
}
/**
 * uses the same tokenization method as last project.
 */ 
void QueryHandler::tokenize(){
    query.terms = removeSpaces(query.original_query);
    vector<string> tokenized;
    for(auto i = query.terms.begin(); i != query.terms.end(); ++i){
        char tmp[i->length() + 4];
        strcpy(tmp, i->c_str());
        int sub = stem(tmp, 0, i->length() -1);
        string t_string(tmp);
        tokenized.push_back(t_string.substr(0, sub+1));

    }
    query.terms = tokenized;
}

std::vector<std::string> QueryHandler::removeSpaces(std::string line){
    std::vector<std::string> retval;
    boost::algorithm::split(retval, line, boost::algorithm::is_any_of(" "));  
    return retval;
}

/**
 * prints each term in the query
 */ 
void QueryHandler::print_terms(){
    for(auto i = query.terms.begin(); i != query.terms.end(); ++i){
        cout << *i << endl;
    }
}

/**
 * Getter for the terms in the query
 */ 
std::vector<std::string> QueryHandler::get_terms(){
    return query.terms;
}

/**
 * This method will first retreieve the dictionary entry for each query term
 * Using that entry, it will then get the location of the posting lists
 * Then, it will retrieve the postings list
 * To compare similarity, Document at a time algorithm will be used
 */ 
void QueryHandler::process_query(){
    int number_of_terms = query.terms.size();
    queue<Posting> term_posting_list[number_of_terms];
    DictionaryEntry dic_ent;
    for(int i = 0; i < number_of_terms; ++i){
        dic_ent = terms.get_dictionary_entry(query.terms.at(i));
        for(int k = 0; k < dic_ent.document_freq; ++k){
            term_posting_list[i].push(terms.get_postings_entry(dic_ent.offset + k));
        }
    }
    /**
     * 
     *  Implement document at a time algorithm here. The Postings lists are saved
     * in the term_posting_list array as a series of queues (should be the easiest way
     * since DaaT uses a k way merge). 
     */

    /**
     * note that comparing the similarity has to be done with the k way merge of the 
     * documents. So peek each queue, the lowest document id(s) will be considered. Pop the
     * values and calculate that documents overall similarity using the cosine similarity
     *  formula (will need a separate data structure to contain the scores of each
     *  document probably).
     */ 

    /*so, until all of the queues are empty, peek() each queue. Whichever queue has the 
    * smallest documente_id, pop it and calculate the cosine similarity. If there is a tie
    * pop all of them and calculate the cosine similarity. 
    * After that, compare the weights to find the ordering
    */


    for(int i = 0; i < number_of_terms; ++i){
        for(int k = 0; k < dic_ent.document_freq; ++k){
            
        }
    }



   bool is_empty = false; 
  
   Posting temp;
   vector<double> posting_weight;
   vector<double> query_weight;
   vector<double> doc_freq; // document frequency to be used for okapi
   vector <double> raw_tf; // term frequency to be used for okapi
   vector <double> dl; // document length to be used for okapi
   vector<Document> doc_length;
   FileParser fp("size.txt");
   //doc_length = fp.parse();   //TODO This is not a method in fileparser. Not sure what you're trying to do with this.
   int sum=0;
   double avdl;

   


   while(!is_empty){
        int min = 2000;
       //get the next smallest document
       for(int i =0; i < number_of_terms; ++i){
           temp = term_posting_list[i].front();
           if(temp.document_id < min){
               min = temp.document_id;
           }
       }
       for(int i=0;i<200;i++){
          //sum+=doc_length.at(i); //TODO This is an error. doc_length is a vector of Documents, not doubles according to your code
        }

        avdl=sum/200;



       for(int i = 0; i < number_of_terms; ++i){
           temp = term_posting_list[i].front();
           if(temp.document_id == min){
               term_posting_list[i].pop();
               double idf_weight = 1 + log10(200 / terms.get_dictionary_entry(query.terms.at(i)).document_freq);
               temp.weight_tf = temp.weight_tf / terms.documents[temp.document_id].number_of_terms;
               //cout << "posting weight is: " << temp.weight_tf * idf_weight << " idf is: " << idf_weight << " tf is: " << temp.weight_tf <<endl;
                posting_weight.push_back(temp.weight_tf * idf_weight);
                double q_weight = 1 + log10(1); //tf for query
                q_weight = q_weight *  (200 / terms.get_dictionary_entry(query.terms.at(i)).document_freq);         //idf
                //cout << "qeight is " << q_weight << endl;
                query_weight.push_back(q_weight);
                //get the cosine similarity now
                terms.documents[temp.document_id].cosine_similarity = calculate_cosine_similarity(posting_weight, query_weight);
                //get the okapi similarity
                //int x=terms.documents[temp.document_id];  //TODO: terms.documents returns a document, not an int. Not sure what you're trying to set x equal to
                //dl.push_back(doc_length.at(i)); //TODO: doc_length is a vector of documents. d1 is a vector of doubles. Cannot convert document to double. Not sure what data you were trying to get here.
                doc_freq.push_back(terms.get_dictionary_entry(query.terms.at(i)).document_freq);
                raw_tf.push_back(temp.weight_tf);
               // terms.documents[temp.document_id].okapi_similarity = calculate_okapi_similarity(doc_freq,raw_tf,avdl,);
           }
       }
       //now check if all queues are empty
       for(int i = 0; i < number_of_terms; ++i){
           is_empty = true;
           if(!term_posting_list[i].empty()){
               is_empty = false;
           }
       }
       //is_empty = true;
   }
}

double QueryHandler::calculate_okapi_similarity(vector<double> df, vector<double> raw_tf, vector <double> dl, int avdl){
    double k=1.2;
    double b=0.75;
    double qtf=1.0; //tf for query
    double w,dt,qt;
    double sum=0;


    for(int i = 0; i < df.size(); ++i){
        w= log((200 - df.at(i) + 0.5)/(df.at(i)+0.5));
        dt= ((k+1) * raw_tf.at(i)) / (k * ((1-b) + b * dl.at(i)/avdl));
        qt=(k+1) * qtf / (k+qtf);
        sum = sum + (w*dt*qt);
    }
   
    return sum;
}

double QueryHandler::calculate_cosine_similarity(vector<double> p_weights, vector<double> q_weights){
    double numerator = 0;
    double denominator = 0;
    for(int i = 0; i < p_weights.size(); ++i){
        numerator = numerator +  (p_weights.at(i) * q_weights.at(i));
        denominator = denominator + (pow(p_weights.at(i), 2.0));
    }
    denominator = sqrt(denominator);
    //cout << "The cosine similarity is: " << numerator/denominator << endl;
    return numerator / denominator;
}


void QueryHandler::print_results(string filename){

  outFile.open(filename);
    for(int i = 0; i < 200; ++i){
        if(terms.documents[i].cosine_similarity > 0){
            cout << "document: " << i+1 << " " << terms.documents[i].document_id << " with a similarity of: " << terms.documents[i].cosine_similarity << endl;
        }
    }

    sort(begin(terms.documents), end(terms.documents), [](Document a, Document b) {return a.cosine_similarity > b.cosine_similarity;});

    for(int i = 0; i < 200; ++i){
        if(terms.documents[i].cosine_similarity > 0){
            cout << "document: " << i+1 << " " << terms.documents[i].document_id << " with a similarity of: " << terms.documents[i].cosine_similarity << endl;
        }
    }

    for(int i = 0; i < 10; ++i){
        if(terms.documents[i].cosine_similarity > 0){
            outFile << terms.documents[i].document_id << ", " << terms.documents[i].cosine_similarity << endl;
        }
    }
    outFile.close();
  /**
  int similarity[]={};
  Document output[10];
  int j=0;
    for(int i = 0; i < 200; ++i){
        if(terms.documents[i].cosine_similarity > 0){
           similarity[j] = terms.documents[i].cosine_similarity ;
           j++;
        }
    }

    int n = sizeof(similarity) / sizeof(similarity[0]); 
    sort(similarity, similarity + n, greater<int>());

    for(int i=0; i<10; i++){
      for(int a=0; a<n ; a++){
        if (terms.documents[a].cosine_similarity == similarity[i]){
          output[i]=terms.documents[a];
        }
      }
    }


    //The Documents array output[] needs to be converted into a string array
    //to be written into a binary file



    for(int i=0;i<10;i++){
      outFile.write((char*)&(output[i]),sizeof(Document));

    }
    */
    
}








