// --------------------------------
// projects/darwin/TestLife.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"
#include "Life.h"

using namespace std;

// 23 methods total
// 20 if exclude abstract method and AbstractCell constructor

// --------------------------------------------------
// Common functionalities inherited from AbstractCell
// --------------------------------------------------
TEST(Life, AbstractCell_ShiftState1) {
	ConwayCell c('*');
	c.shift_state();
	ASSERT_EQ(c.state(), '.');
}

TEST(Life, AbstractCell_ShiftState2) {
	ConwayCell c('.');
	c.shift_state();
	ASSERT_EQ(c.state(), '*');
}

TEST(Life, AbstractCell_ShiftState3) {
	FredkinCell f('0');
	f.shift_state();
	ASSERT_EQ(f.state(), '-');
}

TEST(Life, AbstractCell_ShiftState4) {
	FredkinCell f('-');
	f.shift_state();
	ASSERT_EQ(f.state(), '0');
}

TEST(Life, AbstractCell_Living1) {
	ConwayCell c('*');
	ASSERT_TRUE(c.living());
}

TEST(Life, AbstractCell_Living2) {
	ConwayCell c('.');
	ASSERT_FALSE(c.living());
}

TEST(Life, AbstractCell_Living3) {
	FredkinCell f('0');
	ASSERT_TRUE(f.living());
}

TEST(Life, AbstractCell_Living4) {
	FredkinCell f('-');
	ASSERT_FALSE(f.living());
}

// -----------
// ConwayCell Cell
// -----------

TEST(Life, ConwayCell_Constructor1) {
	ConwayCell c('*');
	ASSERT_EQ(c.state(), '*');
}

TEST(Life, ConwayCell_Constructor2) {
	ConwayCell c('.');
	ASSERT_EQ(c.state(), '.');
}

TEST(Life, ConwayCell_Constructor3) {
	ConwayCell c('-');
	ASSERT_EQ(c.state(), '.');
}

TEST(Life, ConwayCell_Constructor4) {
	ConwayCell c('5');
	ASSERT_EQ(c.state(), '*');
}

// from alive to dead
TEST(Life, ConwayCell_Evolve1) {
	ConwayCell c('*');
	AbstractCell* N[8] = {	new ConwayCell('*'),new ConwayCell('*'),new ConwayCell('*'),
							new ConwayCell('*'),					new ConwayCell('*'),
							new ConwayCell('*'),new ConwayCell('*'),new ConwayCell('*')};
	ASSERT_TRUE(c.evolve(N));
	for(AbstractCell* pointer : N)
		delete pointer;
}

// remain dead
TEST(Life, ConwayCell_Evolve2) {
	ConwayCell c('.');
	AbstractCell* N[8] = {	new ConwayCell('*'),new ConwayCell('*'),new ConwayCell('*'),
							new ConwayCell('*'),					new ConwayCell('*'),
							new ConwayCell('*'),new ConwayCell('*'),new ConwayCell('*')};
	ASSERT_FALSE(c.evolve(N));
	for(AbstractCell* pointer : N)
		delete pointer;
}

// from dead to alive
TEST(Life, ConwayCell_Evolve3) {
	ConwayCell c('.');
	AbstractCell* N[8] = {	new ConwayCell('*'),new ConwayCell('*'),new ConwayCell('*'),
							new ConwayCell('.'),					new ConwayCell('.'),
							new ConwayCell('.'),new ConwayCell('.'),new ConwayCell('.')};
	ASSERT_TRUE(c.evolve(N));
	for(AbstractCell* pointer : N)
		delete pointer;
}

// remain alive
TEST(Life, ConwayCell_Evolve4) {
	ConwayCell c('*');
	AbstractCell* N[8] = {	new ConwayCell('*'),new ConwayCell('*'),new ConwayCell('*'),
							new ConwayCell('.'),					new ConwayCell('.'),
							new ConwayCell('.'),new ConwayCell('.'),new ConwayCell('.')};
	ASSERT_FALSE(c.evolve(N));
	for(AbstractCell* pointer : N)
		delete pointer;
}

TEST(Life, ConwayCell_State1) {
	ConwayCell c('.');
	ASSERT_EQ(c.state(), '.');
}

TEST(Life, ConwayCell_State2) {
	ConwayCell c('*');
	ASSERT_EQ(c.state(), '*');
}

TEST(Life, ConwayCell_State3) {
	ConwayCell c('*');
	c.shift_state();
	ASSERT_EQ(c.state(), '.');
}

// ------------
// FredkinCell Cell
// ------------

TEST(Life, FredkinCell_Constructor1) {
	FredkinCell f('0');
	ASSERT_EQ(f.state(), '0');
}

TEST(Life, FredkinCell_Constructor2) {
	FredkinCell f('-');
	ASSERT_EQ(f.state(), '-');
}

