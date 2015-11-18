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
    /*
    Simulate 12 evolutions.
    Print every grid (i.e. 0, 1, 2, 3, ... 12)
    */
    Life<ConwayCell> l1(cin);
    for(int g = 0; g <= l1.e; g += l1.f)
        l1.print_grid(g, cout);
}