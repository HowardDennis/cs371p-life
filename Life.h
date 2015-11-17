#include <cassert>	// assert
#include <string>	// string
#include <vector>	// vector
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <cstdlib>	// rand

using namespace std;

class AbstractCell {

protected:

  // -----
  // alive
  // -----
	/**
	 * Stores cell's life
	 */

	 bool alive;

public:

	// -------------------------------
	// Constructor
	// -------------------------------
	/** 
	 * Initialization of bool alive depends on char a.
	 * It's alive iff char a is not '-' or '.'
	 */

	AbstractCell(char a);

	// -------
	// evolve
	// -------
	/** 
	 * Looks at the neighbors and return true iff bool alive needs to be changed.
	 * It's pure virtual so that child cells are forced to implement it.
	 */

	virtual bool evolve(AbstractCell** const neighbors) = 0;

	// -----------
	// shift_state
	// -----------
	/** 
	 * Shift the state of this cell.
	 */

	void shift_state();

	// ---------
	// get_state
	// ---------
	/**
	 * In Conway/Fredkin cell, get_state will return a char representing the current state for the each corresponding class.
	 * This is again an abstract method, since each child class might represent a live/dead cell differently.
	 */
	 };