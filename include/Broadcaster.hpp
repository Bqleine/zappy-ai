/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Broadcaster
*/

#pragma once

#include <memory>
#include <string>
#include <optional>
#include <sodium.h>
#include <vector>
#include <array>

namespace ia {
    class Broadcaster final {
        public:
            /**
             * Initiates the sodium library and generates a random nonce
             */
            Broadcaster();

            std::string encrypt(const std::string &msg);
            std::optional<std::string> decrypt(const std::string &msg);

            class SodiumInitException : std::exception {
                public:
                    const char* what() const noexcept override;
            };
        private:
            static constexpr size_t NONCE_SIZE{crypto_aead_xchacha20poly1305_ietf_NPUBBYTES};
            typedef std::array<unsigned char, NONCE_SIZE> Nonce;
            typedef std::array<unsigned char, crypto_aead_xchacha20poly1305_ietf_KEYBYTES> Key;

            struct EncryptedBroadcast {
                    Nonce nonce;
                    std::unique_ptr<unsigned char[]> broadcast;
                    unsigned long long broadcast_len;
            };

            std::unique_ptr<EncryptedBroadcast> encryptMessage(const std::string &msg);
            std::unique_ptr<EncryptedBroadcast> decryptMessage(const std::string &msg);
            bool checkUniqueNonce(const Nonce &nonce);
            
            Nonce _current_nonce;
            std::vector<Nonce> _received_broadcasts;

            // Generated using scripts/genkey.c
            static constexpr Key SECRET_KEY = { 0x93, 0x76, 0x7B, 0x64, 0x8F, 0x42, 0x9, 0xFF, 0x39, 0x6F, 0xE6, 0xA0, 0x5D, 0x9D, 0xC5, 0x83, 0xDD, 0x43, 0x4B, 0x99, 0xC2, 0x5C, 0x70, 0x69, 0x4C, 0x4F, 0x70, 0xAA, 0x70, 0x67, 0xF7, 0xE8 };
    };
}
