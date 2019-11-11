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

/* static void DrawForSerialize();
static int GrpTimerFunc(); */

Point g_pnt1(500, 400);
Point g_pnt2(500, 600);
Point g_pnt3(400, 500);
Point g_pnt4(600, 500);
Point g_revolveBy(700, 700);

Point g_point(500, 500);
Group grpForSerilize(COLORS(COLOR_CYAN | COLOR_FILL), g_point, 0);
Group newGrp;

int main(int argc, char** argv)
{
    Circle crc1(COLORS(COLOR_CYAN | COLOR_FILL), g_pnt2, 0, 30);
    Rect rect1(COLORS(COLOR_CYAN | COLOR_FILL), g_pnt1, 0, 50, 100);
    string strCircle = crc1.Serialize();
    string strRect = rect1.Serialize();

    //DrawInit(1, NULL, 1000, 1000, DrawForSerialize);
    //DrawSetKeyboardFunc(KeyboardFunction);
    //DrawSetTimerFunc(GrpTimerFunc, 100);
    //DrawMainLoop();

    return 0;
}

/* static void DrawForSerialize()
{
    grpForSerilize.Draw();
}

static int GrpTimerFunc()
{
    return 1;
}
 */