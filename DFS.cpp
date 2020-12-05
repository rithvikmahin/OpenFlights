#include "DFS.h"
/** 
 * Constructor for the DFS class.
 * @param file - A filename for a .dat file of routes provided from the user's input.
*/
DFS::DFS(const char* file) {
    const char *filename = file;
    f = new Files();
    std::vector<std::string> data = f->readFile(filename);
    routes = f->getRoutes(data);
}

/**
 * A method that conducts a DFS search to verify whether there is at least one non-direct path from the provided source airport to the destination.
 * @param source - The starting airport.
 * @param destination - The airport to go to.
 * @return - True if a path exists, and false otherwise.
*/
bool DFS::checkPathExists(std::string source, std::string destination) {

    std::cout << "Conducting a depth-first search to ensure that a path exists..." << std::endl;

    std::vector<bool> visited;
    std::vector<std::string> airports;

    // Traverses the map and pushes airports into a vector to assign them indices.
    for (std::map<std::string, std::vector<std::string> >::const_iterator it = routes.begin(); it != routes.end(); ++it) {
        airports.push_back(it->first);
        visited.push_back(false);
    }

    std::stack<std::string> dfs;
    // Adds the starting airport to the DFS search.
    dfs.push(source);

    // An iterative DFS search.
    while (dfs.size() > 0) {
        std::string airport = dfs.top();
        
        if (airport == destination) {
            return true;
        }

        dfs.pop();

        // Converts the airport to its index.
        int sourceIndex = f->getIndex(airport, airports);

        // Indicates that this airport has been traversed.
        if (visited[sourceIndex] == false) {
            visited[sourceIndex] = true;
        }

        for (int i = 0; i < routes[airport].size(); i++) {
            // A modification to skip a direct route from the source to the destination.
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
    delete f;
    return false;
}