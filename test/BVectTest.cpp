#include <cppunit/extensions/HelperMacros.h>
#include "BVect.hpp"

class BVectTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(BVectTest);
  CPPUNIT_TEST(testDominance);
  CPPUNIT_TEST(testWeakDominance);
  CPPUNIT_TEST(testStrictDominance);
  CPPUNIT_TEST(testAreaPredicates);
  CPPUNIT_TEST_SUITE_END();
 private:
  BVect* a;
  BVect* b;
  BVect* c;
  BVect* d;
 public:
  void setUp() {
    std::vector<double> x;
    a = new BVect(1, 2, x);
    b = new BVect(2, 1, x);
    c = new BVect(3, 3, x);
    d = new BVect(2, 2, x);
  }
  void tearDown() {
    delete a;
    delete b;
    delete c;
    delete d;
  }
  void testDominance() {
    CPPUNIT_ASSERT(!a->dominates(*a));
    CPPUNIT_ASSERT(!a->dominates(*b));
    CPPUNIT_ASSERT(a->dominates(*c));
    CPPUNIT_ASSERT(a->dominates(*d));
    CPPUNIT_ASSERT(!b->dominates(*a));
    CPPUNIT_ASSERT(!b->dominates(*b));
    CPPUNIT_ASSERT(b->dominates(*c));
    CPPUNIT_ASSERT(b->dominates(*d));
    CPPUNIT_ASSERT(!c->dominates(*a));
    CPPUNIT_ASSERT(!c->dominates(*b));
    CPPUNIT_ASSERT(!c->dominates(*c));
    CPPUNIT_ASSERT(!c->dominates(*d));
    CPPUNIT_ASSERT(!d->dominates(*a));
    CPPUNIT_ASSERT(!d->dominates(*b));
    CPPUNIT_ASSERT(d->dominates(*c));
    CPPUNIT_ASSERT(!d->dominates(*d));
  }
  void testWeakDominance() {
    CPPUNIT_ASSERT(a->weaklyDominates(*a));
    CPPUNIT_ASSERT(!a->weaklyDominates(*b));
    CPPUNIT_ASSERT(a->weaklyDominates(*c));
    CPPUNIT_ASSERT(a->weaklyDominates(*d));
    CPPUNIT_ASSERT(!b->weaklyDominates(*a));
    CPPUNIT_ASSERT(b->weaklyDominates(*b));
    CPPUNIT_ASSERT(b->weaklyDominates(*c));
    CPPUNIT_ASSERT(b->weaklyDominates(*d));
    CPPUNIT_ASSERT(!c->weaklyDominates(*a));
    CPPUNIT_ASSERT(!c->weaklyDominates(*b));
    CPPUNIT_ASSERT(c->weaklyDominates(*c));
    CPPUNIT_ASSERT(!c->weaklyDominates(*d));
    CPPUNIT_ASSERT(!d->weaklyDominates(*a));
    CPPUNIT_ASSERT(!d->weaklyDominates(*b));
    CPPUNIT_ASSERT(d->weaklyDominates(*c));
    CPPUNIT_ASSERT(d->weaklyDominates(*d));
  }
  void testStrictDominance() {
    CPPUNIT_ASSERT(!a->strictlyDominates(*a));
    CPPUNIT_ASSERT(!a->strictlyDominates(*b));
    CPPUNIT_ASSERT(a->strictlyDominates(*c));
    CPPUNIT_ASSERT(!a->strictlyDominates(*d));
    CPPUNIT_ASSERT(!b->strictlyDominates(*a));
    CPPUNIT_ASSERT(!b->strictlyDominates(*b));
    CPPUNIT_ASSERT(b->strictlyDominates(*c));
    CPPUNIT_ASSERT(!b->strictlyDominates(*d));
    CPPUNIT_ASSERT(!c->strictlyDominates(*a));
    CPPUNIT_ASSERT(!c->strictlyDominates(*b));
    CPPUNIT_ASSERT(!c->strictlyDominates(*c));
    CPPUNIT_ASSERT(!c->strictlyDominates(*d));
    CPPUNIT_ASSERT(!d->strictlyDominates(*a));
    CPPUNIT_ASSERT(!d->strictlyDominates(*b));
    CPPUNIT_ASSERT(d->strictlyDominates(*c));
    CPPUNIT_ASSERT(!d->strictlyDominates(*d));
  }
  void testAreaPredicates() {
    CPPUNIT_ASSERT(a->isInA1AreaOf(*b));
    CPPUNIT_ASSERT(!a->isInA1AreaOf(*c));
    CPPUNIT_ASSERT(!a->isInA1AreaOf(*d));
    CPPUNIT_ASSERT(!b->isInA1AreaOf(*a));
    CPPUNIT_ASSERT(!b->isInA1AreaOf(*c));
    CPPUNIT_ASSERT(!b->isInA1AreaOf(*d));
    CPPUNIT_ASSERT(!c->isInA1AreaOf(*a));
    CPPUNIT_ASSERT(!c->isInA1AreaOf(*b));
    CPPUNIT_ASSERT(!c->isInA1AreaOf(*d));
    CPPUNIT_ASSERT(!d->isInA1AreaOf(*a));
    CPPUNIT_ASSERT(!d->isInA1AreaOf(*b));
    CPPUNIT_ASSERT(!d->isInA1AreaOf(*c));
    CPPUNIT_ASSERT(!a->isInA2AreaOf(*b));
    CPPUNIT_ASSERT(!a->isInA2AreaOf(*c));
    CPPUNIT_ASSERT(!a->isInA2AreaOf(*d));
    CPPUNIT_ASSERT(b->isInA2AreaOf(*a));
    CPPUNIT_ASSERT(!b->isInA2AreaOf(*c));
    CPPUNIT_ASSERT(!b->isInA2AreaOf(*d));
    CPPUNIT_ASSERT(!c->isInA2AreaOf(*a));
    CPPUNIT_ASSERT(!c->isInA2AreaOf(*b));
    CPPUNIT_ASSERT(!c->isInA2AreaOf(*d));
    CPPUNIT_ASSERT(!d->isInA2AreaOf(*a));
    CPPUNIT_ASSERT(!d->isInA2AreaOf(*b));
    CPPUNIT_ASSERT(!d->isInA2AreaOf(*c));
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(BVectTest);
