/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** error.hpp
*/

#pragma once

#include "exception"

class Error: public std::exception {
private:
    const char *_error_message;
public:
    Error(const char *msg);
    [[nodiscard]] const char *what() const noexcept override;
};
