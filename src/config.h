#ifndef CONFIG_H
#define CONFIG_H

#include <chrono>

namespace config {
using tick = unsigned;

namespace gameSpeed {
const extern tick fps; /**< Number of frames calculated and displayed */
extern tick time_between_shrink; /**< Number of ticks between the players move
                                    one step closer to each other*/
}  // namespace gameSpeed

namespace chance {
extern unsigned spawn_asteroide; /**< Avarage time between asteroide spawns */
extern unsigned spawn_powerup; /**< Avarage time between powerup spawns */
}  // namespace chance

namespace duration {
extern std::chrono::milliseconds
    time_between_firing_fast; /**< The time must spend between to fire events
                                 from the same player, when TRIPLE_SHOOT powerup
                                 is active*/
extern std::chrono::milliseconds
    time_between_firing; /**< The time must spend between to fire events from
                            the same player*/
extern std::chrono::milliseconds
    powerup_effect; /**< The time for the powerup to effext*/
extern std::chrono::milliseconds laser;
}  // namespace duration

tick operator"" _ms(unsigned long long ms); /**< Returns the number of tick for
                                               the wanted delay*/
tick operator"" _s(unsigned long long s);   /**< Returns the number of tick for
                                               the wanted delay*/
}  // namespace config

#endif  // CONFIG_H
