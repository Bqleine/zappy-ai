/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Look parsing tests
*/

#include "player/Player.hpp"
#include <criterion/criterion.h>
#include "map/Map.hpp"

#define FILL_MAP(request) do {                                          \
        ia::Player player{{30, 30}, 0, {}, 0, ia::RoleEnum::NITWIT}; \
        std::string str = request;                                      \
        player.fillMap(str);                                            \
    } while (0)

Test(look, all_one_thing)
{
    FILL_MAP("[player,thystame,food]");
}

Test(look, all_one_thing_spaces)
{
    FILL_MAP("[player, thystame, food]");
}

Test(look, all_one_thing_spaces_anywhere)
{
    FILL_MAP("[ player , thystame ,food ]");
}

Test(look, empty_tiles)
{
    FILL_MAP("[,,]");
}

Test(look, multiple_things_in_one_tile)
{
    FILL_MAP("[player player thystame,,food player food player]");
}

Test(look, long_array)
{
    FILL_MAP(
        "[player player thystame,,food player food player,,,thystame,food,phiras,sibur,,deraumere,,mendiane mendiane food,,]")
    ;
}

Test(look, rotations)
{
    ia::Player player{{30, 30}, 0, {}, 0, ia::RoleEnum::NITWIT};
    Position2i pos;
    pos = player.rotatePointToDirection({1, 1});
    cr_assert(pos.x == 1 && pos.y == 1);
    player.setDirection(world::Direction::west);
    pos = player.rotatePointToDirection({1, 1});
    cr_assert(pos.x == -1 && pos.y == 1);
}
