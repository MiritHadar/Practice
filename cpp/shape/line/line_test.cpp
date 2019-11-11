

/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "line.hpp"

using namespace ilrd;
using namespace std;

//static void CircleTest();
//static void DrawLine();
static void DrawForSerialize();

Point g_point(500, 500);
Line lineForSerilize(COLOR_CYAN, g_point, 0, 500);
Line newLine;

int main(int argc, char** argv)
{
    //DrawInit(argc, argv, 1000, 1000, DrawLine);
    //DrawSetKeyboardFunc(KeyboardFunction);
    string str_ = lineForSerilize.Serialize();
    //cout << str_ << endl;

    DrawInit(argc, argv, 1000, 1000, DrawForSerialize);
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawMainLoop();

	return 0;
}

static void DrawForSerialize()
{
    newLine.Draw();
}

/* static void DrawLine()
{
    Point p1(200, 300);
    Line L1(COLOR_GREEN, p1, 90, 250);
    L1.Draw();

    Line L2(COLOR_RED, p1, 90, 250);
    L2.Revolve(p1, 90.0);
    L2.Draw(); 
} */
