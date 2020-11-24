#include "PageRank.h"
int main()
{
    const char *file = "routes.dat";
    PageRank pagerank = PageRank(file);
    pagerank.topPopularAirports("JFK");
}
