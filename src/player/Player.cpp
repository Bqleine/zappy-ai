/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player.cpp
*/

#include "player/Player.hpp"
#include "Utils.hpp"
#include "error/Error.hpp"
#include "map/Map.hpp"
#include "map/World_enums.hpp"
#include "player/FarmerSpawner.hpp"
#include "player/Nitwit.hpp"
#include "player/Farmer.hpp"
#include "player/Incanter.hpp"
#include "player/Gatherer.hpp"
#include "player/Spawner.hpp"
#include "player/Repeater.hpp"
#include <cmath>
#include <cstring>
#include <iostream>
#include <unistd.h>

namespace ia {
    Player::Player(Position2i map_size, int socket, const Parsing &parsing, int nb_left,
        RoleEnum role)
        : _map(map_size.x, map_size.y)
          , _socket(socket)
          , _nb_left(nb_left)
          , _role(role)
          , _parsing(parsing)
    {
        _nb_left = nb_left;
        _pos = {0, 0};
        _dir = world::north;
        _level = 1;
        _nb_mates = 0;
        _inventory = {
            {world::Ressource::linemate, 0},
            {world::Ressource::deraumere, 0},
            {world::Ressource::sibur, 0},
            {world::Ressource::mendiane, 0},
            {world::Ressource::phiras, 0},
            {world::Ressource::thystame, 0},
            {world::Ressource::food, 10}
        };
        _requests = {};
        _responses = {};
        _messages = {};
    }

    void Player::setPos(Position2i pos)
    {
        _pos = pos;
    }

    void Player::fillInventory(std::string &str)
    {
        // REMOVE USELESS [ ]
        str.erase(0, 1);
        str.erase(str.size() - 1, 1);
        str += ",";

        size_t pos;
        size_t pos_nb;
        std::string ressource;
        std::string nb;
        std::string delimiter = ",";

        while ((pos = str.find(delimiter)) != std::string::npos) {
            std::string sub_str = str.substr(0, pos);
            if (sub_str[0] == ' ')
                sub_str.erase(0, 1);
            pos_nb = sub_str.find(' ');
            nb = sub_str.substr(pos_nb, sub_str.size() - pos_nb);
            ressource = sub_str.substr(0, pos_nb);
            str.erase(0, pos + delimiter.length());
            _inventory[strToRessource(ressource.c_str())] = std::stoi(nb);
        }
    }

    Position2i Player::getLookPosForIndex(unsigned int index)
    {
        double y = std::sqrt((double) index);
        double x = index - std::pow(y, 2) - (std::pow(y, 2) / 2);
        int fx = std::floor(x);
        int fy = std::floor(y);

        return {fx, fy};
    }

    Position2i Player::rotatePointToDirection(Position2i rotation)
    {
        Position2i pos;
        for (int i = 1; i < _dir; i++) {
            pos = rotation;
            rotation.x = pos.y;
            rotation.y = -pos.x;
        }
        return rotation;
    }

    void Player::fillMapTile(char *str, unsigned int index)
    {
        static const char *DELIMS = " ";
        char *saveptr = NULL;
        char *content = strtok_r(str, DELIMS, &saveptr);
        Position2i offset = getLookPosForIndex(index);
        offset = rotatePointToDirection(offset);
        world::Tile &tile = _map.getTile({_pos.x + offset.x, _pos.y + offset.y});
        tile.clearRessources();

        while (content != NULL) {
            tile.addRessource(strToRessource(content));
            content = strtok_r(NULL, DELIMS, &saveptr);
        }
    }

    void Player::fillMap(std::string &str)
    {
        static const char *DELIMS = "[]\n,";
        char *saveptr = NULL;
        char *tile = strtok_r(str.data(), DELIMS, &saveptr);
        unsigned int index = 0;

        while (tile != NULL) {
            fillMapTile(tile, index);
            tile = strtok_r(NULL, DELIMS, &saveptr);
            index++;
        }
        std::cout << "TILE INFO: " << _map.getTile({0, 0}).getRessourcesInfos() << std::endl;
    }

