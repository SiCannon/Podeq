#include <math.h>
#include <GL/freeglut.h> 
#include <include/transform_old.h>
#include <include/vector2f.h>
#include <include/gaf.h>

#define PI 3.141592654f
#define TWO_PI 6.283185307f
#define PI_BY_2 1.570796327f
#define PI_BY_4 0.785398163f
#define PI_BY_8 0.392699082f

#define SQR(x) ((x) * (x))

GLfloat angleBetween(GLfloat ux, GLfloat uy, GLfloat vx, GLfloat vy);
GLfloat r_to_d(GLfloat r);
GLfloat d_to_r(GLfloat r);
glf distanceSquared(Vector2f& v1, Vector2f& v2);
GLfloat distanceSquared(Transform_Old *t1, Transform_Old *t2);
glf angleTo(Vector2f& me, Vector2f& target);
GLfloat angleTo(Transform_Old *me, Transform_Old *target);