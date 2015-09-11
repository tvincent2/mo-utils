#ifndef BEDGE
#define BEDGE

#include "BVect.hpp"

class BEdge {
  private:
    BVect _a;
    BVect _b;
    bool _aClosed;
    bool _bClosed;
    bool _point;
  public:
    BEdge (BVect a, BVect b, bool aC = true, bool bC = true) : _a(a), _b(b), _aClosed(aC), _bClosed(bC), _point(a==b) {}
    BEdge (BVect a) : _a(a), _b(a), _aClosed(true), _bClosed(true), _point(true) {}
    BVect leftPoint() const {return _a;}
    BVect rightPoint() const {return _b;}
    bool isAPoint() const {return _point;}
};

#endif
