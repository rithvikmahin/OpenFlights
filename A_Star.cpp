#include "A_Star.h"

/**
 * A method that implements the A* search algorithm on a graph.
 * @param source - The starting airport.
 * @param destination - The airport to find the shortest non-direct path to.
 * @param routes - A map of routes between all of the airports in the data.
 * @param airportCoordinates - A map of airports and their coordinates.
 * @return - A vector containing the shortest non-direct path.
*/
std::vector<std::string> A_Star::search(std::string source, std::string destination, std::map<std::string, std::vector<std::string> > routes, std::map<std::string, std::vector<double> > airportCoordinates) {
    std::priority_queue<A_Star::Node, std::vector<A_Star::Node>, std::greater<A_Star::Node> > open;
    std::map<std::string, bool> closed;

    // An empty node to indicate the starting point has no parent node.
    A_Star::Node tempNode = Node();
    A_Star::Node start = Node(source, &tempNode);

    // Adds the source to begin the search.
    open.push(start);

    std::cout << "Performing an A* search on the graph..." << std::endl;

    while (open.size() > 0) {
        //TODO: Delete this memory
        // Each airport is turned into a node.
        A_Star::Node* current = new Node(open.top());
        open.pop();
        // Indicates that this airport has been traversed.
        closed[current->name] = true;

        // If the destination is reached, returns the path.
        if (current->name == destination) {
            std::vector<std::string> path;
            std::string currentName = current->name;
            
            // Backtracks by find the parent of each node in the path.
            while (currentName != source) {
                path.push_back(currentName);
                currentName = (current->parent)->name;
                current = current->parent;
            }
            // Adds the original source to the path.
            path.push_back(source);
            // Reverse the list from B -> A to get the path from A -> B.
            std::reverse(path.begin(), path.end());

            return path;
        }

        double destinationLatitude = airportCoordinates[destination][0];
        double destinationLongitude = airportCoordinates[destination][1];

        // This loop creates nodes for the airports connected to the current node and adds them to the open priority queue.
        for (int i = 0; i < routes[current->name].size(); i++) {
            std::string name = routes[current->name][i];
            // Creates a node with the current airport's name and the airport that led to it (parent).
            A_Star::Node neighbor = Node(name, current);

            // If the node has already been traversed, don't add it back to the open queue.
            if (closed.count(name) == 1) {
                continue;
            }

            // A modification to skip a node if it is a direct route.
           if (name == destination && current->name == source) {
                continue;
            }

            // A modification to skip a node if it is a path to itself.
            if (name == current->name) {
                continue;
            } 

            double currentLatitude = airportCoordinates[source][0];
            double currentLongitude = airportCoordinates[source][1];

            // Computes the distance on a spherical plane.
            double distance = calculateDistance(currentLatitude, currentLongitude, destinationLatitude, destinationLongitude);
            // Sets the parameter g to be the distance from the parent node to the current node plus the distance from the current node to the destination node.
            neighbor.g = current->g + distance;
            // The heuristic is taken as a measure of the distance from the current node to the destination node.
            neighbor.h  = distance;
            // The sum of g + h is the definition of A*, and is the weighted distance that determines the node's placement in the priority queue.
            neighbor.f = neighbor.g + neighbor.h;

            if (addToOpen(open, neighbor) == true) {
                open.push(neighbor);
            }
        }
        
    }
    // If the previous loop fails, returns an empty vector indicating there is no path (already covered by DFS).
    std::vector<std::string> noPath;
    return noPath;
}

/**
 * Calculates the distance between 2 coordinates on a globe.
 * @param latitude - The source latitude.
 * @param longitude - The source longitude.
 * @param destLatitude - The destination latitude.
 * @param destLongitude - The destination longitude.
 * @return - A double indiciating the distance between these coordinates. 
*/
double A_Star::calculateDistance(double latitude, double longitude, double destLatitude, double destLongitude) {
    double pi = M_PI / 180;
    double distance = 0.5 - (cos((destLatitude - latitude) * pi) / 2) + cos(latitude * pi) * cos(destLatitude * pi) * (1 - (cos((destLongitude - longitude) * pi)) / 2);
    return (12742 * asin(sqrt(distance)));
}

/**
 * A helper method that checks if a node should be added to the open priority queue. It ensures that the smallest weight for the current node exists in the queue.
 * @param open - A priority queue of airport nodes.
 * @param node - The current node to be checked.
 * @return - True if the node can be added, false otherwise.
*/
bool A_Star::addToOpen(std::priority_queue<A_Star::Node, std::vector<A_Star::Node>, std::greater<A_Star::Node> > open, A_Star::Node node) {
    std::priority_queue<A_Star::Node, std::vector<A_Star::Node>, std::greater<A_Star::Node> > openCopy = open;
    for (int i = 0; i < openCopy.size(); i++) {
        A_Star::Node openNode = openCopy.top();
        openCopy.pop();
        // If the current node already exists in the queue and the current node has a greater weight than the one present in the queue, the current node should not be added as a shorter path already exists.
        if (node.name == (openNode.name) && node.f > openNode.f) {
            return false;
        }
    }
    return true;
}   