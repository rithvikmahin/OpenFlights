#define CATCH_CONFIG_MAIN
#include "./catch/catch.hpp"
#include "../Files.h"
#include "../DFS.h"
#include "../A_Star.h"
#include "../PageRank.h"

TEST_CASE("Files readFile() airports") {
    Files f = Files();
    const char* airportFile = "../testAirports.dat";
    std::vector<std::string> airportData = f.readFile(airportFile);
    
    REQUIRE(airportData[0] == "3131,\"Kempegowda International Airport\",\"Bangalore\",\"India\",\"BLR\",\"VOBL\",13.1979,77.706299,3000,5.5,\"N\",\"Asia/Calcutta\",\"airport\",\"OurAirports\"");
    REQUIRE(airportData[1] == "3797,\"John F Kennedy International Airport\",\"New York\",\"United States\",\"JFK\",\"KJFK\",40.63980103,-73.77890015,13,-5,\"A\",\"America/New_York\",\"airport\",\"OurAirports\"");
    REQUIRE(airportData[2] == "3830,\"Chicago O'Hare International Airport\",\"Chicago\",\"United States\",\"ORD\",\"KORD\",41.9786,-87.9048,672,-6,\"A\",\"America/Chicago\",\"airport\",\"OurAirports\"");
    REQUIRE(airportData[3] == "3469,\"San Francisco International Airport\",\"San Francisco\",\"United States\",\"SFO\",\"KSFO\",37.61899948120117,-122.375,13,-8,\"A\",\"America/Los_Angeles\",\"airport\",\"OurAirports\"");
    REQUIRE(airportData[4] == "3484,\"Los Angeles International Airport\",\"Los Angeles\",\"United States\",\"LAX\",\"KLAX\",33.94250107,-118.4079971,125,-8,\"A\",\"America/Los_Angeles\",\"airport\",\"OurAirports\"");
    REQUIRE(airportData[5] == "507,\"London Heathrow Airport\",\"London\",\"United Kingdom\",\"LHR\",\"EGLL\",51.4706,-0.461941,83,0,\"E\",\"Europe/London\",\"airport\",\"OurAirports\"");
    REQUIRE(airportData[6] == "3682,\"Hartsfield Jackson Atlanta International Airport\",\"Atlanta\",\"United States\",\"ATL\",\"KATL\",33.6367,-84.428101,1026,-5,\"A\",\"America/New_York\",\"airport\",\"OurAirports\"");
}

TEST_CASE("Files readFile() routes") {
    Files f = Files();
    const char* routesFile = "../testRoutes.dat";
    std::vector<std::string> routesData = f.readFile(routesFile);

    REQUIRE(routesData[0] == "AA,24,JFK,1234,SFO,1234,,0,123");
    REQUIRE(routesData[1] == "AA,24,SFO,1234,BLR,1234,,0,123");
    REQUIRE(routesData[2] == "AA,24,JFK,1234,BLR,1234,,0,123");
    REQUIRE(routesData[3] == "AA,24,JFK,1234,ORD,1234,,0,123");
    REQUIRE(routesData[4] == "AA,24,ORD,1234,LAX,1234,,0,123");
    REQUIRE(routesData[5] == "AA,24,JFK,1234,LAX,1234,,0,123");
    REQUIRE(routesData[6] == "AA,24,JFK,1234,ATL,1234,,0,123");
    REQUIRE(routesData[7] == "AA,24,ATL,1234,LAX,1234,,0,123");
    REQUIRE(routesData[8] == "AA,24,LAX,1234,LHR,1234,,0,123");
    REQUIRE(routesData[9] == "AA,24,LHR,1234,ATL,1234,,0,123");
    REQUIRE(routesData[10] == "AA,24,LHR,1234,BLR,1234,,0,123");
    REQUIRE(routesData[11] == "AA,24,BLR,1234,BLR,1234,,0,123");
}

TEST_CASE("Files getAirportCoordinates()") {
    Files f = Files();
    const char* airportFile = "../testAirports.dat";
    std::vector<std::string> airportData = f.readFile(airportFile);
    std::map<std::string, std::vector<double> > airportCoordinates = f.getAirportCoordinates(airportData);

    std::vector<double> BLR {13.1979, 77.706299};
    std::vector<double> JFK {40.63980103, -73.77890015};
    std::vector<double> ORD {41.9786, -87.9048};
    std::vector<double> SFO {37.61899948120117, -122.375};
    std::vector<double> LAX {33.94250107, -118.4079971};
    std::vector<double> LHR {51.4706, -0.461941};
    std::vector<double> ATL {33.6367, -84.428101};

    REQUIRE(airportCoordinates["BLR"] == BLR);
    REQUIRE(airportCoordinates["JFK"] == JFK);
    REQUIRE(airportCoordinates["ORD"] == ORD);
    REQUIRE(airportCoordinates["SFO"] == SFO);
    REQUIRE(airportCoordinates["LAX"] == LAX);
    REQUIRE(airportCoordinates["LHR"] == LHR);
    REQUIRE(airportCoordinates["ATL"] == ATL);
}

