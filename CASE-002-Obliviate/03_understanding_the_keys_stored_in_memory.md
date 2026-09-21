# Understanding the keys stored in kernel memory.

- CLAIM
    - We can read and write HMAC keys inside the kernel without changing the permission bit.

- INTERPRETATION
    - To understand this, we need to grasp what happens when a user sends keys to the Linux kernel.
    - For this, I'll take our case-001 used authencesn example.
        1. User sends the key. 
        2. In the above case, our keys go to the af_alg module.
        3. And it triggers the `alg_setkey` function.
        4. That's inside allocates kernel heap memory for our keys.(sock_kmalloc used)

    - That's why we can change the keys.

- CODE 

```c
static int alg_setkey(struct sock *sk, sockptr_t ukey, unsigned int keylen)
{
	struct alg_sock *ask = alg_sk(sk);
	const struct af_alg_type *type = ask->type;
	u8 *key;
	int err;

	key = sock_kmalloc(sk, keylen, GFP_KERNEL);
	if (!key)
		return -ENOMEM;

	err = -EFAULT;
	if (copy_from_sockptr(key, ukey, keylen))
		goto out;

	err = type->setkey(ask->private, key, keylen);

out:
	sock_kzfree_s(sk, key, keylen);

	return err;
}
```

- STATUS
    - `[CONFIRM]`