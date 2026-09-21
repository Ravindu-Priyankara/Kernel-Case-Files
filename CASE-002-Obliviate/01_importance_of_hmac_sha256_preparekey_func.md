# Importance of __hmac_sha256_preparekey function

- IMPORTANCE
    1. __hmac_sha256_preparekey function is the last function from which we can extract user sent hmac key from the function arguments.

    2. This function trigger when encryption and decryption both sides. Not a single way.

    3. At the end of this function, our HMAC keys are wiped, and two states, inner and outer, are built.

- CODE

```c
static void __hmac_sha256_preparekey(struct sha256_block_state *istate,
				     struct sha256_block_state *ostate,
				     const u8 *raw_key, size_t raw_key_len,
				     const struct sha256_block_state *iv)
{
	union {
		u8 b[SHA256_BLOCK_SIZE];
		unsigned long w[SHA256_BLOCK_SIZE / sizeof(unsigned long)];
	} derived_key = { 0 };

	if (unlikely(raw_key_len > SHA256_BLOCK_SIZE)) {
		if (iv == &sha224_iv)
			sha224(raw_key, raw_key_len, derived_key.b);
		else
			sha256(raw_key, raw_key_len, derived_key.b);
	} else {
		memcpy(derived_key.b, raw_key, raw_key_len);
	}

	for (size_t i = 0; i < ARRAY_SIZE(derived_key.w); i++)
		derived_key.w[i] ^= REPEAT_BYTE(HMAC_IPAD_VALUE);
	*istate = *iv;
	sha256_blocks(istate, derived_key.b, 1);

	for (size_t i = 0; i < ARRAY_SIZE(derived_key.w); i++)
		derived_key.w[i] ^= REPEAT_BYTE(HMAC_OPAD_VALUE ^
						HMAC_IPAD_VALUE);
	*ostate = *iv;
	sha256_blocks(ostate, derived_key.b, 1);

	memzero_explicit(&derived_key, sizeof(derived_key));
}
```

- STATUS
    - `[CONFIRM]`
