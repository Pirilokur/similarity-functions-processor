#ifndef OKAPISIMILARITY
#define OKAPISIMILARITY

#include "postinghandler.hpp"

class OkapiSimilarity{
	public:
		OkapiSimilarity();
		double okapi_calculate(std::string term);

	private:
		double idf_weight(std::string term);
		double term_weight(std::string term);
		double query_weight(std::string term);

}