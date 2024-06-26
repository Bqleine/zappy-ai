/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** connection.cpp
*/

#include "connection/Connection.hpp"

#include <utility>

namespace ia {
    Connection::Connection()
    {
        _socket = socket(AF_INET, SOCK_STREAM, 0);
        if (_socket < 0)
            throw::Error("Error during socket creation.");
    }

    Connection::~Connection()
    {
        close(_socket);
    }

    void Connection::connectServer(int port, std::string ip)
    {
        struct sockaddr_in serv_addr;
        char c;

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);

        if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0)
            throw::Error("Invalid address. / Address not supported.");

        if (connect(_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
            throw::Error("Connection failed.");

        while (read(_socket, &c, 1) > 0 && c != '\n');
    }

    Position2i Connection::getMapSize() const
    {
        char c;
        std::string map_size;
        std::string str_x;
        std::string str_y;

        while (read(_socket, &c, 1) > 0 && c != '\n')
            map_size += c;

        size_t posSplit = map_size.find(' ');
        if (posSplit != std::string::npos) {
            str_x = map_size.substr(0, posSplit);
            str_y = map_size.substr(posSplit + 1, map_size.size());
        } else {
            throw Error("Can't get map size from server.");
        }

        return {std::stoi(str_x),
                std::stoi(str_y)};
    }

    int Connection::getNbClients(std::string team_name) const
    {
        std::string client_num;
        char c;
        std::string team_name_formatted = std::move(team_name);
        team_name_formatted += '\n';

        send(_socket, team_name_formatted.c_str(), team_name_formatted.size(), 0);
        while (read(_socket, &c, 1) > 0 && c != '\n')
            client_num += c;

        if (client_num == "ko")
            throw Error("Team is full, can't connect.");
        return std::stoi(client_num);
    }


    int Connection::getSocket() const
    {
        return _socket;
    }
}
