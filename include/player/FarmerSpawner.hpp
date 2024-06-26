/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Spawner
*/

#pragma once

#include "player/Role.hpp"
#include "player/Spawner.hpp"

namespace ia {
    class FarmerSpawner : protected Spawner {
        public:
            void run(Player &player) override;
    };
};
