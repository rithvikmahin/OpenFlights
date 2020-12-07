#define CATCH_CONFIG_MAIN
#include "./catch/catch.hpp"
#include "../Files.h"
#include "../DFS.h"
#include "../A_Star.h"

TEST_CASE("A path exists from JFK -> BLR") { 
    Files f = Files();

    const char* airportFile = "../airports.dat";
    const char* routesFile = "../testRoutes.dat";

    std::vector<std::string> airportData = f.readFile(airportFile);
    std::map<std::string, std::vector<double> > airportCoordinates = f.getAirportCoordinates(airportData);

    std::vector<std::string> routesData = f.readFile(routesFile);
    std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData);

    std::string source = "JFK";
    std::string destination = "BLR";

    DFS dfs = DFS(routesFile);
    bool pathExists = dfs.checkPathExists(source, destination);

    REQUIRE(pathExists == true);
}

TEST_CASE("Shortest path is JFK -> SFO -> BLR") {
    Files f = Files();

    const char* airportFile = "../airports.dat";
    const char* routesFile = "../testRoutes.dat";

    std::vector<std::string> airportData = f.readFile(airportFile);
    std::map<std::string, std::vector<double> > airportCoordinates = f.getAirportCoordinates(airportData);

    std::vector<std::string> routesData = f.readFile(routesFile);
    std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData);

    std::string source = "JFK";
    std::string destination = "BLR";

    A_Star* a_star = new A_Star();
    std::vector<std::string> path = a_star->search(source, destination, routes, airportCoordinates);

    std::string result;
    for (int i = 0; i < path.size() - 1; i++) {
        result += path[i] + " -> ";
    }
    result += path[path.size() - 1];

    REQUIRE(result == "JFK -> SFO -> BLR");

    delete a_star;

}