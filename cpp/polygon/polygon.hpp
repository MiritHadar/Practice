/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_polygon
#define __OL67_polygon

#include <stddef.h> /* size_t */
#include <stdio.h>  /* puts   */

/* Counter */
struct Counter
{
    int m_a;
    int m_b;
};

/* Polygon */
struct Polygon
{
    // numPoints - initial number of points, all of them with value (0,0)
    explicit Polygon();
    explicit Polygon(Polygon &other_);
    Polygon(size_t m_numPoints = 0);
    ~Polygon();

    void Add(const Counter &c);
    bool IsEqual(const Polygon& other) const;
    void Print() const;

    size_t m_numPoints = 4;
    Counter *m_points;
};


#endif /* __OL67_polygon */


