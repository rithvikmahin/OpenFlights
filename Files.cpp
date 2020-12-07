#include "Files.h"
#include <sstream>
#include <algorithm>

/**
 * A method to read the .dat files.
 * @param filename - The name of the .dat file to be read.
 * @return - A vector of strings, where each string is each line in the .dat file. 
*/
std::vector<std::string> Files::readFile(const char* filename) {
    std::ifstream text(filename);
    std::stringstream output;

    // Reads the file into a string stream.
    if (text.is_open()) {
        output << text.rdbuf();
    }

    std::vector<std::string> data;
    
    // Separates each line based on the newline character. 
    for (std::string line; std::getline(output, line, '\n');) {
        data.push_back(line);
    }
    return data;
}

/**
 * A method to return a map of airports and their coordinates.
 * @param data - A vector of strings, where each string is each line in the airports.dat file. 
 * @return - A map of airport names (key) to a vector of doubles (value), where vector[0] is the latitude of the airport and vector[1] is the longitude.
*/
std::map<std::string, std::vector<double> > Files::getAirportCoordinates(std::vector<std::string> data) {
    std::map<std::string, std::vector<double> > airportCoordinates;

    for (int i = 0; i < data.size(); i++) {
        std::string airport = data[i];
        // The token on which to separate each string.
        std::string delimiter = ",";
        size_t index = 0;
        int position = 0;

        std::string sourceAirport;
        double latitude;
        double longitude;

        // This loop goes through the each string and separates data out based on commas.
        while ((index = airport.find(delimiter)) != std::string::npos) {
            
            // Position 4 is the source airport, which is either a 3 digit name or \N to indicate an unknown name. These extract the substrings for the source airport.
            if (position == 4 && airport.substr(0, index) != "\\N") {
                std::string substring = airport.substr(0, index);
                substring.erase(0, 1);
                substring.erase(substring.size() - 1);
                sourceAirport = substring;
            }

            if (position == 4 && airport.substr(0, index) == "\\N") {
                break;
            }

            // Position 6 is the latitude, it is pushed into the vector pertaining to the airport as it always comes before the longitude.
            if (position == 6) {
                std::istringstream latitudeString(airport.substr(0, index));
                latitudeString >> latitude;
                airportCoordinates[sourceAirport].push_back(latitude);
            }

            // Position 7 is the longitude.
            if (position == 7) {
                std::istringstream longitudeString(airport.substr(0, index));
                longitudeString >> longitude;
                airportCoordinates[sourceAirport].push_back(longitude);
            }

            // Removes the current substring from the string and iterates through.
            airport.erase(0, index + delimiter.length());
            position++;
            
            // Position 13 is the end of a string / line.
            if (position == 13) {
                position  = 0;
            }
        }
    }  
    return airportCoordinates;
}

/**
 * A method to return a map of airports and the list of their direct-connected routes.
 * @param data - A vector of strings, where each string is each line in the routes.dat file. 
 * @return - A map of airport names (key) to a vector of strings (value), where each string in the vector is an airport that can be reached from the current source airport.
*/
std::map<std::string, std::vector<std::string> > Files::getRoutes(std::vector<std::string> data) {
    std::map<std::string, std::vector<std::string> > routes;

    // Similar functionality to the method getAirportCoordinates.

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

            route.erase(0, index + delimiter.length());
            position++;
            
            if (position == 7) {
                routes[sourceAirport].push_back(destinationAirport);
                position  = 0;
            }
        }
    }  
    return routes;
}

/**
 * This method finds the index of a given airport in the vector of unique airports.
 * @param airport - The airport whose index needs to be found.
 * @param airports - The vector of airports in which the airport exists. 
*/
int Files::getIndex(std::string airport, std::vector<std::string> airports) {
    int index = 0;
    // This loop finds the index of the airport and returns it.
    for (int i = 0; i < airports.size(); i++) {
        if (airports[i] == airport) {
            index = i;
            break;
        }
    }
    return index;
}


