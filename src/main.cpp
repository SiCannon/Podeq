#include <include/gaf.h>
#include <include/gaf_glut.h>
#include <include/gaf_math.h>
#include <include/game_engine.h>
#include "podeq_game.h"
#include "start_params.h"

PodeqGame *podeq;

//#define debug_only

#ifndef debug_only

int main(int argc, char **argv)
{
	gameEngine = new GameEngine();
	podeq = new PodeqGame();
	gameEngine->world_transform->scale = start_scale;

	init_glut(argc, argv, "Podeq");

	delete(podeq);
	delete(gameEngine);

	return EXIT_SUCCESS;
}

#else

#include "omech.h"

int main()
{
	/*
	double ee = 30.007955242571953;
	double ff = 22.52964313277449;
	double ec = 0.803313971;
	double result = ee - ff / (1.0 - ec * cos(ee));
	printf("%.10lf\n\n", result);
	*/
	



	// 6.2522577281117275
	double e = 0.8025833964347839;
	double M = 10.4401988983154297;

	double E = MeanToEccenAnomalyf(e, M);
	printf("e=%.10lf\n", e);
	printf("M=%.10lf (radians)\n", M);
	printf("M=%.10lf (degress)\n", r_to_d(M));
	printf("result: %.10lf (radians)\n", E);
	printf("result: %.10lf (degrees)\n\n", r_to_d(E));

	printf("... exit ...\n");
	scanf_s("");
	return true;
}

#endif