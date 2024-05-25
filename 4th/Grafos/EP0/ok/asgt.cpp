/* This is the main file that the students must work on to submit; the
 * other one is arb.h
 */

#include "asgt.h"
using namespace std;

Arb read_arb(std::istream& in){
  Arb arb(0);

  size_t num; in >> num; num--;
  
  if(num == 0){
    Vertex x = 1;
    boost::add_edge(x, x, arb);
  }
  
  while(num--) {
    Vertex x, y; cin >> x >> y;
    boost::add_edge(x, y, arb);
  }
  
  return arb;
}


void dfs(Arb &arb, const Vertex& u, const Vertex& parent, int timeIn[], int timeOut[], int& time){
  timeIn[u] = time++;
  
  for (const auto& arc : make_iterator_range(boost::out_edges(u, arb))) {
      Vertex v = boost::target(arc, arb);
      if(v != parent) dfs(arb, v, u, timeIn, timeOut, time);
  }
  timeOut[u] = time++;
}


HeadStart preprocess (Arb &arb, const Vertex& root){
  int time = 0;
  int size = boost::num_vertices(arb);
  int timeIn[size];
  int timeOut[size];
  
  dfs(arb, 1, -1, timeIn, timeOut, time);
	
  return HeadStart(timeIn, timeOut, size);
}

bool is_ancestor (const Vertex& u, const Vertex& v, const HeadStart& data){
  vector<int> timeIn = data.timeIn();
  vector<int> timeOut = data.timeOut();
  
  bool answer = (timeIn.at(u+1) <= timeIn.at(v+1) && timeOut.at(v+1) <= timeOut.at(u+1));

  return answer;
}
