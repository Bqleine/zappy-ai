/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** World_enums.hpp
*/

#pragma once

#include <string>
#include <map>
#include <vector>

namespace ia {
    enum class RoleEnum {
        NITWIT, // do nothing
        SPAWNER, // spawns gatherers
        FARMER, // forks and drops food
        GATHERER, // harvest a column
        INCANTER, // start incantation to level up
        REAPEATER, // repeat all broadcast sent by other team
        FARMER_SPAWNER,         // spawns farmers
    };
}

namespace world {
    enum Ressource {
        linemate = 1,
        deraumere,
        sibur,
        mendiane,
        phiras,
        thystame,
        food
    };

    enum Direction {
        north = 1,
        east,
        south,
        west
    };
}

class Position2i {
    public:
        int x;
        int y;

        [[nodiscard]] std::string posToStr() const;
};

std::string ressourceToStr(world::Ressource ressource);
world::Ressource strToRessource(const char *str);
std::string roleToStr(ia::RoleEnum role);
std::vector<world::Ressource> valuesRessources();
