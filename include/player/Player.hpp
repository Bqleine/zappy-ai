/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Player.hpp
*/

#pragma once

#include <string>
#include <cstring>
#include <fcntl.h>
#include "map/Map.hpp"
#include "player/Request.hpp"
#include "Broadcaster.hpp"
#include "map/World_enums.hpp"
#include "parsing/Parsing.hpp"
#include <sstream>
#define BUFFER_SIZE 4096

namespace ia {
    class Player {
        public:
            Player(Position2i map_size, int socket, const Parsing &parsing, int nb_left,
                RoleEnum role);
            ~Player() = default;

            void setPos(Position2i pos);
            void fillInventory(std::string &str);
            Position2i rotatePointToDirection(Position2i rotation);
            Position2i getLookPosForIndex(unsigned int index);
            void fillMapTile(char *tile, unsigned int index);
            void fillMap(std::string &str);
            void addInventory(world::Ressource ressource);
            void subInventory(world::Ressource ressource, int nb);
            void setDirection(world::Direction dir);

            void forward();
            void turnRight();
            void turnLeft();
            void look();
            void inventory();
            void broadcast(std::string &str);
            void nbrConnect();
            void forkPlayer(RoleEnum role);
            void ejectPlayers();
            void takeObject(world::Ressource ressource);
            void setObject(world::Ressource ressource);
            void incantation();

            void startOtherPlayer(RoleEnum role);
            void replacePlayer(RoleEnum role);
            void consumeResponse();
            void listenServer();
            void listenMessage();
            void travelTo(Position2i pos);
            void runPlayer();
            void playerEjected(world::Direction direction);
            void changeRole(RoleEnum role);
            void eraseMessage(size_t index);
            void eraseUndesiredMessage(size_t index);
            void moveForward();

            [[nodiscard]] world::Direction getDir() const;
            [[nodiscard]] std::vector<Broadcast_message> getMessages() const;
            [[nodiscard]] std::vector<Broadcast_message> getUndesiredMessages() const;
            [[nodiscard]] size_t getNbLeft() const;
            [[nodiscard]] int getLevel() const;
            [[nodiscard]] std::map<world::Ressource, int> getInventory() const;
            [[nodiscard]] world::Map getMap() const;
            [[nodiscard]] Position2i getPos() const;
            [[nodiscard]] std::string getInfo() const;
            [[nodiscard]] const Parsing &getParsing() const;
            [[nodiscard]] int getEjectedDir() const;

        private:
            Broadcaster _broadcaster; // ENCODER/DECODER FOR BROADCASTS
            std::map<world::Ressource, int> _inventory; // INVENTORY
            world::Map _map; // MAP COPY (?)
            Position2i _pos{}; // POS IN HIS MAP COPY, START IN {0, 0}
            world::Direction _dir; // DIRECTION FACING
            int _level{}; // PLAYER'S LEVEL, START AT 1
            std::string _team_name; // NAME OF THE TEAM TO COMMUNICATE TO FIND MATES (?)
            int _socket; // SERVER SOCKET TO COMMUNICATE WITH
            size_t _nb_mates; // NB OF TEAM MATES, START AT 0, ONLY USEFUL TO MAIN IA
            size_t _nb_left; // NB OF MATES THAT CAN JOIN TEAM
            std::vector<std::pair<Request, world::Ressource>> _requests; // REQUESTS SENT TO SERVER
            std::vector<RoleEnum> _requests_fork; // REQUESTS FORKS
            std::vector<Response> _responses; // RESPONSES FROM SERVER THAT MUST MATCH
            //WITH REQUESTS SENT
            std::vector<Broadcast_message> _messages; // TEAM BROADCAST MESSAGES SENT FROM SERVER
            std::vector<Broadcast_message> _undesired_messgaes;
            // OTHER TEAM BROADCAST MESSAGES SENT FROM SERVER
            RoleEnum _role; // PLAYER ROLE
            Parsing _parsing; // NEEDED TO FORK CORRECTLY
            world::Direction _ejected_dir; // DIRECTION OF LAST EJECT
    };
}
