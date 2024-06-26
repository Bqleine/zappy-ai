/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Spawner
*/

#pragma once

#include "player/Role.hpp"

namespace ia {
    class Spawner : public Role {
        public:
            void run(Player &player) override;
        protected:
            void forkPlayers(Player &player, unsigned int amount);
            void spawnPlayers(Player &player, unsigned int amount, RoleEnum role, bool broadcast);
    };
};
