/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* version: 	Final			  		                                      */
/* Last update: 							                                  */
/******************************************************************************/

#include <iostream>            // cout
#include <unordered_map>       // map
#include <unistd.h>			   // sleep
#include "calculator.hpp"      // header file

namespace l1ght
{

using namespace std;

template <typename T>
static stack<T> InitStack()
{
    stack<T> s;

    return s;
}

stack<double> Calculator::m_numbersStack = InitStack<double>();
stack<char> Calculator::m_operatorsStack = InitStack<char>();

// Handle Func
class Handler : private Uncopyable
{
public:
	static void AddOrReduceHandle(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
	static void NumHandle(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void SpaceHandle(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void EndHandle(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void MultiplyOrDivideHandle(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void OpenBracketHandle(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void CloseBracketHandle(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);

private:
    static void UpdateNumbersStack(stack<double> &numbersStack_);
    static void ExecuteTopOperator(stack<double> &numbersStack_, stack<char> &operatorsStack_);
};

// Act Funcs
class Executer : public Uncopyable
{
public:
	static void AddExecute(stack<double> &numbersStack_, stack<char> &operatorsStack_);
    static void ReduceExecute(stack<double> &numbersStack_, stack<char> &operatorsStack_);
	static void DivideExecute(stack<double> &numbersStack_, stack<char> &operatorsStack_);
	static void MultiplyExecute(stack<double> &numbersStack_, stack<char> &operatorsStack_);
};

static void PrintAndEmptyMyStacks(stack<double> &nums_, stack<char> &operators_);
static void InitMaps();
static double ConvertStrToNum(string str_);
static size_t FindNextPos(string str_, size_t i);

typedef void (*hand_func)(stack<double> &numbersStack_,
                          stack<char> &operatorsStack_,
                          string &str_,
                          size_t &i);

typedef void (*act_func)(stack<double> &numbersStack_,
                         stack<char> &operatorsStack_);

hand_func g_lut_handler[256];
act_func g_lut_action[256];
unordered_map<string,double> g_mapOfNums;

bool g_lastTokenWasNum = 0;
double g_tmpNumToPushToStack = -1;

const unsigned char ZERO_ASCII = 48;
const unsigned char NINE_ASCII = 57;
const unsigned char A_ASCII = 65;
const unsigned char Z_ASCII = 90;
const unsigned char SPACE_ASCII = 32;
const size_t NUM_OF_ASCII_CHARS = 256;
//const size_t NUM_OF_LETTERS_FOR

Calculator::Calculator()
{
    InitMaps();
}

static void InitMaps()
{
    // m_numbersStack = InitStack<int>();
    // m_operatorsStack = InitStack<char>();

    g_lut_handler['+'] = Handler::AddOrReduceHandle;
    g_lut_action['+'] = Executer::AddExecute;

    g_lut_handler['-'] = Handler::AddOrReduceHandle; //repare!!!!!!!!!!!!!
    g_lut_action['-'] = Executer::ReduceExecute;

    g_lut_handler['/'] = Handler::MultiplyOrDivideHandle;
    g_lut_action['/'] = Executer::DivideExecute;

    g_lut_handler['*'] = Handler::MultiplyOrDivideHandle;
    g_lut_action['*'] = Executer::MultiplyExecute;

    g_lut_handler['('] = Handler::OpenBracketHandle;
    g_lut_handler[')'] = Handler::CloseBracketHandle;

    g_lut_handler[' '] = Handler::SpaceHandle;
    g_lut_handler['\0'] = Handler::EndHandle;

    for (size_t i = A_ASCII; i <= Z_ASCII; ++i)
    {
        g_lut_handler[i] = Handler::NumHandle;
    }
    
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

vector<double> Calculator::Calculate(const char fileName_[])
{
    vector<string> vecOfStrings = Parser::Parse(fileName_);
    vector<double> vecOfResults;

    for (vector<string>::iterator it = vecOfStrings.begin();
        (it != vecOfStrings.end()) && !(static_cast<string>(*it).empty());
                                                                     ++it)
    {
        vecOfResults.push_back(Execute(*it));
    }

    return vecOfResults;
}

double Calculator::Execute(string str_)
{
    size_t lenStr = str_.length();
    size_t i = 0;

    while (i < lenStr) //Check end
    {
        g_lut_handler[static_cast<unsigned char>(str_[i])](m_numbersStack, m_operatorsStack, str_, i);
        //sleep(1);
    }

    Handler::EndHandle(m_numbersStack, m_operatorsStack, str_, i);

    double result = m_numbersStack.top();
    m_numbersStack.pop();
    cout << "result = " << result << endl;

    return result;
}

static void PrintAndEmptyMyStacks(stack<double> &nums_, stack<char> &operators_)
{
    cout << "numbers:" << endl;
    while(!(nums_.empty()))
    {
        cout << nums_.top() << endl;
        nums_.pop();
    }

    cout << "operators:" << endl;
    while(!(operators_.empty()))
    {
        cout << operators_.top() << endl;
        operators_.pop();
    }
}

double ConvertStrToNum(string str_)
{
    return g_mapOfNums[str_];
}

size_t FindNextPos(string str_, size_t i)
{
    //cout << "substr: " << str_.substr(i, str_.length()) << endl;
    size_t indexOfNextPos = str_.find(' ', i);
    //cout << "!!! " << indexOfNextSpace << " !!!";
    if ((indexOfNextPos > str_.length()) || (str_[indexOfNextPos - 1] == ')'))
    {
        indexOfNextPos = str_.find(')', i);
    }

    return indexOfNextPos;
}

// Handler Funcs
void Handler::AddOrReduceHandle(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    UpdateNumbersStack(numbersStack_);

    while(!(operatorsStack_.empty()) && operatorsStack_.top() != '(')
    {
        ExecuteTopOperator(numbersStack_, operatorsStack_);
    }

    operatorsStack_.push(str_[i]);

    ++i;
}

void Handler::MultiplyOrDivideHandle(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    UpdateNumbersStack(numbersStack_);
    
    while (!(operatorsStack_.empty()) &&
                ((operatorsStack_.top() == '/') || (operatorsStack_.top() == '*')))
    {
        ExecuteTopOperator(numbersStack_, operatorsStack_);
    }

    operatorsStack_.push(str_[i]);

    ++i;
}

void Handler::OpenBracketHandle(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    operatorsStack_.push(str_[i]);
    cout << "openning : " << str_[i] << endl;
    ++i;
}

void Handler::CloseBracketHandle(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    UpdateNumbersStack(numbersStack_);

    while (operatorsStack_.top() != '(')
    {
        ExecuteTopOperator(numbersStack_, operatorsStack_);
        cout << "operatorsStack_.top() = " << operatorsStack_.top() << endl;
    }

    operatorsStack_.pop();
    ++i;
    
}

void Handler::NumHandle(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    size_t nextPos = FindNextPos(str_, i);
    //cout << nextPos << " just spaces: " << str_[nextPos] << endl;
    double num = ConvertStrToNum(str_.substr(i, 3));

    if (g_lastTokenWasNum)
    {
        g_tmpNumToPushToStack *= 10;
        g_tmpNumToPushToStack += num;
    }
    else
    {
        g_tmpNumToPushToStack = num;
        g_lastTokenWasNum = true;
    }

    i = nextPos;
}

void Handler::UpdateNumbersStack(stack<double> &numbersStack_)
{
    if (-1 != g_tmpNumToPushToStack)
    {
        g_lastTokenWasNum = false;
        numbersStack_.push(g_tmpNumToPushToStack);
        g_tmpNumToPushToStack = -1;
    }
}

void Handler::ExecuteTopOperator(stack<double> &numbersStack_, stack<char> &operatorsStack_)
{
    g_lut_action[static_cast<unsigned char>(operatorsStack_.top())](numbersStack_, operatorsStack_);
}

void Handler::SpaceHandle(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    ++i;
}

void Handler::EndHandle(stack<double> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    UpdateNumbersStack(numbersStack_);

    while (!operatorsStack_.empty())
    {
        g_lut_action[static_cast<unsigned char>(operatorsStack_.top())](numbersStack_, operatorsStack_);   
    }

    cout << "end" << endl;
    ++i;
}

// Executer Funcs
void Executer::AddExecute(stack<double> &numbersStack_, stack<char> &operatorsStack_)
{
    double result = numbersStack_.top();
    numbersStack_.pop();
    result = numbersStack_.top() + result;
    numbersStack_.pop();

    // Push in the resault
    numbersStack_.push(result);

    // Pop out the used operator
    operatorsStack_.pop();
}

void Executer::ReduceExecute(stack<double> &numbersStack_, stack<char> &operatorsStack_)
{
    double result = numbersStack_.top();
    numbersStack_.pop();
    result = numbersStack_.top() - result;
    numbersStack_.pop();

    //cout << "ReduceExecute: result = " << result << endl;
    // Push in the resault
    numbersStack_.push(result);

    // Pop out the used operator
    operatorsStack_.pop();
}

void Executer::DivideExecute(stack<double> &numbersStack_, stack<char> &operatorsStack_)
{
    double result = numbersStack_.top();
    numbersStack_.pop();
    result = numbersStack_.top() / result;
    numbersStack_.pop();

    //cout << "ReduceExecute: result = " << result << endl;
    // Push in the resault
    numbersStack_.push(result);

    // Pop out the used operator
    operatorsStack_.pop();
}

void Executer::MultiplyExecute(stack<double> &numbersStack_, stack<char> &operatorsStack_)
{
    double result = numbersStack_.top();
    numbersStack_.pop();
    result = numbersStack_.top() * result;
    numbersStack_.pop();

    //cout << "ReduceExecute: result = " << result << endl;
    // Push in the resault
    numbersStack_.push(result);

    // Pop out the used operator
    operatorsStack_.pop();
}

}//namespace l1ght
