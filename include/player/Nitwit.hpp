/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Nitwit
*/

#pragma once

#include "Role.hpp"

namespace ia {
    class Nitwit : public Role {
        public:
            void run(Player &player) override;
    };
};
