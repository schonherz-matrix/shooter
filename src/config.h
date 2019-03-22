#ifndef CONFIG_H
#define CONFIG_H

namespace config{
    namespace chance{
        extern unsigned spawn_asteroide;  /**< The chance to an asteroide to be spawned is one of this number */
        extern unsigned spawn_powerup;  /**< The chance to a powerup to be spawned is one of this number */
    }

    namespace duration{
        extern unsigned time_between_fireing;  /**< The time must spend between to fire events from the same player*/
    }
}

#endif // CONFIG_H
