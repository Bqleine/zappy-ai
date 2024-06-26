/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Requests.hpp
*/

#pragma once

#include <string>

namespace ia {
    enum Request {
        move_up = 1,
        turn_right,
        turn_left,
        look,
        inventory,
        broadcast,
        number_unused,
        fork,
        eject,
        take,
        set_down,
        start_incantation,
        end_incantation
    };

    class Response {
        private:
            bool _ok;
            int _value;
            std::string _data;

        public:
            Response(bool ok = false, int value = -1, std::string data = "");
            ~Response() = default;

            [[nodiscard]] bool getOk() const;
            [[nodiscard]] int getValue() const;
            [[nodiscard]] std::string getData() const;
    };

    class Broadcast_message {
        private:
            int _dir;
            std::string _data;

        public:
            Broadcast_message(int dir, std::string &data);
            ~Broadcast_message() = default;

            [[nodiscard]] int getDir() const;
            [[nodiscard]] std::string getData() const;
    };
}
