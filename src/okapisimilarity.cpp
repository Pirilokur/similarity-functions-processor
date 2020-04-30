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
	DictionaryEntry d1;
    d1.term = term;
    d1.document_frequency = document_frequency;
	double w;
	w= log((200 - document_frequency + 0.5)/(document_frequency+0.5));
}


double OkapiSimilarity::term_weight(std::string term){
	double k=1.2;
	double b=0.75;
}

double OkapiSimilarity::query_weight(std::string term){
	
}