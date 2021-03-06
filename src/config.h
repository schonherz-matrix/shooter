#ifndef CONFIG_H
#define CONFIG_H

#include <chrono>

namespace config {
using tick = unsigned;

static constexpr bool shortened = false;
static constexpr int mapWidth = 2 * 8 * 2;
static constexpr int mapHeight = (shortened) ? 2 * 9 : 2 * 13;
static constexpr int borderYPos = (shortened) ? 17 : 25;
static constexpr int playerYPos = (shortened) ? 16 : 24;
static constexpr int hitIndicatorHeight = (shortened) ? 3 : 5;
static constexpr int hitIndicatorYOffset = (shortened) ? 1 : 3;
static constexpr int shrinkAmount = (shortened) ? 6 : 10;

namespace gameSpeed {
const extern tick fps; /**< Number of frames calculated and displayed */
extern tick time_between_shrink; /**< Number of ticks between the players move
                                    one step closer to each other*/
}  // namespace gameSpeed

namespace chance {
extern unsigned spawn_asteroide; /**< Avarage time between asteroide spawns */
extern unsigned spawn_powerup;   /**< Avarage time between powerup spawns */
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

namespace distance {
extern double player_spawn_asteroide;
extern double asteroide_evelation;
}  // namespace distance

extern double missile_speed;

namespace players {
extern unsigned max_life;
extern unsigned hurt_by_shot;
}  // namespace players

tick operator"" _ms(unsigned long long ms); /**< Returns the number of tick for
                                               the wanted delay*/
tick operator"" _s(unsigned long long s);   /**< Returns the number of tick for
                                               the wanted delay*/
}  // namespace config

#endif  // CONFIG_H
