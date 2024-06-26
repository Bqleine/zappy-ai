/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Repeater.hpp
*/

#pragma once

#include "Role.hpp"

namespace ia {
    class Repeater : public Role {
        public:
            void run(Player &player) override;
    };
};
