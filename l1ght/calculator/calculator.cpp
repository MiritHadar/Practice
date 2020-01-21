/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* version: 	Final			  		                                      */
/* Last update: 							                                  */
/******************************************************************************/

#include <iostream>            // cout
#include <unordered_map>       // map
//#include <unistd.h>			   // sleep
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

// Stack<int> Calculator::m_numbersStack(InitStack<int>());
// Stack<char> Calculator::m_operatorsStack(InitStack<char>());

// stack<int> Calculator::m_numbersStack = InitStack<int>();
// stack<char> Calculator::m_operatorsStack = InitStack<char>();

stack<int> m_numbersStack;
stack<char> m_operatorsStack;

// Handle Func
class Handler : private Uncopyable
{
public:
	static void AddHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
	static void NumHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void SpaceHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void EndHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
};

// Act Funcs
class Executer : public Uncopyable
{
public:
	static void AddExecute(stack<int> &numbersStack_, stack<char> &operatorsStack_);
};

static void PrintAndEmptyMyStacks(stack<int> &nums_, stack<char> &operators_);
static void InitMaps();
 
typedef void (*hand_func)(stack<int> &numbersStack_,
                          stack<char> &operatorsStack_,
                          string &str_,
                          size_t &i);

typedef void (*act_func)(stack<int> &numbersStack_,
                         stack<char> &operatorsStack_);

hand_func g_lut_handler[256];
act_func g_lut_action[256];
unordered_map<string,int> g_mapOfNums;

const unsigned char ZERO_ASCII = 48;
const unsigned char NINE_ASCII = 57;
const unsigned char OPENNING_BRACKET = 40;
const unsigned char CLOSING_BRACKET = 41;
const unsigned char OPERATORS_ASCII = 48;
const unsigned char SPACE_ASCII = 32;
const size_t NUM_OF_ASCII_CHARS = 256;

Calculator::Calculator()
    // : m_numbersStack(InitStack<int>()),
    //   m_operatorsStack(InitStack<char>())
{
    m_numbersStack = InitStack<int>();
    m_operatorsStack = InitStack<char>();
    InitMaps();
}

static void InitMaps()
{
    g_lut_handler['+'] = Handler::AddHandle;
    g_lut_action['+'] = Executer::AddExecute;

    // g_lut_handler['-'] = ReduceFunc;
    // g_lut_action['-'] = ReduceActFunc;

    // g_lut_handler['/'] = DivideFunc;
    // g_lut_action['/'] = DivideActFunc;

    // g_lut_handler['*'] = MultiplyFunc;
    // g_lut_action['*'] = MultiplyActFunc;

    // g_lut_handler['('] = OpenParenthesisFunc;
    // g_lut_action[')'] = CloseParenthesisFunc;
    g_lut_handler[' '] = Handler::SpaceHandle;
    //g_lut_handler['\0'] = Handler::EndHandle;

    for (size_t i = ZERO_ASCII; i <= NINE_ASCII; ++i)
    {
        g_lut_handler[i] = Handler::NumHandle;
    }
    
    g_mapOfNums["One"] = 1;
}

vector<double> Calculator::Calculate(const char fileName_[])
{
    vector<string> vecOfStrings = Parser::Parse(fileName_);
    vector<double> vecOfResults;

    for (vector<string>::iterator it = vecOfStrings.begin(); it != vecOfStrings.end(); ++it)
    {
        cout << "it: " << *it << endl;
        vecOfResults.push_back(Execute(*it));
    }

    return vecOfResults;
}

double Calculator::Execute(string str_)
{
    // for (auto it = str_.cbegin(); it != str_.cend(); ++it)
    // {
    //     cout << "sign: " << *const_cast<char*>(it.base()) << endl;
    //     g_lut_handler[static_cast<unsigned char>(*const_cast<char*>(it.base()))](m_numbersStack, m_operatorsStack, it);
    // }

    size_t lenStr = str_.length();
    size_t i = 0;
    while (i < lenStr)
    {
        g_lut_handler[static_cast<unsigned char>(str_[i])](m_numbersStack, m_operatorsStack, str_, i);
    }
    
    double result = m_numbersStack.top();
    cout << "result = " << result << endl;
    PrintAndEmptyMyStacks(m_numbersStack, m_operatorsStack);

    return result;
}

static void PrintAndEmptyMyStacks(stack<int> &nums_, stack<char> &operators_)
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

// static void InitMaps()
// {
//     for (size_t i = 0; i < 256; ++i)
//     {
        
//     }
// }

int Calculator::ConvertToNum(string::const_iterator it)
{
    return 0;
}

// Handle Funcs
void Handler::AddHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    while(!(operatorsStack_.empty()) && operatorsStack_.top() != '(')
    {
        g_lut_handler[static_cast<unsigned char>(operatorsStack_.top())](numbersStack_, operatorsStack_, str_, i);
    }

    operatorsStack_.push(str_[i]);
    ++i;
}

// Act Funcs
void Executer::AddExecute(stack<int> &numbersStack_, stack<char> &operatorsStack_)
{

}

void Handler::NumHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    //jump to end of num
    //int num = strtod(&(str_[i]), nullptr);
    size_t nextSpacePos = (str_.substr(i, str_.length())).find(' ', i);
    cout << str_.substr(i, 3) << endl;
    int num = g_mapOfNums[str_.substr(i, 3)];
    cout << "num = " << num << endl;
    numbersStack_.push(num);
    i = nextSpacePos;
}

void Handler::SpaceHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    ++i;
}

void Handler::EndHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    // while (!operatorsStack_.IsEmpty())
    // {
    //     g_lut_action[static_cast<unsigned char>(operatorsStack_.Top())](numbersStack_, operatorsStack_, it);   
    // }
    cout << "end" << endl;
}


}//namespace l1ght
