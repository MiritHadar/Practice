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

stack<int> Calculator::m_numbersStack = InitStack<int>();
stack<char> Calculator::m_operatorsStack = InitStack<char>();

// Handle Func
class Handler : private Uncopyable
{
public:
	static void AddHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
	static void NumHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void SpaceHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void EndHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void ReduceHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void DivideHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void MultiplyHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void OpenBracketHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
    static void CloseBracketHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i);
};

// Act Funcs
class Executer : public Uncopyable
{
public:
	static void AddExecute(stack<int> &numbersStack_, stack<char> &operatorsStack_);
    static void ReduceExecute(stack<int> &numbersStack_, stack<char> &operatorsStack_);
	static void DivideExecute(stack<int> &numbersStack_, stack<char> &operatorsStack_);
	static void MultiplyExecute(stack<int> &numbersStack_, stack<char> &operatorsStack_);
};

static void PrintAndEmptyMyStacks(stack<int> &nums_, stack<char> &operators_);
static void InitMaps();
int ConvertStrIntoNum(string str_);
size_t FindNextSapcePos(string str_, size_t i);

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
const unsigned char A_ASCII = 65;
const unsigned char Z_ASCII = 90;
//const unsigned char OPENNING_BRACKET = 40;
//const unsigned char CLOSING_BRACKET = 41;
//const unsigned char OPERATORS_ASCII = 48;
const unsigned char SPACE_ASCII = 32;
const size_t NUM_OF_ASCII_CHARS = 256;

Calculator::Calculator()
{
    InitMaps();
}

static void InitMaps()
{
    // m_numbersStack = InitStack<int>();
    // m_operatorsStack = InitStack<char>();

    g_lut_handler['+'] = Handler::AddHandle;
    g_lut_action['+'] = Executer::AddExecute;

    g_lut_handler['-'] = Handler::ReduceHandle;
    g_lut_action['-'] = Executer::ReduceExecute;

    g_lut_handler['/'] = Handler::DivideHandle;
    g_lut_action['/'] = Executer::DivideExecute;

    g_lut_handler['*'] = Handler::MultiplyHandle;
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
        //cout << "derefferncing......." << endl;
        //cout << "it: " << *it << "  done *it" << endl;
        vecOfResults.push_back(Execute(*it));
        
        //cout << "done executing" << endl;
    }

    return vecOfResults;
}

double Calculator::Execute(string str_)
{
    size_t lenStr = str_.length();
    size_t i = 0;

    while (i < lenStr)
    {
        g_lut_handler[static_cast<unsigned char>(str_[i])](m_numbersStack, m_operatorsStack, str_, i);
    }

    while (!(m_operatorsStack.empty()))
    {
        g_lut_action[static_cast<unsigned char>(m_operatorsStack.top())](m_numbersStack, m_operatorsStack);
    }

    double result = m_numbersStack.top();
    m_numbersStack.pop();
    cout << "result = " << result << endl;

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

int ConvertStrIntoNum(string str_)
{
    //cout << "g_mapOfNums[str_] = " << g_mapOfNums[str_] << endl;

    //sleep(1);

    return g_mapOfNums[str_];
}

size_t FindNextSapcePos(string str_, size_t i)
{
    //cout << "substr: " << str_.substr(i, str_.length()) << endl;
    size_t indexOfNextSpace = str_.find(' ', i);
    //cout << "!!! " << indexOfNextSpace << " !!!";

    return indexOfNextSpace;
}

// Handler Funcs
void Handler::AddHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    while(!(operatorsStack_.empty()) && operatorsStack_.top() != '(')
    {
        cout << "got + " << endl;
        g_lut_action[static_cast<unsigned char>(operatorsStack_.top())](numbersStack_, operatorsStack_);
    }

    operatorsStack_.push(str_[i]);

    ++i;
}

void Handler::ReduceHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    while(!(operatorsStack_.empty()) && operatorsStack_.top() != '(')
    {
        g_lut_action[static_cast<unsigned char>(operatorsStack_.top())](numbersStack_, operatorsStack_);
    }

    operatorsStack_.push(str_[i]);

    ++i;
}

void Handler::DivideHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{

}

void Handler::MultiplyHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{

}

void Handler::OpenBracketHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{

}

void Handler::CloseBracketHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{

}

void Handler::NumHandle(stack<int> &numbersStack_, stack<char> &operatorsStack_, string &str_, size_t &i)
{
    size_t nextPos = FindNextSapcePos(str_, i);
    //cout << nextPos << " just spaces: " << str_[nextPos] << endl;
    int num = ConvertStrIntoNum(str_.substr(i, 3));
    numbersStack_.push(num);

    //check for brackets
    if (str_[nextPos - 1] == ')')
    {
        --nextPos;
    }

    i = nextPos;
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

// Executer Funcs
void Executer::AddExecute(stack<int> &numbersStack_, stack<char> &operatorsStack_)
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

void Executer::ReduceExecute(stack<int> &numbersStack_, stack<char> &operatorsStack_)
{
    double result = numbersStack_.top();
    numbersStack_.pop();
    result = numbersStack_.top() - result;
    numbersStack_.pop();

    cout << "ReduceExecute: result = " << result << endl;
    // Push in the resault
    numbersStack_.push(result);

    // Pop out the used operator
    operatorsStack_.pop();
}

void Executer::DivideExecute(stack<int> &numbersStack_, stack<char> &operatorsStack_)
{

}

void Executer::MultiplyExecute(stack<int> &numbersStack_, stack<char> &operatorsStack_)
{

}

}//namespace l1ght
