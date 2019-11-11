/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <cstring>
#include "deserialize.hpp"
#include "circle.hpp"
#include "line.hpp"
#include "group.hpp"
#include "rect.hpp"
#include "square.hpp"

using namespace std;

namespace ilrd
{

static SharedPtr<Shape> DeserializeAShape(string line);


vector<SharedPtr<Shape> > Deserialize(std::string& str_)
{
    stringstream stream;
    stream << str_;
    vector <SharedPtr<Shape> > shapesFromString;
    string line;

    do
    {
        getline(stream, line);
        cout << line << endl;
        shapesFromString.push_back(DeserializeAShape(line));

    } while (!stream.eof());

    return shapesFromString;
}

static SharedPtr<Shape> DeserializeAShape(string line)
{
    stringstream stream;
    stream << line;

    string shapeType;
    int shapeColor;
    double x, y, angle = 0, len = 0, heightForRect = 0;

    stream >> shapeType >> shapeColor >> x >> y >> angle;

    SharedPtr<Shape> s = NULL;
    //line
    if (shapeType == g_lut[0])
    {
        s = SharedPtr<Shape>(new Line(static_cast<COLORS>(shapeColor), Point(x,y), angle, len));
    }
    //circ
    else if (shapeType == g_lut[1])
    {
        s = SharedPtr<Shape>(new Circle(static_cast<COLORS>(shapeColor), Point(x,y), angle, len));
    }
    //rect
    else if (shapeType == g_lut[2])
    {
        stream << heightForRect;
        s = SharedPtr<Shape>(new Rect(static_cast<COLORS>(shapeColor), Point(x,y), angle, len, heightForRect));
    }
    //square
    else if (shapeType == g_lut[3])
    {
        s = SharedPtr<Shape>(new Square(static_cast<COLORS>(shapeColor), Point(x,y), angle, len));
    }
    //Group
    else if (shapeType == g_lut[4])
    {
        s = SharedPtr<Shape>(new Group(static_cast<COLORS>(shapeColor), Point(x,y), angle));
    }

   return s;
}

} // namespace ilrd



