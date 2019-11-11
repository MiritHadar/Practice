
#include "point.hpp"

int main()
{
    Point p1;
    Point p2;
    Point p3;
   /* printf("type a limit: ");
     cin >> p1.limit;
 */
    p1.m_x = 0;
    p1.m_y = 0;

    p2.m_x = 1;
    p2.m_y = 1;

    p3.m_x = 2;
    p3.m_x = 2;

    p1.AdjustBy(p2);
/*     p1.Print('(', ')');
 */
    /* p1.CheckLimit();
    p2.CheckLimit(); */

    p1.AdjustBy(3, 4);
    p1.Print(p1.SQUARE);
    

/*     Add(p1, p2);    
 */
}