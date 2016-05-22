#pragma once

#define INTIAL_WNDOW_WIDTH 800
#define INITIAL_WINDOW_HEIGHT 600

#define GravConstant 1.0f

#define Seed 3349653

#define calculated_orbit
//#define show_predicted_orbit
//#define draw_calculated_orbit

// Treat planets and ships as satellites in orbital calculations
#define use_satellites

// Use formulas from braeunig and/or http://www.bogan.ca/orbits/kepler/orbteqtn.html for calculating Eccentric Anomaly
//#define calc_braeunig_eccentric
#define calc_tan_eccentric

//#define hide_game_elements
//#define show_debug_graph