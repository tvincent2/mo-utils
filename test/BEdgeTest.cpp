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
    simpleEdge = new BEdge(a, b);
    pointEdge = new BEdge(c);
    pointEdge2 = new BEdge(c, c);
    simpleEdge2 = new BEdge(d, e);
    longEdge = new BEdge(a, e);
    intersectEdge1 = new BEdge(i1, i2);
    intersectEdge2 = new BEdge(i3, i4);
    intersectEdge3 = new BEdge(i5, i6);
    intersectEdge4 = new BEdge(i7, i8);
  }
  void tearDown() {
    delete simpleEdge;
    delete pointEdge;
    delete pointEdge2;
    delete simpleEdge2;
    delete longEdge;
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
};

CPPUNIT_TEST_SUITE_REGISTRATION(BEdgeTest);
