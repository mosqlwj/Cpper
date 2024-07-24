#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "database/netlist.h"

#include <cassert>
#include <iostream>
#include <string>
#include <regex>

using namespace  std;
using namespace ndb;
TEST_CASE("test netlist case01") {

    Netlist netlist{};
    netlist.Report();
}

TEST_CASE("test netlist case02") {
    Module* m1 = new Module("m1");

    Port* p1 = new Port("I1", Direction::INPUT);
    Port* p2 = new Port("I2", Direction::INPUT);
    Port* p3 = new Port("O", Direction::OUTPUT);

    m1->AddPort(p1);
    m1->AddPort(p2);
    m1->AddPort(p3);



}