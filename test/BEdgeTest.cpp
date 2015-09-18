#include <cppunit/extensions/HelperMacros.h>
#include "BEdge.hpp"

class BEdgeTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(BEdgeTest);
  CPPUNIT_TEST(testPointGetters);
  CPPUNIT_TEST(testIsAPoint);
  CPPUNIT_TEST(testAreaPredicates);
  CPPUNIT_TEST_SUITE_END();
 private:
  BEdge* simpleEdge;
  BEdge* pointEdge;
  BEdge* pointEdge2;
  BEdge* simpleEdge2;
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
  }
  void tearDown() {
    delete simpleEdge;
    delete pointEdge;
    delete pointEdge2;
    delete simpleEdge2;
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
};

CPPUNIT_TEST_SUITE_REGISTRATION(BEdgeTest);
