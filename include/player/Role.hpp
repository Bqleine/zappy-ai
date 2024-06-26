/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Player role algorithms
*/

#pragma once

#include "Player.hpp"

namespace ia {
    class Role {
        public:
            virtual ~Role() = default;

            virtual void run(Player &player) = 0;
    };
};
