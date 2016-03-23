#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>


void print_addrinfo(struct addrinfo* addr) {
   if (addr->ai_family == AF_INET6) {
      struct sockaddr_in6* saddr = (struct sockaddr_in6*)addr->ai_addr;
      char ip_s[INET6_ADDRSTRLEN];
      inet_ntop(AF_INET6, &(saddr->sin6_addr), ip_s, INET6_ADDRSTRLEN);
      printf("%s ", ip_s);
      printf("%hu\n", ntohs(saddr->sin6_port));
   } else if (addr->ai_family == AF_INET) {
      struct sockaddr_in* saddr = (struct sockaddr_in*)addr->ai_addr;
      char ip_s[INET_ADDRSTRLEN];
      inet_ntop(AF_INET, &(saddr->sin_addr), ip_s, INET_ADDRSTRLEN);
      printf("%s ", ip_s);
      printf("%hu\n", ntohs(saddr->sin_port));
   }
}

// print ipv6 from in6_addr
void print_in6_addr(struct in6_addr addr6){
   char str[INET6_ADDRSTRLEN];
   inet_ntop(AF_INET6, &(addr6), str, INET6_ADDRSTRLEN);
   if (strcmp(str,"::")){
      printf("%s\n", str);
   }

}

// print ipv4 from in_addr
void print_in_addr(struct in_addr addr){
   char str[INET_ADDRSTRLEN];
   inet_ntop(AF_INET, &(addr), str, INET_ADDRSTRLEN);
   if (strcmp(str,"0.0.0.0")){
      printf("%s\n", str);
   }

}