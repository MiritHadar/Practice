/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* version: 	Final			  		                                      */
/* Last update: 							                                  */
/******************************************************************************/

#include <iostream>            // cout
#include <unordered_map>       // map
#include "calculator.hpp"      // header file

namespace l1ght
{

using namespace std;

static void PrintMyStack(Stack<int> &nums_, Stack<char> &operators_);
static void InitMap();

// Static member's declaration
Stack<int> Calculator::m_numbersStack;
Stack<char> Calculator::m_operatorsStack;

unordered_map<char*,int(*)()> g_mapOfFuncs; 

const char OPENNING_BRACKET = 40;
const char OPERATORS_ASCII = 48;
const char SPACE_ASCII = 32;
const size_t NUM_OF_ASCII_CHARS = 256;

// Calculator::Calculator()
// {
//     InitMap();
// }

// static void InitMap()
// {
//     g_mapOfFuncs['+'] = AddFunc;
//     g_mapOfFuncs['+'] = AddActFunc;

//     g_mapOfFuncs['-'] = ReduceFunc;
//     g_mapOfFuncs['-'] = ReduceActFunc;

//     g_mapOfFuncs['/'] = DivideFunc;
//     g_mapOfFuncs['/'] = DivideActFunc;

//     g_mapOfFuncs['*'] = MultiplyFunc;
//     g_mapOfFuncs['*'] = MultiplyActFunc;

//     g_mapOfFuncs['('] = OpenParenthesisFunc;
//     g_mapOfFuncs[')'] = CloseParenthesisFunc;

//     for (size_t i = 48; i < 58; ++i)
//     {
//         g_mapOfFuncs[i] = NumFunc; 
//     }   
// }

vector<double> Calculator::Calculate(const char fileName_[])
{
    vector<string> vecOfStrings = Parser::Parse(fileName_);
    vector<double> vecOfResults;

    for (vector<string>::iterator it = vecOfStrings.begin(); it != vecOfStrings.end(); ++it)
    {
        //cout << "it: " << *it << endl;
        SortBetweenStacks(*it);
        vecOfResults.push_back(Execute());
    }

    return vecOfResults;
}

void Calculator::SortBetweenStacks(string str_)
{
    for (auto it = str_.cbegin(); it != str_.cend(); ++it)
    {
        //brackets
        if (*it == OPENNING_BRACKET)
        {
            Calculator::m_operatorsStack.Push(*it);
        }

        //operators
        else if (*it < OPERATORS_ASCII && *it != SPACE_ASCII)
        {
            Calculator::m_operatorsStack.Push(*it);
        }

        //numbers
        else// if ((*it > 65) && (*it < 91))
        {
            //take a while word
            Calculator::m_numbersStack.Push(ConvertToNum(it));
            //jump to next space/word
        }
    }
    
    //     operators
    //     if (*it < OPERATORS_ASCII)
    //     {
    //         Calculator::m_operatorsStack.Push(*it);
    //     }
    //     //numbers
    //     else if ((*it > 65) && (*it < 91))
    //     {
    //         Calculator::m_numbersStack.Push(ConvertToNum(*it));
    //     }
    // }

    //cout << "word:" << word << endl;

   

    PrintMyStack(m_numbersStack, m_operatorsStack);
}

double Calculator::Execute()
{
    double result = 0;

    return result;
}

static void PrintMyStack(Stack<int> &nums_, Stack<char> &operators_)
{
    cout << "numbers:" << endl;
    while(!(nums_.IsEmpty()))
    {
        cout << nums_.Top() << endl;
        nums_.Pop();
    }

    cout << "\n" << "operators:" << endl;
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




}//namespace l1ght
