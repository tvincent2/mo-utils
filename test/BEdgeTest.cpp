#include <cppunit/extensions/HelperMacros.h>
#include "BEdge.hpp"

class BEdgeTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(BEdgeTest);
  CPPUNIT_TEST(testPointGetters);
  CPPUNIT_TEST(testIsAPoint);
  CPPUNIT_TEST(testAreaPredicates);
  CPPUNIT_TEST(testProjComputation);
  CPPUNIT_TEST(testComparisonWithPoint);
  CPPUNIT_TEST_SUITE_END();
 private:
  BEdge* simpleEdge;
  BEdge* pointEdge;
  BEdge* pointEdge2;
  BEdge* simpleEdge2;
  BEdge* longEdge;
 public:
  void setUp() {
    std::vector<double> x;
    BVect a(1, 10, x);
    BVect b(3, 8, x);
    BVect c(0, 0, x);
    BVect d(5, 7, x);
    BVect e(4, 6, x);
    simpleEdge = new BEdge(a, b);
    pointEdge = new BEdge(c);
    pointEdge2 = new BEdge(c, c);
    simpleEdge2 = new BEdge(d, e);
    longEdge = new BEdge(a, e);
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
    DominanceStatus dsz = longEdge->compareWithPoint(bz, left, right);
    CPPUNIT_ASSERT(dsz == DominanceStatus::B_DOM_A);
    DominanceStatus dsa = longEdge->compareWithPoint(ba, left, right);
    CPPUNIT_ASSERT(dsa == DominanceStatus::B_PART_DOM_A);
    DominanceStatus dsb = longEdge->compareWithPoint(bb, left, right);
    CPPUNIT_ASSERT(dsb == DominanceStatus::B_PART_DOM_A);
    DominanceStatus dsc = longEdge->compareWithPoint(bc, left, right);
    CPPUNIT_ASSERT(dsc == DominanceStatus::B_PART_DOM_A);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(BEdgeTest);
