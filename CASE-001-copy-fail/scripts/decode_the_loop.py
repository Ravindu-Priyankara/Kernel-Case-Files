#!/usr/bin/env python3
import zlib

def d(x):
    return bytes.fromhex(x)

def c(f,t,c):
    print(f"COUNTER:\t {t}, DATA:\t {c}");

i=0;
e=zlib.decompress(d("78daab77f57163626464800126063b0610af82c101cc7760c0040e0c160c301d209a154d16999e07e5c1680601086578c0f0ff864c7e568f5e5b7e10f75b9675c44c7e56c3ff593611fcacfa499979fac5190c0c0c0032c310d3"))

while i<len(e):
    c(0,i,e[i:i+4]);
    i+=4

'''Output

COUNTER:         0, DATA:        b'\x7fELF'
COUNTER:         4, DATA:        b'\x02\x01\x01\x00'
COUNTER:         8, DATA:        b'\x00\x00\x00\x00'
COUNTER:         12, DATA:       b'\x00\x00\x00\x00'
COUNTER:         16, DATA:       b'\x02\x00>\x00'
COUNTER:         20, DATA:       b'\x01\x00\x00\x00'
COUNTER:         24, DATA:       b'x\x00@\x00'
COUNTER:         28, DATA:       b'\x00\x00\x00\x00'
COUNTER:         32, DATA:       b'@\x00\x00\x00'
COUNTER:         36, DATA:       b'\x00\x00\x00\x00'
COUNTER:         40, DATA:       b'\x00\x00\x00\x00'
COUNTER:         44, DATA:       b'\x00\x00\x00\x00'
COUNTER:         48, DATA:       b'\x00\x00\x00\x00'
COUNTER:         52, DATA:       b'@\x008\x00'
COUNTER:         56, DATA:       b'\x01\x00\x00\x00'
COUNTER:         60, DATA:       b'\x00\x00\x00\x00'
COUNTER:         64, DATA:       b'\x01\x00\x00\x00'
COUNTER:         68, DATA:       b'\x05\x00\x00\x00'
COUNTER:         72, DATA:       b'\x00\x00\x00\x00'
COUNTER:         76, DATA:       b'\x00\x00\x00\x00'
COUNTER:         80, DATA:       b'\x00\x00@\x00'
COUNTER:         84, DATA:       b'\x00\x00\x00\x00'
COUNTER:         88, DATA:       b'\x00\x00@\x00'
COUNTER:         92, DATA:       b'\x00\x00\x00\x00'
COUNTER:         96, DATA:       b'\x9e\x00\x00\x00'
COUNTER:         100, DATA:      b'\x00\x00\x00\x00'
COUNTER:         104, DATA:      b'\x9e\x00\x00\x00'
COUNTER:         108, DATA:      b'\x00\x00\x00\x00'
COUNTER:         112, DATA:      b'\x00\x10\x00\x00'
COUNTER:         116, DATA:      b'\x00\x00\x00\x00'
COUNTER:         120, DATA:      b'1\xc01\xff'
COUNTER:         124, DATA:      b'\xb0i\x0f\x05'
COUNTER:         128, DATA:      b'H\x8d=\x0f'
COUNTER:         132, DATA:      b'\x00\x00\x001'
COUNTER:         136, DATA:      b'\xf6j;X'
COUNTER:         140, DATA:      b'\x99\x0f\x051'
COUNTER:         144, DATA:      b'\xffj<X'
COUNTER:         148, DATA:      b'\x0f\x05/b'
COUNTER:         152, DATA:      b'in/s'
COUNTER:         156, DATA:      b'h\x00\x00\x00'

'''