    void Player::addInventory(world::Ressource ressource)
    {
        _inventory[ressource] += 1;
    }

    void Player::subInventory(world::Ressource ressource, int nb)
    {
        _inventory[ressource] -= nb;
    }

    void Player::setDirection(world::Direction dir)
    {
        _dir = dir;
    }

    void Player::forward()
    {
        std::cout << "[ACTION] forward" << std::endl;
        std::string forward_cmd = "Forward\n";
        write(_socket, forward_cmd.c_str(), forward_cmd.size());
        _requests.emplace_back(move_up, world::Ressource{});
        this->listenServer();
        this->consumeResponse();
        this->moveForward();
    }

    void Player::turnRight()
    {
        std::string right_cmd = "Right\n";
        write(_socket, right_cmd.c_str(), right_cmd.size());
        _requests.emplace_back(turn_right, world::Ressource{});
        this->listenServer();
        this->consumeResponse();

        switch (_dir) {
            case world::east:
                _dir = world::south;
                break;
            case world::west:
                _dir = world::north;
                break;
            case world::north:
                _dir = world::east;
                break;
            case world::south:
                _dir = world::west;
                break;
            default:
                break;
        }
    }

    void Player::turnLeft()
    {
        std::string left_cmd = "Left\n";
        write(_socket, left_cmd.c_str(), left_cmd.size());
        _requests.emplace_back(turn_left, world::Ressource{});
        this->listenServer();
        this->consumeResponse();

        switch (_dir) {
            case world::east:
                _dir = world::north;
                break;
            case world::west:
                _dir = world::south;
                break;
            case world::north:
                _dir = world::west;
                break;
            case world::south:
                _dir = world::east;
                break;
            default:
                break;
        }
    }

    void Player::look()
    {
        std::string look_cmd = "Look\n";
        write(_socket, look_cmd.c_str(), look_cmd.size());
        _requests.emplace_back(Request::look, world::Ressource{});
        this->listenServer();
        this->consumeResponse();
    }

    void Player::inventory()
    {
        std::string inventory_cmd = "Inventory\n";
        write(_socket, inventory_cmd.c_str(), inventory_cmd.size());
        _requests.emplace_back(Request::inventory, world::Ressource{});
        this->listenServer();
        this->consumeResponse();
    }

    void Player::broadcast(std::string &str)
    {
        std::string broadcast_cmd = "Broadcast ";
        broadcast_cmd += _broadcaster.encrypt(str);
        broadcast_cmd += "\n";
        write(_socket, broadcast_cmd.c_str(), broadcast_cmd.size());
        _requests.emplace_back(Request::broadcast, world::Ressource{});
        this->listenServer();
        this->consumeResponse();
    }

    void Player::nbrConnect()
    {
        std::string nbr_connect_cmd = "Connect_nbr\n";
        write(_socket, nbr_connect_cmd.c_str(), nbr_connect_cmd.size());
        _requests.emplace_back(number_unused, world::Ressource{});
        this->listenServer();
        this->consumeResponse();
    }

    void Player::forkPlayer(RoleEnum role)
    {
        std::string fork_cmd = "Fork\n";
        write(_socket, fork_cmd.c_str(), fork_cmd.size());
        _requests.emplace_back(fork, world::Ressource{});
        _requests_fork.emplace_back(role);
        this->listenServer();
        this->consumeResponse();
    }

    void Player::ejectPlayers()
    {
        std::string eject_cmd = "Eject\n";
        write(_socket, eject_cmd.c_str(), eject_cmd.size());
        _requests.emplace_back(eject, world::Ressource{});
        this->listenServer();
        this->consumeResponse();
    }

