/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** World_enums.cpp
*/

#include "map/World_enums.hpp"

std::string Position2i::posToStr() const
{
    std::string data;

    data += "[";
    data += std::to_string(x);
    data += ",";
    data += std::to_string(y);
    data += "]";

    return data;
}

std::string ressourceToStr(world::Ressource ressource)
{
    switch (ressource) {
        case world::Ressource::linemate:
            return "linemate";
        case world::Ressource::deraumere:
            return "deraumere";
        case world::Ressource::sibur:
            return "sibur";
        case world::Ressource::mendiane:
            return "mendiane";
        case world::Ressource::phiras:
            return "phiras";
        case world::Ressource::thystame:
            return "thystame";
        case world::Ressource::food:
            return "food";
        default:
            return {};
    }
}

world::Ressource strToRessource(const char *str)
{
    std::map<std::string, world::Ressource> strToRessourceMap = {
        {"linemate", world::linemate},
        {"deraumere", world::deraumere},
        {"sibur", world::sibur},
        {"mendiane", world::mendiane},
        {"phiras", world::phiras},
        {"thystame", world::thystame},
        {"food", world::food}
    };

    if (strToRessourceMap.find(str) != strToRessourceMap.end())
        return strToRessourceMap.find(str)->second;

    return {};
}

std::string roleToStr(ia::RoleEnum role)
{
    switch (role) {
        case ia::RoleEnum::NITWIT:
            return "nitwit";
        case ia::RoleEnum::SPAWNER:
            return "spawner";
        case ia::RoleEnum::FARMER:
            return "farmer";
        case ia::RoleEnum::GATHERER:
            return "gatherer";
        case ia::RoleEnum::INCANTER:
            return "incanter";
        case ia::RoleEnum::REAPEATER:
            return "repeater";
        case ia::RoleEnum::FARMER_SPAWNER:
            return "farmer_spawner";
        default:
            return {};
    }
}

std::vector<world::Ressource> valuesRessources()
{
    return {world::linemate, world::deraumere, world::sibur, world::mendiane, world::phiras,
            world::thystame, world::food};
}
