#ifndef SOUND_H
#define SOUND_H
#include <cstdint>

const double c = 1/261.0;
const double d = 1/294.0;
const double e = 1/329.0;
const double f = 1/349.0;
const double g = 1/391.0;
const double gS = 1/415.0;
const double a = 1/440.0;
const double aS = 1/455.0;
const double b = 1/466.0;
const double cH = 1/523.0;
const double cSH = 1/554.0;
const double dH = 1/587.0;
const double dSH = 1/622.0;
const double eH = 1/659.0;
const double fH = 1/698.0;
const double fSH = 1/740.0;
const double gH = 1/784.0;
const double gSH = 1/830.0;
const double aH = 1/880.0;

const double star_wars_notes[] = {a, a, a, f, cH, a, f, cH, a, NULL, eH, eH, eH, fH, cH, gS, f, cH, a, NULL};
const uint32_t star_wars_time[] = {500, 500, 500, 350, 150, 500, 350, 150, 650, 500, 500, 500, 500, 350, 150, 500, 350, 150, 650, 500};

const double shoot_notes[] = {fH, eH, dSH, dH};
const uint32_t shoot_time[] = {25, 25, 25, 25};

const double explosion_notes[] = {aH, gH, fH, dSH, cSH, b};
const uint32_t explosion_time[] = {25, 25, 25, 25, 25, 25};

const double game_over_notes[] = {cH, aH, e, gSH, gS, aH, NULL};
const uint32_t game_over_time[] = {200, 200, 200, 200, 200, 200, 500};

const double win_notes[] = {cH, cH, cH, gH, cH, eH, NULL};
const uint32_t win_time[] = {200, 200, 200, 150, 500, 1000, 500};

#endif