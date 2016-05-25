#include <math.h>
#include <stdio.h>
#include <GL/freeglut.h>
#include <include/gaf_math.h>
#include "omech.h"
#include "defines.h"

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

GLfloat calc_phi(GLfloat e, GLfloat nu)
{
	// http://www.braeunig.us/space/orbmech.htm equation 4.44
	GLfloat n = e * sinf(nu);
	GLfloat d = 1.0f + e * cosf(nu);
	return atan2f(n, d);
}

GLfloat calc_v(GLfloat GM, GLfloat r, GLfloat a)
{
	// http://www.braeunig.us/space/orbmech.htm equation 4.45
	return sqrtf(GM * (2.0f / r - 1.0 / a));
}

GLfloat TrueToMeanAnomalyf(GLfloat e, GLfloat f)
{
	GLfloat E = TrueToEccenAnomalyf(e, f);
	GLfloat M = EccenToMeanAnomalyf(e, E);
	return M;
}

GLfloat TrueToEccenAnomalyf(GLfloat e, GLfloat f)
{
#ifdef calc_braeunig_eccentric
	GLfloat E;
	if (e < 1.0f)
	{
		GLfloat cf = cosf(f);
		E = -acosf((e + cf) / (1.0f + e * cf)); // prefixed negative seems required but is not part of the source material
	}
	else if (e == 1.0f)
	{
		E = tanf(f / 2.0f);
	}
	else
	{
		GLfloat cf = cosf(f);
		E = fabsf(acoshf((e + cf) / (1.0f + e * cf)));
		if (f < 0)
		{
			E = -E;
		}
	}
	return E;
#else
#ifdef calc_tan_eccentric
	if (e < 1.0)
	{
		return 2.0 * atan(tan(f / 2.0) / sqrt((1.0 + e) / (1.0 - e)));
	}
	//else if (e == 1.0)
	//{
	//	printf("TrueToEccenAnomalyf: e == 1\n");
	//	throw "fail";
	//}
	else
	{
		if (e == 1.0f)
		{
			e = 1.0001f;
		}
		return 2.0 * atanh(tan(f / 2.0) / sqrt((e + 1.0) / (e - 1.0)));
	}
#else
	// This can be simplified by removing the final (1.0f + e * cosf(f)) from each term I think...?
	GLfloat sinE = sinf(f) * sqrtf(1.0f - SQR(e)) / (1.0f + e * cosf(f));
	GLfloat cosE = (e + cosf(f)) / (1.0f + e * cosf(f));
	GLfloat E = atan2f(sinE, cosE);
	return E;
#endif
#endif
}

GLfloat EccenToMeanAnomalyf(GLfloat e, GLfloat E)
{
	if (e < 1.0f)
	{
		return E - e * sinf(E);
	}
	else if (e == 1.0f)
	{
		return E + powf(E, 3.0f) / 3.0f;
	}
	else
	{
		return e * sinhf(E) - E;
	}
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

double initial_E_AstronomyAnswers_Simple(double e, double M)
{
	M = fmod(M, TWO_PI_d) - PI_d;
	return cbrt(6.0 * M);
}

double initial_E_Standard(double e, double M)
{
	if (e < 0.8)
	{
		return M;
	}
	else
	{
		return PI_d;
	}
}

GLfloat MeanToEccenAnomalyf_AstronomyAnswers(GLfloat e, GLfloat M)
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

	if (count >= 100)
	{
		//throw "failed";
	}

	return (GLfloat)E;
}

#include <stdio.h>

// http://www.jgiesen.de/kepler/kepler.html
double MeanToEccenAnomalyf_JGiesen(double e, double M)
{
	//printf(">> e = %.16lf, M = %.16lf\n", e, M);

	short maxIter = 30, i = 0;
	double dp = 7.0;
	double delta = pow(10, -dp);

	M = fmod(M, TWO_PI_d) - PI_d;

	double E, F;

	if (e < 0.8)
	{
		E = M;
	}
	else
	{
		E = PI_d;
	}

	//E = initial_E_AstronomyAnswers_Simple(e, M);

	F = E - e*sin(M) - M;

	//printf("F = %.16lf\n", F);

	while ((fabs(F)>delta) && (i<maxIter)) {

		E = E - F / (1.0 - e*cos(E));
		F = E - e*sin(E) - M;

		//printf("i%d: E = %.16lf, F = %.16lf\n", i, E, F);

		i = i + 1;

	}

	if (i >= maxIter)
	{
		//printf("FAIL");
		//scanf_s("");
	}

	return E;
}

double MeanToEccenAnomalyf_Scannon(double e, double M)
{
	// Not done yet
	return 0;
}

