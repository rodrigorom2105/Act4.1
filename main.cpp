#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point
{
	double x, y;
};

// Epsilon
const double EPS = 1e-9;

// 0 -> p, q y r estan alineados
// 1 -> r esta a la derecha de pq
// 2 -> r esta a la izquierda de pq
int orientation(Point p, Point q, Point r)
{
	// Vector p -> q
	double u_x = q.x - p.x;
	double u_y = q.y - p.y;

	// Vector p -> r
	double v_x = r.x - p.x;
	double v_y = r.y - p.y;

	// Producto cruz: u × v = uₓ·v_y − u_y·vₓ
	double val = u_x * v_y - u_y * v_x;

	if (fabs(val) < EPS)
		return 0;
	return (val > 0) ? 2 : 1;
}

// Si p, q, r son colineales, revisa si q es parte del segmento pr
bool onSegment(Point p, Point q, Point r)
{
	// Bounding box
	// su x está entre la menor y la mayor x de p y r,
	// su y está entre la menor y la mayor y de p y r.
	return q.x <= max(p.x, r.x) + EPS && q.x >= min(p.x, r.x) - EPS &&
		   q.y <= max(p.y, r.y) + EPS && q.y >= min(p.y, r.y) - EPS;
}

// Segmento A = p1→p2. Segmento B = p3→p4
bool segmentsIntersect(Point p1, Point p2, Point p3, Point p4)
{
	int o1 = orientation(p1, p2, p3); // De qué lado de la recta A está p3
	int o2 = orientation(p1, p2, p4); // De qué lado de la recta A está p4
	int o3 = orientation(p3, p4, p1); // De qué lado de la recta B está p1
	int o4 = orientation(p3, p4, p2); // De qué lado de la recta B está p2

	// p3 y p4 están en lados opuestos de la recta A. B atraviesa la recta de A.
	// p1 y p2 están en lados opuestos de la recta B. A atraviesa la recta de B.
	if (o1 != o2 && o3 != o4)
		return true;

	// Special collinear cases
	if (o1 == 0 && onSegment(p1, p3, p2)) // p3 está alineado con A y dentro de A
		return true;
	if (o2 == 0 && onSegment(p1, p4, p2)) // p4 está alineado con A y dentro de A
		return true;
	if (o3 == 0 && onSegment(p3, p1, p4)) // p1 está alineado con B y dentro de B
		return true;
	if (o4 == 0 && onSegment(p3, p2, p4)) // p2 está alineado con B y dentro de B
		return true;

	return false; // Los segmentos no se atraviesan ni se tocan, así que no se intersectan.
}