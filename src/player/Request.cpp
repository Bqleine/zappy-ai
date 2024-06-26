/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Request.cpp
*/

#include "player/Request.hpp"

#include <utility>

namespace ia {
    Response::Response(bool ok, int value, std::string data) : _ok(ok), _value(value),
                                                               _data(std::move(data))
    {
    }

    bool Response::getOk() const
    {
        return _ok;
    }

    int Response::getValue() const
    {
        return _value;
    }

    std::string Response::getData() const
    {
        return _data;
    }

    Broadcast_message::Broadcast_message(int dir, std::string &data) : _dir(dir), _data(data)
    {
    }

    int Broadcast_message::getDir() const
    {
        return _dir;
    }

    std::string Broadcast_message::getData() const
    {
        return _data;
    }
}
