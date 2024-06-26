/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** parsing.hpp
*/

#pragma once

#include <string>
#include "error/Error.hpp"
#include "map/World_enums.hpp"
#include <cstring>

namespace ia {
    class Parsing {
        public:
            Parsing();
            Parsing(int port, std::string team_name, std::string machine, RoleEnum role);
            ~Parsing() = default;

            [[nodiscard]] int getPort() const;
            [[nodiscard]] std::string getTeamName() const;
            [[nodiscard]] std::string getMachine() const;
            [[nodiscard]] RoleEnum getRole() const;
            void parseArgs(int argc, char *argv[]);

        private:
            int _port;
            std::string _team_name;
            std::string _machine = "127.0.0.1";
            RoleEnum _role;
    };
}
