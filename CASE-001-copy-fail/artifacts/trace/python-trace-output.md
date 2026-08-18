```txt
strace -f -tt -e trace=socket,bind,setsockopt,accept,sendmsg,splice,recvfrom python3 test.py 
19:54:04.505392 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.509112 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.511480 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.512609 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.517206 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\177ELF", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.522242 splice(3, [0], 7, NULL, 4, 0) = 4
19:54:04.523687 splice(6, NULL, 5, NULL, 4, 0) = 4
19:54:04.524806 recvfrom(5, 0x70abc3fdb2c0, 8, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.530494 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.532582 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.534556 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.535825 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.538244 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\2\1\1\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.540242 splice(3, [0], 9, NULL, 8, 0) = 8
19:54:04.541096 splice(8, NULL, 5, NULL, 8, 0) = 8
19:54:04.542218 recvfrom(5, 0x70abc497a390, 12, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.548309 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.549342 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.550760 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.551867 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.553780 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.555891 splice(3, [0], 11, NULL, 12, 0) = 12
19:54:04.557316 splice(10, NULL, 5, NULL, 12, 0) = 12
19:54:04.558116 recvfrom(5, 0x70abc3f9b990, 16, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.562546 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.563623 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.564796 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.565758 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.567939 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.570047 splice(3, [0], 13, NULL, 16, 0) = 16
19:54:04.570933 splice(12, NULL, 5, NULL, 16, 0) = 16
19:54:04.571737 recvfrom(5, 0x70abc3f9b990, 20, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.576540 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.577729 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.578802 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.581411 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.584552 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\2\0>\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.587034 splice(3, [0], 15, NULL, 20, 0) = 20
19:54:04.587871 splice(14, NULL, 5, NULL, 20, 0) = 20
19:54:04.588809 recvfrom(5, 0x70abc3f9b990, 24, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.593554 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.594522 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.595797 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.596848 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.598820 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\1\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.600977 splice(3, [0], 17, NULL, 24, 0) = 24
19:54:04.601828 splice(16, NULL, 5, NULL, 24, 0) = 24
19:54:04.602777 recvfrom(5, 0x70abc3f9b990, 28, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.607598 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.609102 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.610628 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.611720 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.613625 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAAx\0@\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.615646 splice(3, [0], 19, NULL, 28, 0) = 28
19:54:04.616479 splice(18, NULL, 5, NULL, 28, 0) = 28
19:54:04.617475 recvfrom(5, 0x70abc3f9dcc0, 32, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.622892 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.624149 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.625477 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.626614 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.628524 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.630812 splice(3, [0], 21, NULL, 32, 0) = 32
19:54:04.631673 splice(20, NULL, 5, NULL, 32, 0) = 32
19:54:04.632759 recvfrom(5, 0x70abc3f9dd10, 36, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.637558 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.638411 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.639736 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.640903 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.642744 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA@\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.644964 splice(3, [0], 23, NULL, 36, 0) = 36
19:54:04.646051 splice(22, NULL, 5, NULL, 36, 0) = 36
19:54:04.646796 recvfrom(5, 0x70abc3f9dcc0, 40, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.651262 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.652243 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.654003 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.655268 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.657788 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.660524 splice(3, [0], 25, NULL, 40, 0) = 40
19:54:04.661278 splice(24, NULL, 5, NULL, 40, 0) = 40
19:54:04.662142 recvfrom(5, 0x70abc3f9dd10, 44, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.666606 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.667525 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.668609 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.669577 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.671478 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.673662 splice(3, [0], 27, NULL, 44, 0) = 44
19:54:04.674615 splice(26, NULL, 5, NULL, 44, 0) = 44
19:54:04.675447 recvfrom(5, 0x70abc3f6a3f0, 48, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.679325 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.680235 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.681367 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.682411 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.684492 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.686538 splice(3, [0], 29, NULL, 48, 0) = 48
19:54:04.687568 splice(28, NULL, 5, NULL, 48, 0) = 48
19:54:04.688321 recvfrom(5, 0x70abc3f6a6f0, 52, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.692358 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.693392 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.694590 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.696389 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.698422 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.700353 splice(3, [0], 31, NULL, 52, 0) = 52
19:54:04.701285 splice(30, NULL, 5, NULL, 52, 0) = 52
19:54:04.702051 recvfrom(5, 0x70abc3f6a3f0, 56, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.706326 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.707276 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.708344 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.709272 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.711109 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA@\08\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.712972 splice(3, [0], 33, NULL, 56, 0) = 56
19:54:04.713952 splice(32, NULL, 5, NULL, 56, 0) = 56
19:54:04.714739 recvfrom(5, 0x70abc3f6a6f0, 60, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.719015 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.720073 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.721006 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.721780 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.724220 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\1\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.726122 splice(3, [0], 35, NULL, 60, 0) = 60
19:54:04.727027 splice(34, NULL, 5, NULL, 60, 0) = 60
19:54:04.727817 recvfrom(5, 0x70abc3fecde0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.733249 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.734179 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.735280 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.736263 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.738271 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.740409 splice(3, [0], 37, NULL, 64, 0) = 64
19:54:04.741356 splice(36, NULL, 5, NULL, 64, 0) = 64
19:54:04.742213 recvfrom(5, 0x70abc3fecde0, 68, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.746506 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.747400 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.748574 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.749595 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.751414 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\1\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.753367 splice(3, [0], 39, NULL, 68, 0) = 68
19:54:04.754385 splice(38, NULL, 5, NULL, 68, 0) = 68
19:54:04.755345 recvfrom(5, 0x70abc3fecde0, 72, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.759661 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.760472 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.761534 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.762425 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.764485 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\5\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.766597 splice(3, [0], 41, NULL, 72, 0) = 72
19:54:04.768133 splice(40, NULL, 5, NULL, 72, 0) = 72
19:54:04.769368 recvfrom(5, 0x70abc3fecde0, 76, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.773666 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.774548 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.775807 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.776909 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.778976 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.781191 splice(3, [0], 43, NULL, 76, 0) = 76
19:54:04.782060 splice(42, NULL, 5, NULL, 76, 0) = 76
19:54:04.782794 recvfrom(5, 0x70abc3fbf6d0, 80, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.786837 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.787834 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.789047 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.789918 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.791924 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.793771 splice(3, [0], 45, NULL, 80, 0) = 80
19:54:04.794467 splice(44, NULL, 5, NULL, 80, 0) = 80
19:54:04.795370 recvfrom(5, 0x70abc3fbf7d0, 84, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.799660 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.800644 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.801928 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.803164 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.806005 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0@\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.808689 splice(3, [0], 47, NULL, 84, 0) = 84
19:54:04.809793 splice(46, NULL, 5, NULL, 84, 0) = 84
19:54:04.810503 recvfrom(5, 0x70abc3fbf6d0, 88, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.815050 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.816577 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.817921 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.819147 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.821224 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.823183 splice(3, [0], 49, NULL, 88, 0) = 88
19:54:04.824409 splice(48, NULL, 5, NULL, 88, 0) = 88
19:54:04.825011 recvfrom(5, 0x70abc3fbf7d0, 92, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.829639 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.830583 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.832010 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.832890 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.834958 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0@\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.837153 splice(3, [0], 51, NULL, 92, 0) = 92
19:54:04.838514 splice(50, NULL, 5, NULL, 92, 0) = 92
19:54:04.839171 recvfrom(5, 0x70abc4917f50, 96, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.844761 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.846079 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.847768 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.849049 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.851098 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.853221 splice(3, [0], 53, NULL, 96, 0) = 96
19:54:04.854211 splice(52, NULL, 5, NULL, 96, 0) = 96
19:54:04.854918 recvfrom(5, 0x70abc4917f50, 100, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.859416 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.860755 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.861905 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.862748 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.865056 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\236\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.866872 splice(3, [0], 55, NULL, 100, 0) = 100
19:54:04.867909 splice(54, NULL, 5, NULL, 100, 0) = 100
19:54:04.868931 recvfrom(5, 0x70abc4917f50, 104, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.873562 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.874417 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.875518 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.876469 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.878928 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.881476 splice(3, [0], 57, NULL, 104, 0) = 104
19:54:04.882673 splice(56, NULL, 5, NULL, 104, 0) = 104
19:54:04.883506 recvfrom(5, 0x70abc4917f50, 108, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.887626 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.888513 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.889753 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.890721 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.892521 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\236\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.894273 splice(3, [0], 59, NULL, 108, 0) = 108
19:54:04.894942 splice(58, NULL, 5, NULL, 108, 0) = 108
19:54:04.896038 recvfrom(5, 0x70abc3fa4eb0, 112, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.900431 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.901312 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.902534 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.903661 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.905457 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.907489 splice(3, [0], 61, NULL, 112, 0) = 112
19:54:04.908168 splice(60, NULL, 5, NULL, 112, 0) = 112
19:54:04.909448 recvfrom(5, 0x70abc3fa4eb0, 116, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.913572 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.914580 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.915756 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.917470 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.919623 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\20\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.921789 splice(3, [0], 63, NULL, 116, 0) = 116
19:54:04.922730 splice(62, NULL, 5, NULL, 116, 0) = 116
19:54:04.923365 recvfrom(5, 0x70abc3fa4eb0, 120, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.927685 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.928547 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.929828 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.930900 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.932675 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.934926 splice(3, [0], 65, NULL, 120, 0) = 120
19:54:04.935850 splice(64, NULL, 5, NULL, 120, 0) = 120
19:54:04.936460 recvfrom(5, 0x70abc3fa4eb0, 124, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.941184 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.942332 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.943591 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.944460 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.946597 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA1\3001\377", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.948718 splice(3, [0], 67, NULL, 124, 0) = 124
19:54:04.949534 splice(66, NULL, 5, NULL, 124, 0) = 124
19:54:04.950735 recvfrom(5, 0x70abc3e20520, 128, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.956296 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.957613 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.958833 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.959732 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.961750 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\260i\17\5", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.963906 splice(3, [0], 69, NULL, 128, 0) = 128
19:54:04.964874 splice(68, NULL, 5, NULL, 128, 0) = 128
19:54:04.965997 recvfrom(5, 0x70abc3e20520, 132, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.970361 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.971401 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.973194 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.974148 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.976144 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAAH\215=\17", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.978102 splice(3, [0], 71, NULL, 132, 0) = 132
19:54:04.978895 splice(70, NULL, 5, NULL, 132, 0) = 132
19:54:04.979568 recvfrom(5, 0x70abc3e20520, 136, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.983595 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.984451 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.985351 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:04.986308 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:04.988117 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0001", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:04.989956 splice(3, [0], 73, NULL, 136, 0) = 136
19:54:04.990879 splice(72, NULL, 5, NULL, 136, 0) = 136
19:54:04.992038 recvfrom(5, 0x70abc3e20520, 140, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:04.996581 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:04.997699 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:04.998913 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:05.000038 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:05.002094 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\366j;X", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:05.004034 splice(3, [0], 75, NULL, 140, 0) = 140
19:54:05.004924 splice(74, NULL, 5, NULL, 140, 0) = 140
19:54:05.005712 recvfrom(5, 0x70abc4903350, 144, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:05.009934 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:05.010899 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:05.012122 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:05.012895 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:05.015185 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\231\17\0051", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:05.016943 splice(3, [0], 77, NULL, 144, 0) = 144
19:54:05.017879 splice(76, NULL, 5, NULL, 144, 0) = 144
19:54:05.019035 recvfrom(5, 0x70abc4903350, 148, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:05.023805 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:05.025128 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:05.026564 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:05.028387 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:05.030694 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\377j<X", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:05.033021 splice(3, [0], 79, NULL, 148, 0) = 148
19:54:05.033897 splice(78, NULL, 5, NULL, 148, 0) = 148
19:54:05.034818 recvfrom(5, 0x70abc4903350, 152, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:05.039183 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:05.040384 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:05.041832 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:05.043060 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:05.045094 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\17\5/b", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:05.047389 splice(3, [0], 81, NULL, 152, 0) = 152
19:54:05.048539 splice(80, NULL, 5, NULL, 152, 0) = 152
19:54:05.049645 recvfrom(5, 0x70abc4903350, 156, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:05.054044 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:05.055225 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:05.056693 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:05.058206 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:05.060287 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAAin/s", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:05.062285 splice(3, [0], 83, NULL, 156, 0) = 156
19:54:05.063428 splice(82, NULL, 5, NULL, 156, 0) = 156
19:54:05.064629 recvfrom(5, 0x70abc3e15570, 160, 0, NULL, NULL) = -1 EBADMSG (Bad message)
19:54:05.070072 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
19:54:05.071532 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
19:54:05.072776 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
19:54:05.073618 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
19:54:05.075965 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAAh\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
19:54:05.077893 splice(3, [0], 85, NULL, 160, 0) = 160
19:54:05.078793 splice(84, NULL, 5, NULL, 160, 0) = 160
19:54:05.080053 recvfrom(5, 0x70abc3e15570, 164, 0, NULL, NULL) = -1 EBADMSG (Bad message)
strace: Process 3655 attached
strace: Process 3656 attached
$ 
```