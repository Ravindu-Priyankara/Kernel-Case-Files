#!/usr/bin/env python3
import zlib as z

payload_blob = "78daab77f57163626464800126063b0610af82c101cc7760c0040e0c160c301d209a154d16999e07e5c1680601086578c0f0ff864c7e568f5e5b7e10f75b9675c44c7e56c3ff593611fcacfa499979fac5190c0c0c0032c310d3"

# extract the bytes from hexstring
payload_bytes = bytes.fromhex(payload_blob)

# decompressed the payload
payload = z.decompress(payload_bytes)

with open("original_payload.bin", "wb") as f:
    f.write(payload)

# display some useful data
print(f"compressed: {len(payload_bytes)} bytes")
print(f"decompressed: {len(payload)} bytes")
print(f"magic: {payload[:4]!r}")