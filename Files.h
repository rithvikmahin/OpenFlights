#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

class Files {
    public:
        std::vector<std::string> readFile(const char* filename);
        std::map<std::string, std::vector<std::string> > getRoutes(std::vector<std::string> data);
        std::map<std::string, std::vector<double> > getAirportCoordinates(std::vector<std::string> data);
        int getIndex(std::string destination, std::vector<std::string> airports);
};