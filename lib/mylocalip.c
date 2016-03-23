#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

struct in_addr tmpaddr_local = { 0 };
struct in6_addr tmp6addr_local = IN6ADDR_ANY_INIT ;

struct in_addr mylocalip(char *iface){
    int status;
    struct ifaddrs *myaddrs;
    struct ifaddrs *ifa;
    status = getifaddrs(&myaddrs);
    if (status != 0){
        perror("getifaddrs failed!");
        exit(1);
    }
    for (ifa = myaddrs; ifa != NULL; ifa = ifa->ifa_next) {
        if (NULL == ifa->ifa_addr) {
            continue;
        }
        if ((ifa->ifa_flags & IFF_UP) == 0) {
            continue;
        }
        struct sockaddr_in *s4;
        if (AF_INET == ifa->ifa_addr->sa_family) {
            s4 = (struct sockaddr_in *) (ifa->ifa_addr);
            if (strcmp(ifa->ifa_name,iface) == 0){
                tmpaddr_local = s4->sin_addr;
            }
        }
    }
    freeifaddrs(myaddrs);
    return tmpaddr_local;
}

struct in6_addr mylocalip6(char *iface){
    int status;
    struct ifaddrs *myaddrs;
    struct ifaddrs *ifa;
    status = getifaddrs(&myaddrs);
    if (status != 0){
        perror("getifaddrs failed!");
        exit(1);
    }
    for (ifa = myaddrs; ifa != NULL; ifa = ifa->ifa_next){
        if (NULL == ifa->ifa_addr){
            continue;
        }
        if ((ifa->ifa_flags & IFF_UP) == 0) {
            continue;
        }
        struct sockaddr_in6 *s6;
        if (AF_INET6 == ifa->ifa_addr->sa_family) {
            s6 = (struct sockaddr_in6 *)(ifa->ifa_addr);
            if (strcmp(ifa->ifa_name,iface) == 0 && !IN6_IS_ADDR_LINKLOCAL(&(s6->sin6_addr))){
                tmp6addr_local = s6->sin6_addr;
            }
        }
    }
    freeifaddrs(myaddrs);
    return tmp6addr_local;
}


