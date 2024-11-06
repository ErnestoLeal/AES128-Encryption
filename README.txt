# AES-128 Encryptor

## Overview

This project is a C++ implementation of the AES-128 encryption algorithm. It takes a plaintext string as input, divides it into 16-byte blocks, applies padding if necessary, and then encrypts each block using the AES-128 cipher. The encryption process involves key expansion, byte substitution, row shifting, column mixing, and XOR operations.

### Features

- **Key Expansion**: Expands the original 128-bit key into multiple round keys for the encryption process.
- **Block Division and Padding**: Splits the input into 16-byte blocks and applies PKCS#7 padding for any partial block.
- **AES-128 Encryption**: Encrypts each block using the AES algorithm, including initial and final transformations.

## Project Structure

- **AES128.cpp**: The main file, orchestrates the encryption process.
- **padBlock.h / padBlock.cpp**: Handles padding of the last block.
- **stringToHex.h / stringToHex.cpp**: Converts strings to hexadecimal format for processing.
- **keyExpansion.h / keyExpansion.cpp**: Expands the initial 128-bit key into 10 additional round keys.
- **xorEncrypt.h / xorEncrypt.cpp**: Performs XOR operations with the expanded keys.
- **subByte.h / subByte.cpp**: Applies the AES S-box for byte substitution.
- **shiftRows.h / shiftRows.cpp**: Shifts rows as part of the encryption process.
- **mixColumns.h / mixColumns.cpp**: Mixes columns as part of the encryption.
- **rotateWord.h / rotateWord.cpp**: Rotates bytes in word units for key expansion.

## How It Works

The encryption follows these main steps:

1. **Key Expansion**: 
   - Expands a 16-byte (128-bit) original key into 11 keys using the AES key schedule. These expanded keys are used for each encryption round.

2. **Block Sectioning and Padding**: 
   - Divides the plaintext into 16-byte blocks. 
   - Pads the final block if its size is less than 16 bytes using PKCS#7 padding.

3. **Encryption Process**:
   - Each block undergoes the following transformations:
      - **Initial AddRoundKey**: XORs the block with the first expanded key.
      - **9 Main Rounds**:
         - SubByte (S-Box substitution)
         - ShiftRows (row shifting)
         - MixColumns (column mixing)
         - AddRoundKey (XOR with expanded key)
      - **Final Round (10th)**:
         - SubByte
         - ShiftRows
         - AddRoundKey
   - After processing, each encrypted block is printed in hexadecimal format.

## How to Build and Run

### Requirements
- **Compiler**: g++ or any C++ compiler with C++11 support.
- **Makefile**: A `Makefile` is included for easy building.

### Instructions

1. **Clone or Download** the project files.
2. **Compile** the project using the following command:
   ```bash
   make
   ```
   or directly with g++:
   ```bash
   g++ -std=c++11 -o AES128 AES128.cpp padBlock.cpp stringToHex.cpp keyExpansion.cpp xorEncrypt.cpp subByte.cpp mixColumns.cpp shiftRows.cpp rotateWord.cpp
   ```
3. **Run the Program**:
   ```bash
   ./AES128
   ```

### Expected Output

The program will output the encrypted blocks in hexadecimal format.

**Example**:
```
Encrypted Block 1: [hexadecimal values]
Encrypted Block 2: [hexadecimal values]
...
```

## Notes

- **Encryption Mode**: This program uses ECB mode (Electronic Codebook), where each block is encrypted independently using the same key.
- **AES Standard**: This project is intended for educational purposes and demonstrates the steps of the AES-128 encryption algorithm.

---

## Future Updates

- **Decryptor**: This program will allow the user to decrypt the encrypted message.
- **User Interface**: This program will allow the user to interact with the code through a simple interface which will allow it to select the text to encrypt/decrypt, key and optinos between encryption and decryption.
-