TEST(Life, FredkinCell_Constructor3) {
	FredkinCell f('9');
	AbstractCell* N[8] = {	NULL, 			 	 new FredkinCell('1'), NULL,
							new FredkinCell('-'), 				  	   new FredkinCell('1'),
							NULL,			 	 new FredkinCell('1'), NULL};
	ASSERT_FALSE(f.evolve(N));
	ASSERT_FALSE(f.evolve(N));
	for(AbstractCell* pointer : N)
		if(pointer)
			delete pointer;
	ASSERT_EQ(f.state(), '+');
}

// from alive to dead
TEST(Life, FredkinCell_Evolve1) {
	FredkinCell f('0');
	AbstractCell* N[8] = {	NULL, 			 	 new FredkinCell('1'), NULL,
							new FredkinCell('1'), 				  	   new FredkinCell('1'),
							NULL,			 	 new FredkinCell('1'), NULL};
	ASSERT_TRUE(f.evolve(N));
	for(AbstractCell* pointer : N)
		if(pointer)
			delete pointer;
}

// remain alive
TEST(Life, FredkinCell_Evolve2) {
	FredkinCell f('0');
	AbstractCell* N[8] = {	NULL, 			 	 new FredkinCell('1'), NULL,
							new FredkinCell('-'), 				  	   new FredkinCell('1'),
							NULL,			 	 new FredkinCell('1'), NULL};
	ASSERT_FALSE(f.evolve(N));
	for(AbstractCell* pointer : N)
		if(pointer)
			delete pointer;
}

// from dead to alive
TEST(Life, FredkinCell_Evolve3) {
	FredkinCell f('-');
	AbstractCell* N[8] = {	NULL, 			 	 new FredkinCell('1'), NULL,
							new FredkinCell('-'), 				  	   new FredkinCell('1'),
							NULL,			 	 new FredkinCell('1'), NULL};
	ASSERT_TRUE(f.evolve(N));
	for(AbstractCell* pointer : N)
		if(pointer)
			delete pointer;
}

// remain dead
TEST(Life, FredkinCell_Evolve4) {
	FredkinCell f('-');
	AbstractCell* N[8] = {	NULL, 			 	 new FredkinCell('1'), NULL,
							new FredkinCell('1'), 				  	   new FredkinCell('1'),
							NULL,			 	 new FredkinCell('1'), NULL};
	ASSERT_FALSE(f.evolve(N));
	for(AbstractCell* pointer : N)
		if(pointer)
			delete pointer;
}

TEST(Life, FredkinCell_State1) {
	FredkinCell f('0');
	ASSERT_EQ(f.state(), '0');
}

TEST(Life, FredkinCell_State2) {
	FredkinCell f('-');
	ASSERT_EQ(f.state(), '-');
}

TEST(Life, FredkinCell_State3) {
	FredkinCell f('-');
	f.shift_state();
	ASSERT_EQ(f.state(), '0');
}

// ----
// Cell
// ----

TEST(Life, Cell_CharConstructor1) {
	Cell c('*');
	ASSERT_EQ(c.state(), '*');
	ASSERT_TRUE(dynamic_cast<ConwayCell*>(&c));
}

TEST(Life, Cell_CharConstructor2) {
	Cell c('.');
	ASSERT_EQ(c.state(), '.');
	ASSERT_TRUE(dynamic_cast<ConwayCell*>(&c));
}

TEST(Life, Cell_CharConstructor3) {
	Cell c('0');
	ASSERT_EQ(c.state(), '0');
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c));
}

TEST(Life, Cell_CharConstructor4) {
	Cell c('-');
	ASSERT_EQ(c.state(), '-');
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c));
}

TEST(Life, Cell_CopyConstructor1) {
	Cell c1('*');
	ASSERT_EQ(c1.state(), '*');
	ASSERT_TRUE(dynamic_cast<ConwayCell*>(&c1));
	Cell c2(c1);
	ASSERT_EQ(c2.state(), c1.state());
	ASSERT_NE(&c2, &c1);
	ASSERT_TRUE(dynamic_cast<ConwayCell*>(&c2));
}

TEST(Life, Cell_CopyConstructor2) {
	Cell c1('0');
	ASSERT_EQ(c1.state(), '0');
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c1));
	Cell c2(c1);
	ASSERT_EQ(c2.state(), c1.state());
	ASSERT_NE(&c2, &c1);
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c2));
}

TEST(Life, Cell_CopyConstructor3) {
	Cell c1('.');
	ASSERT_EQ(c1.state(), '.');
	ASSERT_TRUE(dynamic_cast<ConwayCell*>(&c1));
	Cell c2(c1);
	ASSERT_EQ(c2.state(), c1.state());
	ASSERT_NE(&c2, &c1);
	ASSERT_TRUE(dynamic_cast<ConwayCell*>(&c2));
}

