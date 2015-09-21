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
    std::pair<BVect, BVect> computeProjWithPoint(const BVect& bv) const {
      std::pair<BVect, BVect> projections;
      if (this->leftPoint().z1() <= bv.z1() && bv.z1() <= this->rightPoint().z1()) {
        double lambda = ((this->rightPoint().z1() - bv.z1()) / ( this->rightPoint().z1() - this->leftPoint().z1()));
        BVect p(this->leftPoint(), this->rightPoint(), lambda);
        projections.first = BVect(bv.z1(), p.z2(), p.x());
      } else {
        projections.first = this->leftPoint();
      }
      if (this->rightPoint().z2() <= bv.z2() && bv.z2() <= this->leftPoint().z2()) {
        double lambda = ((bv.z2() - this->rightPoint().z2()) / ( this->leftPoint().z2() - this->rightPoint().z2()));
        BVect p(this->leftPoint(), this->rightPoint(), lambda);
        projections.second = BVect(p.z1(), bv.z2(), p.x());
      } else {
        projections.second = this->rightPoint();
      }
      return projections;
    }
    DominanceStatus compareWithPoint(const BEdge& be, BEdge& tleft, BEdge& tright) const {
      if (this->isInA1AreaOf(be) || this->isInA2AreaOf(be))
        return DominanceStatus::NO_DOM;
      BVect bv = be.leftPoint();
      if (this->leftPoint().weaklyDominates(bv) && this->rightPoint().weaklyDominates(bv))
        return DominanceStatus::A_DOM_B;
      if (bv.weaklyDominates(this->leftPoint()) && bv.weaklyDominates(this->rightPoint()))
        return DominanceStatus::B_DOM_A;
      std::pair<BVect, BVect> projs = computeProjWithPoint(bv);
      BVect proj1 = projs.first;
      BVect proj2 = projs.second;
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
    bool intersect(const BEdge& be, BVect& i1, BVect& i2) const {
      double Az1 = this->rightPoint().z1();
      double Az2 = this->rightPoint().z2();
      double Cz1 = be.rightPoint().z1();
      double Cz2 = be.rightPoint().z2();
      double Iz1 = this->leftPoint().z1() - Az1;
      double Iz2 = this->leftPoint().z2() - Az2;
      double Jz1 = be.leftPoint().z1() - Cz1;
      double Jz2 = be.leftPoint().z2() - Cz2;
      double lambda = (Iz2*Cz1 - Iz2*Az1 - Iz1*Cz2 + Iz1*Az2) / (Iz1*Jz2 - Iz2*Jz1);
      double mu  = (Jz2*Cz1 - Jz2*Az1 - Jz1*Cz2 + Jz1*Az2) / (Iz1*Jz2 - Iz2*Jz1);
      if (0 < lambda && lambda < 1 && 0 < mu && mu < 1) {
        i1 = BVect(this->leftPoint(), this->rightPoint(), mu);
        i2 = BVect(be.leftPoint(), be.rightPoint(), lambda);
        return true;
      } else {
        return false;
      }
    }
    DominanceStatus compareLeftEdges(BEdge& t, BEdge& b) const {
      if (t.leftPoint().weaklyDominates(b.leftPoint()))
        return DominanceStatus::A_DOM_B;
      else if (t.leftPoint().isInA1AreaOf(b.leftPoint())) {
        std::pair<BVect, BVect> projs = t.computeProjWithPoint(b.leftPoint());
        BVect proj1 = projs.first;
        BVect proj2 = projs.second;
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
        std::pair<BVect, BVect> projs = t.computeProjWithPoint(b.rightPoint());
        BVect proj1 = projs.first;
        BVect proj2 = projs.second;
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
        BVect intThis;
        BVect intBe;
        if (this->intersect(be, intThis, intBe)) {
          tleft = BEdge(this->leftPoint(), intThis);
          tright = BEdge(intThis, this->rightPoint());
          beleft = BEdge(be.leftPoint(), intBe);
          beright = BEdge(intBe, be.rightPoint());
          DominanceStatus left = compareLeftEdges(tleft, beleft);
          DominanceStatus right = compareRightEdges(tright, beright);
          return DominanceStatus::MUTUAL_DOM;
        } else {
          if (this->isInA1AreaOf(be) || this->isInA2AreaOf(be))
            return DominanceStatus::NO_DOM;
          std::pair<BVect, BVect> projb1 = this->computeProjWithPoint(be.leftPoint());
          BVect proj1bleft = projb1.first;
          BVect proj2bleft = projb1.second;
          std::pair<BVect, BVect> projb2 = this->computeProjWithPoint(be.rightPoint());
          BVect proj1bright = projb2.first;
          BVect proj2bright = projb2.second;
          std::pair<BVect, BVect> projt1 = be.computeProjWithPoint(this->leftPoint());
          BVect proj1tleft = projt1.first;
          BVect proj2tleft = projt1.second;
          std::pair<BVect, BVect> projt2 = be.computeProjWithPoint(this->rightPoint());
          BVect proj1tright = projt2.first;
          BVect proj2tright = projt2.second;
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
