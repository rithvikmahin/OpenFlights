#include "PageRank.h"
#include "DFS.h"
#include "Files.h"
#include "A_Star.h"

int main() {

    //TODO: Accept user args, swap between PageRank and A* as need be.

    const char* airportFile = "airports.dat";
    const char* routeFile = "routes.dat";

    Files f = Files();

    std::vector<std::string> airportData = f.readFile(airportFile);
    std::map<std::string, std::vector<double> > airportCoordinates = f.getAirportCoordinates(airportData);

    std::vector<std::string> routesData = f.readFile(routeFile);
    std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData);

    std::string source = "JFK";
    std::string destination = "LHR";

    DFS dfs = DFS(routeFile);
    bool pathExists = dfs.checkPathExists(source, destination);
    A_Star* a_star = new A_Star();

    if (pathExists) {
        std::vector<std::string> path = a_star->search(source, destination, routes, airportCoordinates);
        for (int i = 0; i < path.size(); i++) {
            std::cout << path[i] << std::endl;
        }
    } else {
        std::cout <<  "No path was found." << std::endl;
    }
    delete a_star;
}
