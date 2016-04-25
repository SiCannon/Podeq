#include <math.h>
#include <GL/freeglut.h> 

#define PI 3.141592654f
#define TWO_PI 6.283185307f
#define PI_BY_2 1.570796327f
#define PI_BY_4 0.785398163f
#define PI_BY_8 0.392699082f

#define SQR(x) ((x) * (x))

GLfloat angleBetween(GLfloat ux, GLfloat uy, GLfloat vx, GLfloat vy);
GLfloat r_to_d(GLfloat r);