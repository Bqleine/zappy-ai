/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Gatherer.hpp
*/

#pragma once

#include "Role.hpp"
#include "map/World_enums.hpp"

namespace ia {
    class Gatherer : public Role {
        public:
            void run(Player &player) override;
            void pickUpTile(Player &player);
            void dropInventory(Player &player);

            [[nodiscard]] int listenRow(Player &player) const;
            [[nodiscard]] world::Direction getDirEjected(Player &player) const;
    };
};
