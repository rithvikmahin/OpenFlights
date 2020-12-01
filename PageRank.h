#pragma once
#include "Files.h"
class PageRank
{
public:
    PageRank(const char *file);
    void topPopularAirports(std::string source);

private:
    std::vector<std::vector<double> > createMarkovMatrix();
    std::vector<std::vector<double> > getProbabilities(std::string source);
    std::map<std::string, std::vector<std::string> > routes;
    int dimension;
    std::vector<std::string> airports;
    Files* f;
};