#include "../include/sat_collider.h"
#include "../include/polygon2f.h"
#include "../include/vector2f.h"

bool SatCollider::collide(Polygon2f *poly1, Polygon2f *poly2)
{
	if (!test(poly1, poly2))
	{
		return false;
	}
	else
	{
		return test(poly2, poly1);
	}	
}

bool SatCollider::test(Polygon2f *poly1, Polygon2f *poly2)
{
	bool collision = true;

	for (short i = 0; i < poly1->vertex_count; i++)
	{
		short i1 = i;
		short i2 = i + 1;
		if (i2 >= poly1->vertex_count)
		{
			i2 = 0;
		}

		Vector2f a = poly1->transformed[i1];
		Vector2f b = poly1->transformed[i2];
		Vector2f n = normal(a, b);

		bool all_negative = true;

		for (short j = 0; j < poly2->vertex_count; j++)
		{
			glf dot = dot_product(a - poly2->transformed[j], n);
			if (dot >= 0)
			{
				all_negative = false;
				break;
			}
		}

		if (all_negative)
		{
			collision = false;
			break;
		}
	}

	return collision;
}