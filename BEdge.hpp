#ifndef BEDGE
#define BEDGE

#include "BVect.hpp"

class BEdge {
  public:
    BEdge (BVect a, BVect b, bool aC, bool bC){_a = a; _b = b; _aClosed = aC; _bClosed = bC;}
    BEdge (BVect a, BVect b){_a = a; _b = b; _aClosed = true; _bClosed = true;}
    BEdge (BVect a){_a = a; _b = a; aClosed = true; bClosed = true;}
    BVect _a;
    BVect _b;
    bool _aClosed;
    bool _bClosed;
};

#endif
