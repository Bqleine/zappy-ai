/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** connection.hpp
*/

#pragma once

#include <string>
#include "error/Error.hpp"
#include "arpa/inet.h"
#include <iostream>
#include <unistd.h>
#include "map/World_enums.hpp"

namespace ia {
    class Connection {
        public:
            Connection();
            ~Connection();

            void connectServer(int port, std::string ip);
            [[nodiscard]] Position2i getMapSize() const;
            int getNbClients(std::string team_name) const;
            [[nodiscard]] int getSocket() const;

        private:
            int _socket;
    };
}
