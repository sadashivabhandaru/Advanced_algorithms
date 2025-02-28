#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>

// SHA-256 Constants
const uint32_t K[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// SHA-256 Initial Hash Values
uint32_t H[] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

uint32_t rightRotate(uint32_t n, uint32_t d) {
    return (n >> d) | (n << (32 - d));
}

uint32_t sigma0(uint32_t x) {
    return rightRotate(x, 2) ^ rightRotate(x, 13) ^ rightRotate(x, 22);
}

uint32_t sigma1(uint32_t x) {
    return rightRotate(x, 6) ^ rightRotate(x, 11) ^ rightRotate(x, 25);
}

uint32_t SIGMA0(uint32_t x) {
    return rightRotate(x, 7) ^ rightRotate(x, 18) ^ (x >> 3);
}

uint32_t SIGMA1(uint32_t x) {
    return rightRotate(x, 17) ^ rightRotate(x, 19) ^ (x >> 10);
}

uint32_t ch(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (~x & z);
}

uint32_t maj(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

std::string sha256(const std::string& text) {
    std::vector<uint8_t> data(text.begin(), text.end());
    uint64_t originalLength = data.size() * 8;
    data.push_back(0x80);
    while ((data.size() * 8) % 512 != 448) {
        data.push_back(0x00);
    }
    for (int i = 7; i >= 0; --i) {
        data.push_back((originalLength >> (i * 8)) & 0xFF);
    }
    std::vector<uint32_t> hash(H, H + 8);
    for (size_t i = 0; i < data.size(); i += 64) {
        std::vector<uint32_t> W(64, 0);
        for (int t = 0; t < 16; ++t) {
            W[t] = (data[i + t * 4] << 24) | (data[i + t * 4 + 1] << 16) | (data[i + t * 4 + 2] << 8) | data[i + t * 4 + 3];
        }
        for (int t = 16; t < 64; ++t) {
            W[t] = SIGMA1(W[t-2]) + W[t-7] + SIGMA0(W[t-15]) + W[t-16];
        }
        uint32_t a, b, c, d, e, f, g, h;
        a = hash[0]; b = hash[1]; c = hash[2]; d = hash[3];
        e = hash[4]; f = hash[5]; g = hash[6]; h = hash[7];
        for (int t = 0; t < 64; ++t) {
            uint32_t temp1 = h + sigma1(e) + ch(e, f, g) + K[t] + W[t];
            uint32_t temp2 = sigma0(a) + maj(a, b, c);
            h = g; g = f; f = e; e = d + temp1;
            d = c; c = b; b = a; a = temp1 + temp2;
        }
        hash[0] += a; hash[1] += b; hash[2] += c; hash[3] += d;
        hash[4] += e; hash[5] += f; hash[6] += g; hash[7] += h;
    }
    std::stringstream ss;
    for (auto h : hash) {
        ss << std::hex << std::setw(8) << std::setfill('0') << h;
    }
    return ss.str();
}

int main() {
    // Input 1: "The Gospel according to Mark: Chapter 1..."
    std::string text1 = "The Gospel according to Mark: Chapter 1...";
    std::string hash1 = sha256(text1);
    std::cout << "SHA-256 Hash of the Book of Mark: " << hash1 << std::endl;

    // Input 2: A different input
    std::string text2 = "This is a test string for SHA-256.";
    std::string hash2 = sha256(text2); // Corrected line
    std::cout << "SHA-256 Hash of the test string: " << hash2 << std::endl;

    return 0;
}
