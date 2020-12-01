#include "PageRank.h"
#include "Files.h"
#include <stack>
#include "A_Star.h"
#include <queue>
#include "math.h"

int main() {

    const char* airportFile = "airports.dat";
    const char* routeFile = "testRoutes2.dat";

    Files f = Files();

    std::vector<std::string> airportData = f.readFile(airportFile);
    std::map<std::string, std::vector<double> > airportCoordinates = f.getAirportCoordinates(airportData);

    std::vector<std::string> routesData = f.readFile(routeFile);
    std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData);


    // A*
    std::string source = "AER";
    std::string destination = "SVX";

    A_Star* a_star = new A_Star();
    std::vector<std::string> path = a_star->search(source, destination, routes, airportCoordinates);

    if (path.size() == 0) {
        std::cout <<  "No path was found." << std::endl;
    } else {
        std::cout << "Path" << std::endl;
        for (int i = 0; i < path.size(); i++) {
            std::cout << path[i] << std::endl;
        }
    }
    
    delete a_star;
}
