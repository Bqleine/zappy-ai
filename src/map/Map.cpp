/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map.cpp
*/

#include "map/Map.hpp"

#include "player/Player.hpp"
#include <cassert>
#include <iostream>

namespace world {
    Tile::Tile()
    {
        _pos = {};

        int nb_ressources = 8;

        for (int i = 0; i < nb_ressources; i++)
            _ressources[(Ressource) i] = 0;
    }

    Tile::Tile(Position2i pos)
    {
        _pos = pos;

        int nb_ressources = 8;

        for (int i = 0; i < nb_ressources; i++)
            _ressources[(Ressource) i] = 0;
    }

    void Tile::clearRessources()
    {
        for (auto &res : _ressources) {
            res.second = 0;
        }
    }

    void Tile::addRessource(Ressource ressource)
    {
        const auto it = _ressources.find(ressource);

        if (it != _ressources.end())
            _ressources.find(ressource)->second += 1;
    }

    void Tile::subRessource(Ressource ressource)
    {
        const auto it = _ressources.find(ressource);

        if (it != _ressources.end())
            _ressources.find(ressource)->second -= 1;
    }

    std::string Tile::getRessourcesInfos() const
    {
        std::string data = "LINEMATE: " + std::to_string(this->getRessourceSize(linemate)) +
                           "\nDERAUMERE: " + std::to_string(this->getRessourceSize(deraumere)) +
                           "\nSIBUR: " + std::to_string(this->getRessourceSize(sibur)) +
                           "\nMENDIANE: " + std::to_string(this->getRessourceSize(mendiane)) +
                           "\nPHIRAS: " + std::to_string(this->getRessourceSize(phiras)) +
                           "\nTHYSTAME: " + std::to_string(this->getRessourceSize(thystame)) +
                           "\nFOOD: " + std::to_string(this->getRessourceSize(food)) + "\n";

        return data;
    }

    std::map<Ressource, int> Tile::getRessources() const
    {
        return _ressources;
    }

    int Tile::getRessourceSize(Ressource ressource) const
    {
        auto it = _ressources.find(ressource);

        if (it != _ressources.end())
            return _ressources.find(ressource)->second;
        return -1;
    }

    Map::Map(int width, int height)
        : _width(width), _height(height)
    {
        assert(width != 0);
        assert(height != 0);
        _map.resize(width);
        for (int x = 0; x < width; ++x) {
            _map[x].resize(height);
            for (int y = 0; y < height; ++y) {
                _map[x][y] = Tile({x, y});
            }
        }
    }

    Position2i Map::getSize() const
    {
        return {_width, _height};
    }

    Tile &Map::getTile(Position2i pos)
    {
        int x = std::abs(pos.x % _width);
        int y = std::abs(pos.y % _height);
        return _map[x][y];
    }
}
