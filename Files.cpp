#include "Files.h"

std::vector<std::string> Files::readFile(const char* filename) {
    std::ifstream text(filename);
    std::stringstream output;

    if (text.is_open()) {
        output << text.rdbuf();
    }

    std::vector<std::string> data;
    
    for (std::string line; std::getline(output, line, '\n');) {
        data.push_back(line);
    }

    return data;
}

std::map<std::string, std::vector<std::string> > Files::getData(std::vector<std::string> data) {
    std::map<std::string, std::vector<std::string> > routes;

    for (int i = 0; i < data.size(); i++) {
        std::string route = data[i];

        std::string delimiter = ",";
        size_t index = 0;
        int position = 0;

        std::string sourceAirport;
        std::string destinationAirport;

        while ((index = route.find(delimiter)) != std::string::npos) {
            //std::cout << route << std::endl;

            if (position == 2) {
                sourceAirport = route.substr(0, index);
                //std::cout << "Source " << sourceAirport << std::endl;
                //std::cout << "-----------" << std::endl;
            }

            if (position == 4) {
                destinationAirport = route.substr(0, index);
            }

            /**if (position == 6) {
                std::string numberOfLayovers = route.substr(0, index);
                layovers[sourceAirport + "-" + destinationAirport] = std::stoi(numberOfLayovers);
            }*/

            if (position == 7) {
                routes[sourceAirport].push_back(destinationAirport);
                //std::cout << "Source " << sourceAirport << " Destination " << destinationAirport << std::endl;
                position  = 0;
            }

            route.erase(0, index + delimiter.length());
            position++;
        }
    }  
    return routes;
}

int Files::getDestinationIndex(std::string destination, std::vector<std::string> airports) {
    int index = 0;
    for (int i = 0; i < airports.size(); i++) {
        if (airports[i] == destination) {
            index = i;
            break;
        }
    }
    //std::cout << "Destination " << destination << " Index " << index << std::endl;
    return index;
}

std::map<std::string, int> Files::getRouteLayovers() {
    return layovers;
}

