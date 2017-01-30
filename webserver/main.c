# include <stdio.h>
# include <string.h>
# include <errno.h>
#include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <stdlib.h>
# include <signal.h>

# include "socket.h"
# include "message.h"

void initialiser_signaux(void)
{
  // if current handling is SIG_ERR, set to SIG_IGN
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
  {
    perror("signal");
  }
}

void traite_client(int socket_client) {
  if (display_welcome_message(socket_client) == -1)
  {
    close(socket_client);
    return;
  }

  int connected = 1;
  while (connected)
  {
    if ( (connected = repeat_messages(socket_client)) == -1)
    {
      close(socket_client);
      return;
    }
  }
}

int main (void)
{
  initialiser_signaux();
  int socket_serveur;
  if ( (socket_serveur = creer_serveur(8080)) == -1)
  {
    perror("creer serveur");
    exit(1);
  }

  while (1)
  {
    int socket_client = accept(socket_serveur, NULL, NULL);
    if (socket_client == -1)
    {
      perror("accept client");
      close(socket_client);
      continue; // go to next client
    }

    if ( fork() == 0)
    {
      traite_client(socket_client);
    }
    close(socket_client);
  }
  return 0;
}
