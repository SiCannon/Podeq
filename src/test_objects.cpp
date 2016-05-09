#include "../include/test_objects.h"
#include <include/gaf_util.h>

Hex::Hex()
{
	poly = new Polygon2f();
	poly->set_size(3);
	poly->set_vertex(0, -1.0f, 0);
	poly->set_vertex(1, 1.0f, 0);
	poly->set_vertex(2, 0, 2.0f);
	poly->color = colorv(192, 192, 64);
	polydraw = new Polygon2f_Draw(poly);
}

Tri::Tri()
{
	poly = new Polygon2f();
	poly->set_size(3);
	poly->set_vertex(0, 5.0f, 0);
	poly->set_vertex(1, 7.0f, 0);
	poly->set_vertex(2, 6.0f, 2.0f);
	poly->color = colorv(192, 64, 192);
	polydraw = new Polygon2f_Draw(poly);
}

CollisionDetector::CollisionDetector(Hex * hex, Tri * tri)
{
	this->hex = hex;
	this->tri = tri;
}

void CollisionDetector::update(Timer * timer)
{

}
