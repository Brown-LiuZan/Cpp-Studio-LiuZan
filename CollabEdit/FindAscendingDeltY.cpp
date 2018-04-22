#include <utility>
#include <vector>
#include <cstdint>

using namespace std;

struct Point
{
    int x;
    int y;
};

/****
 输入 Points[], x 递增排序，且不重复。 求 Points 中的两个点 PointMax 和  PointMin，满足以下条件：
 ① PointMax.x > PointMin.x ；
 ② PointMax.y - PointMin.y = MAX(Point ∈ Points，并且满足条件  ① )；
 ------------

 A = {0, 1} = min , B = {1, 2}, C= {2, 3} = max
 C.y - A.y = 2 = MAX( {C-A}, {C-B}, {B-A})

 A = {0, 3} = min , B = {1, 100}, C= {2, 0} = min D = {3, 98} = max 
 ****/

pair<int, int> FindMaxAscendingDeltY(vector<Point> const & inPoints)
{
    assert(inPoints.size() >= 2 && inPoints.size() < INT_MAX);

    // Initial solution.
    pair<int, int> vMinMaxIndics {0, 1};  // Initial solution defined by <PointMinIndex, PointMaxIndex>
    int64_t vMaxDeltY = inPoints[1].y - inPoints[0].y; // Inital delt Y.

    // For possilbe new solution
    int vRealMinIndex = vMaxDeltY > 0 ? 0 : 1; // Lower bound of a different new solution.

    // Scanning remaining Points.
    while (int i = 2; i <  inPoints.size(); ++i)
    {
        if (inPoints[i].y > inPoints[vMinMaxIndics.second].y)
        {
            // Solution update condition 1: Higher upper bound, update the inital solution diretly.
            vMinMaxIndics.second= i;
            vMaxDeltY = inPoints[vMinMaxIndics.second] - inPoints[vMinMaxIndics.first];
        }
        else
        {
            int64_t vDeltY = inPoints[i].y - inPoints[vRealMinIndex ].y;
             if (vDeltY > vMaxDeltY)
             {
                 // Solution update conditon 2: Bigger ascending height, replace the inital solution with a different new solution .
                 vMinMaxIndics.first = vRealMinIndex ;
                 vNewMinIndics.second = i;
                 vMaxDeltY = vDeltY;
             }
             else if (vDeltY < 0)
             {
                 // Solution update condition 3: Make sure the lower bound of new possible solution has the smallest y that have ever been seen.
                 vRealMinIndex = i;
             }               
         }
     }

     return vMinMaxIndics;
}

