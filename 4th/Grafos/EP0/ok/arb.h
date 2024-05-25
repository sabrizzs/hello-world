/* the definition of HeadStart may be changed in this file; the rest
 * MUST NOT be changed
 */

#ifndef ARB_H
#define ARB_H

#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS,
                              boost::vecS,
                              boost::directedS> Arb;
typedef boost::graph_traits<Arb>::vertex_descriptor Vertex;

/* Students must adapt this class for their needs; the innards of
   these objects are only accessed by the student's code */
class HeadStart {

public:
  HeadStart(int timeIn[], int timeOut[], int size){
    for (auto i = 0; i < size; i++)  timeInArray.push_back(timeIn[i]);
    for (auto i = 0; i < size; i++)  timeOutArray.push_back(timeOut[i]);
  }
  
  std::vector<int> timeIn() const{
    return timeInArray;
  }
  
  std::vector<int> timeOut() const{
    return timeOutArray;
  }
  
private:
  std::vector<int> timeInArray;
  std::vector<int> timeOutArray;
};

#endif // #ifndef ARB_H
