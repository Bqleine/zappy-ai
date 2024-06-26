/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Gatherer.cpp
*/

#include "player/Gatherer.hpp"
#include "player/Incanter.hpp"
#include <iostream>

namespace ia {
    void Gatherer::run(Player &player)
    {
        int row = -1;

        // waiting to be ejected by Spawner
        // this defines Spawner dir
        while (player.getPos().x == 0 && player.getPos().y == 0)
            player.listenServer();

        while (row == -1) {
            player.listenServer(); // get the row asked by the Spawner
            row = this->listenRow(player);
        }
        
        world::Direction dir_spawner = (world::Direction) player.getEjectedDir();
        std::cout << "[GATHERER] Ejected\n";

        int turn_times = (6 + dir_spawner - 1) % 4;
        std::cout << "[GATHERER] turning " << turn_times << "times" << std::endl;
        for (int i = 0; i < turn_times; i++) { // face away from spawner
            player.turnRight();
        }
        std::cout << "[GATHERER] Facing same direction as spawner." << std::endl;

        std::cout << "[GATHERER] going to row " << row << " direction " << dir_spawner << std::endl;
        for (int i = 0; i != row; i++)
            player.forward();

        player.turnLeft(); // face in the direction of the row

        std::cout << "[GATHERER] Harvesting row." << std::endl;;
        // take every ressources on his row
        if (player.getDir() == world::west || player.getDir() == world::east) {
            for (int i = 0; i != player.getMap().getSize().x; i++)
                this->pickUpTile(player);
        } else {
            for (int i = 0; i != player.getMap().getSize().y; i++)
                this->pickUpTile(player);
        }

        std::cout << "[GATHERER] finished harvesting row" << std::endl;

        player.turnLeft(); // face towards spawner

        for (int i = 0; i != row + 1; i++)
            player.forward(); // go to Spawner

        player.inventory();
        this->dropInventory(player); // drop every ressources except food
        player.changeRole(RoleEnum::INCANTER); // becomes Incanter
    }

    void Gatherer::pickUpTile(Player &player)
    {
        player.forward();
        player.look();

        for (auto &ressource : valuesRessources())
            while (player.getMap().getTile(player.getPos()).getRessources()[ressource] > 0)
                player.takeObject(ressource);
        std::cout << "[GATHERER] look after below" << std::endl;
        player.look();
    }

    void Gatherer::dropInventory(Player &player)
    {
        for (auto &ressource : valuesRessources()) {
            if (ressource == world::Ressource::food)
                continue;
            while (player.getInventory()[ressource] > 0)
                player.setObject(ressource);
        }
    }

    int Gatherer::listenRow(Player &player) const
    {
        int row = -1;

        if (!player.getMessages().empty()) {
            std::cout << "[GATHERER] Message: " << player.getMessages().at(0).getData() <<
                std::endl;
            row = std::stoi(player.getMessages().at(0).getData());
            player.eraseMessage(0);
        }
        return row;
    }
}
