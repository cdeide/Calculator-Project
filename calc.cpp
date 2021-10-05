/*
Name: Connor Deide
Class: CPSC 122, Section 1
Date Submitted: April 21, 2021
Assignment: Project 13
Description: Part 2 of Calculator Assignment 
To Compile: make
To Execute: ./calc "(121+12)"
*/

#include <iostream>
using namespace std;

#include "calc.h"
#include <cstring>


//Write functions in this order.  Constructor and destructor will be built as the
//functions it invokes are written

Calc::Calc(char* argvIn)
{
  inFix = new char[strlen(argvIn) + 1];
  strcpy(inFix, argvIn);

  stk = new Stack; 
  //Check the tokens
  if (!CheckTokens())
  {
    cout << "Error: expression is not valid" << endl;
    exit(EXIT_FAILURE);
  }
  //Check the parenthesis
  if (!CheckParens())
  {
    cout << "Error: Parenthesis are not balanced" << endl;
    exit(EXIT_FAILURE);
  }
  
  //Invoke MakeValueTbl
  MakeValueTbl();
  //Invoke Parse
  Parse();
  //Invoke InfixToPostfix
  InFixToPostFix();
}

Calc::~Calc()
{
  delete stk;
  stk = NULL;
}

bool Calc::CheckTokens()
{
  int pos = 0;
  char ch = inFix[pos];
  while (ch != '\0')
  {
    if (!isdigit(ch) && ch != '(' && ch != ')' && ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '"')
    {
      return false;
    }
    pos++;
    ch = inFix[pos];
  }
  return true;
}

void Calc::MakeValueTbl()
{
  valueTbl = new int[26];
  for (int i = 0; i < 26; i++)
    valueTbl[i] = 0;
  valueIdx = 0;
}

void Calc::Parse()
{
  char* tmp = new char[strlen(inFix) + 1];
  valueIdx = 0;
  int tmpIdx = 0;
  int tmpIdx2 = 0;
  char ch = inFix[tmpIdx];
  
  while (ch != '\0')
  {
    if (isdigit(ch))
    {
      int last = FindLast(tmpIdx);
      char* digitTmp = new char[last - tmpIdx + 2];
      for (int i = tmpIdx; i <= last; i++)
      {
        digitTmp[i - tmpIdx] = inFix[i];
      }
      digitTmp[last - tmpIdx + 1] = '\0';
      //Fill value table
      valueTbl[valueIdx] = atoi(digitTmp);
      tmp[tmpIdx2] = 'A' + valueIdx;
      tmpIdx += strlen(digitTmp);
      valueIdx++;
      delete digitTmp;
      digitTmp = NULL;
    }
    else
    {
      tmp[tmpIdx2] = inFix[tmpIdx];
      tmpIdx++;
    }
    tmpIdx2++;
    ch = inFix[tmpIdx];
  }
  delete inFix;
  inFix = tmp;
  tmp = NULL;
}

int Calc::FindLast(int cur)
{
  while (inFix[cur] >= '0' && inFix[cur] <= '9')
    cur++;
  return (cur - 1);
}

bool Calc::CheckParens()
{
  int pos = 0;
  char ch = inFix[pos];
  while (ch != '\0')
  {
    if (ch == '(')
      stk->Push(ch);
    if (ch == ')')
    {
      if (stk->IsEmpty())
        return false;
      stk->Pop();
    }
    pos++;
    ch = inFix[pos];
  }
  return stk->IsEmpty();
}

void Calc::DisplayInFix()
{
  int i = 0;
  while (inFix[i] != '\0')
  {
    cout << inFix[i];
    i++;
  }
  cout << endl;
  return;
}

void Calc::InFixToPostFix()
{
  int pos = 0;
  postFix = new char[FindPosLength() + 1];
  for (int i = 0; i < strlen(inFix) ; i++)
  {
    char ch = inFix[i];
    if (ch >= 'A' && ch <= 'Z')
    {
      postFix[pos] = ch;
      pos++;
    }
    if (ch == '(' || isOper(ch))
      stk->Push(ch);
    if (ch == ')')
    {
      while (stk->Peek() != '(')
      {
        postFix[pos] = (char)stk->Peek();
        pos++;
        stk->Pop();
      }
      stk->Pop();
    }
  }
  postFix[pos] = '\0';
}

void Calc::DisplayPostFix()
{
  int i = 0;
  while (postFix[i] != '\0')
  {
    cout << postFix[i];
    i++;
  }
  cout << endl;
  return;
}

int Calc::Evaluate()
{
  valueIdx++;
  for (int i = 0; postFix[i] != '\0'; i++)
  {
    char ch = postFix[i];
    if (ch >= 'A' && ch <= 'Z')
      stk->Push(ch);
    else
    {
      char ch2 = stk->Peek();
      stk->Pop();
      char ch1 = stk->Peek();
      stk->Pop();
      valueTbl[valueIdx] = Comp(ch1, ch2, ch);
      stk->Push(char(valueIdx + 65));
      valueIdx;
    }
  }
  return valueTbl[stk->Peek() - 65];
}

int Calc::Comp(char ch1, char ch2, char oper)
{
  
  int num1 = valueTbl[ch1 - 65];
  int num2 = valueTbl[ch2 - 65];
  if (oper == '+')
    return (num1 + num2);
  if (oper == '-')
    return (num1 - num2);
  if (oper == '*')
    return (num1 * num2);
  if (oper == '/')
    return (num1 / num2);
  else
    exit(EXIT_FAILURE);
}

int Calc::FindPosLength()
{
  int length = 0;
  for (int i = 0; i < strlen(inFix) ; i++)
  {
    if (inFix[i] >= 'A' && inFix[i] <= 'Z' || isOper(inFix[i]))
      length++;
  }
  return length;
}

bool Calc::isOper(char oper)
{
  bool truthVal = 0;
  if (oper == '+' || oper == '-' || oper == '*' || oper == '/')
    truthVal = true;
  return truthVal;
}




