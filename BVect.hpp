#ifndef BVECT
#define BVECT

#include <vector>

using namespace std;

class BVect {
  public:
    BVect (double y1, double y2, vector<double> x){_y1 = y1; _y2 = y2; _x = x;}
    double _y1;
    double _y2;
    vector<double> _x;
};

#endif
