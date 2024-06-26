/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** main.cpp
*/

#include "Ia.hpp"
#include "player/Player.hpp"

std::string show_usage()
{
    return "USAGE: ./zappy_ai -p port -n name -h machine";
}

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "-help") == 0) {
        std::cout << show_usage().c_str() << std::endl;
        return 0;
    }

    ia::Parsing parsing;
    parsing.parseArgs(argc, argv);

    ia::Connection connection{};
    connection.connectServer(parsing.getPort(), parsing.getMachine());
    int nb_left = connection.getNbClients(parsing.getTeamName());
    Position2i map_size = connection.getMapSize();
    ia::Player ia(map_size, connection.getSocket(), parsing, nb_left, parsing.getRole());
    ia.runPlayer();
}
