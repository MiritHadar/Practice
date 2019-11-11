/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "rect.hpp"

using namespace ilrd;

//static void CircleTest();
//static void DrawRect();
static void DrawForSerialize();

Point g_point(500, 500);
Rect rectForSerilize(static_cast<COLORS>(COLOR_CYAN | COLOR_FILL), g_point, 0, 200, 300);

int main(int argc, char** argv)
{
    //DrawInit(argc, argv, 1000, 1000, DrawRect);
    //DrawSetKeyboardFunc(KeyboardFunction);
    string str_ = rectForSerilize.Serialize();
    cout << str_ << endl;

    DrawInit(argc, argv, 1000, 1000, DrawForSerialize);
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawMainLoop();
    
    return 0;
}

/* static void DrawRect()
{
    Point p1(500, 500);
    Rect R1(static_cast<COLORS>(COLOR_FILL | COLOR_BLUE), p1, 90, 100, 400);
    R1.Draw();
} */

static void DrawForSerialize()
{
    rectForSerilize.Draw();
}