#include "../../../code/includes/fsm.hh"
#include "../../../code/includes/macros.hh"
struct Point
{
public:
	unsigned short x, y, z;
};
struct Line
{
public:
	fsm::o_set<Point> Points;
};
struct Plane
{
public:
	fsm::o_set<Line> Lines;
};
struct Plane plane;
char i, j;
void main()
{
	plane.Lines[i].Points[i].x = 10;
	plane.Lines[i].Points[0].y = 20;
}
