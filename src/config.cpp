#include "config.h"

using namespace config;


const tick config::gameSpeed::fps = 33;
tick config::gameSpeed::time_between_shrink = 10_s;

unsigned config::chance::spawn_asteroide = 100;
unsigned config::chance::spawn_powerup = 600;

tick config::duration::time_between_fireing = 500_ms;
tick config::duration::time_between_fireing_fast = 200_ms;
tick config::duration::powerup_effect = 5_s;
tick config::duration::laser_spacing = 70_ms;




tick config::operator"" _ms(unsigned long long ms){
    return gameSpeed::fps * static_cast<unsigned>(ms) / 1000;
}

tick config::operator"" _s(unsigned long long s){
    return gameSpeed::fps * static_cast<unsigned>(s);
}
