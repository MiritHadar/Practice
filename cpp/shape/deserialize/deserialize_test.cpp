/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>		// o / i
#include <vector>		// vector
#include <algorithm>	// for_each
#include "deserialize.hpp"
#include "line.hpp"
#include "circle.hpp"
#include "rect.hpp"
#include "square.hpp"
#include "group.hpp"

using namespace std;
using namespace ilrd;

void SerializeTest();
void DeserializeTest();
static void DrawForSerialize();
static int TimerFunc();
static int MyKeyboardFunction(unsigned char key, int x, int y);
static void DrawFromVector();
static void DrawEachShape(SharedPtr<Shape> shapeInVec);

Point g_pnt1(500, 400);
Point g_pnt2(500, 600);
Point g_pnt3(400, 500);
Point g_pnt4(600, 500);
Point g_revolveBy(700, 700);
Point g_point(500, 500);
static Shape* g_crc1 = new Circle(COLORS(COLOR_CYAN | COLOR_FILL), g_pnt2, 0, 30);
vector<SharedPtr<Shape> > g_vectorOfShapes;
const char* fileName = "output";

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		//DeserializeTest(argv[1]);
		DeserializeTest();
	}
	else
	{
		SerializeTest();
	}

	return 0;
}

void SerializeTest()
{
    DrawInit(1, NULL, 1000, 1000, DrawForSerialize);
    DrawSetKeyboardFunc(MyKeyboardFunction);
    //DrawSetTimerFunc(TimerFunc, 100);
    DrawMainLoop();
}

static void DrawForSerialize()
{
    g_crc1->Draw();
}

static int TimerFunc()
{
	g_crc1->Revolve(g_pnt1, 180);

    return 1;
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
		std::ofstream outFile;
		outFile.open(fileName);
		outFile << g_crc1->Serialize();

		outFile.close();
    }

    return 0;
}

void DeserializeTest()
{
	stringbuf buffer;
	ifstream inFile;
	inFile.open(fileName);
	inFile >> &buffer;
	string str;
	str = buffer.str();
	inFile.close();

	g_vectorOfShapes = Deserialize(str);
	(static_cast<SharedPtr<Shape*> >(g_vectorOfShapes[0])).Serialize();
	DrawInit(1, NULL, 1000, 1000, DrawFromVector);
    DrawSetKeyboardFunc(MyKeyboardFunction);
    DrawMainLoop();
}

static void DrawFromVector()
{
	for_each(g_vectorOfShapes.begin(), g_vectorOfShapes.end(), DrawEachShape);
}

static void DrawEachShape(SharedPtr<Shape> shapeInVec)
{
	shapeInVec->Draw();
}