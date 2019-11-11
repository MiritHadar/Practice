/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "polygon.hpp"

Polygon::Polygon(size_t numPoints_)
    : m_numPoints(numPoints_), m_points(NULL)
{
    m_points = new Counter[numPoints_];
    printf("Ctor : m_numPoints - %lu\n", m_numPoints);
}

Polygon::Polygon(Polygon &other_)
    : m_numPoints(other_.m_numPoints), m_points(NULL)
{
    m_points = new Counter[other_.m_numPoints];

    for (size_t i = 0; i < other_.m_numPoints; ++i)
    {
        m_points[i].m_a = other_.m_points[i].m_a;
        m_points[i].m_b = other_.m_points[i].m_b;
    }
}

Polygon::~Polygon()
{
    puts("Dtor");
}

void Polygon::Add(const Counter &c)
{
    puts("Add two polygons");

    for (size_t i = 0; i < m_numPoints; ++i)
    {
        m_points[i].m_a += c.m_a;
        m_points[i].m_b += c.m_b;
    }
}

bool Polygon::IsEqual(const Polygon& other) const
{
    size_t i = 0;

    if (other.m_numPoints != m_numPoints)
    {
        return 0;
    }

    for (i = 0; i < m_numPoints; ++i)
    {
        if (m_points[i].m_a != other.m_points[i].m_a || m_points[i].m_b != other.m_points[i].m_b)
        {
            return 0;
        }
    }

    return 1;
}

void Polygon::Print() const
{
    for (size_t i = 0; i < m_numPoints; ++i)
    {
        printf("%lu: (%d, %d)\n", i, m_points[i].m_a, m_points[i].m_b);
    }
}






