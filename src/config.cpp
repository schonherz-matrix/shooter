#include "config.h"

using namespace config;
using namespace std::literals::chrono_literals;

const tick config::gameSpeed::fps = 33;
tick config::gameSpeed::time_between_shrink = 45_s;

unsigned config::chance::spawn_asteroide = 3_s;
unsigned config::chance::spawn_powerup = 5500_ms;

std::chrono::milliseconds config::duration::time_between_firing = 500ms;
std::chrono::milliseconds config::duration::time_between_firing_fast = 200ms;
std::chrono::milliseconds config::duration::powerup_effect = 8s;
std::chrono::milliseconds config::duration::laser = 3s;

double config::distance::player_spawn_asteroide = 3;
double config::distance::asteroide_evelation = 5;

tick config::operator"" _ms(unsigned long long ms) {
  return gameSpeed::fps * static_cast<unsigned>(ms) / 1000;
}

tick config::operator"" _s(unsigned long long s) {
  return gameSpeed::fps * static_cast<unsigned>(s);
}

unsigned config::players::max_life = 1000;
unsigned config::players::hurt_by_shot = 15;
