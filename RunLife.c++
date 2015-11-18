// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2015
// Glenn P. Downing
// -------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // cout, endl
#include "Life.h"

// ----
// main
// ----

int main () {
    using namespace std;

    // -----------------
    // Conway Cell 21x13
    // -----------------

    cout << "*** Life<ConwayCell> 21x13 ***" << endl << endl;
    Life<ConwayCell> l1(cin);
    for(int g = 0; g <= l1.e; g += l1.f)
        l1.print_grid(g, cout);
        
    cout << "*** Life<ConwayCell> 20x29 ***" << endl << endl;
    Life<ConwayCell> l2(cin);
    for(int g = 0; g <= l2.e; g += l2.f)
        l2.print_grid(g, cout);
        
    cout << "*** Life<ConwayCell> 109x69 ***" << endl << endl;
    Life<ConwayCell> l3(cin);
    for(int g = 0; g <= l3.e; g += l3.f)
        l3.print_grid(g, cout);
        
    cout << "*** Life<FredkinCell> 20x20 ***" << endl << endl;
    Life<FredkinCell> l4(cin);
    for(int g = 0; g <= l4.e; g += l4.f)
        l4.print_grid(g, cout);
        
    cout << "*** Life<Cell> 20x20 ***" << endl << endl;
    Life<Cell> l5(cin);
    for(int g = 0; g <= l5.e; g += l5.f)
        l5.print_grid(g, cout);
        
    cout << "*** Life<FredkinCell> 100x75 ***" << endl << endl;
    Life<FredkinCell> l6(cin);
    for(int g = 0; g <= l6.e; g += l6.f)
        l6.print_grid(g, cout);
        
    cout << "*** Life<ConwayCell> 150x60 ***" << endl << endl;
    Life<ConwayCell> l7(cin);
    for(int g = 0; g <= l7.e; g += l7.f)
        l7.print_grid(g, cout);
        
    cout << "*** Life<Cell> 150x50 ***" << endl << endl;
    Life<Cell> l8(cin);
    for(int g = 0; g <= l8.e; g += l8.f)
        l8.print_grid(g, cout);
}
