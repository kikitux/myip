//
// Created by Alvaro Miranda on 28/12/15.
//

#ifndef MYIP_MYLOCALIP_H_H
#define MYIP_MYLOCALIP_H_H
// struct

// functions
struct in_addr mylocalip(char *iface);
struct in6_addr mylocalip6(char *iface);

//int show_address_info4( struct ifaddrs *ifa );
//int show_address_info6( struct ifaddrs *ifa );
#endif //MYIP_MYLOCALIP_H_H
