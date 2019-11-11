/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/
#include <fstream>      //ofstream

#include "circle.hpp"

using namespace std;
using namespace ilrd;

//static void CircleTest();
//static void DrawCircle();
static void DrawForSerialize();
//static int TimerFunc();
void CheckShapeType(string& str_);

Point g_point(200, 300);
Point g_revolve_by(100, 100);
Circle g_circ(COLOR_CYAN, g_point, 90, 150);
Circle circForSerilize(COLOR_CYAN, g_point, 90, 200);
Circle newCirc;

//const char* FILE_NAME = "circle_data.txt";

int main(int argc, char** argv)
{
    //DrawInit(argc, argv, 1000, 1000, DrawForSerialize);
    //DrawSetKeyboardFunc(MyKeyboardFunction);
    //DrawSetTimerFunc(TimerFunc, 100);
    //DrawMainLoop();

    string str_ = circForSerilize.Serialize();
    cout << str_ << endl;

    DrawInit(argc, argv, 1000, 1000, DrawForSerialize);
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawMainLoop();

	return 0;
}

static void DrawForSerialize()
{
    newCirc.Draw();
}

/* static void DrawCircle()
{
    Point p1(200, 300);
    Point revolve_by(100, 100);

    Circle c1(COLOR_CYAN, p1, 90, 150);
    c1.Revolve(revolve_by, 180.0);
    c1.Draw();

    Point p2(200, 300);
    Circle c2(COLOR_MAGENTA, p2, 90, 100);
    c2.Draw();

    Point p3(200, 300);
    Point p4(400, 600);
    Circle c3(COLOR_BLUE, p3, 45, 37.5);
    c3.SetColor(COLOR_YELLOW);
    c3.SetAngle(150);
    c3.SetPosition(p4);
    c3.Draw();
} */