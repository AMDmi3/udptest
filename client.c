#include <sys/socket.h>
#include <netinet/in.h>
#include <err.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int s;

    if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
        err(1, "socket");

    struct sockaddr_in sin;
    bzero(&sin, sizeof(sin));
    sin.sin_len = sizeof(sin);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(12345);
    sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    long n = 0;
    while (1) {
        ssize_t len = sendto(s, NULL, 0, 0, (struct sockaddr*)&sin, sizeof(sin));
        fprintf(stderr, "%ld: sent %zd bytes\n", n++, len);
        usleep(100);
    }

    return 0;
}