    void Player::takeObject(world::Ressource ressource)
    {
        std::string take_cmd = "Take ";
        take_cmd += ressourceToStr(ressource);
        take_cmd += '\n';
        write(_socket, take_cmd.c_str(), take_cmd.size());
        _requests.emplace_back(take, ressource);
        this->listenServer();
        this->consumeResponse();
    }

    void Player::setObject(world::Ressource ressource)
    {
        std::string set_cmd = "Set ";
        set_cmd += ressourceToStr(ressource);
        set_cmd += '\n';
        write(_socket, set_cmd.c_str(), set_cmd.size());
        _requests.emplace_back(set_down, ressource);
        this->listenServer();
        this->consumeResponse();
    }

    void Player::incantation()
    {
        std::string incantation_cmd = "Incantation\n";
        write(_socket, incantation_cmd.c_str(), incantation_cmd.size());
        _requests.emplace_back(start_incantation, world::Ressource{});
        this->listenServer();
        this->consumeResponse();
    }

    void Player::listenServer()
    {
        std::vector<std::array<char, BUFFER_SIZE>> buffer_stack;
        ssize_t bytes_received;

        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(_socket, &read_fds);
        std::string data;
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        int retval = select(_socket + 1, &read_fds, nullptr, nullptr, &tv);

        switch (retval) {
            case -1:
                throw Error("Error with select.");
            case 0:
                break;
            default:
                do {
                    buffer_stack.emplace_back();
                    std::array<char, BUFFER_SIZE> &buffer = buffer_stack.back();
                    bytes_received = read(_socket, buffer.data(), BUFFER_SIZE - 1);
                    if (bytes_received <= 0) {
                        throw Error("Failed to receive message from server");
                    }
                    buffer[bytes_received] = '\0';
                } while (bytes_received == BUFFER_SIZE - 1);
        }

        for (const auto &buffer : buffer_stack) {
            data += buffer.data();
        }

        std::string line;
        std::istringstream iss(data);
        while (std::getline(iss, line)) {
            if (!line.empty()) {
                std::cout << "Data received from server: " << line << std::endl;
                if (line == "ok") {
                    Response resp_ok(true);
                    _responses.emplace_back(resp_ok);
                    return;
                }
                if (line == "ko") {
                    Response resp_ko(false);
                    _responses.emplace_back(resp_ko);
                    return;
                }
                if (line == "dead")
                    throw Error("Player dead");
                if (line[0] == '[') {
                    Response resp_objects(false, -1, line);
                    _responses.emplace_back(resp_objects);
                    return;
                }
                if (line == "Elevation underway") {
                    Response resp_elevation(true, -1, line);
                    _responses.emplace_back(resp_elevation);
                    return;
                }
                if (strncmp(line.c_str(), "Current level: ", 15) == 0) {
                    std::size_t data_dir = line.find_last_of(' ');
                    std::string data_message = line.substr(data_dir + 1, 1);
                    int value = stoi(data_message);
                    _responses.emplace_back(value);
                    return;
                }
                if (strncmp(line.c_str(), "eject: ", 7) == 0) {
                    std::size_t data_dir = line.find(' ');
                    std::string data_message = line.substr(data_dir + 1, 1);
                    switch (stoi(data_message)) {
                        case 1:
                            _ejected_dir = world::Direction::north;
                            break;
                        case 7:
                            _ejected_dir = world::Direction::east;
                            break;
                        case 5:
                            _ejected_dir = world::Direction::south;
                            break;
                        case 3:
                            _ejected_dir = world::Direction::west;
                            break;
                        default:
                            return;
                    }
                    this->playerEjected(_ejected_dir);
                    return;
                }
                if (isNumber(line)) {
                    int value = std::stoi(line);
                    Response resp_nbr(true, value);
                    _responses.emplace_back(resp_nbr);
                    return;
                }
                if (line.starts_with("message ") && line.size() > 11) {
                    std::string str_dir = line.substr(8, 1);
                    int dir = std::stoi(str_dir);
                    std::cout << "[BROADCAST] from direction" << dir << std::endl;
                    std::string data_message = line.substr(11, line.size() - 11);
                    std::optional<std::string> decrypted = _broadcaster.decrypt(data_message);
                    if (decrypted.has_value()) {
                        Broadcast_message msg(dir, decrypted.value());
                        std::cout << "received broadcast: « " << decrypted.value() << " »" <<
                            std::endl;
                        _messages.emplace_back(msg);
                    } else {
                        Broadcast_message msg(dir, data_message);
                        _undesired_messgaes.emplace_back(msg);
                    }
                }
            }
        }
    }

