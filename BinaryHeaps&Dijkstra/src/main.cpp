#include "graph/graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "dijkstra/dijkstra.h"


int main(int argc, char **argv) {
std::vector<unsigned> distances;

if(argc < 3) {
std::cout << "error: Expecting origin destination pair\n";
}

unsigned int o,d;
try {
o = std::atoi(argv[1]);
d = std::atoi(argv[2]);

  Graph g = Graph(std::cin);
  distances = dijkstra(o,g,2);



 }catch (const char* msg) {
std::cout  << msg << std::endl; 
 }

std::cout << distances[d-1]<<"\n";

}
