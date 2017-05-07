#include "ExprTree.h"
#include <sstream>
#include <stack>

/*
 * Helper function that tests whether a string is a non-negative integer.
 */

bool isdigit(const char & c){

  switch (c) {
  case '0' :
  case '1' :
  case '2' :
  case '3' :
  case '4' :
  case '5' :
  case '6' :
  case '7' :
  case '8' :
  case '9' : return true;
  }

  return false;
   
}

bool is_number(const std::string & s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

/*
 * Helper function that converts a string to an int.
 */
int to_number(const std::string & s){
  return atoi(s.c_str());
}

/*
 * Helper function that converts a number to a string.
 */
string to_string(const int & n){
  std::stringstream stream;
  stream << n;
  return stream.str();
}

/*
 * Helper function that creates a TreeNode with the appropriate operator
 * when given a string that's "+", "-", "*" or "/". If the string is wrong
 * it gives a NoOp value.
 */
TreeNode * createOperatorNode(const string & op){

  if (op == "+") return new TreeNode(Plus);
  if (op == "-") return new TreeNode(Minus);
  if (op == "*") return new TreeNode(Times);
  if (op == "/") return new TreeNode(Divide);
  return new TreeNode(NoOp);

}

/*
 * Basic constructor that sets up an empty Expr Tree.
 */
ExprTree::ExprTree(){
  root = NULL;
  _size = 0;
}

/*
 * Constructor that takes a TreeNode and sets up an ExprTree with that node at the root.
 */
ExprTree::ExprTree(TreeNode * r){
  root = r;
  _size = 0;
  
  std::stack<TreeNode *> s;
  s.push(root);
  
  while (s.size() > 0) {
    TreeNode * n = s.top();
    s.pop();
    
    if (n != NULL) {
      s.push(n->getLeftChild());
      s.push(n->getRightChild());
      _size++;
    }
  }
}

/*
 * Destructor to clean up the tree.
 */
ExprTree::~ExprTree(){
  std::stack<TreeNode *> s;
  s.push(root);
  
  while (s.size() > 0) {
    TreeNode * n = s.top();
    s.pop();
    
    if (n != NULL) {
      s.push(n->getLeftChild());
      s.push(n->getRightChild());
      delete n;
    }
  }
}

/*
 * This function takes a string representing an arithmetic expression and breaks
 * it up into components (number, operators, parentheses).
 * It returns the broken up expression as a vector of strings.
 */
vector<string> ExprTree::tokenise(string expression){
  vector<string> ret;
  string temp = "";
  
  for (int i = 0; i < expression.size(); i++) {
    if (!isdigit(expression[i])) {
      if (temp.size() > 0) {
        ret.push_back(temp);
        temp.clear();
      }
      if (expression[i] != ' ') {
        string oper(1, expression[i]);
        ret.push_back(oper);
      }
    } else {
      temp.push_back(expression[i]);
    }
  }
  
  if (temp.size() > 0) {
    ret.push_back(temp);
  }
  
  return ret;
}

/*
 * This function will return the priority of operator
 * the higher the more precedence
 */
int getPrecdence(string o){
  if (o == "+" || o == "-") return 1;
  else if (o == "*" || o == "/") return 2;
  else return 3;
}

/*
 * This function will pop one operator and two Node and union them into one node and push it to stack s
 */
void popOperator(std::stack<TreeNode *> &s, std::stack<string> &sOperator) {
  TreeNode * rhs = s.top();
  s.pop();
  
  TreeNode * lhs = s.top();
  s.pop();
  
  TreeNode * n = createOperatorNode(sOperator.top());
  sOperator.pop();
  
  n->setLeftChild(lhs);
  n->setRightChild(rhs);
  
  s.push(n);
}

/*
 * This function takes a vector of strings representing an expression (as produced
 * by tokenise(string), and builds an ExprTree representing the same expression.
 */

ExprTree ExprTree::buildTree(vector<string> tokens){
  std::stack<TreeNode *> s;
  std::stack<string> sOperator;
  
  for (int i = 0; i < tokens.size(); i++) {
    if (is_number(tokens[i])) {
      s.push(new TreeNode(to_number(tokens[i])));
    } else {
      if (sOperator.size() > 0) {
        if (getPrecdence(sOperator.top()) >= getPrecdence(tokens[i]) && sOperator.top() != "(") {
          popOperator(s, sOperator);
        }
      }
      
      if (tokens[i] != ")") {
        sOperator.push(tokens[i]);
      } else {
        while (sOperator.top() != "(") {
          popOperator(s, sOperator);
        }
        
        sOperator.pop();
      }
    }
  }
  
  while (sOperator.size() > 0) {
    popOperator(s, sOperator);
  }
  
  ExprTree ret = *(new ExprTree(s.top()));
  return ret;
}

/*
 * This function takes a TreeNode and does the maths to calculate
 * the value of the expression it represents.
 */
int ExprTree::evaluate(TreeNode * n){
  if (!n->isOperator()) {
    return n->getValue();
  }
  
  int lhs = evaluate(n->getLeftChild());
  int rhs = evaluate(n->getRightChild());
  
  switch (n->getOperator()) {
    case Plus:
      return lhs + rhs;
    case Minus:
      return lhs - rhs;
    case Times:
      return lhs * rhs;
    case Divide:
      return lhs / rhs;
    default:
      return 0;
  }
}

/*
 * When called on an ExprTree, this function calculates the value of the
 * expression represented by the whole tree.
 */
int ExprTree::evaluateWholeTree(){
  return evaluate(root);
}

/*
 * This function will return prefixOrder String start from node n
 */
string preTraversal(TreeNode * n) {
  if (!n->isOperator()) {
    return to_string(n->getValue());
  }
  
  return n->toString() + " " + preTraversal(n->getLeftChild()) + " " + preTraversal(n->getRightChild());
}

/*
 * Given an ExprTree t, this function returns a string
 * that represents that same expression as the tree in
 * prefix notation.
 */
string ExprTree::prefixOrder(const ExprTree & t){
  return preTraversal(t.root);
}

/*
 * This function will return infixOrder String start from node n
 */
string inTraversal(TreeNode * n) {
  if (!n->isOperator()) {
    return to_string(n->getValue());
  }
  
  return inTraversal(n->getLeftChild()) + " " + n->toString() + " " + inTraversal(n->getRightChild());
}

/*
 * Given an ExprTree t, this function returns a string
 * that represents that same expression as the tree in
 * infix notation.
 */
string ExprTree::infixOrder(const ExprTree & t){
  return inTraversal(t.root);
}

/*
 * This function will return postfixOrder String start from node n
 */
string postTraversal(TreeNode * n) {
  if (!n->isOperator()) {
    return to_string(n->getValue());
  }
  
  return postTraversal(n->getLeftChild()) + " " + postTraversal(n->getRightChild()) + " " + n->toString();
}

/*
 * Given an ExprTree t, this function returns a string
 * that represents that same expression as the tree in
 * postfix notation.
 */
string ExprTree::postfixOrder(const ExprTree & t){
  return postTraversal(t.root);
}

/*
 * Returns the size of the tree. (i.e. the number of nodes in it)
 */
int ExprTree::size(){ return _size; }

/*
 * Returns true if the tree contains no nodes. False otherwise.
 */
bool ExprTree::isEmpty(){ return _size == 0; }

TreeNode * ExprTree::getRoot(){ return root; }
