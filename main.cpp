#include "PageRank.h"
#include "DFS.h"
#include "Files.h"
#include "A_Star.h"

int main() {

    std::string airportFileName;
    const char* airportFile;
    std::cout << "Enter the name of the file containing the list of airports." << std::endl;

    if (!(std::getline(std::cin, airportFileName))) {
        std::cout << "Wrong input." << std::endl;
        return -1;
    }

    if (!airportFileName.empty()) {
        airportFile = airportFileName.c_str();
    }

    std::string routesFileName;
    const char* routesFile;
    std::cout << "Enter the name of the file containing the list of routes." << std::endl;

    if (!(std::getline(std::cin, routesFileName))) {
        std::cout << "Wrong input." << std::endl;
        return -1;
    }

    if (!routesFileName.empty()) {
        routesFile = routesFileName.c_str();
    }

    std::string choice;
    std::cout << "Enter A* to find the shortest non-direct path from a source to a destination airport using A* and DFS. Enter PageRank to use PageRank and find the list of most popular airports out of a source airport." << std::endl;

    if (!(std::getline(std::cin, choice))) {
        std::cout << "Wrong input." << std::endl;
        return -1;
    }

    if (!choice.empty() && (choice == "A*" || choice == "PageRank")) {

        std::string source;
        std::string sourceName;
        std::cout << "Enter the name of the source airport." << std::endl;

        if (!(std::getline(std::cin, sourceName))) {
            std::cout << "Wrong input." << std::endl;
            return -1;
        }

        if (!sourceName.empty()) {
            source = sourceName;
        }

        if (choice == "A*") {
            Files f = Files();

            std::vector<std::string> airportData = f.readFile(airportFile);
            std::map<std::string, std::vector<double> > airportCoordinates = f.getAirportCoordinates(airportData);

            std::vector<std::string> routesData = f.readFile(routesFile);
            std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData);

            std::string destination;
            std::string destinationName;
            std::cout << "Enter the name of the destination airport." << std::endl;

            if (!(std::getline(std::cin, destinationName))) {
                std::cout << "Wrong input." << std::endl;
                return -1;
            }

            if (!destinationName.empty()) {
                destination = destinationName;
            }

            DFS dfs = DFS(routesFile);
            bool pathExists = dfs.checkPathExists(source, destination);
            A_Star* a_star = new A_Star();

            if (pathExists) {
                std::vector<std::string> path = a_star->search(source, destination, routes, airportCoordinates);
                for (int i = 0; i < path.size() - 1; i++) {
                    std::cout << path[i] << " -> ";
                }
                std::cout << path[path.size() - 1] << std::endl;
            } else {
                std::cout <<  "No path was found." << std::endl;
            }
            delete a_star;
            return 1;
        }

        if (choice == "PageRank") {
            PageRank pagerank = PageRank(routesFile);
            pagerank.topPopularAirports(source);
        }

        std::cout << "Wrong input." << std::endl;
        return -1;
    }
}
