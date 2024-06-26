/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** parsing.cpp
*/

#include "parsing/Parsing.hpp"
#include <iostream>

namespace ia {
    Parsing::Parsing()
    {
        _role = RoleEnum::SPAWNER;
        _port = -1;
    }

    Parsing::Parsing(int port, std::string team_name, std::string machine, RoleEnum role) :
        _port(port),
        _team_name(std::move(team_name)), _machine(std::move(machine)), _role(role)
    {
    }

    int Parsing::getPort() const
    {
        return _port;
    }

    std::string Parsing::getTeamName() const
    {
        return _team_name;
    }

    std::string Parsing::getMachine() const
    {
        return _machine;
    }

    RoleEnum Parsing::getRole() const
    {
        return _role;
    }

    void Parsing::parseArgs(int argc, char *argv[])
    {
        if (argc < 5)
            throw::Error("Missing arguments.");
        if (argc > 9)
            throw::Error("Too much arguments.");

        for (int i = 1; i < argc;) {
            if (strcmp(argv[i], "-p") == 0) {
                _port = std::stoi(argv[i + 1]);
                i += 2;
                continue;
            }
            if (strcmp(argv[i], "-n") == 0) {
                _team_name = argv[i + 1];
                i += 2;
                continue;
            }
            if (strcmp(argv[i], "-h") == 0) {
                _machine = argv[i + 1];
                i += 2;
                continue;
            }
            if (strcmp(argv[i], "-r") == 0) {
                if (strcmp(argv[i + 1], "nitwit") == 0)
                    _role = RoleEnum::NITWIT;
                else if (strcmp(argv[i + 1], "spawner") == 0)
                    _role = RoleEnum::SPAWNER;
                else if (strcmp(argv[i + 1], "farmer") == 0)
                    _role = RoleEnum::FARMER;
                else if (strcmp(argv[i + 1], "gatherer") == 0)
                    _role = RoleEnum::GATHERER;
                else if (strcmp(argv[i + 1], "incanter") == 0)
                    _role = RoleEnum::INCANTER;
                else if (strcmp(argv[i + 1], "repeater") == 0)
                    _role = RoleEnum::REAPEATER;
                else if (strcmp(argv[i + 1], "farmer_spawner") == 0)
                    _role = RoleEnum::FARMER_SPAWNER;
                i += 2;
                continue;
            }
        }
        if (_port == -1)
            throw::Error("No port specified.");
        if (_port < 0)
            throw::Error("Port must be valid.");
        if (_team_name.empty())
            throw::Error("No team name specified.");
    }
}
