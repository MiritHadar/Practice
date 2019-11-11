/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "square.hpp"

using namespace ilrd;

static void DrawSquare();
static int TimerFunction();

Point g_pnt1(500, 500);

Square g_sqr1(COLOR_CYAN, g_pnt1, 90, 150);
Square g_sqr2(COLOR_GREEN, g_pnt1, 270, 150);

int main(int argc, char** argv)
{

    DrawInit(argc, argv, 1000, 1000, DrawSquare);
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetTimerFunc(TimerFunction, 300);
    DrawMainLoop();
    
    return 0;
}

static void DrawSquare()
{
    g_sqr1.Draw();
    g_sqr2.Draw();
    /*g_sqr1.SetPosition(revolveBy);
    g_sqr1.Draw();

    s1.Revolve(p1, 30);
    s1.SetColor(COLOR_WHITE);
    s1.Draw();

    s1.Revolve(p2, 250);
    s1.SetColor(COLOR_RED);
    s1.Draw(); */
}

static int TimerFunction()
{
    Point revolveBy(400, 400);
    g_sqr1.Revolve(revolveBy, 30.0);
    g_sqr2.Revolve(revolveBy, 180.0);

    return 1;  /* draw */
}
