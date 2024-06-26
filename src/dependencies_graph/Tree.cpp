/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Tree.cpp
*/

#include "dependencies_graph/Dependencies_graph.hpp"

namespace ia {
    Requirement::Requirement(int value, void (Player::*playerMethod)(), Player *playerInstance) :
        _value(value), _playerMethod(playerMethod), _playerInstance(playerInstance)
    {
    }

    int Requirement::getValue() const
    {
        return _value;
    }

    void Requirement::execMethod() const
    {
        if (_playerInstance && _playerMethod) {
            (_playerInstance->*_playerMethod)();
        }
    }

    Node::Node()
    {
        _parent = nullptr;
        _requirements = {};
    }

    void Node::addRequirement(Requirement &requirement)
    {
        _requirements.emplace_back(requirement);
    }

    void Node::addRequirements(std::vector<Requirement> &requirements)
    {
        for (size_t i = 0; i < requirements.size(); i++)
            _requirements.emplace_back(requirements.at(i));
    }


    void Node::setParent(Node *parent)
    {
        _parent = parent;
    }

    std::vector<Requirement> Node::getRequirements() const
    {
        return _requirements;
    }


    Node *Node::getParent() const
    {
        return _parent;
    }

    Dependencies_graph::Dependencies_graph()
    {
        _node = nullptr;
    }

    Dependencies_graph::~Dependencies_graph()
    {
        Node *currentNode = _node;
        while (currentNode != nullptr) {
            Node *parent = currentNode->getParent();
            delete currentNode;
            currentNode = parent;
        }
    }

    void Dependencies_graph::setNode(Node *node)
    {
        _node = node;
    }


    void Dependencies_graph::addParent(Node *parent) const
    {
        if (_node == nullptr)
            return;
        Node *currentNode = _node;
        while (currentNode->getParent() != nullptr)
            currentNode = currentNode->getParent();
        currentNode->setParent(parent);
    }

    void Dependencies_graph::setupTree(Player player)
    {
        // REQUIREMENTS ORDERED AS FOLLOW :
        // nb_players - linemate - deraumere
        // sibur - mendiane - phiras - thystame

        Node *node_lvl8 = new Node();
        std::vector<Requirement> requirements_lvl8 = {
            {6, &Player::forward, &player},
            {2, &Player::forward, &player},
            {2, &Player::forward, &player},
            {2, &Player::forward, &player},
            {2, &Player::forward, &player},
            {2, &Player::forward, &player},
            {1, &Player::forward, &player}
        };
        node_lvl8->addRequirements(requirements_lvl8);

        Node *node_lvl7 = new Node();
        std::vector<Requirement> requirements_lvl7 = {
            {6, &Player::forward, &player},
            {1, &Player::forward, &player},
            {2, &Player::forward, &player},
            {3, &Player::forward, &player},
            {0, &Player::forward, &player},
            {1, &Player::forward, &player},
            {0, &Player::forward, &player}
        };
        node_lvl7->addRequirements(requirements_lvl7);
        node_lvl8->setParent(node_lvl7);

        Node *node_lvl6 = new Node();
        std::vector<Requirement> requirements_lvl6 = {
            {4, &Player::forward, &player},
            {1, &Player::forward, &player},
            {2, &Player::forward, &player},
            {1, &Player::forward, &player},
            {3, &Player::forward, &player},
            {0, &Player::forward, &player},
            {0, &Player::forward, &player}
        };
        node_lvl6->addRequirements(requirements_lvl6);
        node_lvl7->setParent(node_lvl6);

        Node *node_lvl5 = new Node();
        std::vector<Requirement> requirements_lvl5 = {
            {4, &Player::forward, &player},
            {1, &Player::forward, &player},
            {1, &Player::forward, &player},
            {2, &Player::forward, &player},
            {0, &Player::forward, &player},
            {1, &Player::forward, &player},
            {0, &Player::forward, &player}
        };
        node_lvl5->addRequirements(requirements_lvl5);
        node_lvl6->setParent(node_lvl5);

        Node *node_lvl4 = new Node();
        std::vector<Requirement> requirements_lvl4 = {
            {2, &Player::forward, &player},
            {2, &Player::forward, &player},
            {0, &Player::forward, &player},
            {1, &Player::forward, &player},
            {0, &Player::forward, &player},
            {2, &Player::forward, &player},
            {0, &Player::forward, &player}
        };
        node_lvl4->addRequirements(requirements_lvl4);
        node_lvl5->setParent(node_lvl4);

        Node *node_lvl3 = new Node();
        std::vector<Requirement> requirements_lvl3 = {
            {2, &Player::forward, &player},
            {1, &Player::forward, &player},
            {1, &Player::forward, &player},
            {1, &Player::forward, &player},
            {0, &Player::forward, &player},
            {0, &Player::forward, &player},
            {0, &Player::forward, &player}
        };
        node_lvl3->addRequirements(requirements_lvl3);
        node_lvl4->setParent(node_lvl3);

        Node *node_lvl2 = new Node();
        std::vector<Requirement> requirements_lvl2 = {
            {1, &Player::turnLeft, &player},
            {1, &Player::turnLeft, &player},
            {0, &Player::turnLeft, &player},
            {0, &Player::turnLeft, &player},
            {0, &Player::turnLeft, &player},
            {0, &Player::turnLeft, &player},
            {0, &Player::turnLeft, &player}
        };
        node_lvl2->addRequirements(requirements_lvl2);
        node_lvl3->setParent(node_lvl2);

        _node = node_lvl8;
    }

    Node *Dependencies_graph::getParent(int idx) const
    {
        if (_node == nullptr)
            return nullptr;
        Node *currentNode = _node;
        for (int i = 0; i < idx; i++) {
            if (currentNode->getParent() != nullptr)
                currentNode = currentNode->getParent();
            else
                return nullptr;
        }
        return currentNode;
    }

    Node *Dependencies_graph::getNodeLvl(int level) const
    {
        int lvl = 7 - level;

        return getParent(lvl);
    }
}
