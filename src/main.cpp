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


#include <vector>
int my_function(int x)
{
	return x * 5;
}
int my_other_function(int a)
{
	return a * 10;
}

typedef int(*func_pointer)(int x);

std::vector<func_pointer> pointers;

void register_callback(func_pointer fp)
{
	pointers.push_back(fp);
}
void call_them(int x)
{
	for (unsigned int i = 0; i < pointers.size(); i++)
	{
		int r = pointers[i](x);
		printf("r:%d\n", r);
	}
}
void Test_FunctionPointers()
{
	register_callback(my_function);
	register_callback(my_other_function);
	call_them(20);
}

#include "omech.h"
void Test_MeanToEccenAnomalyf()
{
	double e = 0.8025833964347839;
	double M = 10.4401988983154297;

	double E = MeanToEccenAnomalyf(e, M);
	printf("e=%.10lf\n", e);
	printf("M=%.10lf (radians)\n", M);
	printf("M=%.10lf (degress)\n", r_to_d(M));
	printf("result: %.10lf (radians)\n", E);
	printf("result: %.10lf (degrees)\n\n", r_to_d(E));
}

int main()
{
	Test_FunctionPointers();

	printf("\n\n... exit ...\n");
	scanf_s("");
	return true;
}

#endif