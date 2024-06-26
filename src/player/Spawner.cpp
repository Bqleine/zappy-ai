/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Spawner
*/

#include "player/Spawner.hpp"
#include "map/World_enums.hpp"
#include <cstdlib>
#include <iostream>
#include <unistd.h>

namespace ia {
    void Spawner::forkPlayers(Player &player, unsigned int amount)
    {
        for (unsigned int i = 0; i < amount; i++) {
            std::cout << "[SPAWNER] forking player #" << i << std::endl;
            player.forkPlayer(RoleEnum::NITWIT);
        }
    }
    
    void Spawner::spawnPlayers(Player &player, unsigned int amount, RoleEnum role, bool broadcast)
    {
        unsigned int spawned = 0;
        do {
            player.nbrConnect();
            if (player.getNbLeft() >= 1) {
                std::cout << "[SPAWNER] spawning player #" << spawned << std::endl;
                player.startOtherPlayer(role);
                if (broadcast) {
                    std::string msg = std::to_string(spawned);
                    player.broadcast(msg);
                }
                spawned++;
            }
            usleep(100'000);
        } while (spawned < amount);
        std::cout << "[SPAWNER] all eggs spawned" << std::endl;
    }

    void Spawner::run(Player &player)
    {
        // Fill other eggs
        std::cout << "[SPAWNER] spawning " << player.getNbLeft() << " nitwits to fill extra eggs" <<
            std::endl;
        for (size_t i = 0; i < player.getNbLeft(); i++) {
            player.startOtherPlayer(RoleEnum::NITWIT);
        }

        unsigned int gatherer_count = std::min(10, player.getMap().getSize().x - 1);
        forkPlayers(player, gatherer_count + 3);

        std::cout << "[SPAWNER] spawning " << gatherer_count << " gatherers" << std::endl;
        spawnPlayers(player, gatherer_count, RoleEnum::GATHERER, true);
        spawnPlayers(player, 3, RoleEnum::FARMER_SPAWNER, false);
        do {
            player.nbrConnect();
        } while (player.getNbLeft() != 0);
        player.ejectPlayers();
    }
};
