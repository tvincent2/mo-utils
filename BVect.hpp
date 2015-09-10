#ifndef BVECT
#define BVECT

#include <vector>

using namespace std;

class BVect {
  private:
    double _y1;
    double _y2;
    vector<double> _x;
  public:
    BVect (double y1, double y2, vector<double> x) : _y1(y1), _y2(y2), _x(x) {}
    double y1() const {return _y1;}
    double y2() const {return _y2;}
    vector<double> x() const {return _x;}
    bool operator == (const BVect& bv) const {
      return (this->y1() == bv.y1() && this->y2() == bv.y2());
    }
    bool operator != (const BVect bv) const {
      return !(*this == bv);
    }
    bool weaklyDominates(const BVect& bv) const {
      return (this->y1() <= bv.y1() && this->y2() <= bv.y2());
    }
    bool dominates(const BVect& bv) const {
      return (this->weaklyDominates(bv) && (*this != bv));
    }
    bool strictlyDominates(const BVect& bv) const {
      return (this->y1() < bv.y1() && this->y2() < bv.y2());
    }
    bool operator < (const BVect& bv) const {
      return this->strictlyDominates(bv);
    }
    bool operator <= (const BVect& bv) const {
      return this->dominates(bv);
    }
};

#endif
