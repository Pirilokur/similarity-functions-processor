#include "okapisimilarity.hpp"
#include "stemmer.h"
#include "tokenizer.h"

#include <cstring>
#include <iostream>
#include <queue>
#include <math.h>
#include <algorithm>

using namespace std;

OkapiSimilarity::OkapiSimilarity(){

}
//"w" from the formula
double OkapiSimilarity::idf_weight(std::string term){
	DictionaryEntry d1; ////document_frequency is going to be used
    d1.term = term;
    d1.document_frequency = document_frequency;
	double w;
	w= log((200 - document_frequency + 0.5)/(document_frequency+0.5));
	return w;
}


double OkapiSimilarity::term_weight(std::string term){
	double k=1.2;
	double b=0.75;
	double dl, avdl; //needed to be calculated elsewhere
	Posting p1; //term_frequency is going to be used

}

double OkapiSimilarity::query_weight(std::string term){
	double k=1.2
}

double OkapiSimilarity::okapi_calculate(std::string term){
	double result;
	result= idf_weight(term) * term_weight(term) * query_weight(term);
}