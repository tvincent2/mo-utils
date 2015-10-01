#include <cppunit/extensions/HelperMacros.h>
#include "DominanceStatus.hpp"


class DominanceStatusTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(DominanceStatusTest);
  CPPUNIT_TEST(testDominanceStatus);
  CPPUNIT_TEST(testInvert);
  CPPUNIT_TEST_SUITE_END();
 private:
  DominanceStatus nd;
  DominanceStatus adb;
  DominanceStatus apdb;
  DominanceStatus bda;
  DominanceStatus bpda;
  DominanceStatus md;
 public:
  void setUp() {
    nd = DominanceStatus::NO_DOM;
    adb = DominanceStatus::A_DOM_B;
    apdb = DominanceStatus::A_PART_DOM_B;
    bda = DominanceStatus::B_DOM_A;
    bpda = DominanceStatus::B_PART_DOM_A;
    md = DominanceStatus::MUTUAL_DOM;
  }
  void tearDown() {}
  void testDominanceStatus() {
    CPPUNIT_ASSERT (nd == DominanceStatus::NO_DOM);
    CPPUNIT_ASSERT (adb == DominanceStatus::A_DOM_B);
    CPPUNIT_ASSERT (apdb == DominanceStatus::A_PART_DOM_B);
    CPPUNIT_ASSERT (bda == DominanceStatus::B_DOM_A);
    CPPUNIT_ASSERT (bpda == DominanceStatus::B_PART_DOM_A);
    CPPUNIT_ASSERT (md == DominanceStatus::MUTUAL_DOM);
  }
  void testInvert() {
    CPPUNIT_ASSERT (invert(nd) == DominanceStatus::NO_DOM);
    CPPUNIT_ASSERT (invert(adb) == DominanceStatus::B_DOM_A);
    CPPUNIT_ASSERT (invert(apdb) == DominanceStatus::B_PART_DOM_A);
    CPPUNIT_ASSERT (invert(bda) == DominanceStatus::A_DOM_B);
    CPPUNIT_ASSERT (invert(bpda) == DominanceStatus::A_PART_DOM_B);
    CPPUNIT_ASSERT (invert(md) == DominanceStatus::MUTUAL_DOM);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(DominanceStatusTest);
