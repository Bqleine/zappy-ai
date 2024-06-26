/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Farmer.cpp
*/

#include "player/Farmer.hpp"

namespace ia {
    void Farmer::run(Player &player)
    {
        for (int i = 0; i < 9; i++) {
            player.setObject(world::Ressource::food);
        }
    }
}
