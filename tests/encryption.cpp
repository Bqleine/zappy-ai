/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Encryption tests
*/

#include <criterion/criterion.h>
#include "Broadcaster.hpp"
#include "coding_style.h"

Test(encryption, encrypt)
{
    ia::Broadcaster broadcaster;
    broadcaster.encrypt("Hello");
}

Test(encryption, unique_nonce)
{
    ia::Broadcaster broadcaster;
    cr_assert_neq(broadcaster.encrypt("Hello"), broadcaster.encrypt("Hello"));
}

Test(encryption, unique_nonce2)
{
    ia::Broadcaster broadcaster;
    ia::Broadcaster broadcaster2;
    cr_assert_neq(broadcaster.encrypt("Hello"), broadcaster2.encrypt("Hello"));
}

Test(encryption, decrypt_10000)
{
    ia::Broadcaster broadcaster;
    for (size_t i = 0; i < 10000; i++) {
        std::string str = broadcaster.encrypt("Hello");
        std::optional<std::string> decrypted = broadcaster.decrypt(str);
        cr_assert(decrypted.has_value());
        cr_assert_str_eq(decrypted.value().data(), "Hello");
    }
}

Test(encryption, decrypt_twice)
{
    ia::Broadcaster broadcaster;
    std::string str = broadcaster.encrypt("Hello");
    broadcaster.decrypt(str);
    cr_assert(!broadcaster.decrypt(str).has_value());
}

Test(encryption, decrypt_long_10000)
{
    ia::Broadcaster broadcaster;
    for (size_t i = 0; i < 10000; i++) {
        std::string str = broadcaster.encrypt(CODING_STYLE);
        std::optional<std::string> decrypted = broadcaster.decrypt(str);
        cr_assert(decrypted.has_value());
        cr_assert_str_eq(decrypted.value().data(), CODING_STYLE);
    }
}

Test(encryption, decrypt_invalid)
{
    ia::Broadcaster broadcaster;
    cr_assert(!broadcaster.decrypt("").has_value());
    cr_assert(!broadcaster.decrypt("caca").has_value());
    cr_assert(!broadcaster.decrypt("euitdle uietduiltl").has_value());
    cr_assert(!broadcaster.decrypt("euitdle uietduiltl").has_value());
    cr_assert(!broadcaster.decrypt("ASNVdzXxjh8plOGbKNshr7TKbnz1m/cJ sKjSo8TQKnTn2tjQDR/kELMTKMLD ").has_value());
}

Test(encryption, decrypt_forged)
{
    ia::Broadcaster broadcaster;
    cr_assert(!broadcaster.decrypt("ASNVdzXxjh8plOGbKNshr7TKbnz1m/cJ sKjSo8TQKnTn2tjQDR/kELMTKMLE").has_value());
    cr_assert(!broadcaster.decrypt("ASNVdzXxjh8plOGbKNshr7TKbnz2m/cJ sKjSo8TQKnTn2tjQDR/kELMTKMLD").has_value());
}
