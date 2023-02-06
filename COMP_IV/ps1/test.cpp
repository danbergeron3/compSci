// Dr. Rykalova
// test.cpp for PS1a
// updated 1/31/2020

#include <iostream>
#include <string>

#include "FibLFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TEST
#include <boost/test/unit_test.hpp>



BOOST_AUTO_TEST_CASE(sixteenBitsThreeTaps) {

  FibLFSR l("1011011000110110");
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 1);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 0);
  BOOST_REQUIRE(l.step() == 1);

  FibLFSR l2("1011011000110110");
  BOOST_REQUIRE(l2.generate(9) == 51);
}

BOOST_AUTO_TEST_CASE(ZeroTest) {
    FibLFSR l("0000000000000000");
    for(int i = 0; i < 1000; i++){
        BOOST_REQUIRE(l.step() == 0);
    }
}

BOOST_AUTO_TEST_CASE(OnesTest) {
    FibLFSR l("1111111111111111");
    BOOST_REQUIRE(l.generate(11) == 0);
    BOOST_REQUIRE(l.generate(12) != 0);
    
}

