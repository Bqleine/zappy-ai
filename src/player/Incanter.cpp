/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Incanter.cpp
*/

#include "player/Incanter.hpp"
#include <iostream>

namespace ia {
    void Incanter::run(Player &player)
    {
        const int needed_food = 30;
        int nb_broadcasts = 0;

        player.inventory();

        while (player.getInventory()[world::food] < needed_food)
            player.takeObject(world::food);
        std::string ready = "Ready for incantation.";
        player.broadcast(ready);
        nb_broadcasts += 1;
        std::cout << "[INCANTER] " << "Waiting for incanters.\n";
        while (nb_broadcasts != 6) {
            if (player.getInventory()[world::food] < needed_food) {
                player.takeObject(world::food);
            }
            player.listenServer();
            if (this->listenReady(player))
                nb_broadcasts += 1;
        }
        std::cout << "[INCANTER] " << "Starting incantations.\n";
        player.look();
        while (player.getLevel() != 8)
            player.incantation();
    }

    bool Incanter::listenReady(Player &player) const
    {
        bool player_ready = false;

        if (!player.getMessages().empty()) {
            std::cout << "[INCANTER] Message received: " << player.getMessages().at(0).getData() <<
                std::endl;
            if (player.getMessages().at(0).getData() == "Ready for incantation.")
                player_ready = true;
            player.eraseMessage(0);
        }
        return player_ready;
    }
}
