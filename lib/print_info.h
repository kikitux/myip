//
// Created by Alvaro Miranda on 28/12/15.
//

#ifndef MYIP_PRINT_ADDRINFO_H
#define MYIP_PRINT_ADDRINFO_H
#include <netdb.h> // struct addrinfo
void print_addrinfo(struct addrinfo* addr);
void print_in_addr(struct in_addr addr);
void print_in6_addr(struct in6_addr addr6);
#endif //MYIP_PRINT_ADDRINFO_H
