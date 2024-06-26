/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tree.hpp
*/

#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <iostream>
#include "../player/Player.hpp"

namespace ia {
    class Requirement {
        private:
            int _value;
            void (Player::*_playerMethod)();
            Player *_playerInstance;

        public:
            Requirement(int value, void (Player::*playerMethod)(), Player *playerInstance);
            ~Requirement() = default;

            [[nodiscard]] int getValue() const;
            void execMethod() const;
    };

    class Node {
        private:
            Node *_parent;
            std::vector<Requirement> _requirements;

        public:
            Node();
            ~Node() = default;

            void addRequirement(Requirement &requirement);
            void addRequirements(std::vector<Requirement> &requirements);
            void setParent(Node *parent);

            [[nodiscard]] std::vector<Requirement> getRequirements() const;
            [[nodiscard]] Node *getParent() const;
    };

    class Dependencies_graph {
        private:
            Node *_node;

        public:
            Dependencies_graph();
            ~Dependencies_graph();

            void setNode(Node *node);
            void addParent(Node *parent) const;
            void setupTree(Player player);

            [[nodiscard]] Node *getParent(int idx) const;
            [[nodiscard]] Node *getNodeLvl(int level) const;
    };
}
