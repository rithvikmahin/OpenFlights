#pragma once
#define _USE_MATH_DEFINES 
#include "Files.h"
#include "math.h"
# define M_PI   3.14159265358979323846
#include <queue>

class A_Star {
    public:
        class Node {
            public:
                std::string name;
                Node* parent;
                double g;
                double h;
                double f;

                // The default constructor, used for starting nodes with no parents.
                Node() {
                    this->name = "";
                    this->parent = NULL;
                    this->g = 0;
                    this->h = 0;
                    this->f = 0;
                }

                // The copy constructor.
                Node(const Node& node) {
                    this->name = node.name;
                    this->parent = node.parent;
                    this->g = node.g;
                    this->h = node.h;
                    this->f = node.f;
                }
                
                Node(std::string name, A_Star::Node* parent) {
                    this->name = name;
                    this->parent = parent;
                    this->g = 0;
                    this->h = 0;
                    this->f = 0;
                }   

                // Overloaded the < operator to sort nodes in a priority queue.
                bool operator < (const Node& node) const {
                    return (f < node.f);
                }  

                // Overloaded the > operator to sort nodes in a priority queue.
                bool operator > (const Node& node) const {
                    return (f > node.f);
                }    

                // Overloads the assignment operator to assign nodes to one another.
                Node& operator=(const Node& node) {
                    this->name = node.name;
                    this->parent = node.parent;
                    this->g = node.g;
                    this->h = node.h;
                    this->f = node.f;
                    return *this;
                }
        };  

        std::vector<std::string> search(std::string source, std::string destination, std::map<std::string, std::vector<std::string> > routes, std::map<std::string, std::vector<double> > airportCoordinates);

    private:
        double calculateDistance(double latitude, double longitude, double destLatitude, double destLongitude); 
        bool addToOpen(std::priority_queue<A_Star::Node, std::vector<A_Star::Node>, std::greater<A_Star::Node> >, A_Star::Node node);
};