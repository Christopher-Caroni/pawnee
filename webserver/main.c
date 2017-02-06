# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/socket.h>
# include <stdlib.h>
# include <signal.h>

# include "socket.h"
# include "message.h"

void traitement_signal(int sig)
{
  printf("Signal %d reçu\n", sig);
  if (sig == SIGCHLD)
  {
    int child;
    while ( (child = waitpid(-1, NULL, WNOHANG) > 0))
    {
      printf("waited for child pid = %d to end\n", child);
    }
  }
}

void initialiser_signaux(void)
{
  // if current handling is SIG_ERR, set to SIG_IGN
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
  {
    perror("signal");
  }

  // set action to traitement_signal when receiving signal SIGCHLD
  struct sigaction sa ;
  sa.sa_handler = traitement_signal;
  sigemptyset (&sa.sa_mask); // ensemble vide à bloqier
  sa.sa_flags = SA_RESTART; // redemarrer fonctions qui auraient pu etre interrompus
  if (sigaction(SIGCHLD, &sa, NULL) == -1)
  {
    perror("sigaction(SIGCHLD)");
  }
}

void traite_client(int socket_client) {
  display_welcome_message(socket_client);
  repeat_messages(socket_client);
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
    printf("accepted client\n");
    if (socket_client == -1)
    {
      perror("accept client");
      close(socket_client);
      continue; // go to next client
    }

    if ( fork() == 0)
    {
      traite_client(socket_client);
      return 0;
    }
    close(socket_client);
  }
  return 0;
}
