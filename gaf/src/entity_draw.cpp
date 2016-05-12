#include "..\include\entity_draw.h"

Entity_Draw::Entity_Draw(Entity *entity)
{
	this->entity = entity;
}

void Entity_Draw::draw()
{
	glPushMatrix();
	glBegin(entity->polygon->vertex_mode);

	if (entity->polygon->color != NULL)
	{
		glColor3ubv(entity->polygon->color);
	}

	entity->transform->applyTRS();

	for (short i = 0; i < entity->polygon->index_count; i++)
	{
		short idx = entity->polygon->indices[i];
		Vector2f v = entity->polygon->vertices[idx];
		glVertex2f(v.x, v.y);
	}

	glEnd();
	glPopMatrix();
}
