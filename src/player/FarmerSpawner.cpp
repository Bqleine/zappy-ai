/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Spawner
*/

#include "player/FarmerSpawner.hpp"
#include "map/World_enums.hpp"
#include <iostream>

namespace ia {
    void FarmerSpawner::run(Player &player)
    {
        const unsigned int farmer_count = 7;
        // wait for eject
        while (player.getPos().x == 0 && player.getPos().y == 0)
            player.listenServer();
        world::Direction dir_spawner = (world::Direction) player.getEjectedDir();
        std::cout << "[FARMER SPAWNER] Ejected\n" << std::endl;
        for (int i = 0; i < dir_spawner - 1; i++) { // face towards spawner
            player.turnRight();
        }
        player.forward();
        forkPlayers(player, farmer_count);
        spawnPlayers(player, farmer_count - 1, RoleEnum::FARMER, false);
        spawnPlayers(player, 1, RoleEnum::FARMER_SPAWNER, false);
    }
}
