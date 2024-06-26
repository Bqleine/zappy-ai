/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Farmer.hpp
*/

#pragma once

#include "Role.hpp"

namespace ia {
    class Farmer : public Role {
        public:
            void run(Player &player) override;
    };
};
