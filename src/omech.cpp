#include <math.h>
#include <GL/freeglut.h>
#include <include/gaf_math.h>

GLfloat calc_e(GLfloat r, GLfloat vsq, GLfloat GM, GLfloat phi)
{
    // http://www.braeunig.us/space/orbmech.htm equation 4.30
    
    GLfloat t1 = r * vsq / GM - 1;
    GLfloat t2 = SQR(t1) * SQR(cosf(phi)) + SQR(sinf(phi));
    
    return sqrtf(t2);
}

GLfloat calc_a(GLfloat r, GLfloat vsq, GLfloat GM)
{
    // http://www.braeunig.us/space/orbmech.htm equation 4.32
    return 1.0f / ((2.0f / r) - (vsq / GM));
}

GLfloat calc_nu(GLfloat r, GLfloat vsq, GLfloat GM, GLfloat phi)
{
    // http://www.braeunig.us/space/orbmech.htm equation 4.31
    GLfloat term1 = r * vsq / GM;
    GLfloat cosPhi = cosf(phi);
    
    GLfloat num = term1 * cosPhi * sinf(phi);
    GLfloat den = term1 * SQR(cosPhi) - 1.0f;
    
    return atan2f(num, den);
}

GLfloat calc_Rp(GLfloat a, GLfloat e)
{
    // http://www.braeunig.us/space/orbmech.htm equation 4.21
    return  a * (1.0f - e);
}

GLfloat calc_Ra(GLfloat a, GLfloat e)
{
    // http://www.braeunig.us/space/orbmech.htm equation 4.22
    return  a * (1.0f + e);
}
