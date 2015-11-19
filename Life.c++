#include "Life.h"

using namespace std;

// ------------
// AbstractCell
// ------------
AbstractCell::AbstractCell(char a)
{
	if(a == '.'||a == '-')
		alive = false;
	else
		alive = true;
}

void AbstractCell::shift_state(){alive = !alive;}

bool AbstractCell::isAlive(){ return alive;}

// -----------
// Conway Cell
// -----------
ConwayCell::ConwayCell(char a): AbstractCell(a) {}

bool ConwayCell::evolve(AbstractCell** const n){
	int c = 0;
	for(int i = 0; i <= 7; ++i){
		if(n[i] != NULL && n[i]->isAlive())
			++c;
	}
	assert(c >= 0 && c <= 8);

	if(alive && (c < 2 || c > 3))
		return true;
	else if(!alive && c == 3)
		return true;
	return false;
}
char ConwayCell::state(){
	if(alive)
		return '*';
	else
		return '.';
}

// ------------
// Fredkin Cell
// ------------
FredkinCell::FredkinCell(char a): AbstractCell(a){
	if(a == '+')
		age = 10;
	else if(a <= '9' && a >= '0')
		age = a - '0';
	assert(age >= 0);
}

bool FredkinCell::evolve(AbstractCell** const n){
	int c = 0;
	if(n[1] && n[1]->isAlive())
		++c;
	if(n[3] && n[3]->isAlive())
		++c;
	if(n[4] && n[4]->isAlive())
		++c;
	if(n[6] && n[6]->isAlive())
		++c;
	assert(c >= 0 && c <= 4);

	if(alive && (c == 0 || c == 2 || c == 4)){
		age = 0;
		return true;
	}
	else if(!alive && (c == 1 || c == 3)){
		assert(age == 0);
		return true;
	}
	if(alive) {
		assert(age >= 0);
		++age;
	}
	return false;
}
char FredkinCell::state(){
	if(alive) {
		if(age >= 10)
			return '+';
		else
			return (char)(age + '0');
	}
	else
		return '-';
}

// ----
// Cell
// ----

Cell::Cell(char a){
	if(a == '*'||a == '.')
		_p = new ConwayCell(a);
	else
		_p = new FredkinCell(a);
}

Cell::Cell(const Cell& rhs){
	if(dynamic_cast<ConwayCell*>(rhs._p))
		_p = new ConwayCell(*(dynamic_cast<ConwayCell*>(rhs._p)));
	else
		_p = new FredkinCell(*(dynamic_cast<FredkinCell*>(rhs._p)));
}

Cell::~Cell(){
	delete _p;
}

bool Cell::evolve(AbstractCell** const n){
	char oldstate = _p->state();
	bool output = _p->evolve(n);
	if(FredkinCell* cell = dynamic_cast<FredkinCell*>(_p)){
		if(oldstate == '1' && cell->state()=='2'){
			_p = new ConwayCell('*');
			delete cell;
		}
	}
	return output;
}

void Cell::shift_state(){
	_p->shift_state();
}

char Cell::state(){
	return _p->state();
}

bool Cell::isAlive(){
	return _p->isAlive();
}

AbstractCell* Cell::operator & (){
	return _p;
}
