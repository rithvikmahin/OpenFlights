#pragma once 
#include "Files.h"
#include "math.h"
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

                Node() {
                    this->name = "";
                    this->parent = NULL;
                    this->g = 0;
                    this->h = 0;
                    this->f = 0;
                }

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

                bool operator < (const Node& node) const {
                    return (f < node.f);
                }   

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
        bool addToOpen(std::vector<A_Star::Node>, A_Star::Node node);
};