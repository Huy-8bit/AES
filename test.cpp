#include <iostream>

using namespace std;

const int KEY_SIZE = 16; // AES-128 key size in bytes
const int NUM_ROUNDS = 10; // Number of rounds in AES-128

// Given S-Box for AES
const unsigned char SBOX[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
    0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    // Rest of the S-Box values omitted for brevity
};

const unsigned char rcon[11] = {
  0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, 0x00
};

void rot_word(unsigned char* word) {
    unsigned char temp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;
}

void sub_word(unsigned char* word) {
    for (int i = 0; i < 4; i++) {
        word[i] = SBOX[word[i]];
    }
}



void aes_key_expand (string &k0) {
    const int Nk = 4;
    const int Nb = 4;
    const int Nr = 10;

    unsigned char key[Nk * 4];
    memcpy(key,k0.c_str(),KEY_SIZE);

    unsigned char temp[4];

    for (int i = Nk ; i < Nb * (Nr + 1); i++) {
        for (int j = 0; j < 4; j++) {
            temp[j] = key[(i - 1) * 4 + j];
        }
        if (i % Nk == 0) {
            rot_word(temp);
            sub_word(temp);
            temp[0] ^= rcon[i / Nk];
        } else if (Nk > 6 && i % Nk == 4) {
            sub_word(temp);
        }
        for (int j = 0; j < 4; j++) {
            key[i * 4 + j] = key[(i - Nk) * 4 + j] ^ temp[j];
        }
    }
}

int main() {
    // string k0("Thats my Kung Fu");
    // unsigned char key_schedule[(NUM_ROUNDS + 1) * KEY_SIZE];
    // aes_key_expand(k0);
    // for (int i = 0; i <= NUM_ROUNDS; i++) {
    //     cout << "Round " << i << ": ";
    //     for (int j = 0; j < KEY_SIZE; j++) {
    //         printf("%02x ", key_schedule[i * KEY_SIZE + j]);
    //     }
    //     cout << endl;
    // }
    string k0("Thats my Kung Fu");
    aes_key_expand(k0);
    for (int i = 0; i <= NUM_ROUNDS; i++) 
    {
        cout << "Round " << i << ": ";
        for (int j = 0; j < KEY_SIZE; j++)
        {
            printf("%02x ", k0[i * KEY_SIZE + j]);
        }
        
    }
    
    return 0;
}