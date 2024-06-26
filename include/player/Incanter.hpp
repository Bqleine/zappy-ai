/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Incanter.hpp
*/

#pragma once

#include "Role.hpp"

namespace ia {
    class Incanter : public Role {
        public:
            void run(Player &player) override;
            [[nodiscard]] bool listenReady(Player &player) const;
    };
};
