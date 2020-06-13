#include <iostream>
#include <bitset>
#include <cinttypes>

static uint32_t rev(uint32_t x) {
    std::bitset<32> bitset(x);

    // Find the last 1 bit
    ssize_t last = 0;
    for (ssize_t i = 31; i >= 0; --i) {
        if (bitset[i]) {
            last = i;
            break;
        }
    }

    // Reverses it
    ssize_t nf = (last + 1) / 2;
    for (ssize_t i = 0; i < nf; ++i) {
        ssize_t j = last - i;
        uint32_t y = bitset[i];
        bitset[i] = bitset[j];
        bitset[j] = y;
        //std::swap(bitset[i], bitset[j]);
    }

    return static_cast<uint32_t>(bitset.to_ulong());
}

int main() {
    uint32_t x, y;
    std::cin >> x;
    y = rev(x);
    std::cout << y << std::endl;
    return 0;
}
