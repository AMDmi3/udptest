#include <sys/socket.h>
#include <netinet/in.h>
#include <err.h>
#include <strings.h>
#include <stdio.h>

int main() {
    int s;

    if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
        err(1, "socket");

    int yes = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(yes)) < 0)
        err(1, "SO_REUSEPORT");

    struct sockaddr_in sin;
    bzero(&sin, sizeof(sin));
    sin.sin_len = sizeof(sin);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(12345);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(s, (struct sockaddr*)&sin, sizeof(sin)) < 0)
        err(1, "bind");

    long n = 0;
    char buf[65536];
    while (1) {
        ssize_t len = recv(s, buf, 65536, 0);
        fprintf(stderr, "%ld: received %zd bytes\n", n++, len);
    }

    return 0;
}
