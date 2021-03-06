#include <iostream>
#include "graph/graph.h"
#include "hpmatch/hpmatch.h"
#include <string.h>
#include <chrono>
#include <cmath>
int run(int n, double p)
{
  std::cout << "generating graph\n";
  Graph g(n,p);
  std::cout << "done\n";
  int num_match;
  std::chrono::system_clock::time_point t = std::chrono::system_clock::now();

  for(unsigned r = 0; r < 300; r++) {
    if(r == 0)
      num_match = HPmatch::match(g.U, g.V,true);
    else
      num_match = HPmatch::match(g.U, g.V,false);
  }
  std::cout << "time(ms)= " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-t).count();
  std::cout << "repetitions=300";
  std::cout << ",match=" << num_match;
  std::cout << ",n=" << g.n;
  std::cout << ",m=" << g.m;
  std::cout << std::endl;

}
int main() {
  unsigned int n = 13;

  double pinit = 0.1;
  for(unsigned ninx = 0; ninx< 6;ninx++) {
    run(std::pow(2,n), pinit);
    pinit = pinit * 0.5;
  }


}
