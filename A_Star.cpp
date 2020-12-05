#include "A_Star.h"

std::vector<std::string> A_Star::search(std::string source, std::string destination, std::map<std::string, std::vector<std::string> > routes, std::map<std::string, std::vector<double> > airportCoordinates) {
    std::priority_queue<A_Star::Node, std::vector<A_Star::Node>, std::greater<A_Star::Node> > open;
    std::map<std::string, bool> closed;

    A_Star::Node tempNode = Node();
    A_Star::Node start = Node(source, &tempNode);

    open.push(start);

    std::cout << "Performing an A* search on the graph..." << std::endl;

    while (open.size() > 0) {
        //TODO: Delete this memory
        A_Star::Node* current = new Node(open.top());
        open.pop();
        closed[current->name] = true;

        if (current->name == destination) {
            std::vector<std::string> path;
            std::string currentName = current->name;
            
            while (currentName != source) {
                path.push_back(currentName);
                currentName = (current->parent)->name;
                current = current->parent;
            }

            path.push_back(source);
            std::reverse(path.begin(), path.end());

            return path;
        }

        double destinationLatitude = airportCoordinates[destination][0];
        double destinationLongitude = airportCoordinates[destination][1];

        for (int i = 0; i < routes[current->name].size(); i++) {
            std::string name = routes[current->name][i];
            A_Star::Node neighbor = Node(name, current);

            if (closed.count(name) == 1) {
                continue;
            }

           if (name == destination && current->name == source) {
                continue;
            }

            if (name == current->name) {
                continue;
            } 

            double currentLatitude = airportCoordinates[source][0];
            double currentLongitude = airportCoordinates[source][1];
            double distance = calculateDistance(currentLatitude, currentLongitude, destinationLatitude, destinationLongitude);
            neighbor.g = current->g + distance;
            //TODO: Determine heuristic
            neighbor.h  = distance;
            neighbor.f = neighbor.g + neighbor.h;

            if (addToOpen(open, neighbor) == true) {
                open.push(neighbor);
            }
        }
        
    }
    std::vector<std::string> noPath;
    return noPath;
}


double A_Star::calculateDistance(double latitude, double longitude, double destLatitude, double destLongitude) {
    double pi = M_PI / 180;
    double distance = 0.5 - (cos((destLatitude - latitude) * pi) / 2) + cos(latitude * pi) * cos(destLatitude * pi) * (1 - (cos((destLongitude - longitude) * pi)) / 2);
    return (12742 * asin(sqrt(distance)));
}

bool A_Star::addToOpen(std::priority_queue<A_Star::Node, std::vector<A_Star::Node>, std::greater<A_Star::Node> > open, A_Star::Node node) {
    std::priority_queue<A_Star::Node, std::vector<A_Star::Node>, std::greater<A_Star::Node> > openCopy = open;
    for (int i = 0; i < openCopy.size(); i++) {
        A_Star::Node openNode = openCopy.top();
        openCopy.pop();
        if (node.name == (openNode.name) && node.f > openNode.f) {
            return false;
        }
    }
    return true;
}   