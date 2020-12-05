#include "PageRank.h"

/** 
 * Constructor for the PageRank class.
 * @param file - A filename for a .dat file provided from the user's input.
*/
PageRank::PageRank(const char *file)
{
    const char *filename = file;
    f = new Files();
    std::vector<std::string> data = f->readFile(filename);
    routes = f->getRoutes(data);
    // The number of unique airports in the routes.dat file.
    dimension = routes.size();
}

/**
 * Generates the graph of state transitions / markov matrix for the list of routes provided.
 * @return - Returns a 2D vector of size NxN, where N is the number of unique airports in the routes.dat file.
*/
std::vector<std::vector<double> > PageRank::createMarkovMatrix()
{
    // Creates a matrix of dimension rows and dimension columns.
    std::vector<std::vector<double> > markov(dimension, std::vector<double>(dimension, 0));
    for (std::map<std::string, std::vector<std::string> >::const_iterator it = routes.begin(); it != routes.end(); ++it)
    {
        airports.push_back(it->first);
    }

    for (int i = 0; i < airports.size(); i++)
    {
        std::string source = airports[i];
        int sourceIndex = i;
        // Finds the vector of routes (value) corresponding to the source (key).
        std::vector<std::string> destinations = routes[source];

        for (int j = 0; j < destinations.size(); j++)
        {
            std::string destination = destinations[j];
            // Finds the index of the destination in the vector of airports.
            int destinationIndex = f->getIndex(destination, airports);

            markov[sourceIndex][destinationIndex] += (double) 1 / destinations.size();
        }
    }
    return markov;
}

/** 
 * Generates the steady state vector to determine the long-term probability of each state transition.
 * @param source - The source airport provided by the user.
 * @return - A vector containing the probability of travelling from the source airport to each destination airport.
 */
std::vector<std::vector<double> > PageRank::getProbabilities(std::string source)
{
    // Creates a vector with dimension rows and 1 column.
    std::vector<std::vector<double> > startingState(1, std::vector<double>(dimension, 0));
    std::vector<std::vector<double> > markov = createMarkovMatrix();
    int sourceIndex = f->getIndex(source, airports);

    // Sets the airport that the user starts at.
    startingState[0][sourceIndex] = 1;

    std::vector<std::vector<double> > steadyState(1, std::vector<double>(dimension, 0));

    // Performs matrix multiplication over a number of cycles / iterations to find the steady state vector.
    for (int iterations = 0; iterations < 20; iterations++)
    {
        for (int i = 0; i < 1; i++)
        {
            for (int j = 0; j < dimension; j++)
            {
                for (int k = 0; k < dimension; k++)
                {
                    steadyState[i][j] += startingState[i][k] * markov[k][j];
                }
            }
        }
        startingState = steadyState;
        // Clears the steady state vector after each multiplication cycle.
        for (int m = 0; m < steadyState[0].size(); m++)
        {
            steadyState[0][m] = 0;
        }
    }
    return startingState;
}

void PageRank::topPopularAirports(std::string source){
  int numberAirports = 10;
    std::vector<std::string> popularAirports;
    std::vector<double> probabilities;
    std::vector<std::vector<double> > startingState = getProbabilities(source);

    for (int i = 0; i < numberAirports; i++)
    {
        int maxIndex = 0;
        double max = 0;
        double probability = 0;
        for (int i = 0; i < startingState[0].size(); i++)
        {
            if (startingState[0][i] > max)
            {
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

    for (int i = 0; i < popularAirports.size(); i++)
    {
        std::cout << "Airport " << popularAirports[i] << " Probability " << probabilities[i] << std::endl;
    }

    delete f;
}
