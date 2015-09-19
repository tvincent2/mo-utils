#ifndef BEDGE
#define BEDGE

#include <utility>
#include "BVect.hpp"
#include "DominanceStatus.hpp"

class BEdge {
  private:
    BVect _a;
    BVect _b;
    bool _aClosed;
    bool _bClosed;
    bool _point;
  public:
    BEdge() {}
    BEdge (BVect a, BVect b, bool aC = true, bool bC = true) : _a(a), _b(b), _aClosed(aC), _bClosed(bC), _point(a==b) {}
    BEdge (BVect a) : _a(a), _b(a), _aClosed(true), _bClosed(true), _point(true) {}
    BVect leftPoint() const {return _a;}
    BVect rightPoint() const {return _b;}
    bool isAPoint() const {return _point;}
    bool isInA1AreaOf(const BEdge& be) const {
      return (this->rightPoint().isInA1AreaOf(be.leftPoint()));
    }
    bool isInA2AreaOf(const BEdge& be) const {
      return be.isInA1AreaOf(*this);
    }
    std::pair<double, double> computeLambdasWithPoint(const BVect& bv) const {
      std::pair<double, double> lambdas;
      if (this->leftPoint().z1() <= bv.z1() && bv.z1() <= this->rightPoint().z1())
        lambdas.first = ((this->rightPoint().z1() - bv.z1()) / ( this->rightPoint().z1() - this->leftPoint().z1()));
      else lambdas.first = 1;
      if (this->rightPoint().z2() <= bv.z2() && bv.z2() <= this->leftPoint().z2())
        lambdas.second = ((bv.z2() - this->rightPoint().z2()) / ( this->leftPoint().z2() - this->rightPoint().z2()));
      else lambdas.second = 0;
      return lambdas;
    }
    DominanceStatus compareWithPoint(const BEdge& be, BEdge& tleft, BEdge& tright) const {
      if (this->isInA1AreaOf(be) || this->isInA2AreaOf(be))
        return DominanceStatus::NO_DOM;
      BVect bv = be.leftPoint();
      if (this->leftPoint().weaklyDominates(bv) && this->rightPoint().weaklyDominates(bv))
        return DominanceStatus::A_DOM_B;
      if (bv.weaklyDominates(this->leftPoint()) && bv.weaklyDominates(this->rightPoint()))
        return DominanceStatus::B_DOM_A;
      std::pair<double, double> lambdas = computeLambdasWithPoint(bv);
      BVect proj1(this->leftPoint(), this->rightPoint(), lambdas.first);
      BVect proj2(this->leftPoint(), this->rightPoint(), lambdas.second);
      if (proj1.weaklyDominates(bv))
        return DominanceStatus::A_DOM_B;
      else {
        if (proj1 != this->leftPoint())
          tleft = BEdge(this->leftPoint(), proj1);
        if (proj2 != this->rightPoint())
          tright = BEdge(proj2, this->rightPoint());
        return DominanceStatus::B_PART_DOM_A;
      }
    }
    bool intersect(const BEdge& be, double& lambda) const {
      double Az1 = this->leftPoint().z1();
      double Az2 = this->leftPoint().z2();
      double Cz1 = be.leftPoint().z1();
      double Cz2 = be.leftPoint().z2();
      double Iz1 = this->rightPoint().z1() - Az1;
      double Iz2 = this->rightPoint().z2() - Az2;
      double Jz1 = be.rightPoint().z1() - Cz1;
      double Jz2 = be.rightPoint().z2() - Cz2;
      double lam = (Iz1*Cz1 - Iz1*Az1 - Iz2*Cz2 + Iz2*Az2) / (Iz1*Jz2 - Iz2*Jz1);
      double mu  = (Iz2*Cz1 - Iz2*Az1 - Iz1*Cz2 + Iz1*Az2) / (Iz1*Jz2 - Iz2*Jz1);
      if (0 < lam && lam < 1 && 0 < mu && mu < 1) {
        lambda = lam;
        return true;
      } else {
        return false;
      }
    }
    DominanceStatus compareLeftEdges(BEdge& t, BEdge& b) const {
      if (t.leftPoint().weaklyDominates(b.leftPoint()))
        return DominanceStatus::A_DOM_B;
      else if (t.leftPoint().isInA1AreaOf(b.leftPoint())) {
        std::pair<double, double> lambdas = t.computeLambdasWithPoint(b.leftPoint());
        BVect proj1(t.leftPoint(), t.rightPoint(), lambdas.first);
        BVect proj2(t.leftPoint(), t.rightPoint(), lambdas.second);
        if (b.leftPoint().dominates(proj1)) {
          t = BEdge(t.leftPoint(), proj1);
          return DominanceStatus::B_PART_DOM_A;
        } else {
          return DominanceStatus::A_DOM_B;
        }
      } else {
        return invert(compareLeftEdges(b, t));
      }
    }
    DominanceStatus compareRightEdges(BEdge& t, BEdge& b) const {
      if (t.rightPoint().weaklyDominates(b.rightPoint()))
        return DominanceStatus::A_DOM_B;
      else if (t.rightPoint().isInA2AreaOf(b.rightPoint())) {
        std::pair<double, double> lambdas = t.computeLambdasWithPoint(b.rightPoint());
        BVect proj1(t.leftPoint(), t.rightPoint(), lambdas.first);
        BVect proj2(t.leftPoint(), t.rightPoint(), lambdas.second);
        if (b.rightPoint().dominates(proj2)) {
          t = BEdge(proj2, t.rightPoint());
          return DominanceStatus::B_PART_DOM_A;
        } else {
          return DominanceStatus::A_DOM_B;
        }
      } else {
        return invert(compareRightEdges(b, t));
      }
    }
    DominanceStatus compareWith(const BEdge& be, BEdge& tleft, BEdge& tright, BEdge& beleft, BEdge& beright) const {
      if (this->isAPoint() && be.isAPoint()) {
        if (this->leftPoint().dominates(be.leftPoint()))
          return DominanceStatus::A_DOM_B;
        else if (be.leftPoint().dominates(this->leftPoint()))
          return DominanceStatus::B_DOM_A;
        else return DominanceStatus::NO_DOM;
      } else if (this->isAPoint()) {
        return invert(be.compareWithPoint(*this, tleft, tright));
      } else if (be.isAPoint()) {
        return this->compareWithPoint(be, beleft, beright);
      } else {
        double lambda;
        if (this->intersect(be, lambda)) {
          BVect intersection(this->leftPoint(), this->rightPoint(), lambda);
          tleft = BEdge(this->leftPoint(), intersection);
          tright = BEdge(intersection, this->rightPoint());
          beleft = BEdge(be.leftPoint(), intersection);
          beright = BEdge(intersection, be.rightPoint());
          DominanceStatus left = compareLeftEdges(tleft, beleft);
          DominanceStatus right = compareRightEdges(tright, beright);
          return DominanceStatus::MUTUAL_DOM;
        } else {
          if (this->isInA1AreaOf(be) || this->isInA2AreaOf(be))
            return DominanceStatus::NO_DOM;
          std::pair<double, double> lambdasb1 = this->computeLambdasWithPoint(be.leftPoint());
          BVect proj1bleft(this->leftPoint(), this->rightPoint(), lambdasb1.first);
          BVect proj2bleft(this->leftPoint(), this->rightPoint(), lambdasb1.second);
          std::pair<double, double> lambdasb2 = this->computeLambdasWithPoint(be.rightPoint());
          BVect proj1bright(this->leftPoint(), this->rightPoint(), lambdasb2.first);
          BVect proj2bright(this->leftPoint(), this->rightPoint(), lambdasb2.second);
          std::pair<double, double> lambdast1 = this->computeLambdasWithPoint(this->leftPoint());
          BVect proj1tleft(be.leftPoint(), be.rightPoint(), lambdast1.first);
          BVect proj2tleft(be.leftPoint(), be.rightPoint(), lambdast1.second);
          std::pair<double, double> lambdast2 = this->computeLambdasWithPoint(this->rightPoint());
          BVect proj1tright(be.leftPoint(), be.rightPoint(), lambdast2.first);
          BVect proj2tright(be.leftPoint(), be.rightPoint(), lambdast2.second);
          bool adomb = false;
          bool bdoma = false;
          bool apartdomb = false;
          bool bpartdoma = false;
          if (be.leftPoint().weaklyDominates(proj1bleft)) {
            bdoma = true;
            if (proj1bleft != this->leftPoint()) {
              tleft = BEdge(this->leftPoint(), proj1bleft);
              bpartdoma = true;
            }
          }
          if (be.rightPoint().weaklyDominates(proj2bright)) {
            bdoma = true;
            if (proj2bright != this->rightPoint()) {
              tright = BEdge(proj2bright, this->rightPoint());
              bpartdoma = true;
            }
          }
          if (proj2bleft.weaklyDominates(be.leftPoint())) {
            adomb = true;
          }
          if (proj1bright.weaklyDominates(be.rightPoint())) {
            adomb = true;
          }
          if (this->leftPoint().weaklyDominates(proj1tleft)) {
            adomb = true;
            if (proj1tleft != be.leftPoint()) {
              beleft = BEdge(be.leftPoint(), proj1tleft);
              apartdomb = true;
            }
          }
          if (this->rightPoint().weaklyDominates(proj2tright)) {
            adomb = true;
            if (proj2tright != be.rightPoint()) {
              beright = BEdge(proj2tright, be.rightPoint());
              apartdomb = true;
            }
          }
          if (proj2tleft.weaklyDominates(this->leftPoint())) {
            bdoma = true;
          }
          if (proj1tright.weaklyDominates(this->rightPoint())) {
            bdoma = true;
          }
          if (adomb && bdoma)
            return DominanceStatus::MUTUAL_DOM;
          if (apartdomb)
            return DominanceStatus::A_PART_DOM_B;
          if (adomb)
            return DominanceStatus::A_DOM_B;
          if (bpartdoma)
            return DominanceStatus::B_PART_DOM_A;
          if (bdoma)
            return DominanceStatus::B_DOM_A;
          return DominanceStatus::NO_DOM;
        }
      }
    }
};

#endif
