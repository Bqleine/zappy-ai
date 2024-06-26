/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Utils.cpp
*/

#include "Utils.hpp"

bool isNumber(const std::string &s)
{
    for (char c : s) {
        if (!isdigit(c) && c != '\n') {
            return false;
        }
    }
    return true;
}
