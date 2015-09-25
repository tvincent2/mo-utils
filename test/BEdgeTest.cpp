#include <cppunit/extensions/HelperMacros.h>
#include "BEdge.hpp"

class BEdgeTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(BEdgeTest);
  CPPUNIT_TEST(testPointGetters);
  CPPUNIT_TEST(testIsAPoint);
  CPPUNIT_TEST(testAreaPredicates);
  CPPUNIT_TEST(testProjComputation);
  CPPUNIT_TEST(testComparisonWithPoint);
  CPPUNIT_TEST(testIntersection);
  CPPUNIT_TEST(testComparisonLeft);
  CPPUNIT_TEST(testComparisonRight);
  CPPUNIT_TEST(testEdgeComparison);
  CPPUNIT_TEST_SUITE_END();
 private:
  BEdge* simpleEdge;
  BEdge* pointEdge;
  BEdge* pointEdge2;
  BEdge* simpleEdge2;
  BEdge* longEdge;
  BEdge* intersectEdge1;
  BEdge* intersectEdge2;
  BEdge* intersectEdge3;
  BEdge* intersectEdge4;
  BEdge* leftEdge1;
  BEdge* leftEdge2;
  BEdge* leftEdge3;
  BEdge* rightEdge1;
  BEdge* rightEdge2;
  BEdge* rightEdge3;
  BEdge* longEdge1;
  BEdge* longEdge2;
  BEdge* longEdge3;
  BEdge* longEdge4;
  BEdge* longEdge5;
  BEdge* longEdge6;
 public:
  void setUp() {
    std::vector<double> x;
    BVect a(1, 10, x);
    BVect b(3, 8, x);
    BVect c(0, 0, x);
    BVect d(5, 7, x);
    BVect e(4, 6, x);
    BVect i1(0, 8, x);
    BVect i2(8, 0, x);
    BVect i3(0, 10, x);
    BVect i4(4, 2, x);
    BVect i5(0, 5, x);
    BVect i6(8, 3, x);
    BVect i7(5, 6, x);
    BVect i8(8, 3, x);
    BVect le1(2, 8, x);
    BVect le2(1, 7, x);
    BVect le3(3, 6, x);
    BVect re1(8, 2, x);
    BVect re2(6, 3, x);
    BVect re3(7, 1, x);
    BVect intersection(5, 5, x);
    BVect ba1(1, 11, x);
    BVect ba2(11, 1, x);
    BVect bb1(0, 5, x);
    BVect bb2(5, 0, x);
    BVect bc1(0, 8, x);
    BVect bc2(5, 3, x);
    BVect bd1(3, 8, x);
    BVect bd2(9, 0, x);
    BVect be1(3, 8, x);
    BVect be2(8, 3, x);
    BVect bf1(4, 7, x);
    BVect bf2(8, 5, x);
    simpleEdge = new BEdge(a, b);
    pointEdge = new BEdge(c);
    pointEdge2 = new BEdge(c, c);
    simpleEdge2 = new BEdge(d, e);
    longEdge = new BEdge(a, e);
    intersectEdge1 = new BEdge(i1, i2);
    intersectEdge2 = new BEdge(i3, i4);
    intersectEdge3 = new BEdge(i5, i6);
    intersectEdge4 = new BEdge(i7, i8);
    leftEdge1 = new BEdge(le1, intersection);
    leftEdge2 = new BEdge(le2, intersection);
    leftEdge3 = new BEdge(le3, intersection);
    rightEdge1 = new BEdge(intersection, re1);
    rightEdge2 = new BEdge(intersection, re2);
    rightEdge3 = new BEdge(intersection, re3);
    longEdge1 = new BEdge(ba1, ba2);
    longEdge2 = new BEdge(bb1, bb2);
    longEdge3 = new BEdge(bc1, bc2);
    longEdge4 = new BEdge(bd1, bd2);
    longEdge5 = new BEdge(be1, be2);
    longEdge6 = new BEdge(bf1, bf2);
  }
  void tearDown() {
    delete simpleEdge;
    delete pointEdge;
    delete pointEdge2;
    delete simpleEdge2;
    delete longEdge;
    delete intersectEdge1;
    delete intersectEdge2;
    delete intersectEdge3;
    delete intersectEdge4;
    delete leftEdge1;
    delete leftEdge2;
    delete leftEdge3;
    delete rightEdge1;
    delete rightEdge2;
    delete rightEdge3;
    delete longEdge1;
    delete longEdge2;
    delete longEdge3;
    delete longEdge4;
    delete longEdge5;
  }
  void testPointGetters() {
    CPPUNIT_ASSERT(simpleEdge->leftPoint().z1() == 1);
    CPPUNIT_ASSERT(simpleEdge->leftPoint().z2() == 10);
    CPPUNIT_ASSERT(simpleEdge->rightPoint().z1() == 3);
    CPPUNIT_ASSERT(simpleEdge->rightPoint().z2() == 8);
    CPPUNIT_ASSERT(pointEdge->leftPoint().z1() == 0);
    CPPUNIT_ASSERT(pointEdge->leftPoint().z2() == 0);
    CPPUNIT_ASSERT(pointEdge->rightPoint().z1() == 0);
    CPPUNIT_ASSERT(pointEdge->rightPoint().z2() == 0);
    CPPUNIT_ASSERT(pointEdge2->leftPoint().z1() == 0);
    CPPUNIT_ASSERT(pointEdge2->leftPoint().z2() == 0);
    CPPUNIT_ASSERT(pointEdge2->rightPoint().z1() == 0);
    CPPUNIT_ASSERT(pointEdge2->rightPoint().z2() == 0);
  }
  void testIsAPoint() {
    CPPUNIT_ASSERT(!simpleEdge->isAPoint());
    CPPUNIT_ASSERT(pointEdge->isAPoint());
    CPPUNIT_ASSERT(pointEdge2->isAPoint());
  }
  void testAreaPredicates() {
    CPPUNIT_ASSERT(simpleEdge->isInA1AreaOf(*simpleEdge2));
    CPPUNIT_ASSERT(!simpleEdge->isInA2AreaOf(*simpleEdge2));
    CPPUNIT_ASSERT(!simpleEdge->isInA1AreaOf(*pointEdge));
    CPPUNIT_ASSERT(!simpleEdge->isInA2AreaOf(*pointEdge));
    CPPUNIT_ASSERT(!simpleEdge2->isInA1AreaOf(*simpleEdge));
    CPPUNIT_ASSERT(simpleEdge2->isInA2AreaOf(*simpleEdge));
    CPPUNIT_ASSERT(!simpleEdge2->isInA1AreaOf(*pointEdge));
    CPPUNIT_ASSERT(!simpleEdge2->isInA2AreaOf(*pointEdge));
    CPPUNIT_ASSERT(!pointEdge->isInA1AreaOf(*simpleEdge));
    CPPUNIT_ASSERT(!pointEdge->isInA2AreaOf(*simpleEdge));
    CPPUNIT_ASSERT(!pointEdge->isInA1AreaOf(*simpleEdge2));
    CPPUNIT_ASSERT(!pointEdge->isInA2AreaOf(*simpleEdge2));
  }
  void testProjComputation() {
    std::vector<double> x;
    BVect zero(0, 0, x);
    BVect a(0, 9, x);
    BVect b(3, 5, x);
    BVect c(2, 8, x);
    std::pair<double, double> pz = longEdge->computeLambdasWithPoint(zero);
    std::pair<double, double> pa = longEdge->computeLambdasWithPoint(a);
    std::pair<double, double> pb = longEdge->computeLambdasWithPoint(b);
    std::pair<double, double> pc = longEdge->computeLambdasWithPoint(c);
    CPPUNIT_ASSERT(pz.first == 1);
    CPPUNIT_ASSERT(pz.second == 0);
    CPPUNIT_ASSERT(pa.first == 1);
    CPPUNIT_ASSERT(pa.second == 0.75);
    CPPUNIT_ASSERT(pb.first == 1.0/3.0);
    CPPUNIT_ASSERT(pb.second == 0);
    CPPUNIT_ASSERT(pc.first == 2.0/3.0);
    CPPUNIT_ASSERT(pc.second == 0.5);
  }
  void testComparisonWithPoint() {
    std::vector<double> x;
    BVect zero(0, 0, x);
    BEdge bz(zero);
    BVect a(0, 9, x);
    BEdge ba(a);
    BVect b(3, 5, x);
    BEdge bb(b);
    BVect c(2, 8, x);
    BEdge bc(c);
    BEdge left;
    BEdge right;
    BVect aProj2(1.75, 9, x);
    BVect bProj1(3, (7.0 + 1.0/3.0), x);
    BVect cProj1(2, (8.0 + 2.0/3.0), x);
    BVect cProj2(2.5, 8, x);
    DominanceStatus dsz = longEdge->compareWithPoint(bz, left, right);
    CPPUNIT_ASSERT(dsz == DominanceStatus::B_DOM_A);
    DominanceStatus dsa = longEdge->compareWithPoint(ba, left, right);
    CPPUNIT_ASSERT(dsa == DominanceStatus::B_PART_DOM_A);
    CPPUNIT_ASSERT(right.rightPoint() == longEdge->rightPoint());
    CPPUNIT_ASSERT(right.leftPoint() == aProj2);
    DominanceStatus dsb = longEdge->compareWithPoint(bb, left, right);
    CPPUNIT_ASSERT(dsb == DominanceStatus::B_PART_DOM_A);
    CPPUNIT_ASSERT(left.leftPoint() == longEdge->leftPoint());
    CPPUNIT_ASSERT(left.rightPoint() == bProj1);
    DominanceStatus dsc = longEdge->compareWithPoint(bc, left, right);
    CPPUNIT_ASSERT(dsc == DominanceStatus::B_PART_DOM_A);
    CPPUNIT_ASSERT(left.leftPoint() == longEdge->leftPoint());
    CPPUNIT_ASSERT(left.rightPoint() == cProj1);
    CPPUNIT_ASSERT(right.leftPoint() == cProj2);
    CPPUNIT_ASSERT(right.rightPoint() == longEdge->rightPoint());
  }
  void testIntersection() {
    BVect i1, i2;
    CPPUNIT_ASSERT(intersectEdge1->intersect(*intersectEdge2, i1, i2));
    CPPUNIT_ASSERT(i1.z1() == 2 && i1.z2() == 6);
    CPPUNIT_ASSERT(intersectEdge1->intersect(*intersectEdge3, i1, i2));
    CPPUNIT_ASSERT(i1.z1() == 4 && i1.z2() == 4);
    CPPUNIT_ASSERT(!intersectEdge1->intersect(*intersectEdge4, i1, i2));
  }
  void testComparisonLeft() {
    BEdge rest;
    CPPUNIT_ASSERT(rest.compareLeftEdges(*leftEdge1, *leftEdge2) == DominanceStatus::B_DOM_A);
    CPPUNIT_ASSERT(rest.compareLeftEdges(*leftEdge1, *leftEdge3) == DominanceStatus::B_PART_DOM_A);
    CPPUNIT_ASSERT(rest.leftPoint().z1() == 2 && rest.leftPoint().z2() == 8);
    CPPUNIT_ASSERT(rest.rightPoint().z1() == 3 && rest.rightPoint().z2() == 7);
    CPPUNIT_ASSERT(rest.compareLeftEdges(*leftEdge2, *leftEdge1) == DominanceStatus::A_DOM_B);
    CPPUNIT_ASSERT(rest.compareLeftEdges(*leftEdge3, *leftEdge1) == DominanceStatus::A_PART_DOM_B);
    CPPUNIT_ASSERT(rest.leftPoint().z1() == 2 && rest.leftPoint().z2() == 8);
    CPPUNIT_ASSERT(rest.rightPoint().z1() == 3 && rest.rightPoint().z2() == 7);
  }
  void testComparisonRight() {
    BEdge rest;
    CPPUNIT_ASSERT(rest.compareRightEdges(*rightEdge1, *rightEdge2) == DominanceStatus::B_PART_DOM_A);
    CPPUNIT_ASSERT(rest.leftPoint().z1() == 7 && rest.leftPoint().z2() == 3);
    CPPUNIT_ASSERT(rest.rightPoint().z1() == 8 && rest.rightPoint().z2() == 2);
    CPPUNIT_ASSERT(rest.compareRightEdges(*rightEdge1, *rightEdge3) == DominanceStatus::B_DOM_A);
    CPPUNIT_ASSERT(rest.compareRightEdges(*rightEdge2, *rightEdge1) == DominanceStatus::A_PART_DOM_B);
    CPPUNIT_ASSERT(rest.leftPoint().z1() == 7 && rest.leftPoint().z2() == 3);
    CPPUNIT_ASSERT(rest.rightPoint().z1() == 8 && rest.rightPoint().z2() == 2);
    CPPUNIT_ASSERT(rest.compareRightEdges(*rightEdge3, *rightEdge1) == DominanceStatus::A_DOM_B);
  }
  void testEdgeComparison() {
    BEdge tleft;
    BEdge tright;
    BEdge bleft;
    BEdge bright;
    CPPUNIT_ASSERT(longEdge1->compareWith(*longEdge2, tleft, tright, bleft, bright) == DominanceStatus::B_DOM_A);
    CPPUNIT_ASSERT(longEdge2->compareWith(*longEdge1, tleft, tright, bleft, bright) == DominanceStatus::A_DOM_B);
    CPPUNIT_ASSERT(longEdge1->compareWith(*longEdge3, tleft, tright, bleft, bright) == DominanceStatus::B_PART_DOM_A);
    CPPUNIT_ASSERT(tright.leftPoint().z1() == 9 && tright.leftPoint().z2() == 3);
    CPPUNIT_ASSERT(tright.rightPoint().z1() == 11 && tright.rightPoint().z2() == 1);
    CPPUNIT_ASSERT(longEdge3->compareWith(*longEdge1, tleft, tright, bleft, bright) == DominanceStatus::A_PART_DOM_B);
    CPPUNIT_ASSERT(bright.leftPoint().z1() == 9 && bright.leftPoint().z2() == 3);
    CPPUNIT_ASSERT(bright.rightPoint().z1() == 11 && bright.rightPoint().z2() == 1);
    CPPUNIT_ASSERT(longEdge1->compareWith(*longEdge4, tleft, tright, bleft, bright) == DominanceStatus::B_PART_DOM_A);
    CPPUNIT_ASSERT(tleft.leftPoint().z1() == 1 && tleft.leftPoint().z2() == 11);
    CPPUNIT_ASSERT(tleft.rightPoint().z1() == 3 && tleft.rightPoint().z2() == 9);
    CPPUNIT_ASSERT(longEdge4->compareWith(*longEdge1, tleft, tright, bleft, bright) == DominanceStatus::A_PART_DOM_B);
    CPPUNIT_ASSERT(bleft.leftPoint().z1() == 1 && bleft.leftPoint().z2() == 11);
    CPPUNIT_ASSERT(bleft.rightPoint().z1() == 3 && bleft.rightPoint().z2() == 9);
    CPPUNIT_ASSERT(longEdge1->compareWith(*longEdge5, tleft, tright, bleft, bright) == DominanceStatus::B_PART_DOM_A);
    CPPUNIT_ASSERT(tleft.leftPoint().z1() == 1 && tleft.leftPoint().z2() == 11);
    CPPUNIT_ASSERT(tleft.rightPoint().z1() == 3 && tleft.rightPoint().z2() == 9);
    CPPUNIT_ASSERT(tright.leftPoint().z1() == 9 && tright.leftPoint().z2() == 3);
    CPPUNIT_ASSERT(tright.rightPoint().z1() == 11 && tright.rightPoint().z2() == 1);
    CPPUNIT_ASSERT(longEdge5->compareWith(*longEdge1, tleft, tright, bleft, bright) == DominanceStatus::A_PART_DOM_B);
    CPPUNIT_ASSERT(bleft.leftPoint().z1() == 1 && bleft.leftPoint().z2() == 11);
    CPPUNIT_ASSERT(bleft.rightPoint().z1() == 3 && bleft.rightPoint().z2() == 9);
    CPPUNIT_ASSERT(bright.leftPoint().z1() == 9 && bright.leftPoint().z2() == 3);
    CPPUNIT_ASSERT(bright.rightPoint().z1() == 11 && bright.rightPoint().z2() == 1);
    CPPUNIT_ASSERT(longEdge1->compareWith(*longEdge6, tleft, tright, bleft, bright) == DominanceStatus::MUTUAL_DOM);
    CPPUNIT_ASSERT(tleft.leftPoint().z1() == 1 && tleft.leftPoint().z2() == 11);
    CPPUNIT_ASSERT(tleft.rightPoint().z1() == 4 && tleft.rightPoint().z2() == 8);
    CPPUNIT_ASSERT(bleft.leftPoint().z1() == 4 && bleft.leftPoint().z2() == 7);
    CPPUNIT_ASSERT(bleft.rightPoint().z1() == 6 && bleft.rightPoint().z2() == 6);
    CPPUNIT_ASSERT(tright.leftPoint().z1() == 6 && tright.leftPoint().z2() == 6);
    CPPUNIT_ASSERT(tright.rightPoint().z1() == 11 && tright.rightPoint().z2() == 1);
    CPPUNIT_ASSERT(longEdge6->compareWith(*longEdge1, tleft, tright, bleft, bright) == DominanceStatus::MUTUAL_DOM);
    CPPUNIT_ASSERT(bleft.leftPoint().z1() == 1 && bleft.leftPoint().z2() == 11);
    CPPUNIT_ASSERT(bleft.rightPoint().z1() == 4 && bleft.rightPoint().z2() == 8);
    CPPUNIT_ASSERT(tleft.leftPoint().z1() == 4 && tleft.leftPoint().z2() == 7);
    CPPUNIT_ASSERT(tleft.rightPoint().z1() == 6 && tleft.rightPoint().z2() == 6);
    CPPUNIT_ASSERT(bright.leftPoint().z1() == 6 && bright.leftPoint().z2() == 6);
    CPPUNIT_ASSERT(bright.rightPoint().z1() == 11 && bright.rightPoint().z2() == 1);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(BEdgeTest);
