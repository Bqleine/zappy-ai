/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** error.cpp
*/

#include "error/Error.hpp"

Error::Error(const char *msg)
{
    _error_message = msg;
}

const char *Error::what() const noexcept
{
    return _error_message;
}
