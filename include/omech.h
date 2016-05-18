#include <GL/freeglut.h>

GLfloat calc_e(GLfloat r, GLfloat vsq, GLfloat GM, GLfloat phi);
GLfloat calc_a(GLfloat r, GLfloat vsq, GLfloat GM);
GLfloat calc_nu(GLfloat r, GLfloat vsq, GLfloat GM, GLfloat phi);
GLfloat calc_Rp(GLfloat a, GLfloat e);
GLfloat calc_Ra(GLfloat a, GLfloat e);
GLfloat calc_n(GLfloat GM, GLfloat a);
GLfloat calc_r(GLfloat a, GLfloat e, GLfloat nu);
GLfloat calc_phi(GLfloat e, GLfloat nu);
GLfloat calc_v(GLfloat GM, GLfloat r, GLfloat a);

GLfloat TrueToMeanAnomalyf(GLfloat e, GLfloat f);
GLfloat TrueToEccenAnomalyf(GLfloat e, GLfloat f);
GLfloat EccenToMeanAnomalyf(GLfloat e, GLfloat E);
GLfloat MeanToTrueAnomalyf(GLfloat e, GLfloat M);
double MeanToEccenAnomalyf(double e, double M);
GLfloat EccenToTrueAnomalyf(GLfloat e, GLfloat E);