    void Player::startOtherPlayer(RoleEnum role)
    {
        std::string command;
        if (true) {
            command =
                "./zappy_ai -p " + std::to_string(_parsing.getPort()) + " -n " +
                _parsing.getTeamName() + " -h " + _parsing.getMachine()
                + " -r " + roleToStr(role);
        } else {
            command =
                "kgx -e './zappy_ai -p " + std::to_string(_parsing.getPort()) + " -n " +
                _parsing.getTeamName() + " -h " + _parsing.getMachine()
                + " -r " + roleToStr(role) + "'";
        }
        pid_t pid = ::fork();
        if (pid == 0) {
            std::exit(std::system(command.c_str()));
        }
    }

    void Player::consumeResponse()
    {
        while (_requests.size() != _responses.size()) {
            // std::cout << "requests: " << _requests.size() << std::endl;
            this->listenServer();
        }
        while (!_requests.empty() && !_responses.empty()) {
            Request request = _requests[0].first;
            world::Ressource ressource = _requests[0].second;
            Response response = _responses[0];
            std::string data = response.getData();
            int value = response.getValue();
            switch (request) {
                case eject:
                    if (!response.getOk()) {
                        // HANDLE
                    }
                    break;
                case take:
                    if (response.getOk()) {
                        this->addInventory(ressource);
                        _map.getTile(_pos).subRessource(ressource);
                    }
                    break;
                case set_down:
                    if (response.getOk()) {
                        this->subInventory(ressource, 1);
                        _map.getTile(_pos).addRessource(ressource);
                    } else {
                        std::cout << "Set down KO for ressource " << ressource << std::endl;
                    }
                    break;
                case Request::look:
                    fillMap(data);
                    break;
                case Request::inventory:
                    fillInventory(data);
                    break;
                case number_unused:
                    _nb_left = value;
                    break;
                case start_incantation:
                    if (response.getOk())
                        _requests.emplace_back(end_incantation, world::Ressource{});
                    break;
                case end_incantation:
                    if (response.getOk())
                        _level = value;
                    break;
                case fork:
                    if (response.getOk()) {
                        //this->startOtherPlayer(_requests_fork.at(0));
                        _requests_fork.erase(_requests_fork.begin());
                    }
                default:
                    break;
            }
            _requests.erase(_requests.begin());
            _responses.erase(_responses.begin());
        }
    }

    void Player::listenMessage()
    {
        while (!_messages.empty()) {
            _messages.erase(_messages.begin());
        }
    }

    void Player::travelTo(Position2i target)
    {
        while (_pos.x != target.x) {
            if ((_pos.x - target.x + _map.getSize().x) % _map.getSize().x <= (
                    _pos.x + target.x) % _map.getSize().x) {
                if (_dir != world::west) {
                    turnLeft();
                    turnLeft();
                    _dir = world::west;
                }
            } else {
                if (_dir != world::east) {
                    turnRight();
                    turnRight();
                    _dir = world::east;
                }
            }
            forward();
            //if (!_map.getTile(_pos).getRessources().empty())
            //    this->takeObject();
        }

        while (_pos.y != target.y) {
            if ((_pos.y - target.y + _map.getSize().y) % _map.getSize().y <= (
                    _pos.y + target.y) % _map.getSize().y) {
                if (_dir != world::north) {
                    turnLeft();
                    turnLeft();
                    _dir = world::north;
                }
            } else {
                if (_dir != world::south) {
                    turnRight();
                    turnRight();
                    _dir = world::south;
                }
            }
            forward();
            //if (!_map.getTile(_pos).getRessources().empty())
            //    this->takeObject();
        }
    }


