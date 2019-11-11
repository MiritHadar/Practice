/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************/

#include <features.h>
#include <fstream>
#include <sstream>
#include <cstring>

#include <stdio.h>
#include "group.hpp"

using namespace std;
using namespace ilrd;

const char* FILE_NAME = "shape_data.txt";

static void SqrAnimation();
static void DrawSquare();
static int SqrTimerFunc();

static void GrpAnimation();
static void DrawGrp();
static int GrpTimerFunc();

static void SerializeTest();
static int MyKeyboardFunction(unsigned char key, int x, int y);
static void DrawForSerialize();
static void DeSerializeTest();
static void DrawFromFile();

std::ofstream fp;

/*globals for SqrAnimation*/
Point g_pnt1(500, 400);
Point g_pnt2(500, 600);
Point g_pnt3(400, 500);
Point g_pnt4(600, 500);
Point g_revolveBy(700, 700);

Square g_sqr1(COLORS(COLOR_RED | COLOR_FILL), g_pnt1, 90, 50);
Square g_sqr2(COLORS(COLOR_GREEN | COLOR_FILL), g_pnt2, 90, 50);
Square g_sqr3(COLORS(COLOR_CYAN | COLOR_FILL), g_pnt3, 90, 50);
Square g_sqr4(COLORS(COLOR_MAGENTA | COLOR_FILL), g_pnt4, 90, 50);
/*globals for GrpAnimation*/
Group g_grp(COLORS(COLOR_YELLOW), g_pnt1, 0);

int main(int argc, char** argv)
{
    //SqrAnimation();
    GrpAnimation();
    //SerializeTest();
    //DeSerializeTest();

    return 0;
}

static void SqrAnimation()
{
    DrawInit(1, NULL, 1000, 1000, DrawSquare);
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetTimerFunc(SqrTimerFunc, 100);
    DrawMainLoop();
}

static void GrpAnimation()
{
    Circle crc1(COLORS(COLOR_CYAN | COLOR_FILL), g_pnt2, 0, 30);
    Line line1(COLOR_WHITE, g_pnt3, 90, 100);
    Rect rect1(COLOR_YELLOW, g_pnt4, 0, 50, 70);

    g_grp.Add(&g_sqr1);
    g_grp.Add(&crc1);
    g_grp.Add(&line1);
    g_grp.Add(&rect1);
    g_grp.SetColor(COLOR_RED);

    DrawInit(1, NULL, 1000, 1000, DrawGrp);
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetTimerFunc(GrpTimerFunc, 100);
    DrawMainLoop();
}

static void DrawGrp()
{
    g_grp.SetColor(COLOR_RED);
    g_grp.Revolve(g_revolveBy, 5.0);

    g_grp.Draw();
}

static int GrpTimerFunc()
{
    //g_grp.SetAngle(1.0); 
    //g_grp.Revolve(g_revolveBy, 5.0);

    return 1;
}

static void DrawSquare()
{
    g_sqr1.Draw();
    g_sqr2.Draw();
    g_sqr3.Draw();
    g_sqr4.Draw();
}


static int SqrTimerFunc()
{
    static double angle = 30.0;
    g_sqr1.Revolve(g_revolveBy, 5.0);
    g_sqr2.Revolve(g_revolveBy, 5.0);
    g_sqr3.Revolve(g_revolveBy, 5.0);
    g_sqr4.Revolve(g_revolveBy, 5.0);

    g_sqr1.SetAngle(angle);
    g_sqr2.SetAngle(angle);
    g_sqr3.SetAngle(angle);
    g_sqr4.SetAngle(angle); 
    angle += 20;
    
    return 1;  /* draw */
}

static void SerializeTest()
{
    DrawInit(1, NULL, 1000, 1000, DrawForSerialize);
    DrawSetKeyboardFunc(MyKeyboardFunction);
    DrawSetTimerFunc(SqrTimerFunc, 100);
    DrawMainLoop();
}

static void DrawForSerialize()
{
    g_sqr1.Draw();
}

static int MyKeyboardFunction(unsigned char key, int x, int y)
{
    printf("Keyboard: %02x,%d,%d\n", key, x, y);
    ofstream outFile;

    if (key == 0x1b /* ESC */)
    {
        return -1;
    }

    if (key == 0x70 /*  p  */)
    {
        outFile.open(FILE_NAME, ofstream::out);
        outFile << g_sqr1.GetAngle() << " " << g_sqr1.GetColor() << " "
                << g_sqr1.GetPosition().GetX() << " " << g_sqr1.GetPosition().GetY()
                << g_sqr1.GetLength() << endl;

        cout << "picture saved" << endl;
        outFile.close();
    }

    return 0;
}


static void DeSerializeTest()
{
    DrawInit(1, NULL, 1000, 1000, DrawFromFile);
    DrawSetKeyboardFunc(KeyboardFunction);
    DrawSetTimerFunc(SqrTimerFunc, 100);
    DrawMainLoop();
}

static void DrawFromFile()
{
    ifstream inFile;
    inFile.open(FILE_NAME, ifstream::in);

    double angle = 0;
    int color = 0;
    double x = 0;
    double y = 0;
    double len = 0;

    inFile >> angle >> color >> x >> y >> len;

    inFile.close();
    Point center(x, y);
    Square new_sqr(static_cast<COLORS>(color), center, angle, len);
    new_sqr.Draw();
}
