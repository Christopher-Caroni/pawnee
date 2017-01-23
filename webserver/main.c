# include <stdio.h>
# include <string.h>
# include <errno.h>
#include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include "socket.h"

int main (void)
{
  while (1)
  {
    int socket_serveur = creer_serveur(8080);
    int socket_client = accept(socket_serveur, NULL, NULL);
    if ( socket_client == -1)
    {
      perror("accept");
    }
    char* message = "German: Hallo! Willkommen Kuruk Server von Nicolas de Moraes und Christopher Caroni erstellt.\n"
    "English: Hello! Welcome to the Kuruk server created by Nicolas De Moraës and Christopher Caroni.\n"
    "Spanish: ¡Hola! servidor Kuruk Bienvenido creado por Nicolás de Moraes y Christopher Caroni.\n"
    "French: Bonjour! Bienvenue sur le serveur Kuruk créé par Nicolas De Moraës et Christopher Caroni.\n"
    "Hindi: नमस्कार! आपका स्वागत है Kuruk सर्वर निकोलस डे मोरेस और क्रिस्टोफर Caroni द्वारा बनाई गई।\n"
    "Italian: Buongiorno! server di benvenuto Kuruk creato da Nicolas de Moraes e Christopher Caroni.\n"
    "Japanese: こんにちは！ニコラス・デ・モラエスとクリストファー・カロニによって作成されたウェルカムKurukサーバー\n"
    "Norwegian: Hello! Velkommen Kuruk server opprettet av Nicolas de Moraes og Christopher Caroni.\n"
    "Polish: Cześć! Witamy serwer Kuruk stworzony przez Nicolasa de Moraes i Christopher Caroni.\n"
    "Portuguese: Olá! servidor Kuruk Bem-vindo criado por Nicolas de Moraes e Christopher Caroni.\n";
    if (write(socket_client, message, strlen(message)) == -1) {
      perror("write message");
      return -1;
    }

    int connected = 1;
    while (connected)
    {
      char readMessage[1024];
      connected = read(socket_client, &readMessage, 1024);
      write(socket_client, &readMessage, connected);
    }
    /* Une fois qu'on lit rien, on ferme les sockets */
    close(socket_client);
    close(socket_serveur);
  }
  return 0;
}
