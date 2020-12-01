#include "DFS.h"

DFS::DFS(const char* file) {
    const char *filename = file;
    f = new Files();
    std::vector<std::string> data = f->readFile(filename);
    routes = f->getRoutes(data);
    layovers = f->getRouteLayovers();
}

bool DFS::checkPathExists(std::string source, std::string destination) {

    std::vector<bool> visited;
    std::vector<std::string> airports;

    for (std::map<std::string, std::vector<std::string> >::const_iterator it = routes.begin(); it != routes.end(); ++it) {
        airports.push_back(it->first);
        visited.push_back(false);
    }

    std::stack<std::string> dfs;
    dfs.push(source);

    while (dfs.size() > 0) {
        std::string airport = dfs.top();
        
        if (airport == destination) {
            return true;
        }

        dfs.pop();

        int sourceIndex = f->getIndex(airport, airports);

        if (visited[sourceIndex] == false) {
            visited[sourceIndex] = true;
        }

        for (int i = 0; i < routes[airport].size(); i++) {
            if (airport == source && routes[airport][i] == destination) {
                continue;
            }
            std::string destination = routes[airport][i];
            int destinationIndex = f->getIndex(destination, airports);
            if (visited[destinationIndex] == false) {
                dfs.push(destination);
            }
        }
    }
    return false;
}