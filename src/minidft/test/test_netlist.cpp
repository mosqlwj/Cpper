#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "netlist.h"

#include <cassert>
#include <iostream>
#include <string>
#include <regex>

using namespace  std;
using namespace ndb;
TEST_CASE("test netlist case01") {
    Netlist netlist;
    netlist.Report();
}
