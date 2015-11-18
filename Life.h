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
	 * Stores cell's life status
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
	// state
	// ---------
	/**
	 * Return a char representing the current state for the corresponding class.
	 * Since the two cells have different representative characters, this is abstract
	 */
	virtual char state() = 0;

	// -------
	// living
	// -------
	/**
	 * Tells whether a cell is alive or not.
	 * Since that information is simply stored as a bool in state, I could just return the value of state.
	 */
	bool living();

	 };

class ConwayCell: public AbstractCell{

public:
	// -----------------------
	// ConwayCell constructor 
	// -----------------------
	/** 
	 *  Constructs a Conway cell with the argument
	 */
	ConwayCell(char a);

	// -------------------
	// ConwayCell::evolve
	// -------------------
	/**
	 *  Returns true if the state needs to be changed. n is for neighbors
	 */
	bool evolve(AbstractCell** const n);

	// ------------------
	// ConwayCell::state 
	// ------------------
	/**
	 *  Prints the symbol of the state. '*' for alive, else '.'
	 */
	char state();
};

class FredkinCell: public AbstractCell{

private:

	// ---
	// age
	// ---
	/**
	 *  Keeps the age for future use
	 */
	int age = 0;

public:

	// ------------------------------
	// FredkinCell constructor
	// ------------------------------
	/**
	 * Initializes age based on char a
	 */
	FredkinCell(char a);
	// -------------------
	// FredkinCell::evolve
	// -------------------
	/**
	 *  Returns true if the state needs to be changed. n is for neighbors
	 *  Needs to change it's age as well as state
	 */
	bool evolve(AbstractCell** const n);

	// ------------------
	// FredkinCell::state 
	// ------------------
	/**
	 *  Prints the symbol of the state. An int for alive, else '-'
	 */
	char state();
};

class Cell{
private:
	// --
	// _p
	// --
	/**
	 * Address of the AbstractCell that Cell handles.
	 */
	AbstractCell* _p;

public:
	// -----------------------
	// Cell constructor
	// -----------------------
	/**
	 * Makes a new ConwayCell/FredkinCell for _p.
	 */
	Cell(char a);
	// -----------------------
	// Cell copy constructor
	// -----------------------
	/**
	 * Copies the AbstractCell present into _p
	 */
	Cell(const Cell& rhs);
	// -----------------
	// Cell's destructor
	// -----------------
	/**
	 * Deallocates _p space.
	 */
	~Cell();
	// ------
	// evolve
	// ------
	/**
	 * Run's the cell's evolve, and changes the FredkinCell if needed
	 */
	bool evolve(AbstractCell** const neighbors);

	// ---------
	// operator&
	// ---------
	/**
	 * Overloaded operator& to return _p
	 */
	AbstractCell* operator & ();

	// -----------
	// shift_state
	// -----------
	/**
	 * Runs shift_state() for the cell type
	 */
	void shift_state();

	// ---------
	// state
	// ---------
	/**
	 * Runs state() for the cell type
	 */
	char state();

	// -------
	// living
	// -------
	/**
	 * Runs living() for the cell type
	 */
	bool living();
};
