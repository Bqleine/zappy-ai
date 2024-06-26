/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Repeater.cpp
*/

#include "player/Repeater.hpp"
#include <unistd.h>

namespace ia {
    void Repeater::run(Player &player)
    {
        while (player.getInventory()[world::food] > 5) {
            player.inventory();
            while (!player.getUndesiredMessages().empty()) {
                std::string data = player.getUndesiredMessages().at(0).getData();
                player.broadcast(data);
                player.eraseUndesiredMessage(0);
            }
        }
        player.forkPlayer(RoleEnum::REAPEATER);
        player.nbrConnect();
        do {
            player.nbrConnect();
            usleep(100'000);
        } while (player.getNbLeft() != 1);
        player.startOtherPlayer(RoleEnum::REAPEATER);
    }
}
