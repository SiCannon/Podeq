all: compile
	@echo "compiled ok!"

src_files = \
		src/monster.cpp \
		src/planet.cpp \
		src/orbit_path.cpp \
		src/ellipse.cpp \
		src/ship.cpp \
		src/omech.cpp \
		src/orbit.cpp

gaf_files = \
		gaf/transform.cpp \
		gaf/timer.cpp \
		gaf/base_actor.cpp \
		gaf/screenutil.cpp \
		gaf/textutils.cpp \
		gaf/mouse.cpp \
		gaf/keyboard.cpp \
		gaf/shapes.cpp \
		gaf/gaf_math.cpp

compile:
	g++ -std=c++11 -g \
		-I include \
		-I gaf \
		src/main.cpp \
		$(src_files) \
		$(gaf_files) \
		-lGL \
		-lglut \
		-o bin/podeq

run: all
	bin/podeq
	
test:
	g++ -std=c++11 -g \
		-I include \
		-I gaf \
		src/test.cpp \
		$(src_files) \
		$(gaf_files) \
		-lGL \
		-lglut \
		-o bin/test