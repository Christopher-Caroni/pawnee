# include <sys/types.h>
# include <sys/socket.h>
# include <errno.h>
# include <stdio.h>
#include <arpa/inet.h>


int set_reuse_option(int socket)
{
  int optval = 1;
  return setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, & optval, sizeof(int) );
}

int bind_socket(int socket_serveur, int port)
{
  struct sockaddr_in saddr ;
  saddr.sin_family = AF_INET ; /* Socket ipv4 */
  saddr.sin_port = htons(port); /* Port d ’écoute */
  saddr.sin_addr.s_addr = INADDR_ANY ; /* écoute sur toutes les interfaces */

  return bind(socket_serveur, (struct sockaddr *)& saddr, sizeof(saddr));
}

int creer_serveur(int port) {
  int socket_serveur;
  if ( (socket_serveur = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket_serveur");
    return -1;
  }

  if (set_reuse_option(socket_serveur) == -1)
  {
    perror("Cannot set SO_REUSEADDR option");
    return -1;
  }

  if (bind_socket(socket_serveur, port) == -1)
  {
    perror("Cannot bind socket_serveur");
    return -1;
  }

  if ( listen(socket_serveur, 10) == -1)
  {
    perror("socket_serveur cannot listen");
    return -1;
  }
  return socket_serveur;
}
