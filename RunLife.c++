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
    Life<ConwayCell> l4(cin);
    for(int g = 0; g <= l4.e; g += l4.f)
        l4.print_grid(g, cout);
        
    cout << "*** Life<Cell> 20x20 ***" << endl << endl;
    Life<ConwayCell> l5(cin);
    for(int g = 0; g <= l5.e; g += l5.f)
        l5.print_grid(g, cout);
}
