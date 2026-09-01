# Crypto key randomization and failure

- CLAIM
    - If we change the first 8 bytes, the exploit will break.

- TEST
    - run scripts/randomizer/key_randomizer.
    - toggle FULL_RANDOMIZE flag and observe behavior.

- OBSERVATION
    - If we change first 8 bytes, exploit always failed.
    - First 8 byte
        - 0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x10
        - Meaning:
            - Failed to identify yet.

- INTERPRETATION:
    - We can change these things.
         - size of the key
         - randomize the keys except first 8 byte.

- TODO
    - Find the meaning of the first 8 bytes.
    - Reason about why random bytes fail if they touch the first 8 bytes.
    - Need to look back on near setkey.
    - What's needed for being valid 8 bytes?

- STATUS
    - `[CONFIRMED]`