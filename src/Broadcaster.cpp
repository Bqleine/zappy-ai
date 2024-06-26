/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Broadcaster
*/

#include "Broadcaster.hpp"
#include <cstring>
#include <iostream>

namespace ia {
    Broadcaster::Broadcaster()
    {
        if (sodium_init() == -1)
            throw SodiumInitException();
        randombytes_buf(_current_nonce.data(), NONCE_SIZE);
    }
    
    std::string Broadcaster::encrypt(const std::string &msg)
    {
        std::unique_ptr<EncryptedBroadcast> message = encryptMessage(msg);
        std::string out;
        constexpr size_t base64_nonce_size = sodium_base64_ENCODED_LEN(NONCE_SIZE, sodium_base64_VARIANT_ORIGINAL);
        size_t base64_broadcast_size = sodium_base64_ENCODED_LEN(message->broadcast_len, sodium_base64_VARIANT_ORIGINAL);
        out.resize(base64_nonce_size + base64_broadcast_size);

        sodium_bin2base64(out.data(), base64_nonce_size, message->nonce.data(), NONCE_SIZE, sodium_base64_VARIANT_ORIGINAL);
        out[base64_nonce_size - 1] = '_';
        sodium_bin2base64(out.data() + base64_nonce_size, base64_broadcast_size, message->broadcast.get(), message->broadcast_len, sodium_base64_VARIANT_ORIGINAL);
        out.resize(out.size() - 1);
        return out;
    }

    std::unique_ptr<Broadcaster::EncryptedBroadcast> Broadcaster::encryptMessage(const std::string &msg)
    {
        size_t encrypted_len = msg.size() + crypto_aead_xchacha20poly1305_ietf_ABYTES;
        std::unique_ptr<EncryptedBroadcast> message = std::make_unique<EncryptedBroadcast>();
        message->broadcast.reset(new unsigned char[encrypted_len]);

        sodium_increment(_current_nonce.data(), NONCE_SIZE);
        message->nonce = _current_nonce;
        crypto_aead_xchacha20poly1305_ietf_encrypt(message->broadcast.get(), &message->broadcast_len, (unsigned char *) msg.data(), msg.size(), NULL, 0, NULL, _current_nonce.data(), SECRET_KEY.data());
        return message;
    }

    std::optional<std::string> Broadcaster::decrypt(const std::string &msg)
    {
        std::unique_ptr<EncryptedBroadcast> message = decryptMessage(msg);
        std::string decrypted;
        unsigned long long decrypted_len;

        if (message == nullptr)
            return std::nullopt;
        if (!checkUniqueNonce(message->nonce))
            return std::nullopt;
        decrypted_len = message->broadcast_len - crypto_aead_xchacha20poly1305_ietf_ABYTES;
        decrypted.resize(decrypted_len);
        if (crypto_aead_xchacha20poly1305_ietf_decrypt((unsigned char *) decrypted.data(), &decrypted_len, NULL, message->broadcast.get(), message->broadcast_len, NULL, 0, message->nonce.data(), SECRET_KEY.data()) != 0) {
            std::cerr << "message forged" << std::endl;
            return std::nullopt;
        }
        return decrypted;
    }

    std::unique_ptr<Broadcaster::EncryptedBroadcast> Broadcaster::decryptMessage(const std::string &msg)
    {
        constexpr size_t base64_nonce_size = sodium_base64_ENCODED_LEN(NONCE_SIZE, sodium_base64_VARIANT_ORIGINAL);
        size_t nonce_len;
        std::unique_ptr<EncryptedBroadcast> message = std::make_unique<EncryptedBroadcast>();
        const char *nonce_end = nullptr;
        size_t broadcast_max_len;

        if (msg.size() < base64_nonce_size + 2)
            return nullptr;
        if (sodium_base642bin(message->nonce.data(), NONCE_SIZE, msg.data(), base64_nonce_size, NULL, &nonce_len, &nonce_end, sodium_base64_VARIANT_ORIGINAL)) {
            std::cerr << "failed to read nonce" << std::endl;
            return nullptr;
        }
        nonce_end++;
        broadcast_max_len = strlen(nonce_end) / 4 * 3;
        message->broadcast.reset(new unsigned char[broadcast_max_len]);
        if (sodium_base642bin(message->broadcast.get(), broadcast_max_len, nonce_end, strlen(nonce_end), NULL, (size_t *) &message->broadcast_len, NULL, sodium_base64_VARIANT_ORIGINAL)) {
            std::cerr << "failed to read payload" << std::endl;
            return nullptr;
        }
        return message;
    }

    bool Broadcaster::checkUniqueNonce(const Nonce &nonce)
    {
        for (const Nonce &received : _received_broadcasts) {
            if (received == nonce) {
                std::cerr << "nonce already received" << std::endl;
                return false;
            }
        }
        _received_broadcasts.push_back(nonce);
        return true;
    }

    const char* Broadcaster::SodiumInitException::what() const noexcept {
        return "Failed to initialize libsodium";
    }
}
