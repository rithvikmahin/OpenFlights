#pragma once 
#include "Files.h"
#include <stack>

class DFS {
    public:
        DFS(const char* file);
        bool checkPathExists(std::string source, std::string destination);
        
    
    private:
        std::map<std::string, std::vector<std::string> > routes;
        Files f;
};