TEST(Life, Cell_CopyConstructor4) {
	Cell c1('-');
	ASSERT_EQ(c1.state(), '-');
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c1));
	Cell c2(c1);
	ASSERT_EQ(c2.state(), c1.state());
	ASSERT_NE(&c2, &c1);
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c2));
}

TEST(Life, Cell_Evolve1) {
	Cell c1('*');
	ASSERT_EQ(c1.state(), '*');
	ASSERT_TRUE(dynamic_cast<ConwayCell*>(&c1));
	AbstractCell* N[8] = {	new ConwayCell('*'),new ConwayCell('*'),new ConwayCell('*'),
							new ConwayCell('*'),					new ConwayCell('.'),
							new ConwayCell('.'),new ConwayCell('.'),new ConwayCell('.')};
	ASSERT_TRUE(c1.evolve(N));
	for(AbstractCell* pointer : N)
		delete pointer;
}

TEST(Life, Cell_Evolve2) {
	Cell c1('0');
	ASSERT_EQ(c1.state(), '0');
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c1));
	AbstractCell* N[8] = {	new ConwayCell('*'),new ConwayCell('*'),new ConwayCell('*'),
							new ConwayCell('*'),					new ConwayCell('.'),
							new ConwayCell('.'),new ConwayCell('.'),new ConwayCell('.')};
	ASSERT_TRUE(c1.evolve(N));
	for(AbstractCell* pointer : N)
		delete pointer;
}

TEST(Life, Cell_Evolve3) {
	Cell c1('1');
	ASSERT_EQ(c1.state(), '1');
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c1));
	AbstractCell* N[8] = {	new ConwayCell('*'),new ConwayCell('*'),new ConwayCell('*'),
							new ConwayCell('-'),					new ConwayCell('.'),
							new ConwayCell('.'),new ConwayCell('.'),new ConwayCell('.')};
	ASSERT_FALSE(c1.evolve(N));
	ASSERT_TRUE(dynamic_cast<ConwayCell*>(&c1));
	ASSERT_EQ(c1.state(), '*');
	for(AbstractCell* pointer : N)
		delete pointer;
}

TEST(Life, Cell_ShiftState1) {
	Cell c('*');
	ASSERT_EQ(c.state(), '*');
	c.shift_state();
	ASSERT_EQ(c.state(), '.');
}

TEST(Life, Cell_ShiftState2) {
	Cell c('.');
	ASSERT_EQ(c.state(), '.');
	c.shift_state();
	ASSERT_EQ(c.state(), '*');
}

TEST(Life, Cell_ShiftState3) {
	Cell c('0');
	ASSERT_EQ(c.state(), '0');
	c.shift_state();
	ASSERT_EQ(c.state(), '-');
}

TEST(Life, Cell_ShiftState4) {
	Cell c('-');
	ASSERT_EQ(c.state(), '-');
	c.shift_state();
	ASSERT_EQ(c.state(), '0');
}

TEST(Life, Cell_State1) {
	Cell c('*');
	ASSERT_EQ(c.state(), '*');
}

TEST(Life, Cell_State2) {
	Cell c('0');
	ASSERT_EQ(c.state(), '0');
}

TEST(Life, Cell_State3) {
	Cell c1('*');
	ASSERT_EQ(c1.state(), '*');
	Cell c2(c1);
	ASSERT_EQ(c2.state(), '*');
}

TEST(Life, Cell_Living1) {
	Cell c('*');
	ASSERT_TRUE(c.living());
}

TEST(Life, Cell_Living2) {
	Cell c('.');
	ASSERT_FALSE(c.living());
}

TEST(Life, Cell_Living3) {
	Cell c('0');
	ASSERT_TRUE(c.living());
}

TEST(Life, Cell_Living4) {
	Cell c('-');
	ASSERT_FALSE(c.living());
}

TEST(Life, Cell_GetPointer1) {
	Cell c('*');
	ASSERT_EQ((&c)->state(), '*');
}

TEST(Life, Cell_GetPointer2) {
	Cell c('0');
	ASSERT_EQ((&c)->state(), '0');
}

TEST(Life, Cell_GetPointer3) {
	Cell c1('*');
	ASSERT_EQ((&c1)->state(), '*');
	Cell c2(c1);
	ASSERT_EQ((&c2)->state(), '*');
	ASSERT_NE(&c2, &c1);
}

// ----
// Life
// ----

TEST(Life, Life_Constructor1) {
	stringstream in("ConwayCell\n4\n4\n0\n1\n....\n.**.\n.**.\n....");
	Life<ConwayCell> l(in);
	stringstream out;
	l.print_grid(0, out);
	ASSERT_EQ("Generation = 0, Population = 4.\n....\n.**.\n.**.\n....\n\n", out.str());
}

