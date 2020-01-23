/******************************************************************************/
/* Author: 		    Mirit Hadar											  	  */
/* Version: 	    Final			  		                                  */
/* Last update:     22-01-2020						                          */
/******************************************************************************/

#include <iostream>            // cout
#include <unordered_map>       // map

#include "calculator.hpp"      // header file

namespace l1ght
{

using namespace std;

typedef void (*hand_func)(stack<double> &numbersStack_,
                          stack<char> &operatorsStack_,
                          string &str_,
                          size_t &i);

typedef void (*act_func)(stack<double> &numbersStack_,
                         stack<char> &operatorsStack_);                     

// Global data structures
hand_func g_lut_handler[256];
act_func g_lut_action[256];
unordered_map<string,double> g_mapOfNums;

// Global variables
double g_tmpNumToPushToStack = -1;
const unsigned char FIRST_ASCII_LETTER = 65;
const unsigned char LAST_ASCII_LETTER = 90;

// Handle Func
class Handler : private Uncopyable
{
public:
    // Ctors
    explicit Handler() = default;
    ~Handler() = default;

    // Funcs
	static void AddOrReduce(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void MultiplyOrDivide(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void OpenBracket(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void CloseBracket(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
	static void Num(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void Space(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void End(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);

private:
    //Helper Funcs
    static void UpdateNumbersStack(stack<double> &numbersStack_);
    static void ExecuteTopOperator(stack<double> &numbersStack_, stack<char> &operatorsStack_);
};

// Executing Funcs
class Executer : public Uncopyable
{
public:
    // Ctors
    explicit Executer() = default;
    ~Executer() = default;

    // Funcs
	static void Add(stack<double> &numbersStack_, stack<char> &operatorsStack_);
    static void Reduce(stack<double> &numbersStack_, stack<char> &operatorsStack_);
	static void Divide(stack<double> &numbersStack_, stack<char> &operatorsStack_);
	static void Multiply(stack<double> &numbersStack_, stack<char> &operatorsStack_);
};

// Static Func Declaration
template <typename T>
static stack<T> InitStack();
static void InitHelperMaps();
static double ConvertStrToNum(string str_);
static size_t FindNextPos(string str_, size_t i);

Calculator::Calculator()
    : m_numbersStack(InitStack<double>()),
      m_operatorsStack(InitStack<char>())
{
    InitHelperMaps();
}

/*************************************** Calculators Definition ************************************/
vector<double> Calculator::Calculate(const char fileName_[])
{
    Parser p;
    vector<string> strExperssions = p.Parse(fileName_);
    vector<double> results;

    vector<string>::iterator firstExpression = strExperssions.begin();
    vector<string>::iterator lastExpression = strExperssions.end();

    // Iterate over all experssions and return there results
    for (vector<string>::iterator it = firstExpression;
        (it != lastExpression) && !(static_cast<string>(*it).empty()); ++it)
    {
        results.push_back(Execute(*it));
    }

    return results;
}

double Calculator::Execute(string str_)
{
    size_t lenStr = str_.length();
    size_t i = 0;

    // Iterate over string, convert words to nums and calculate
    while (i < lenStr)
    {
        g_lut_handler[static_cast<unsigned char>(str_[i])](m_numbersStack, m_operatorsStack, str_, i);
    }

    // Handle '\0' at end of string
    Handler::End(m_numbersStack, m_operatorsStack, str_, i);

    double result = m_numbersStack.top();
    m_numbersStack.pop();

    return result;
}

/**************************************** Handler Definition ***************************************/
void Handler::AddOrReduce(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    UpdateNumbersStack(numbersStack_);

    // Perform initially arithmetic actions with priority and former actions with similar priority
    while(!(operatorsStack_.empty()) && operatorsStack_.top() != '(')
    {
        ExecuteTopOperator(numbersStack_, operatorsStack_);
    }

    operatorsStack_.push(str_[i]);

    ++i;
}

void Handler::MultiplyOrDivide(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    UpdateNumbersStack(numbersStack_);
    
    // Perform initially former actions with similar priority
    while (!(operatorsStack_.empty()) &&
                ((operatorsStack_.top() == '/') || (operatorsStack_.top() == '*')))
    {
        ExecuteTopOperator(numbersStack_, operatorsStack_);
    }

    operatorsStack_.push(str_[i]);

    ++i;
}

void Handler::OpenBracket(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    operatorsStack_.push(str_[i]);

    ++i;
}

void Handler::CloseBracket(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    UpdateNumbersStack(numbersStack_);

    // Perform arithmetic placed within the brackets
    while (operatorsStack_.top() != '(')
    {
        ExecuteTopOperator(numbersStack_, operatorsStack_);
    }

    operatorsStack_.pop();
    ++i;
    
}

void Handler::Num(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    // Find next space or closing bracket position
    size_t nextPos = FindNextPos(str_, i);
    double num = ConvertStrToNum(str_.substr(i, 3));

    // For multi-digit numbers
    if (-1 != g_tmpNumToPushToStack)
    {
        g_tmpNumToPushToStack *= 10;
        g_tmpNumToPushToStack += num;
    }
    else
    {
        g_tmpNumToPushToStack = num;
    }

    i = nextPos;
}

void Handler::UpdateNumbersStack(stack<double> &numbersStack_)
{
    // Declaring finishing to read a single number and pushing it to stack
    if (-1 != g_tmpNumToPushToStack)
    {
        numbersStack_.push(g_tmpNumToPushToStack);
        g_tmpNumToPushToStack = -1;
    }
}

void Handler::ExecuteTopOperator(stack<double> &numbersStack_, stack<char> &operatorsStack_)
{
    g_lut_action[static_cast<unsigned char>(operatorsStack_.top())](numbersStack_, operatorsStack_);
}

void Handler::Space(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    ++i;
}

void Handler::End(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    UpdateNumbersStack(numbersStack_);

    // Perform actions if remain in operator's stack
    while (!operatorsStack_.empty())
    {
        g_lut_action[static_cast<unsigned char>(operatorsStack_.top())](numbersStack_, operatorsStack_);   
    }
}

/*************************************** Executer Definition ***************************************/
void Executer::Add(stack<double> &numbersStack_, stack<char> &operatorsStack_)
{
    double result = numbersStack_.top();
    numbersStack_.pop();
    result = numbersStack_.top() + result;
    numbersStack_.pop();

    // Push in the resault
    numbersStack_.push(result);

    // Pop out the '+' operator
    operatorsStack_.pop();
}

void Executer::Reduce(stack<double> &numbersStack_, stack<char> &operatorsStack_)
{
    double result = numbersStack_.top();
    numbersStack_.pop();
    result = numbersStack_.top() - result;
    numbersStack_.pop();

    // Push in the resault
    numbersStack_.push(result);

    // Pop out the '-' operator
    operatorsStack_.pop();
}

void Executer::Divide(stack<double> &numbersStack_, stack<char> &operatorsStack_)
{
    double result = numbersStack_.top();
    numbersStack_.pop();
    result = numbersStack_.top() / result;
    numbersStack_.pop();

    // Push in the resault
    numbersStack_.push(result);

    // Pop out the '/' operator
    operatorsStack_.pop();
}

void Executer::Multiply(stack<double> &numbersStack_, stack<char> &operatorsStack_)
{
    double result = numbersStack_.top();
    numbersStack_.pop();
    result = numbersStack_.top() * result;
    numbersStack_.pop();

    // Push in the resault
    numbersStack_.push(result);

    // Pop out the '*' operator
    operatorsStack_.pop();
}

/************************************** Static functions *******************************************/

// Assigning stacks to members of Calculator's class. for Ctor's use
template <typename T>
static stack<T> InitStack()
{
    stack<T> s;

    return s;
}

// Init global LUTs and map
static void InitHelperMaps()
{
    // Assign to LUT Functions that handle operators
    g_lut_handler['+'] = Handler::AddOrReduce;
    g_lut_action['+'] = Executer::Add;

    g_lut_handler['-'] = Handler::AddOrReduce;
    g_lut_action['-'] = Executer::Reduce;

    g_lut_handler['/'] = Handler::MultiplyOrDivide;
    g_lut_action['/'] = Executer::Divide;

    g_lut_handler['*'] = Handler::MultiplyOrDivide;
    g_lut_action['*'] = Executer::Multiply;

    g_lut_handler['('] = Handler::OpenBracket;
    g_lut_handler[')'] = Handler::CloseBracket;

    g_lut_handler[' '] = Handler::Space;
    g_lut_handler['\0'] = Handler::End;

    // Assign to LUT Functions that handle numbers in letters
    for (size_t i = FIRST_ASCII_LETTER; i <= LAST_ASCII_LETTER; ++i)
    {
        g_lut_handler[i] = Handler::Num;
    }
    
    // Assign to map the numeric value of each key number name
    g_mapOfNums["Zer"] = 0;
    g_mapOfNums["One"] = 1;
    g_mapOfNums["Two"] = 2;
    g_mapOfNums["Thr"] = 3;
    g_mapOfNums["Fou"] = 4;
    g_mapOfNums["Fiv"] = 5;
    g_mapOfNums["Six"] = 6;
    g_mapOfNums["Sev"] = 7;
    g_mapOfNums["Eig"] = 8;
    g_mapOfNums["Nin"] = 9;
}

static double ConvertStrToNum(string str_)
{
    return g_mapOfNums[str_];
}

static size_t FindNextPos(string str_, size_t i)
{
    size_t indexOfNextPos = str_.find(' ', i);
    if ((indexOfNextPos > str_.length()) || (str_[indexOfNextPos - 1] == ')'))
    {
        indexOfNextPos = str_.find(')', i);
    }

    return indexOfNextPos;
}

} // namespace l1ght
