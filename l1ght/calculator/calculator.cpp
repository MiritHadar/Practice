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

// Handle Func
class Handler : private Uncopyable
{
public:
	static void AddHandle(Stack<int> &numbersStack_, Stack<char> &operatorsStack_, string::const_iterator it);
	static void NumHandle(Stack<int> &numbersStack_, Stack<char> &operatorsStack_, string::const_iterator it);
    static void SpaceHandle(Stack<int> &numbersStack_, Stack<char> &operatorsStack_, string::const_iterator it);
    static void EndHandle(Stack<int> &numbersStack_, Stack<char> &operatorsStack_, string::const_iterator it);
};

// Act Funcs
class Executer : public Uncopyable
{
public:
	static void AddExecute(Stack<int> &numbersStack_, Stack<char> &operatorsStack_, string::const_iterator it);
};

static void PrintAndEmptyMyStacks(Stack<int> &nums_, Stack<char> &operators_);
static void InitMapsOfFuncs();

//unordered_map<char*,int(*)()> g_mapOfFuncs; 
typedef void (*hand_func)(Stack<int> &numbersStack_,
                          Stack<char> &operatorsStack_,
                          string::const_iterator it);

typedef void (*act_func)(Stack<int> &numbersStack_,
                         Stack<char> &operatorsStack_,
                         string::const_iterator it);

hand_func g_lut_handler[256];
act_func g_lut_action[256];

const unsigned char ZERO_ASCII = 48;
const unsigned char NINE_ASCII = 57;
const unsigned char OPENNING_BRACKET = 40;
const unsigned char CLOSING_BRACKET = 41;
const unsigned char OPERATORS_ASCII = 48;
const unsigned char SPACE_ASCII = 32;
const size_t NUM_OF_ASCII_CHARS = 256;

Calculator::Calculator()
    :m_numbersStack(Stack<int>()),
     m_operatorsStack(Stack<char>())
{
    InitMapsOfFuncs();
}

static void InitMapsOfFuncs()

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

// void Calculator::SortBetweenStacks(string str_)
// {
//     for (auto it = str_.cbegin(); it != str_.cend(); ++it)
//     {
//         //brackets
//         if (*it == OPENNING_BRACKET)
//         {
//             Calculator::m_operatorsStack.Push(*it);
//         }

//         //operators
//         else if (*it < OPERATORS_ASCII && *it != SPACE_ASCII)
//         {
//             Calculator::m_operatorsStack.Push(*it);
//             ++it;   // skips single space
//         }

//         //numbers
//         else// if ((*it > 65) && (*it < 91))
//         {
//             //take a whole word
//             g_mapOfFuncs[*it+(*(++it))](); // return num acording to two first letters
//             Calculator::m_numbersStack.Push(ConvertToNum(it));
//             while(*it != SPACE_ASCII)
//             {
//                 if(*it == CLOSING_BRACKET)
//                 {
//                     Calculator::m_operatorsStack.Push(*it);
//                 }
//             }
//             ++it;
//         }
//     }

//     PrintAndEmptyMyStacks(m_numbersStack, m_operatorsStack);
// }

double Calculator::Execute(string str_)
{
    for (auto it = str_.cbegin(); it != str_.cend(); ++it)
    {
        cout << "sign: " << *const_cast<char*>(it.base()) << endl;
        //PrintAndEmptyMyStacks(m_numbersStack, m_operatorsStack);
        g_lut_handler[static_cast<unsigned char>(*const_cast<char*>(it.base()))](m_numbersStack, m_operatorsStack, it);
    }

    double result = m_numbersStack.Top();
    cout << "result = " << result << endl;
    PrintAndEmptyMyStacks(m_numbersStack, m_operatorsStack);

    return result;
}

static void PrintAndEmptyMyStacks(Stack<int> &nums_, Stack<char> &operators_)
{
    cout << "numbers:" << endl;
    while(!(nums_.IsEmpty()))
    {
        cout << nums_.Top() << endl;
        nums_.Pop();
    }

    cout << "operators:" << endl;
    while(!(operators_.IsEmpty()))
    {
        cout << operators_.Top() << endl;
        operators_.Pop();
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
void Handler::AddHandle(Stack<int> &numbersStack_, Stack<char> &operatorsStack_, string::const_iterator it)
{
    while(!(operatorsStack_.IsEmpty()) && operatorsStack_.Top() != '(')
    {
        g_lut_handler[static_cast<unsigned char>(operatorsStack_.Top())](numbersStack_, operatorsStack_, it);
    }

    operatorsStack_.Push(*const_cast<char*>(it.base()));
    ++it;
}

// Act Funcs
void Executer::AddExecute(Stack<int> &numbersStack_, Stack<char> &operatorsStack_, string::const_iterator it)
{

}

void Handler::NumHandle(Stack<int> &numbersStack_, Stack<char> &operatorsStack_, string::const_iterator it)
{
    //jump to end of num
    int num = strtod(it.base(), nullptr);
    numbersStack_.Push(num);
    //++it;
}

void Handler::SpaceHandle(Stack<int> &numbersStack_, Stack<char> &operatorsStack_, string::const_iterator it)
{
    //++it;
}

void Handler::EndHandle(Stack<int> &numbersStack_, Stack<char> &operatorsStack_, string::const_iterator it)
{
    // while (!operatorsStack_.IsEmpty())
    // {
    //     g_lut_action[static_cast<unsigned char>(operatorsStack_.Top())](numbersStack_, operatorsStack_, it);   
    // }
}


}//namespace l1ght
