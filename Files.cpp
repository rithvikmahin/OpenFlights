#include "Files.h"
#include <sstream>
#include <algorithm>

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

std::map<std::string, std::vector<double> > Files::getAirportCoordinates(std::vector<std::string> data) {
    std::map<std::string, std::vector<double> > airportCoordinates;

    for (int i = 0; i < data.size(); i++) {
        std::string airport = data[i];

        std::string delimiter = ",";
        size_t index = 0;
        int position = 0;

        std::string sourceAirport;
        double latitude;
        double longitude;

        bool number = false;

        while ((index = airport.find(delimiter)) != std::string::npos) {

            if (position == 4 && airport.substr(0, index) != "\\N") {
                std::string substring = airport.substr(0, index);
                substring.erase(0, 1);
                substring.erase(substring.size() - 1);
                sourceAirport = substring;
            }

            if (position == 4 && airport.substr(0, index) == "\\N") {
                break;
            }

            if (position == 6) {
                std::istringstream latitudeString(airport.substr(0, index));
                latitudeString >> latitude;
                airportCoordinates[sourceAirport].push_back(latitude);
            }

            if (position == 7) {
                std::istringstream longitudeString(airport.substr(0, index));
                longitudeString >> longitude;
                airportCoordinates[sourceAirport].push_back(longitude);
            }

            airport.erase(0, index + delimiter.length());
            position++;

            if (position == 13) {
                position  = 0;
            }
        }
    }  
    return airportCoordinates;
}


std::map<std::string, std::vector<std::string> > Files::getRoutes(std::vector<std::string> data) {
    std::map<std::string, std::vector<std::string> > routes;

    for (int i = 0; i < data.size(); i++) {
        std::string route = data[i];

        std::string delimiter = ",";
        size_t index = 0;
        int position = 0;

        std::string sourceAirport;
        std::string destinationAirport;

        while ((index = route.find(delimiter)) != std::string::npos) {

            if (position == 2) {
                sourceAirport = route.substr(0, index);
            }

            if (position == 4) {
                destinationAirport = route.substr(0, index);
            }

            if (position == 6) {
                std::string numberOfLayovers = route.substr(0, index);
                std::stringstream layoversStream(numberOfLayovers);
                int layoversInteger = 0;
                layoversStream >> layoversInteger;
                layovers[sourceAirport + "-" + destinationAirport] = layoversInteger;
            }

            if (position == 7) {
                routes[sourceAirport].push_back(destinationAirport);
                position  = 0;
            }

            route.erase(0, index + delimiter.length());
            position++;
        }
    }  
    return routes;
}

int Files::getIndex(std::string destination, std::vector<std::string> airports) {
    int index = 0;
    for (int i = 0; i < airports.size(); i++) {
        if (airports[i] == destination) {
            index = i;
            break;
        }
    }
    return index;
}

std::map<std::string, int> Files::getRouteLayovers() {
    return layovers;
}

