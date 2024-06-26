/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Nitwit
*/

#include "player/Nitwit.hpp"

void ia::Nitwit::run(Player &player)
{
    while (1)
        player.listenServer();
}