TEST_CASE("Files getRoutes() false (for PageRank)") {
    Files f = Files();
    const char* routesFile = "../testRoutes.dat";
    std::vector<std::string> routesData = f.readFile(routesFile);
    std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData, false);

    std::vector<std::string> BLR {"BLR"};
    std::vector<std::string> JFK {"SFO", "BLR", "ORD", "LAX", "ATL"};
    std::vector<std::string> ORD {"LAX"};
    std::vector<std::string> SFO {"BLR"};
    std::vector<std::string> LAX {"LHR"};
    std::vector<std::string> LHR {"ATL", "BLR"};
    std::vector<std::string> ATL {"LAX"};

    REQUIRE(routes["BLR"] == BLR);
    REQUIRE(routes["JFK"] == JFK);
    REQUIRE(routes["ORD"] == ORD);
    REQUIRE(routes["SFO"] == SFO);
    REQUIRE(routes["LAX"] == LAX);
    REQUIRE(routes["LHR"] == LHR);
    REQUIRE(routes["ATL"] == ATL);
}

TEST_CASE("Files getRoutes() true (for A*)") {
    Files f = Files();
    const char* routesFile = "../testRoutes.dat";
    std::vector<std::string> routesData = f.readFile(routesFile);
    std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData, true);

    std::vector<std::string> BLR {"BLR", "BLR"};
    // It is the first airport added and does not need to go to itself.
    std::vector<std::string> JFK {"SFO", "BLR", "ORD", "LAX", "ATL"};
    std::vector<std::string> ORD {"ORD", "LAX"};
    std::vector<std::string> SFO {"SFO", "BLR"};
    std::vector<std::string> LAX {"LAX", "LHR"};
    std::vector<std::string> LHR {"LHR", "ATL", "BLR"};
    std::vector<std::string> ATL {"ATL", "LAX"};

    REQUIRE(routes["BLR"] == BLR);
    REQUIRE(routes["JFK"] == JFK);
    REQUIRE(routes["ORD"] == ORD);
    REQUIRE(routes["SFO"] == SFO);
    REQUIRE(routes["LAX"] == LAX);
    REQUIRE(routes["LHR"] == LHR);
    REQUIRE(routes["ATL"] == ATL);
}

TEST_CASE("Files getIndex()") {
    Files f = Files();
    std::vector<std::string> airports;

    airports.push_back("JFK");
    airports.push_back("SFO");
    airports.push_back("ORD");

    REQUIRE(f.getIndex("JFK", airports) == 0);
    REQUIRE(f.getIndex("SFO", airports) == 1);
    REQUIRE(f.getIndex("ORD", airports) == 2);
}

TEST_CASE("DFS A path exists from JFK -> BLR") { 
    Files f = Files();

    const char* airportFile = "../airports.dat";
    const char* routesFile = "../testRoutes.dat";

    std::vector<std::string> airportData = f.readFile(airportFile);
    std::map<std::string, std::vector<double> > airportCoordinates = f.getAirportCoordinates(airportData);

    std::vector<std::string> routesData = f.readFile(routesFile);
    std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData, true);

    std::string source = "JFK";
    std::string destination = "BLR";

    DFS dfs = DFS(routesFile);
    bool pathExists = dfs.checkPathExists(source, destination);

    REQUIRE(pathExists == true);
}

TEST_CASE("DFS A path exists from ATL -> IAH (longest path)") { 
    Files f = Files();

    const char* airportFile = "../airports.dat";
    const char* routesFile = "../testRoutes3.dat";

    std::vector<std::string> airportData = f.readFile(airportFile);
    std::map<std::string, std::vector<double> > airportCoordinates = f.getAirportCoordinates(airportData);

    std::vector<std::string> routesData = f.readFile(routesFile);
    std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData, true);

    std::string source = "ATL";
    std::string destination = "IAH";

    DFS dfs = DFS(routesFile);
    bool pathExists = dfs.checkPathExists(source, destination);

    REQUIRE(pathExists == true);
}

