#define BOOST_TEST_MODULE MyTest
#define BOOST_TEST_DYN_LINK
#include "boost/test/unit_test.hpp"

/* This file is the test for experimenting the use of boost test framework */

BOOST_AUTO_TEST_CASE(my_test)
{
	BOOST_CHECK(true);
}
