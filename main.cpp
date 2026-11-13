#include <cstdint>
#include <cstdlib>
#include <sstream>
#include <string>

namespace {
using u64 = std::uint64_t;
using u128 = unsigned __int128;

u64 multiply_mod(u64 a, u64 b, u64 modulus) {
    return static_cast<u64>((static_cast<u128>(a) * b) % modulus);
}

bool is_prime_exponent(int p) {
    if (p < 2) return false;
    if (p % 2 == 0) return p == 2;
    for (int divisor = 3; divisor * divisor <= p; divisor += 2) {
        if (p % divisor == 0) return false;
    }
    return true;
}

bool is_mersenne_prime(int p) {
    if (p == 2) return true;
    const u64 mersenne = (u64{1} << p) - 1;
    u64 residue = 4;
    for (int i = 0; i < p - 2; ++i) {
        residue = (multiply_mod(residue, residue, mersenne) + mersenne - 2) % mersenne;
    }
    return residue == 0;
}
} // namespace

// Returns lines of "exponent|2^exponent-1"; the returned pointer remains valid
// until the next call. JavaScript reads it with UTF8ToString.
extern "C" const char* find_mersenne_primes(int max_exponent) {
    static std::string output;
    output.clear();
    if (max_exponent < 2 || max_exponent > 61) return "";

    std::ostringstream result;
    bool first = true;
    for (int p = 2; p <= max_exponent; ++p) {
        if (!is_prime_exponent(p) || !is_mersenne_prime(p)) continue;
        if (!first) result << '\n';
        first = false;
        result << p << '|' << ((u64{1} << p) - 1);
    }
    output = result.str();
    return output.c_str();
}

#ifndef __EMSCRIPTEN__
#include <iostream>
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: mersenne <max-exponent 2..61>\n";
        return 2;
    }
    char* end = nullptr;
    const long value = std::strtol(argv[1], &end, 10);
    if (!end || *end != '\0' || value < 2 || value > 61) {
        std::cerr << "Maximum exponent must be an integer from 2 to 61.\n";
        return 2;
    }
    const std::string results = find_mersenne_primes(static_cast<int>(value));
    if (results.empty()) {
        std::cout << "No Mersenne primes found.\n";
    } else {
        std::cout << results << '\n';
    }
    return 0;
}
#endif
