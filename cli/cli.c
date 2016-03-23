#include <arpa/inet.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include "mylocalip.h"
#include "myexip.h"
#include "print_info.h"

struct in_addr addr = { 0 };
struct in6_addr addr6 =  IN6ADDR_ANY_INIT ;


int main(int argc, char **argv){

    int ver = 4; // defaults to ipv4
    int c; // used in getopts
    int internal = -1;
    char *iface = "";

    opterr = 0;
    while ((c = getopt (argc, argv, "h6i:")) != -1){
        switch (c)
        {
            case 'h':
                fprintf(stdout,"use: %s [-6] [-i ethN]\n",argv[0]);
                exit(0);
            case '6':
                ver = 6; // ipv6
                break;
            case 'i':
                internal = 0; // internal ip
                iface = optarg; // on interhace iface
                break;
            case '?':
                if (optopt == 'i') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                    fprintf(stderr, "use: %s [-6] [-i ethN]\n", argv[0]);
                } else if (isprint(optopt)) {
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                } else {
                    fprintf(stderr,
                            "Unknown option character `\\x%x'.\n",
                            optopt);
                }
                exit(1);
        } // end switch
    } // end while

    if (internal == 0){
        if (ver == 6) {
            addr6 = mylocalip6(iface);
            print_in6_addr(addr6);
        } else {
            addr = mylocalip(iface);
            print_in_addr(addr);
        }
    } else {
        if (ver == 6) {
          addr6 = myexip6();
          print_in6_addr(addr6);
        } else {
          addr = myexip();
          print_in_addr(addr);
        }
    }

    return 0;

}
