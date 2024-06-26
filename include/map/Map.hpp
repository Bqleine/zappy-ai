/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map.hpp
*/

#pragma once

#include "World_enums.hpp"
#include <vector>
#include <memory>
#include <map>
#include <algorithm>

namespace ia {
    class Player;
}

namespace world {
    class Tile {
        private:
            Position2i _pos{};
            std::map<Ressource, int> _ressources;

        public:
            Tile();
            Tile(Position2i pos);
            ~Tile() = default;

            void clearRessources();
            void addRessource(Ressource ressource);
            void subRessource(Ressource ressource);

            [[nodiscard]] std::string getRessourcesInfos() const;
            [[nodiscard]] std::map<Ressource, int> getRessources() const;
            [[nodiscard]] int getRessourceSize(Ressource ressource) const;
    };

    class Map {
        private:
            std::vector<std::vector<Tile>> _map;
            int _width;
            int _height;

        public:
            Map(int width, int height);
            ~Map() = default;

            [[nodiscard]] Position2i getSize() const;
            [[nodiscard]] Tile &getTile(Position2i pos);
    };
} // namespace gui
