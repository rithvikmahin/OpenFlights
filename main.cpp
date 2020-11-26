#include "PageRank.h"
#include "Files.h"
#include <stack>

int main() {
    const char *file = "testRoutes.dat";
    PageRank pagerank = PageRank(file);
    //pagerank.topPopularAirports("JFK");
    const char *filename = "testRoutes.dat";
    Files f = Files();
    std::vector<std::string> data = f.readFile(filename);
    std::map<std::string, std::vector<std::string> > routes = f.getData(data);
    std::map<std::string, int> layovers = f.getRouteLayovers();

    std::string source = "JFK";
    std::string destination = "BLR";

    std::vector<bool> visited;
    std::vector<std::string> airports;

    for (std::map<std::string, std::vector<std::string> >::const_iterator it = routes.begin(); it != routes.end(); ++it) {
        airports.push_back(it->first);
        visited.push_back(false);
    }

    /**for (int i = 0; i < airports.size(); i++) {
        std::cout << "Source " << airports[i] << std::endl;
        std::cout << "Routes size " << (routes[airports[i]]).size() << std::endl;
        for (int j = 0; j < (routes[airports[i]]).size(); j++) {
            std::cout << "Index " << j << std::endl;
            //std::cout << "Destination " << routes[airports[i]][j] << std::endl;
        }
    } */


    std::stack<std::string> dfs;
    dfs.push(source);

    std::map<std::string, std::vector<std::string> > visitedRoutes;

    while (dfs.size() > 0) {
        std::string stackElement = dfs.top();
        dfs.pop();


        if (visited[pagerank.getDestinationIndex(stackElement, airports)] == false) {
            std::cout << stackElement << std::endl;
            visited[pagerank.getDestinationIndex(stackElement, airports)] = true;
        }

        for (int i = 0; i < routes[source].size(); i++) {
            if (visited[pagerank.getDestinationIndex(routes[source][i], airports)] == false) {
                //std::cout << "Routes " << routes[source][i] << std::endl;
                visitedRoutes[stackElement].push_back(routes[source][i]);
                dfs.push(routes[source][i]);
            } /** else {
                for (int j = 0; j < routes[stackElement].size(); j++) {
                    if (routes[source][i] == routes[stackElement][j]) {
                        break;
                    }
                }
                dfs.push(routes[source][i]);
            } */
        }
    }
}
