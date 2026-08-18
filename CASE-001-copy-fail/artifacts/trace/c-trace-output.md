ravindu@ravindu-Standard-PC-i440FX-PIIX-1996:~/research/copy-fail$ strace -f -tt -e trace=socket,bind,setsockopt,accept,sendmsg,splice,recvfrom ./test 
Reach to socket syscall
16:32:32.461101 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.464026 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.465760 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.466801 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.468237 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.469760 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\177ELF", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.472560 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.473822 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.475677 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 0 failed

Reach to socket syscall
16:32:32.489365 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.491262 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.492591 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.493585 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.494983 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.497141 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\2\1\1\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.499267 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.500711 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.502217 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 4 failed

Reach to socket syscall
16:32:32.507828 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.509127 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.510385 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.511087 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.512242 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.513607 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.515387 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.516596 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.518408 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 8 failed

Reach to socket syscall
16:32:32.524727 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.526369 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.527760 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.528609 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.529854 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.531682 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.533399 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.535202 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.537723 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 12 failed

Reach to socket syscall
16:32:32.544176 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.545499 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.546831 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.547735 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.548819 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.549997 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\2\0>\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.551567 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.552811 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.554459 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 16 failed

Reach to socket syscall
16:32:32.560305 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.561450 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.562672 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.563430 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.564525 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.565607 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\1\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.567119 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.568648 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.570187 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 20 failed

Reach to socket syscall
16:32:32.577294 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.579304 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.581034 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.581796 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.583067 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.584700 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAAx\0@\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.586866 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.588219 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.589699 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 24 failed

Reach to socket syscall
16:32:32.595448 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.596566 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.598058 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.598857 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.600297 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.601644 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.603433 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.604787 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.606665 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 28 failed

Reach to socket syscall
16:32:32.613272 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.614660 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.616008 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.616723 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.617841 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.618998 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA@\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.620645 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.621817 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.623507 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 32 failed

Reach to socket syscall
16:32:32.629241 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.630312 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.631530 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.632283 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.633093 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.634172 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.635660 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.636752 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.638312 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 36 failed

Reach to socket syscall
16:32:32.644204 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.645700 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.647178 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.647925 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.649551 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.650729 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.652393 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.653818 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.655740 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 40 failed

Reach to socket syscall
16:32:32.661732 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.662953 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.664094 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.664782 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.666776 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.668253 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.670123 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.671199 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.673037 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 44 failed

Reach to socket syscall
16:32:32.679296 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.681166 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.682997 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.684110 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.685643 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.687064 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.688723 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.689860 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.691663 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 48 failed

Reach to socket syscall
16:32:32.697611 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.698811 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.700209 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.701054 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.702290 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.703942 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA@\08\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.705577 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.706844 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.708583 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 52 failed

Reach to socket syscall
16:32:32.714269 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.715624 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.717449 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.718251 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.719738 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.721167 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\1\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.723117 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.724179 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.725966 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 56 failed

Reach to socket syscall
16:32:32.731955 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.733170 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.734532 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.735548 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.736743 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.738058 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.739620 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.741165 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.742882 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 60 failed

Reach to socket syscall
16:32:32.748847 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.750146 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.751432 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.752373 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.753694 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.755436 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\1\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.757549 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.758817 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.760845 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 64 failed

Reach to socket syscall
16:32:32.767366 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.769160 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.770628 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.771636 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.772757 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.774043 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\5\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.775681 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.776972 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.778594 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 68 failed

Reach to socket syscall
16:32:32.784458 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.785725 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.787155 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.787863 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.789117 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.790432 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.792564 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.794004 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.795830 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 72 failed

Reach to socket syscall
16:32:32.801904 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.803202 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.804637 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.805469 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.806510 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.807565 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.809170 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.810233 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.811757 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 76 failed

Reach to socket syscall
16:32:32.817722 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.819188 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.820503 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.821265 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.822468 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.823609 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0@\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.825005 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.826463 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.828675 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 80 failed

Reach to socket syscall
16:32:32.835589 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.836991 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.838643 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.839373 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.841080 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.842330 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.844203 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.845363 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.847204 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 84 failed

Reach to socket syscall
16:32:32.853587 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.855133 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.856516 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.857728 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.859100 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.860809 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0@\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.864668 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.866797 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.868738 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 88 failed

Reach to socket syscall
16:32:32.875046 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.876369 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.877765 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.878652 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.879773 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.881074 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.882971 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.884107 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.885822 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 92 failed

Reach to socket syscall
16:32:32.891469 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.892737 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.894009 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.894657 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.896057 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.897121 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\236\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.898727 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.900231 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.902612 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 96 failed

Reach to socket syscall
16:32:32.908832 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.910363 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.911705 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.912725 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.913866 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.915393 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.916959 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.918069 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.920235 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 100 failed

