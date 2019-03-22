#ifndef CONFIG_H
#define CONFIG_H

namespace config{
    using tick = unsigned;

    namespace gameSpeed{
        const extern tick fps; /**< Number of frames calculated and displayed */
        extern tick time_between_shrink; /**< Number of ticks between the players move one step closer to each other*/
    }

    namespace chance{
        extern unsigned spawn_asteroide;  /**< The chance to an asteroide to be spawned is one of this number */
        extern unsigned spawn_powerup;  /**< The chance to a powerup to be spawned is one of this number */
    }

    namespace duration{
        extern tick time_between_fireing;  /**< The time must spend between to fire events from the same player*/
        extern tick powerup_effect;  /**< The time for the powerup to effext*/
        extern tick laser_spacing;  /**< The time between laser-missiles*/
    }

    tick operator"" _ms(unsigned long long ms); /**< Returns the number of tick for the wanted delay*/
    tick operator"" _s(unsigned long long s); /**< Returns the number of tick for the wanted delay*/
}

#endif // CONFIG_H
