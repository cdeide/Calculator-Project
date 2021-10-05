/*
Name: Connor Deide
Class: CPSC 122, Section 1
Date Submitted: April 9, 2021
Assignment: Project 12
Description: Part 1 of Calculator Assignment 
To Compile: make
To Execute: ./calc "(121+12)"
*/

#include <iostream>
using namespace std;

#include "calc.h"

int main(int argc, char* argv[])
{
  //Start test of constructor
  /*
  Calc* C = new Calc(argv[1]);
  
  cout << "Infix after being parsed: ";
  C->DisplayInFix();
  
  delete C;
  return 0;
  */
  //End test of constructor
  
  
  //Start test of DisplayInFix
  /*
  Calc* C = new Calc(argv[1]);
  
  cout << "Infix: ";
  C->DisplayInFix();
  
  cout << "PostFix: ";
  C->DisplayPostFix();
  
  delete C;
  return 0;
  */
  //End test of DisplayInFix
  
  //Start test of Evaluate
  
  Calc* C = new Calc(argv[1]);
  
  cout << "Infix: ";
  C->DisplayInFix();
  
  cout << "Postfix: ";
  C->DisplayPostFix();
  
  cout << "Evaluated Expression: ";
  cout << C->Evaluate() << endl;
  
  delete C;
  return 0;
  
  //End test of Evaluate
}
