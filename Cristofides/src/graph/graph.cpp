#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cassert>
double parse_mantissa_float(std::string s)
{ //https://stackoverflow.com/questions/38381030/unable-to-parse-mantissa-and-exponent-value-separately
  double value;
  std::string del = "e+";
  int e_pos = s.find(del);
  if(e_pos != -1){
    //there is a mantissa
    double mantissa = std::stod(s.substr(0, e_pos));
    int exponent = std::stoi(s.substr(e_pos + del.length(),s.length()));
    value = mantissa*std::pow(10, exponent);
  }
  else{
    std::stringstream va(s);
    va >> value;
  }
  return value;
}


double Graph::distance_between(unsigned n1, unsigned n2) {
  double deltax = vertex_coordinates_x[n1] - vertex_coordinates_x[n2];
  double deltay = vertex_coordinates_y[n1] - vertex_coordinates_y[n2];
  //return round(sqrt( deltax*deltax + deltay*deltay ));
  return round(sqrt( deltax*deltax + deltay*deltay ));
}

unsigned find_root(std::vector<unsigned> &parent, unsigned node)
{
  if(parent[node]==node) //is root
    return node;
  else
    return find_root(parent, parent[node]);
}

void merge_tree(std::vector<unsigned> &parent, unsigned t1, unsigned t2)
{
  unsigned roott1 = find_root(parent, t1);
  parent[roott1] = find_root(parent,t2);
}

//creates a Minimum Spanning Tree
//based on http://www.geeksforgeeks.org/greedy-algorithms-set-2-kruskals-minimum-spanning-tree-mst/
std::vector<unsigned> Graph::gen_mst()
{
  std::sort(edges_pt.begin(), edges_pt.end(),Edge::less_than_pointer);
  std::vector<unsigned> node_degrees;
  node_degrees.reserve(n);
  std::vector<unsigned> sets;
  for(unsigned i = 0; i < n; i++) {
    node_degrees.push_back(0);
    sets.push_back(i);
  }

  unsigned edges_added = 0;
  unsigned curr_edge = 0;
  while(edges_added < n-1){
    unsigned n1, n2;
    n1 = edges_pt[curr_edge]->n1;
    n2 = edges_pt[curr_edge]->n2;
    unsigned rootn1 = find_root(sets, n1);
    unsigned rootn2 = find_root(sets, n2);
    if(rootn1!=rootn2) {
      //edge does not add a cycle
      edges_pt[curr_edge]->edge_count=1;
      merge_tree(sets, n1, n2);
      edges_added++;
      node_degrees[n1] += 1;
      node_degrees[n2] += 1;
    }
    curr_edge++;
  }
  return node_degrees;
}

//file parsing based on:
//http://www.inf.ufrgs.br/~MRPRITT/doku.php?id=inf05016:2017-1-trabalhos
Graph::Graph(std::istream& inputF)
{
  std::string line="", dummy;
  while (line.substr(0,9) != "DIMENSION")
    getline(inputF,line);
    std::vector<std::string> tokens;
    char *cstr = new char[line.length()+1];
    strcpy(cstr, line.c_str());
    char *p = std::strtok(cstr, " ");
    while (p) {
      std::string token(p);
      tokens.push_back(token);
      p = std::strtok(NULL, " ");
    }

    std::stringstream linestr;
    linestr.str(tokens[tokens.size()-1]);
    linestr >> n;
    m = (n*(n-1))/2;

  while (line.substr(0,18) != "NODE_COORD_SECTION")
    getline(inputF,line);

  vertex_coordinates_x.reserve(n);
  vertex_coordinates_y.reserve(n);

  unsigned i=0;
  while (i<n) {
    getline(inputF,line);
    std::stringstream arc(line);
    unsigned node;
    std::string xstr, ystr;
    double x, y;
    arc >> node >> xstr >> ystr;
    x = parse_mantissa_float(xstr);
    y = parse_mantissa_float(ystr);
    vertex_coordinates_x.push_back(x);
    vertex_coordinates_y.push_back(y);
    i++;
  }
  edges = new Edge[m];
  edges_vertex.resize(n-1);
  unsigned count_e=0;
  //calculate distances
  for(unsigned j=0; j<n; j++){
    for(unsigned k=j+1; k<n; k++){
      Edge e;
      e.n1 = j;
      e.n2 = k;
      e.distance = distance_between(j,k);
      e.edge_count = 0;
      //std::cout <<e.n1+1 <<" "<<e.n2+1<< " "<<e.distance<< "\n";
      edges[count_e] = e;
      Edge *pt = edges + count_e;
      edges_pt.push_back(pt);
      edges_vertex[j].push_back(pt);
      count_e++;
    }
  }
}

void Graph::reset(){
  for(unsigned inx = 0; inx < m; inx++){
    edges[inx].edge_count = 0;
  }
}
