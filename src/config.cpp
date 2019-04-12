#include "config.h"

using namespace config;
using namespace std::literals::chrono_literals;

const tick config::gameSpeed::fps = 33;
tick config::gameSpeed::time_between_shrink = 45_s;

unsigned config::chance::spawn_asteroide = 2_s;
unsigned config::chance::spawn_powerup = 12_s;

std::chrono::milliseconds config::duration::time_between_firing = 500ms;
std::chrono::milliseconds config::duration::time_between_firing_fast = 200ms;
std::chrono::milliseconds config::duration::powerup_effect = 8s;
std::chrono::milliseconds config::duration::laser = 3s;

tick config::operator"" _ms(unsigned long long ms) {
  return gameSpeed::fps * static_cast<unsigned>(ms) / 1000;
}

tick config::operator"" _s(unsigned long long s) {
  return gameSpeed::fps * static_cast<unsigned>(s);
}
