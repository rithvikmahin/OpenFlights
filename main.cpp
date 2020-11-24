/**#include "Files.h"

int main() {
    const char* filename = "routes.dat";
    Files file = Files();

    std::vector<std::string> data = file.readFile(filename);
    std::map<std::string, std::vector<std::string> > routes = file.getData(data);
    std::map<std::string, int> routeLayovers = file.getRouteLayovers();

    std::string sourceAirport = "JFK";
    std::string destinationAirport = "BLR";

    int layovers = routeLayovers[sourceAirport + '-' + destinationAirport];
    
    if (layovers == 0) {

    }
} */

#include "Files.h"


int main() {
    const char* filename = "routes.dat";
    Files file = Files();

    std::vector<std::string> data = file.readFile(filename);
    std::map<std::string, std::vector<std::string> > routes = file.getData(data);

    // Pagerank
    int dimension = routes.size();

    //Creates a dimension * dimension matrix of zeros
    std::vector<std::vector<double> > markov(dimension, std::vector<double>(dimension, 0));
    std::vector<std::string> airports;

    for(std::map<std::string, std::vector<std::string> >::const_iterator it = routes.begin(); it != routes.end(); ++it) {
        // To keep track of which row belongs to which source airport
        //std::cout << "Airport " << it->first << std::endl;
        airports.push_back(it->first);
    } 

    for(int i = 0; i < airports.size(); i++) {
        std::string source = airports[i];
        int sourceIndex = i;
        std::vector<std::string> destinations = routes[source];

        for (int j = 0; j < destinations.size(); j++) {
            std::string destination = destinations[j];
            int destinationIndex = file.getDestinationIndex(destination, airports);
            
            markov[sourceIndex][destinationIndex] += (double) 1 / destinations.size();
            //std::cout << "Probability Writing " << markov[sourceIndex][destinationIndex] << std::endl;
        }
    }

    std::vector<std::vector<double> > startingState(1, std::vector<double>(dimension, 0));

    std::string source = "LAX";
    int sourceIndex = file.getDestinationIndex(source, airports);

    startingState[0][sourceIndex] = 1;

    std::vector<std::vector<double> > steadyState(1, std::vector<double>(dimension, 0));

    for (int iterations = 0; iterations < 1; iterations++) {
        for (int i = 0; i < 1; i++) {
            for (int j = 0; j < dimension; j++) {
                for (int k = 0; k < dimension; k++) {
                    steadyState[i][j] += startingState[i][k] * markov[k][j];
                }
            }
        }
        startingState = steadyState;
        for (int m = 0; m < steadyState[0].size(); m++) {
            steadyState[0][m] = 0;
        }
    }

    int numberAirports = 10;
    std::vector<std::string> popularAirports;
    std::vector<double> probabilities;

    for (int i = 0; i < numberAirports; i++) {
        int maxIndex = 0;
        double max = 0;
        double probability = 0;
        for (int i = 0; i < startingState[0].size(); i++) {
            if (startingState[0][i] > max) {
                max = startingState[0][i];
                maxIndex = i;
                probability = startingState[0][i];

            }
        }
        startingState[0][maxIndex] = 0;
        std::string airport = airports[maxIndex];
        popularAirports.push_back(airport);
        probabilities.push_back(probability);
    }

    for (int i = 0; i < popularAirports.size(); i++) {
        std::cout << "Airport " << popularAirports[i] << " Probability " << probabilities[i] << std::endl;
    }
}