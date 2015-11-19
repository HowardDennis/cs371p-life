#include <cassert>	// assert
#include <string>	// string
#include <vector>	// vector
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <cstdlib>	// rand

using namespace std;

// -------------
// AbstractCell
// -------------

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
	 * Cells whether a cell is alive or not.
	 * Since that information is simply stored as a bool in state, I could just return the value of state.
	 */
	bool living();

	 };

// ----------
// ConwayCell
// ----------

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

// -----------
// FredkinCell
// -----------

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

// -----
// Cell
// -----
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

template<typename C>

// -----
// Life
// -----
class Life{
private:
	// -----------------
	// p and _g
	// -----------------
	/**
	 * P stores the current population.
	 * _g stores the current generation.
	 */
	int p = 0, _g=0;
	// ----
	// grid
	// ----
	/**
	 * Stored the world as a vector of vectors of user specified type.
	 */
	vector<vector<C>> grid;
	// ----
	// iter
	// ----
	/**
	 * Iterable Vector
	 */
	vector<C> iter;
public:
	// -----------------
	// e and f
	// -----------------
	/**
	 * These save the number of evolutions and frequency of prints
	 */
	int e, f;
	// --------------------------
	// Lifeconstructor
	// --------------------------
	/**
	 * Makes a grid based on the received input.
	 */
	Life(istream& in){
		int r, c;
		string type;
		in >> type;
		in >> r >> c >> e >> f;
		for(int i = 0; i < r; ++i){
			grid.push_back(vector<C>());
			for(int j = 0; j < c; ++j){
				char temp;
				in >> temp;

				C cell(temp);
				grid[i].push_back(cell);
				if(cell.living())
					++p;
			}
		}
		for(int i = 0; i < r; ++i){
			for(int j = 0; j < c; ++j){
				iter.push_back(grid[i][j]);
			}
		}
	}

private:
	// -------------
	// run_evol
	// -------------
	/** 
	 * Runs evolution until _g, reaches the input generation, max_g.
	 * All neighboring cells are supplied to the evolving cell. Some neighbors' state will be ignored.
	 * Cells needing change will be placed in a buffer and changed after the turn.
	 */
	void run_evol(int max_g){
		int r = grid.size(), c = grid[0].size();
		for(; _g < max_g; ++_g){
			vector<AbstractCell*> buffer;
			// Iterate through the grid
			for(int i = 0; i < r; ++i){
				for(int j = 0; j < c; ++j){
					// Construct a array of 8 pointers that'll later be used to determine the state of the neighbors.
					AbstractCell* neighbors[8] = {NULL};
					if(j - 1 >= 0){
						if(i - 1 >= 0){
							neighbors[0] = &grid[i-1][j-1];
						}
						neighbors[3] = &grid[i][j-1];
						if(i + 1 < r){
							neighbors[5] = &grid[i+1][j-1];
						}
					}
					if(i - 1 >= 0)
						neighbors[1] = &grid[i-1][j];
					if(i + 1 < r)
						neighbors[6] = &grid[i+1][j];
					if(j + 1 < c){
						if(i - 1 >= 0)
							neighbors[2] = &grid[i-1][j+1];
						neighbors[4] = &grid[i][j+1];
						if(i + 1 < r)
							neighbors[7] = &grid[i+1][j+1];
					}

					// If evolve() return true, which means the cell needs to shift its state, push it onto the buffer.
					if(grid[i][j].evolve(neighbors))
						buffer.push_back(&grid[i][j]);
				}
			}
			// For each cell pointed by the buffer, shift its state.
			for(AbstractCell* change : buffer){
				change->shift_state();
				if(change->living())
					++p;
				else
					--p;
			}
		}
		/*for(int i = 0; i < r; ++i){
			for(int j = 0; j < c; ++j){
				iter[i*r + j] = grid[i][j];
			}
		}*/
	}



public:
	// ----------
	// print_grid
	// ----------
	/**
	 * Prints the grid of the current generation, g.
	 */
	void print_grid(int g, ostream& w){
		run_evol(g);
		w << "Generation = " << g << ", Population = " << p << "." << endl;
		for(unsigned int i = 0; i < grid.size(); ++i){
			for(unsigned int j = 0; j < grid[i].size(); ++j){
				w << grid[i][j].state();
			}
			w << endl;
		}
		w << endl;
	}

	// -----------------
	// begin, end and at
	// -----------------
	/**
	 * Make the grid in Life iterable
	 */
    C at(int n) {
    	assert(n >= 0 && (n < grid[0].size()*grid.size()));
    	int w = grid[0].size();
    	return grid[n/w][n%w];
    }
    
    C* begin() { // 2nd: add typename
   	return &grid[0][0]; //&iter[0];
   }

   C* end() { // 3rd: add typename
   	return &grid[0][3]; //&iter[iter.size() - 1];
   }
};

