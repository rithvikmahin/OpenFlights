#include "PageRank.h"
#include "Files.h"
#include <stack>
#include <queue>

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
        //std::cout << "Routes size " << (routes[airports[i]]).size() << std::endl;
        for (int j = 0; j < (routes[airports[i]]).size(); j++) {
            //std::cout << "Index " << j << std::endl;
            std::cout << "Destination " << routes[airports[i]][j] << std::endl;
        }
    } */


    /**std::stack<std::string> dfs;
    dfs.push(source);*/

    /**while (dfs.size() > 0) {
        std::string stackElement = dfs.top();
        //std::cout << stackElement << std::endl;
        dfs.pop();

        if (visited[pagerank.getDestinationIndex(stackElement, airports)] == false) {
            std::cout << stackElement << std::endl;
            visited[pagerank.getDestinationIndex(stackElement, airports)] = true;
        }

        for (int i = 0; i < routes[stackElement].size(); i++) {
            if (visited[pagerank.getDestinationIndex(routes[stackElement][i], airports)] == false) {
                std::cout << "Routes " << routes[stackElement][i] << std::endl;
                dfs.push(routes[stackElement][i]);
            }
        }
    }*/

    std::queue<std::string> bfs;

    bfs.push(source);
    visited[pagerank.getDestinationIndex(source, airports)] = true;

    while (bfs.size() > 0) {
        std::string top = bfs.front();
        bfs.pop();
        std::cout << top << std::endl;

        for (int i = 0; i < routes[top].size(); i++) {
            std::cout << "Routes " << routes[top][i] << std::endl;
            if (visited[pagerank.getDestinationIndex(routes[top][i], airports)]== false) {
                bfs.push(routes[top][i]);
                visited[pagerank.getDestinationIndex(routes[top][i], airports)] = true;
            }
        }
    }
}
