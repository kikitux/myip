#include <config.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include "builtins.h"
#include "shell.h"
#include "bashgetopt.h"
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include "variables.h"

// local

#include <netinet/in.h>
#include "mylocalip.h"
#include "myexip.h"
#include "print_info.h"

struct in_addr addr = { 0 };
struct in6_addr addr6 =  IN6ADDR_ANY_INIT ;
char str[INET_ADDRSTRLEN];
char str6[INET6_ADDRSTRLEN];

builtin_myip (list) WORD_LIST *list;
{
  WORD_LIST *w = NULL;
  int opt = 0;
  char *var = NULL;
  bool overwrite = false;
  bool ipv6 = false;

  //catch no options // to be used when you want no options, but will allow words
  //if (no_options (list)){
  //    return (EX_USAGE);
  //}

  //catch no arguments // list is the array of words and options
  //if (list == 0){
  //  builtin_usage();
  //  return(EX_USAGE);
  //}

  reset_internal_getopt();
  while ((opt = internal_getopt (list, "ov:h6")) != -1){
    switch(opt) {
      case 'o':
        overwrite = true;
        break;
      case '6':
        ipv6 = true;
        break;
      case 'v':
        var = list_optarg; /* should add check for valid variable name */
        break;
      case 'h':
        builtin_usage();
        break;
      default:
        break;
    }
  }
  list = loptend;

  //catch no options // at this stage should be no more arguments
  // we check again because default allow continue and we may want want words
  if (no_options (list)){
    return (EX_USAGE);
  }

  if (var){
    SHELL_VAR *v = find_variable(var);
    if (v && overwrite == false) {
      printf("OS var %s has values. not overwriting\n",var);
    }
    if (!v || overwrite == true) {
      printf("setting values\n");
      if (ipv6 == true) {
        //addr6 = myexip6();
        //inet_ntop(AF_INET6, &(addr6), str6, INET6_ADDRSTRLEN);
        //bind_variable (var, str6, 0);
      } else {
        //addr = myexip();
        //inet_ntop(AF_INET, &(addr), str, INET_ADDRSTRLEN);
        //bind_variable (var, str, 0);
      }
    }
  } else {
      printf("printing values\n");
      if (ipv6 == true) {
          //addr6 = myexip6();
          //print_in6_addr(addr6);
      } else {
          //addr = myexip();
          //print_in_addr(addr);
      }
  }

  if (list != 0){
    w = list;
    while (w != 0){
      //printf("%s\n", w->word->word);
      w = w->next;
    }
  }
  fflush (stdout);
  return (EXECUTION_SUCCESS);
}

char *builtin_myip_doc[] = {
	"myip is a resolver of the public ip\n",
	"the service is done by myexternalip.com\n",
	"usage:\n",
	"myip -v var ipv4 [-o]\n",
	"myip -v var ipv6 [-o]\n",
	(char *)NULL
};

struct builtin builtin_myip_struct = {
	"builtin_myip",			/* builtin name */
	builtin_myip,			/* function implementing the builtin */
	BUILTIN_ENABLED,		/* initial flags for builtin */
	builtin_myip_doc,			/* array of long documentation strings. */
	"myip -v var -o ipv4",	/* usage synopsis; becomes short_doc */
	0				/* reserved for internal use */
};
