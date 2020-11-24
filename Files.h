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
        std::map<std::string, std::vector<std::string> > getData(std::vector<std::string> data);
        std::map<std::string, int> getRouteLayovers();

        int getDestinationIndex(std::string destination, std::vector<std::string> airports);

        std::map<std::string, int> layovers;
};