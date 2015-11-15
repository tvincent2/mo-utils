#ifndef BVECT
#define BVECT

#include <vector>
#include <iostream>

using namespace std;

class BVect {
  private:
    double _z1;
    double _z2;
    vector<double> _x;
  public:
    BVect () {}
    BVect (double z1, double z2, vector<double> x) : _z1(z1), _z2(z2), _x(x) {}
    BVect (const BVect& b1, const BVect& b2, double lambda) {
      _z1 = lambda * b1.z1() + (1-lambda) * b2.z1();
      _z2 = lambda * b1.z2() + (1-lambda) * b2.z2();
      for (unsigned i = 0; i < b1.x().size(); ++i) {
        _x.push_back(lambda * b1.x().at(i) + (1-lambda) * b2.x().at(i));
      }
    }
    double z1() const {return _z1;}
    double z2() const {return _z2;}
    vector<double> x() const {return _x;}
    bool operator == (const BVect& bv) const {
      return (this->z1() == bv.z1() && this->z2() == bv.z2());
    }
    bool operator != (const BVect bv) const {
      return !(*this == bv);
    }
    bool weaklyDominates(const BVect& bv) const {
      return (this->z1() <= bv.z1() && this->z2() <= bv.z2());
    }
    bool dominates(const BVect& bv) const {
      return (this->weaklyDominates(bv) && (*this != bv));
    }
    bool strictlyDominates(const BVect& bv) const {
      return (this->z1() < bv.z1() && this->z2() < bv.z2());
    }
    bool isInA1AreaOf(const BVect& bv) const {
      return (bv.z1() > this->z1() && bv.z2() < this->z2());
    }
    bool isInA2AreaOf(const BVect& bv) const {
      return bv.isInA1AreaOf(*this);
    }
    friend ostream& operator << (ostream& s, const BVect& bv) {
      s << "(" << bv.z1() << ", " << bv.z2() << ")";
      return s;
    }
};

#endif