// http://www.projectpluto.com/kepler.htm
static double near_parabolic(const double ecc_anom, const double e)
{
	const double anom2 = (e > 1. ? ecc_anom * ecc_anom : -ecc_anom * ecc_anom);
	double term = e * anom2 * ecc_anom / 6.;
	double rval = (1. - e) * ecc_anom - term;
	unsigned n = 4;

	while (fabs(term) > 1e-15)
	{
		term *= anom2 / (double)(n * (n + 1));
		rval -= term;
		n += 2;
	}
	return(rval);
}

// http://www.projectpluto.com/kepler.htm
#define MAX_ITERATIONS 7
#define THRESH 1.e-12
#define MIN_THRESH 1.e-15
#define CUBE_ROOT( X)  (exp( log( X) / 3.))
static double kepler(const double ecc, double mean_anom)
{
	double curr, err, thresh, offset = 0.;
	double delta_curr = 1.;
	bool is_negative = false;
	unsigned n_iter = 0;

	if (!mean_anom)
		return(0.);

	if (ecc < 1.)
	{
		if (mean_anom < -PI || mean_anom > PI)
		{
			double tmod = fmod(mean_anom, PI * 2.);

			if (tmod > PI)             /* bring mean anom within -pi to +pi */
				tmod -= 2. * PI;
			else if (tmod < -PI)
				tmod += 2. * PI;
			offset = mean_anom - tmod;
			mean_anom = tmod;
		}

		if (ecc < .9)     /* low-eccentricity formula from Meeus,  p. 195 */
		{
			curr = atan2(sin(mean_anom), cos(mean_anom) - ecc);
			do
			{
				err = (curr - ecc * sin(curr) - mean_anom) / (1. - ecc * cos(curr));
				curr -= err;
			} while (fabs(err) > THRESH);
			return(curr + offset);
		}
	}


	if (mean_anom < 0.)
	{
		mean_anom = -mean_anom;
		is_negative = true;
	}

	curr = mean_anom;
	thresh = THRESH * fabs(1. - ecc);
	/* Due to roundoff error,  there's no way we can hope to */
	/* get below a certain minimum threshhold anyway:        */
	if (thresh < MIN_THRESH)
		thresh = MIN_THRESH;
	if ((ecc > .8 && mean_anom < PI / 3.) || ecc > 1.)    /* up to 60 degrees */
	{
		double trial = mean_anom / fabs(1. - ecc);

		if (trial * trial > 6. * fabs(1. - ecc))   /* cubic term is dominant */
		{
			if (mean_anom < PI)
				trial = CUBE_ROOT(6. * mean_anom);
			else        /* hyperbolic w/ 5th & higher-order terms predominant */
				trial = asinh(mean_anom / ecc);
		}
		curr = trial;
	}
	if (ecc > 1. && mean_anom > 4.)    /* hyperbolic, large-mean-anomaly case */
		curr = log(mean_anom);

	if (ecc < 1.)
		while (fabs(delta_curr) > thresh)
		{
			if (n_iter++ > MAX_ITERATIONS)
				err = near_parabolic(curr, ecc) - mean_anom;
			else
				err = curr - ecc * sin(curr) - mean_anom;
			delta_curr = -err / (1. - ecc * cos(curr));
			curr += delta_curr;
		}
	else
		while (fabs(delta_curr) > thresh)
		{
			if (n_iter++ > MAX_ITERATIONS)
				err = -near_parabolic(curr, ecc) - mean_anom;
			else
				err = ecc * sinh(curr) - curr - mean_anom;
			delta_curr = -err / (ecc * cosh(curr) - 1.);
			curr += delta_curr;
		}
	return(is_negative ? offset - curr : offset + curr);
}


double MeanToEccenAnomalyf(double e, double M)
{
	return kepler(e, M);
}

GLfloat EccenToTrueAnomalyf(GLfloat e, GLfloat E)
{
#ifdef calc_braeunig_eccentric
	glf s = sinf(E)*sqrtf(1.0f - SQR(e)) / (1.0f - e * cosf(E));
	glf c = (cosf(E) - e) / (1.0f - e * cosf(E));
	glf f = atan2f(s, c);
	return f;
#else
#ifdef calc_tan_eccentric
	if (e < 1.0f)
	{
		return 2.0f * atanf(sqrtf((1.0f + e) / (1.0f - e)) * tanf(E / 2.0f));
	}
	//else if (e == 1.0f)
	//{
	//	throw "fail";
	//}
	else
	{
		if (e == 1.0f)
		{
			e = 1.0001f;
		}
		return 2.0f * atanf(sqrtf((e + 1.0f) / (e - 1.0f)) * tanhf(E / 2.0f));
	}
#else
	glf cosE = cosf(E);
	glf nu = fabsf(acosf((e - cosE) / (e * cosE - 1)));
	if (E < 0 || E > TWO_PI)
	{
		return -nu;
	}
	else
	{
		return nu;
	}
#endif
#endif
}
