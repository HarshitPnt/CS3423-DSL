#include "../../../code/includes/fsm.hh"
#include "../../../code/includes/macros.hh"
struct Point
{
public:
	long int x, y;
	std::string name;
};
struct Grid
{
public:
	fsm::o_set<Point> set;
};
unsigned short abs(unsigned short x)
{
	if (x > 0)
	{
		return x;
	}
	else
	{
		return -x;
	}
}
unsigned short root_newton_raphson(unsigned short num, unsigned short precision)
{
	unsigned short curr = num / 2;
	unsigned short new_guess;
	new_guess = curr - (curr * curr - num) / (2 * curr);
	if (abs(new_guess - curr) < precision)
	{
		return new_guess;
	}
}
unsigned short distance(Point a, Point b)
{
	unsigned short dist = root_newton_raphson((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y), 0.000100);
	return dist;
}
unsigned char size(fsm::o_set<Point> y)
{
	unsigned char x;
	return x;
}
void insert(fsm::o_set<unsigned short> xx, unsigned short y)
{
	return;
}
fsm::o_set<unsigned short> findEuclideanDistance(Grid grid1)
{
	char s = size(grid1.set);
	fsm::o_set<unsigned short> return_values;
	char i = 0;
	char j = i + 1;
	insert(return_values, distance(grid1.set[i], grid1.set[j]));
	j += 1;
	i += 1;
	return return_values;
}
void main()
{
	struct Point p1, p2, p3, p4;
	struct Grid grid;
	grid.set.insert(p1);
	grid.set.insert(p2);
	grid.set.insert(p3);
	grid.set.insert(p4);

	char i = 0;
	grid.set[i].x = i;
	grid.set[i].y = i * i;
	i += 1;
	fsm::o_set<unsigned short> distances = findEuclideanDistance(grid);
	i = 0;
	i += 1;
}
