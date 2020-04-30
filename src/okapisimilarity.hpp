#ifndef OKAPISIMILARITY
#define OKAPISIMILARITY

#include "postinghandler.hpp"

class OkapiSimilarity{
	public:
		OkapiSimilarity();


	private:
		double idf_weight(std::string term);
		double term_weight(std::string term);
		double query_weight(std::string term);
}