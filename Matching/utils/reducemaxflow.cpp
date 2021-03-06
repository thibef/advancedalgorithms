//reduces a Bipartite Matching instance to a maxflow instance

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main() {
  std::string line="", dummy;
  while (line.substr(0,6) != "p edge")
    getline(std::cin,line);
  int n, m;
  std::stringstream linestr;
  linestr.str(line);
  linestr >> dummy >> dummy >> n >> m;

  std::cout << "c maxflow graph\n";
  std::cout << "p max " << n+2 <<" "<< m+n<<std::endl;
  std::cout << "n 1 s\n";
  std::cout << "n " << n+2 << " t\n";

  for(unsigned ninx = 1; ninx <=n/2; ninx++){
    std::cout << "a 1" << " "<< ninx << " 1\n";
  }

  for(unsigned ninx = n/2+1; ninx <=n; ninx++){
    std::cout << "a " <<  ninx << " " <<n+2 << " 1\n";
  }
  
  unsigned i; 
  i=0;
  while (i<m) {
    getline(std::cin,line);
    if (line.substr(0,2) == "e ") {
      std::stringstream arc(line);
      unsigned s,d;
      char ac;

      arc >> ac >> s >> d;
      std::cout << "a " << s << " "<< d << " 1\n";

      i++;
    }
  }
  
}



