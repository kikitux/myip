#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

struct in_addr tmpaddr_ex = { 0 };
struct in6_addr tmp6addr_ex = IN6ADDR_ANY_INIT ;

void error(const char *msg) { perror(msg); exit(0); }

struct in_addr myexip() {
    int sockfd, bytes, sent, received, total;
    int portno = 80;
    char response[4096];
    char *host = "ipv4.myexternalip.com";
    char *message = "GET /raw HTTP/1.1\r\nHost: ipv4.myexternalip.com\r\nConnection: close\r\n\r\n";

    struct hostent *server;
    struct sockaddr_in serv_addr;

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    /* lookup the ip address */
    server = gethostbyname2(host, AF_INET);
    if (server == NULL) error("ERROR, no such host");

    /* fill in the structure */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    /* connect the socket */
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd, message + sent, total - sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent += bytes;
    } while (sent < total);

    /* receive the response */
    memset(response, 0, sizeof(response));
    total = sizeof(response) - 1;
    received = 0;
    do {
        bytes = read(sockfd, response + received, total - received);
        if (bytes < 0)
            error("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received += bytes;
    } while (received < total);

    if (received == total)
        error("ERROR storing complete response from socket");

    /* close the socket */
    close(sockfd);

    /* process response */

    char *token = NULL;
    char *code = NULL;
    char *ip = NULL;

    token = strtok(response, "\r");
    int i = 0;

    while (token) {
        if (strncmp(token, "HTTP/1", 6) == 0) {
            code = token;
        }
        ip = token;
        i++;
        token = strtok(NULL, "\n");
    }
    if (strcmp(code, "HTTP/1.1 200 OK") == 0) {
        inet_pton(AF_INET, ip, &(tmpaddr_ex));
        return tmpaddr_ex;
    }

    exit(1);
}

struct in6_addr myexip6() {
    int sockfd, bytes, sent, received, total;
    int portno = 80;
    char response[4096];
    char *host = "ipv6.myexternalip.com";
    char *message = "GET /raw HTTP/1.1\r\nHost: ipv6.myexternalip.com\r\nConnection: close\r\n\r\n";

    struct hostent *server;
    struct sockaddr_in6 serv_addr6;

    /* create the socket */
    sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    /* lookup the ip address */
    server = gethostbyname2(host, AF_INET6);
    if (server == NULL) error("ERROR, no such host");

    /* fill in the structure */
    memset(&serv_addr6, 0, sizeof(serv_addr6));
    serv_addr6.sin6_family = AF_INET6;
    serv_addr6.sin6_port = htons(portno);
    memcpy(&serv_addr6.sin6_addr.s6_addr, server->h_addr, server->h_length);

    /* connect the socket */
    if (connect(sockfd, (struct sockaddr *) &serv_addr6, sizeof(serv_addr6)) < 0)
        error("ERROR connecting");

    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd, message + sent, total - sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent += bytes;
    } while (sent < total);

    /* receive the response */
    memset(response, 0, sizeof(response));
    total = sizeof(response) - 1;
    received = 0;
    do {
        bytes = read(sockfd, response + received, total - received);
        if (bytes < 0)
            error("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received += bytes;
    } while (received < total);

    if (received == total)
        error("ERROR storing complete response from socket");

    /* close the socket */
    close(sockfd);

    /* process response */

    char *token = NULL;
    char *code = NULL;
    char *ip = NULL;

    token = strtok(response, "\r");
    int i = 0;

    while (token) {
        if (strncmp(token, "HTTP/1", 6) == 0) {
            code = token;
        }
        ip = token;
        i++;
        token = strtok(NULL, "\n");
    }
    if (strcmp(code, "HTTP/1.1 200 OK") == 0) {
        inet_pton(AF_INET6, ip, &(tmp6addr_ex));
        return tmp6addr_ex;
    }

    exit(1);
}
