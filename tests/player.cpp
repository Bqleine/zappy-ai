/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** player.cpp
*/

#include <criterion/criterion.h>
#include "player/Player.hpp"
#include "connection/Connection.hpp"
#include "parsing/Parsing.hpp"

#define PORT_TEST 4243
#define TEAM_NAME_TEST "test"
#define MACHINE_TEST "127.0.0.1"

TestSuite(playerConnection);
TestSuite(playerCommands);

/* SERVER SHOULD BE RUNNING WITH FOLLOWING PARAMETERS
    ./zappy_server -p 4243 -x 30 -y 30 -n team1 team2 team3 test -c 10
*/

ia::Player connect_ia()
{
    try {
        ia::Connection connection{};
        connection.connectServer(PORT_TEST, "127.0.0.1");
        connection.getNbClients(TEAM_NAME_TEST);

        Position2i map_size = connection.getMapSize();
        ia::Parsing parsing{PORT_TEST, TEAM_NAME_TEST, MACHINE_TEST, ia::RoleEnum::NITWIT};
        int nb_left = connection.getNbClients(parsing.getTeamName());
        ia::Player ia(map_size, connection.getSocket(), parsing, nb_left, ia::RoleEnum::NITWIT);
        return ia;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
}

Test(playerConnection, basicConnection)
{
    ia::Player ia = connect_ia();

    ia.forward();

    cr_assert_eq(ia.getPos().x, 0);
    cr_assert_eq(ia.getPos().y, 1);
}

Test(playerCommands, forwardNorth)
{
    ia::Player ia = connect_ia();

    ia.forward();

    cr_assert_eq(ia.getPos().x, 0);
    cr_assert_eq(ia.getPos().y, 1);
}

Test(playerCommands, forwardEast)
{
    ia::Player ia = connect_ia();

    ia.turnRight();
    ia.forward();

    cr_assert_eq(ia.getPos().x, 1);
    cr_assert_eq(ia.getPos().y, 0);
}

Test(playerCommands, forwardSouth)
{
    ia::Player ia = connect_ia();

    ia.turnRight();
    ia.turnRight();
    ia.forward();

    cr_assert_eq(ia.getPos().x, 0);
    cr_assert_eq(ia.getPos().y, ia.getMap().getSize().x);
}

Test(playerCommands, forwardWest)
{
    ia::Player ia = connect_ia();

    ia.turnLeft();
    ia.forward();

    cr_assert_eq(ia.getPos().x, ia.getMap().getSize().x);
    cr_assert_eq(ia.getPos().y, 0);
}

Test(playerCommands, inventory)
{
    ia::Player ia = connect_ia();

    ia.inventory();

    cr_assert_eq(ia.getInventory().at(world::Ressource::linemate), 0);
    cr_assert_eq(ia.getInventory().at(world::Ressource::deraumere), 0);
    cr_assert_eq(ia.getInventory().at(world::Ressource::sibur), 0);
    cr_assert_eq(ia.getInventory().at(world::Ressource::mendiane), 0);
    cr_assert_eq(ia.getInventory().at(world::Ressource::phiras), 0);
    cr_assert_eq(ia.getInventory().at(world::Ressource::thystame), 0);
    cr_assert_eq(ia.getInventory().at(world::Ressource::food), 10);
}

Test(playerCommands, addInventory)
{
    ia::Player ia = connect_ia();

    ia.addInventory(world::linemate);

    cr_assert_eq(ia.getInventory().at(world::Ressource::linemate), 1);
}

Test(playerCommands, subInventory)
{
    ia::Player ia = connect_ia();

    ia.addInventory(world::linemate);
    ia.subInventory(world::linemate, 1);

    cr_assert_eq(ia.getInventory().at(world::Ressource::linemate), 0);
}

Test(playerCommands, ejectedNorth)
{
    ia::Player ia = connect_ia();

    ia.playerEjected(world::Direction::north);

    cr_assert_eq(ia.getPos().x, 0);
    cr_assert_eq(ia.getPos().y, 1);
}

Test(playerCommands, ejectedEast)
{
    ia::Player ia = connect_ia();

    ia.playerEjected(world::Direction::east);

    cr_assert_eq(ia.getPos().x, 1);
    cr_assert_eq(ia.getPos().y, 0);
}

Test(playerCommands, ejectedSouth)
{
    ia::Player ia = connect_ia();

    ia.playerEjected(world::Direction::south);

    cr_assert_eq(ia.getPos().x, 0);
    cr_assert_eq(ia.getPos().y, ia.getMap().getSize().x);
}

Test(playerCommands, ejectedWest)
{
    ia::Player ia = connect_ia();

    ia.playerEjected(world::Direction::west);

    cr_assert_eq(ia.getPos().x, ia.getMap().getSize().y);
    cr_assert_eq(ia.getPos().y, 0);
}