TEST_CASE("DFS A path does not exist from JFK -> SFO (direct paths not counted)") { 
    Files f = Files();

    const char* airportFile = "../airports.dat";
    const char* routesFile = "../testRoutes.dat";

    std::vector<std::string> airportData = f.readFile(airportFile);
    std::map<std::string, std::vector<double> > airportCoordinates = f.getAirportCoordinates(airportData);

    std::vector<std::string> routesData = f.readFile(routesFile);
    std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData, true);

    std::string source = "JFK";
    std::string destination = "SFO";

    DFS dfs = DFS(routesFile);
    bool pathExists = dfs.checkPathExists(source, destination);

    REQUIRE(pathExists == false);
}

TEST_CASE("DFS A path does not exist from JFK -> JFK (path to self not counted)") { 
    Files f = Files();

    const char* airportFile = "../airports.dat";
    const char* routesFile = "../testRoutes.dat";

    std::vector<std::string> airportData = f.readFile(airportFile);
    std::map<std::string, std::vector<double> > airportCoordinates = f.getAirportCoordinates(airportData);

    std::vector<std::string> routesData = f.readFile(routesFile);
    std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData, true);

    std::string source = "JFK";
    std::string destination = "SFO";

    DFS dfs = DFS(routesFile);
    bool pathExists = dfs.checkPathExists(source, destination);

    REQUIRE(pathExists == false);
}

TEST_CASE("DFS A path does not exist from JFK -> IAH (source not in the dataset)") { 
    Files f = Files();

    const char* airportFile = "../airports.dat";
    const char* routesFile = "../testRoutes.dat";

    std::vector<std::string> airportData = f.readFile(airportFile);
    std::map<std::string, std::vector<double> > airportCoordinates = f.getAirportCoordinates(airportData);

    std::vector<std::string> routesData = f.readFile(routesFile);
    std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData, true);

    std::string source = "IAH";
    std::string destination = "BLR";

    DFS dfs = DFS(routesFile);
    bool pathExists = dfs.checkPathExists(source, destination);

    REQUIRE(pathExists == false);
}

TEST_CASE("DFS A path does not exist from JFK -> IAH (destination not in the dataset)") { 
    Files f = Files();

    const char* airportFile = "../airports.dat";
    const char* routesFile = "../testRoutes.dat";

    std::vector<std::string> airportData = f.readFile(airportFile);
    std::map<std::string, std::vector<double> > airportCoordinates = f.getAirportCoordinates(airportData);

    std::vector<std::string> routesData = f.readFile(routesFile);
    std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData, true);

    std::string source = "JFK";
    std::string destination = "IAH";

    DFS dfs = DFS(routesFile);
    bool pathExists = dfs.checkPathExists(source, destination);

    REQUIRE(pathExists == false);
}

TEST_CASE("DFS A path does not exist from JFK -> IAH (source and destination not in the dataset)") { 
    Files f = Files();

    const char* airportFile = "../airports.dat";
    const char* routesFile = "../testRoutes.dat";

    std::vector<std::string> airportData = f.readFile(airportFile);
    std::map<std::string, std::vector<double> > airportCoordinates = f.getAirportCoordinates(airportData);

    std::vector<std::string> routesData = f.readFile(routesFile);
    std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData, true);

    std::string source = "IAH";
    std::string destination = "AXK";

    DFS dfs = DFS(routesFile);
    bool pathExists = dfs.checkPathExists(source, destination);

    REQUIRE(pathExists == false);
}

TEST_CASE("Shortest path is JFK -> SFO -> BLR") {
    Files f = Files();

    const char* airportFile = "../airports.dat";
    const char* routesFile = "../testRoutes.dat";

    std::vector<std::string> airportData = f.readFile(airportFile);
    std::map<std::string, std::vector<double> > airportCoordinates = f.getAirportCoordinates(airportData);

    std::vector<std::string> routesData = f.readFile(routesFile);
    std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData, true);

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

TEST_CASE("Shortest path is ATL -> SFO -> IAH") {
    Files f = Files();

    const char* airportFile = "../airports.dat";
    const char* routesFile = "../testRoutes3.dat";

    std::vector<std::string> airportData = f.readFile(airportFile);
    std::map<std::string, std::vector<double> > airportCoordinates = f.getAirportCoordinates(airportData);

    std::vector<std::string> routesData = f.readFile(routesFile);
    std::map<std::string, std::vector<std::string> > routes = f.getRoutes(routesData, true);

    std::string source = "ATL";
    std::string destination = "IAH";

    A_Star* a_star = new A_Star();
    std::vector<std::string> path = a_star->search(source, destination, routes, airportCoordinates);

    std::string result;
    for (int i = 0; i < path.size() - 1; i++) {
        result += path[i] + " -> ";
    }
    result += path[path.size() - 1];

    REQUIRE(result == "ATL -> DTW -> SFO -> EWR -> MIA -> IAH");

    delete a_star;
}