    void Player::runPlayer()
    {
        std::cout << "Run player with role " << roleToStr(_role) << std::endl;
        switch (_role) {
            case RoleEnum::NITWIT:
                return Nitwit().run(*this);
            case RoleEnum::FARMER:
                return Farmer().run(*this);
            case RoleEnum::INCANTER:
                return Incanter().run(*this);
            case RoleEnum::GATHERER:
                return Gatherer().run(*this);
            case RoleEnum::SPAWNER:
                return Spawner().run(*this);
            case RoleEnum::REAPEATER:
                return Repeater().run(*this);
            case RoleEnum::FARMER_SPAWNER:
                return FarmerSpawner().run(*this);
        }
    }

    void Player::moveForward()
    {
        switch (_dir) {
            case world::east:
                _pos.x = (_pos.x + 1) % _map.getSize().y;
                break;
            case world::west:
                if ((_pos.x - 1) < 0)
                    _pos.x = _map.getSize().y;
                else
                    _pos.x = (_pos.x - 1) % _map.getSize().y;
                break;
            case world::north:
                _pos.y = (_pos.y + 1) % _map.getSize().x;
                break;
            case world::south:
                if ((_pos.y - 1) < 0)
                    _pos.y = _map.getSize().x;
                else
                    _pos.y = (_pos.y - 1) % _map.getSize().y;
                break;
            default:
                break;
        }
    }

    void Player::playerEjected(world::Direction dir)
    {
        world::Direction old_dir = _dir;
        _dir = dir;
        this->moveForward();
        _dir = old_dir;
    }

    void Player::changeRole(RoleEnum role)
    {
        _role = role;
        this->runPlayer();
    }

    void Player::eraseMessage(size_t index)
    {
        _messages.erase(_messages.begin() + index);
    }

    void Player::eraseUndesiredMessage(size_t index)
    {
        _undesired_messgaes.erase(_undesired_messgaes.begin() + index);
    }

    world::Direction Player::getDir() const
    {
        return _dir;
    }

    std::vector<Broadcast_message> Player::getMessages() const
    {
        return _messages;
    }

    std::vector<Broadcast_message> Player::getUndesiredMessages() const
    {
        return _undesired_messgaes;
    }

    size_t Player::getNbLeft() const
    {
        return _nb_left;
    }

    int Player::getLevel() const
    {
        return _level;
    }

    std::map<world::Ressource, int> Player::getInventory() const
    {
        return _inventory;
    }

    world::Map Player::getMap() const
    {
        return _map;
    }

    Position2i Player::getPos() const
    {
        return _pos;
    }

    std::string Player::getInfo() const
    {
        std::string data;
        data += "POS: ";
        data += _pos.posToStr();

        data += ";FOOD: ";
        data += std::to_string(_inventory.at(world::Ressource::food));

        data += ";LEVEL: ";
        data += std::to_string(_level);

        data += ";INVENTORY: [";
        data += std::to_string(_inventory.at(world::Ressource::linemate));
        data += ",";
        data += std::to_string(_inventory.at(world::Ressource::deraumere));
        data += ",";
        data += std::to_string(_inventory.at(world::Ressource::sibur));
        data += ",";
        data += std::to_string(_inventory.at(world::Ressource::mendiane));
        data += ",";
        data += std::to_string(_inventory.at(world::Ressource::phiras));
        data += ",";
        data += std::to_string(_inventory.at(world::Ressource::thystame));
        data += "]";

        return data;
    }

    const Parsing &Player::getParsing() const
    {
        return _parsing;
    }

    int Player::getEjectedDir() const
    {
        return _ejected_dir;
    }
}
