#include <math.h>
#include <GL/freeglut.h>
#include <include/gaf_math.h>
#include "omech.h"

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

GLfloat calc_n(GLfloat GM, GLfloat a)
{
	// http://www.braeunig.us/space/orbmech.htm equation 4.39
	return sqrtf(GM / powf(a, 3.0f));
}

GLfloat calc_r(GLfloat a, GLfloat e, GLfloat nu)
{
	// http://www.braeunig.us/space/orbmech.htm equation 4.43
	return a * (1.0f - SQR(e)) / (1.0f + e * cosf(nu));
}

GLfloat TrueToMeanAnomalyf(GLfloat e, GLfloat f)
{
	GLfloat E = TrueToEccenAnomalyf(e, f);
	GLfloat M = EccenToMeanAnomalyf(e, E);
	return M;
}

GLfloat TrueToEccenAnomalyf(GLfloat e, GLfloat f)
{
	GLfloat sinE = sinf(f) * sqrtf(1.0f - SQR(e)) / (1.0f + e * cosf(f));
	GLfloat cosE = (e + cosf(f)) / (1.0f + e * cosf(f));
	GLfloat E = atan2f(sinE, cosE);
	return E;
}

GLfloat EccenToMeanAnomalyf(GLfloat e, GLfloat E)
{
	GLfloat M = E - e * sinf(E);
	return M;
}

GLfloat MeanToTrueAnomalyf(GLfloat e, GLfloat M)
{
	GLfloat E = MeanToEccenAnomalyf(e, M);
	GLfloat f = EccenToTrueAnomalyf(e, E);
	return f;
}

double initial_E_OrbitNerd(GLfloat e, GLfloat M)
{
	// Make sure M lies between -pi and pi
	M = fmodf(M, 2 * PI);
	if (M < PI)
	{
		M = M + 2.0f * PI;
	}
	else if (M > PI)
	{
		M = M - 2.0f * PI;
	}

	double E;

	if ((M > -PI && M < 0) || (M > PI))
	{
		E = M - e;
	}
	else
	{
		E = M + e;
	}

	return E;
}

double initial_E_AstronomyAnswers_Simple(GLfloat e, GLfloat M)
{
	M = fmodf(M, TWO_PI) - PI;
	return cbrt(6.0 * M);
}

GLfloat MeanToEccenAnomalyf(GLfloat e, GLfloat M)
{
	double E = initial_E_AstronomyAnswers_Simple(e, M);

	double Enew = E;
	double zero = 1E-7f;
	short count = 0;
	while (((count == 0) || fabs(Enew - E) > zero) && (count < 100))
	{
		count++;
		E = Enew;
		Enew = E + (M - E + e*sin(E)) / (1.0f - e*cos(E));
	}
	E = Enew;

	return E;
}


GLfloat EccenToTrueAnomalyf(GLfloat e, GLfloat E)
{
	glf s = sinf(E)*sqrtf(1.0f - SQR(e)) / (1.0f - e * cosf(E));
	glf c = (cosf(E) - e) / (1.0f - e * cosf(E));
	glf f = atan2f(s, c);
	return f;
}