TEST(Life, Life_Constructor2) {
	stringstream in("FredkinCell\n4\n4\n0\n1\n----\n-00-\n-00-\n----");
	Life<FredkinCell> l(in);
	stringstream out;
	l.print_grid(0, out);
	ASSERT_EQ("Generation = 0, Population = 4.\n----\n-00-\n-00-\n----\n\n", out.str());
}

TEST(Life, Life_Constructor3) {
	stringstream in("Cell\n4\n4\n0\n1\n....\n-**-\n-00-\n----");
	Life<Cell> l(in);
	stringstream out;
	l.print_grid(0, out);
	ASSERT_EQ("Generation = 0, Population = 4.\n....\n-**-\n-00-\n----\n\n", out.str());
}

TEST(Life, Life_RunEvo1) {
	stringstream in("ConwayCell\n5\n5\n1\n1\n.....\n..*..\n..*..\n..*..\n.....");
	Life<ConwayCell> l(in);
	stringstream out;
	l.print_grid(1, out);// test run_evolution within print_grid
	ASSERT_EQ("Generation = 1, Population = 3.\n.....\n.....\n.***.\n.....\n.....\n\n", out.str());
}

TEST(Life, Life_RunEvo2) {
	stringstream in("FredkinCell\n5\n5\n1\n1\n-----\n--00-\n-0-0-\n-00--\n-----");
	Life<FredkinCell> l(in);
	stringstream out;
	l.print_grid(1, out);// test run_evolution within print_grid
	ASSERT_EQ("Generation = 1, Population = 12.\n--00-\n--1-0\n01-10\n0-1--\n-00--\n\n", out.str());
}

TEST(Life, Life_RunEvo3) {
	stringstream in("Cell\n5\n5\n2\n1\n-----\n--00-\n-0-0-\n-00--\n-----");
	Life<Cell> l(in);
	stringstream out;
	l.print_grid(1, out);// test run_evolution within print_grid
	ASSERT_EQ("Generation = 1, Population = 12.\n--00-\n--1-0\n01-10\n0-1--\n-00--\n\n", out.str());
	stringstream out2;
	l.print_grid(2, out2);
	ASSERT_EQ("Generation = 2, Population = 12.\n-0-1-\n0-*-1\n-*-*-\n1-*-0\n-1-0-\n\n", out2.str());
}

TEST(Life, Life_at1) {
	stringstream in("Cell\n5\n5\n2\n1\n-----\n--00-\n-0-0-\n-00--\n-----");
	Life<Cell> l(in);
	ASSERT_EQ(l.at(0).state(), '-');
}

TEST(Life, Life_at2) {
	stringstream in("Cell\n5\n5\n2\n1\n-----\n--00-\n-0-0-\n-00--\n-----");
	Life<Cell> l(in);
	ASSERT_EQ(l.at(7).state(), '0');
}

TEST(Life, Life_at3) {
	stringstream in("Cell\n5\n5\n2\n1\n-----\n--00-\n-0-0-\n-00--\n-----");
	Life<Cell> l(in);
	ASSERT_EQ(l.at(24).state(), '-');
}

TEST(Life, Life_begin1) {
	stringstream in("ConwayCell\n5\n5\n1\n1\n.....\n..*..\n..*..\n..*..\n.....");
	Life<ConwayCell> l(in);
	ASSERT_EQ(l.begin()->state(), '.');
}

TEST(Life, Life_begin2) {
	stringstream in("ConwayCell\n5\n5\n1\n1\n.*...\n..*..\n..*..\n..*..\n.....");
	Life<ConwayCell> l(in);
	ConwayCell* c = l.begin();
	ASSERT_EQ((++c)->state(), '*');
}

TEST(Life, Life_begin3) {
	stringstream in("ConwayCell\n5\n5\n1\n1\n.....\n*.*..\n..*..\n..*..\n.....");
	Life<ConwayCell> l(in);
	ASSERT_EQ((l.begin() + 5)->state(), '.');
}

TEST(Life, Life_end1) {
	stringstream in("ConwayCell\n5\n5\n1\n1\n.....\n..*..\n..*..\n..*..\n.....");
	Life<ConwayCell> l(in);
	ASSERT_EQ((l.end() - 1)->state(), '.');
}

TEST(Life, Life_end2) {
	stringstream in("ConwayCell\n5\n5\n1\n1\n.*...\n..*..\n..*..\n..*..\n.....");
	Life<ConwayCell> l(in);
	ASSERT_EQ((l.end() - 1)->state(), '.');
}

TEST(Life, Life_end3) {
	stringstream in("ConwayCell\n5\n5\n1\n1\n.....\n*.*..\n..*..\n..*..\n*....");
	Life<ConwayCell> l(in);
	ASSERT_EQ((l.end() - 5)->state(), '*');
}
