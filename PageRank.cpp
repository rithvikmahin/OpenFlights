#include "PageRank.h"
PageRank::PageRank(const char *file)
{
    const char *filename = file;
    f = new Files();
    std::vector<std::string> data = f->readFile(filename);
    routes = f->getRoutes(data);
    dimension = routes.size();
}

std::vector<std::vector<double> > PageRank::createMarkovMatrix()
{
    std::vector<std::vector<double> > markov(dimension, std::vector<double>(dimension, 0));
    for (std::map<std::string, std::vector<std::string> >::const_iterator it = routes.begin(); it != routes.end(); ++it)
    {
        airports.push_back(it->first);
    }

    for (int i = 0; i < airports.size(); i++)
    {
        std::string source = airports[i];
        int sourceIndex = i;
        std::vector<std::string> destinations = routes[source];

        for (int j = 0; j < destinations.size(); j++)
        {
            std::string destination = destinations[j];
            int destinationIndex = f->getIndex(destination, airports);

            markov[sourceIndex][destinationIndex] += (double)1 / destinations.size();
        }
    }
    return markov;
}
std::vector<std::vector<double> > PageRank::getProbabilities(std::string source)
{
    std::vector<std::vector<double> > startingState(1, std::vector<double>(dimension, 0));
    std::vector<std::vector<double> > markov = createMarkovMatrix();
        int sourceIndex = f->getIndex(source, airports);

    startingState[0][sourceIndex] = 1;

    std::vector<std::vector<double> > steadyState(1, std::vector<double>(dimension, 0));

    for (int iterations = 0; iterations < 1; iterations++)
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
