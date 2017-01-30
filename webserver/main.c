# include <stdio.h>
# include <string.h>
# include <errno.h>
#include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <stdlib.h>

# include "socket.h"
# include "message.h"


int main (void)
{
  while (1)
  {
    int socket_serveur;
    if ( (socket_serveur = creer_serveur(8080)) == -1)
    {
      perror("creer serveur");
      exit(1);
    }
    int socket_client = accept(socket_serveur, NULL, NULL);
    if (socket_client == -1)
    {
      perror("accept client");
    }

    if (display_welcome_message(socket_client) == -1)
    {
      exit(1);
    }

    int connected = 1;
    while (connected)
    {
      connected = repeat_messages(socket_client);
    }
    /* Une fois qu'on lit rien, on ferme les sockets */
    close(socket_client);
    close(socket_serveur);
  }
  return 0;
}
