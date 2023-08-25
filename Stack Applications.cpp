#include<iostream>
#include<conio.h>
#include<string>
#include<iomanip>
#include <fstream>
using namespace std;
template<class itemType>
class stack
{//stack class
private:
int top;
int maxStack;
itemType* items;
public:
stack();
stack(int max);
~stack();
int isFull()const;
int isEmpty()const;
void push(itemType newItem);
void pop(itemType& item);
itemType peek();
};
template<class itemType>
stack<itemType >::stack() {
maxStack = 500;
top = -1;
items = new itemType[maxStack];
}
template<class itemType>
stack<itemType >::stack(int max) {
maxStack = max;
top = -1;
items = new itemType[max];
}
template<class itemType>
stack<itemType >::~stack() {
delete[] items;
}
template<class itemType>
int stack<itemType >::isEmpty()const
{
return(top == -1);
}
template<class itemType>
itemType stack<itemType > ::peek()
{
return(items[top]);
}
template<class itemType>
int stack<itemType > ::isFull()const
{
return(top == maxStack - 1);
}
template<class itemType>
void stack<itemType >::push(itemType newItem) {
if (isFull()) {
cout << " stack overflow " << endl; exit(1);
}
top++;
items[top] = newItem;
}
template<class itemType>
void stack<itemType >::pop(itemType& item) {
if (isEmpty()) {
cout << " stack underflow " << endl; exit(1);
}
item = items[top];
top--;
}
//==========================================================================================================
bool isOperand(char c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
{
return true;
}
else
{
return false;
}
}
bool isOperator(char c)
{
if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
{
return true;
}
else
{
return false;
}
}
int prec(char op)
{
if (op == '^')
return 3;
else if (op == '/' || op == '*')
return 2;
else if (op == '+' || op == '-')
return 1;
else
return -1; //return negative
}
float precedence(int a, int b, char op) {//Perform operation on operands
if (op == '+')
return b + a;
else if (op == '-')
return b - a;
else if (op == '*')
return b * a;
else if (op == '/')
return b / a;
else if (op == '^')
return pow(b, a); //find b^a
else
return -1; //return negative
}
float postfixEvaluate(string p)
{//postfix evaluation for results
float op1, op2;
float item;
stack<float> st;
for (int i = 0; i < p.length(); i++)
{
if (p[i] == ' ')
{
p[i]++;
continue;
}
if (isOperand(p[i]))
{
st.push(p[i] - '0');//pushing and converting string
}
else if (isOperator(p[i]))
{
op1 = st.peek();
st.pop(item);//pop last item
op2 = st.peek();
st.pop(item);//pop 2nd last item
st.push(precedence(op1, op2, p[i]));
}
}
return st.peek();//return result
}
bool expressionValidation(string exp)
{//checking for valid and invalid expressions
stack<char> s;
char ch;
for (int i = 0; i < exp.length(); i++)
{
if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
{
// Push the element in the stack
ch = exp[i];
s.push(ch);
continue;//move to the next iteraion and again check the char
}
if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}')
{
switch (exp[i])
{
case ')'://if the top element is [ or { then the expression isn't balanced
ch = s.peek();
s.pop(ch);
if (ch != '(')
return false;
break;
case '}'://if the top element is [ or ( then the expression isn't balanced
ch = s.peek();
s.pop(ch);
if (ch != '{')
return false;
break;
case ']'://if the top element is ( or { then the expression isn't balanced
ch = s.peek();
s.pop(ch);
if (ch != '[')
return false;
break;
}
}
else//if there char is any other then brackets then move to the next iteration
continue;
}
return (s.isEmpty());
}
string infixToPostfix(string exp)
{//convertin the infix to postfix expression
stack<char> s;//empty stack
string postfix; char ch;
for (int i = 0; i < exp.length(); i++)
{
if (exp[i] == ' ')
{//if empty space is encountered increment and continue
exp[i]++;
continue;
}
if (isOperand(exp[i]))
{//if operend is encountered add it to the result
postfix += exp[i];
}
else if (exp[i] == '(')
{
s.push(exp[i]);
}
else if (exp[i] == ')')
{// if ')' is encountered
//pop all the elements until '(' found
while ((s.peek() != '(') && (!s.isEmpty()))
{
postfix += s.peek();
s.pop(ch);
}
s.pop(ch);
}
else if (isOperator(exp[i]))
{
if (s.isEmpty())
{//if the stack is empty push the current operator
s.push(exp[i]);
}
else
{
if ((prec(exp[i]) > prec(s.peek())) || ((prec(exp[i]) == prec(s.peek())) && (exp[i] == '^')))
{//check equal or lower precedence of the operator
 //if peek and current operator '^' have equal prec push into stack
s.push(exp[i]);
}
else
{
while ((!s.isEmpty()) && (prec(exp[i]) <= prec(s.peek())))
{//check higher precedence of the operator
//if peek has higher prec add it to the result and pop
postfix += s.peek();
s.pop(ch);
}
s.push(exp[i]);
}
}
}
}
while (!s.isEmpty())//add all the remaining items in the result
{
postfix += s.peek();
s.pop(ch);
}
return postfix;
}
void display(string p, string li)
{//displaying results on screen
int countop = 0, countopt = 0;
for (int i = 0; i < p.length(); i++)
{// checking for specific conditions
//for postfix evaluation the number of operators in postfix are always 1 less then the operands
if (isOperand(p[i]))
countop++;
else if (isOperator(p[i]))
countopt++;
}
if (countop == countopt + 1) {
cout << " " << infixToPostfix(li) << setw(28) << li << " " << postfixEvaluate(p) << endl;
}
else if (countop <= countopt)
{
cout << " " << p << setw(34) << li << " not enough operands" << endl;
}
else if (countop - 1 >= countopt)
{
cout << " " << p << setw(33) << li << " too many operands" << endl;
}
}
void fileinput()
{//getting data from file
char ch; string post = ""; float res = 0.0;
ifstream myfile("infix.txt");
if (!myfile)
{
cerr << "File not found" << endl;
exit(1);
}
if (myfile.is_open())
{
string line;
cout << " POSTFIX Expression INFIX Equivalent RESULT " << endl;
cout << "==============================================================" << endl << endl;
while (getline(myfile, line))
{//input data line by line from file
if (expressionValidation(line)) {//if the expression is balanced then proceed
post = infixToPostfix(line);
display(post, line);
}
else
{//if the expression is not balanced
cout << " ------ This PARENTHISIZED expression was not valid ------ " << endl;
}
cout << endl;
}
}
myfile.close();
}
//==================DRIVER CODE===================
int main() {
fileinput();
return 0;
}