Reach to socket syscall
16:32:32.926071 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.927352 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.928712 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.929541 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.930641 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.931786 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\236\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.933798 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.935200 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.937146 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 104 failed

Reach to socket syscall
16:32:32.943450 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.944771 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.946182 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.946868 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.948312 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.949531 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.951056 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.952187 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.953812 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 108 failed

Reach to socket syscall
16:32:32.960223 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.961571 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.962731 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.963662 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.964827 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.965991 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\20\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.967677 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.968968 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.970642 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 112 failed

Reach to socket syscall
16:32:32.977248 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.978590 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.980174 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.980943 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:32.982587 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:32.984191 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:32.986445 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:32.987716 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:32.989307 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 116 failed

Reach to socket syscall
16:32:32.995145 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:32.997209 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:32.998759 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:32.999520 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:33.000770 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:33.002056 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA1\3001\377", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:33.003717 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:33.004815 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:33.006598 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 120 failed

Reach to socket syscall
16:32:33.012907 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:33.014701 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:33.016104 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:33.016796 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:33.017880 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:33.019483 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\260i\17\5", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:33.021056 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:33.022147 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:33.023728 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 124 failed

Reach to socket syscall
16:32:33.029695 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:33.031095 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:33.032346 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:33.033270 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:33.034400 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:33.035472 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAAH\215=\17", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:33.037186 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:33.038226 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:33.039594 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 128 failed

Reach to socket syscall
16:32:33.045496 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:33.046651 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:33.048419 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:33.049511 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:33.050630 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:33.051769 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\0\0\0001", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:33.053549 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:33.054636 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:33.056402 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 132 failed

Reach to socket syscall
16:32:33.061823 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:33.063010 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:33.064333 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:33.064971 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:33.065851 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:33.067215 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\366j;X", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:33.068659 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:33.069702 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:33.071084 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 136 failed

Reach to socket syscall
16:32:33.076846 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:33.078054 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:33.079247 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:33.079974 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:33.080825 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:33.082021 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\231\17\0051", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:33.083556 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:33.085087 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:33.086691 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 140 failed

Reach to socket syscall
16:32:33.092694 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:33.093724 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:33.095070 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:33.095686 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:33.096577 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:33.097610 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\377j<X", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:33.099231 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:33.100411 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:33.101739 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 144 failed

Reach to socket syscall
16:32:33.107402 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:33.108416 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:33.109646 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:33.110331 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:33.111284 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:33.112312 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAA\17\5/b", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:33.113891 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:33.115252 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:33.116845 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 148 failed

Reach to socket syscall
16:32:33.122921 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:33.124512 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:33.125717 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:33.126490 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:33.127721 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:33.128957 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAAin/s", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:33.130772 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:33.131806 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:33.133527 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 152 failed

Reach to socket syscall
16:32:33.139551 socket(AF_ALG, SOCK_SEQPACKET|SOCK_CLOEXEC, 0) = 4
Reach to bind syscall
16:32:33.140800 bind(4, {sa_family=AF_ALG, salg_type="aead", salg_feat=0, salg_mask=0, salg_name="authencesn(hmac(sha256),cbc(aes))"}, 88) = 0
Reach to setsockopt syscall
16:32:33.142099 setsockopt(4, SOL_ALG, ALG_SET_KEY, "\10\0\1\0\0\0\0\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 40) = 0
16:32:33.142767 setsockopt(4, SOL_ALG, ALG_SET_AEAD_AUTHSIZE, NULL, 4) = 0
Reach to accept syscall
16:32:33.143878 accept(4, NULL, NULL)   = 5
Reach to sendmsg syscall
16:32:33.144913 sendmsg(5, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="AAAAh\0\0\0", iov_len=8}], msg_iovlen=1, msg_control=[{cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x3, cmsg_data="\x00\x00\x00\x00"}, {cmsg_len=36, cmsg_level=SOL_ALG, cmsg_type=0x2, cmsg_data="\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"}, {cmsg_len=20, cmsg_level=SOL_ALG, cmsg_type=0x4, cmsg_data="\x08\x00\x00\x00"}], msg_controllen=88, msg_flags=0}, MSG_MORE) = 8
16:32:33.146475 splice(3, NULL, 7, NULL, 4, 0) = 4
Data sent from file 2 pipe
16:32:33.147598 splice(6, NULL, 5, NULL, 4, 0) = 4
Data sent from pipe 2 dest
Reach to recv syscall
16:32:33.149117 recvfrom(5, 0x5e595c0795e0, 64, 0, NULL, NULL) = -1 EBADMSG (Bad message)
Recv:: Bad message
Counter 156 failed

[1.] Execute the target file...
strace: Process 2153 attached
strace: Process 2154 attached
$ 
