# include <errno.h>
#include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <signal.h>
# include <regex.h>


const char* WELCOME_MESSAGE =
"          _____                    _____                    _____                    _____                    _____          \n"
"         /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\         \n"
"        /::\\____\\                /::\\____\\                /::\\    \\                /::\\____\\                /::\\____\\       \n"
"       /:::/    /               /:::/    /               /::::\\    \\              /:::/    /               /:::/    /        \n"
"      /:::/    /               /:::/    /               /::::::\\    \\            /:::/    /               /:::/    /         \n"
"     /:::/    /               /:::/    /               /:::/\\:::\\    \\          /:::/    /               /:::/    /          \n"
"    /:::/____/               /:::/    /               /:::/__\\:::\\    \\        /:::/    /               /:::/____/         \n"
"   /::::\\    \\              /:::/    /               /::::\\   \\:::\\    \\      /:::/    /               /::::\\    \\           \n"
"  /::::::\\____\\________    /:::/    /      _____    /::::::\\   \\:::\\    \\    /:::/    /      _____    /::::::\\____\\________  \n"
" /:::/\\:::::::::::\\    \\  /:::/____/      /\\    \\  /:::/\\:::\\   \\:::\\____\\  /:::/____/      /\\    \\  /:::/\\:::::::::::\\    \\ \n"
"/:::/  |:::::::::::\\____\\|:::|    /      /::\\____\\/:::/  \\:::\\   \\:::|    ||:::|    /      /::\\____\\/:::/  |:::::::::::\\____\\\n"
"\\::/   |::|~~~|~~~~~     |:::|____\\     /:::/    /\\::/   |::::\\  /:::|____||:::|____\\     /:::/    /\\::/   |::|~~~|~~~~~     \n"
" \\/____|::|   |           \\:::\\    \\   /:::/    /  \\/____|:::::\\/:::/    /  \\:::\\    \\   /:::/    /  \\/____|::|   |          \n"
"       |::|   |            \\:::\\    \\ /:::/    /         |:::::::::/    /    \\:::\\    \\ /:::/    /         |::|   |          \n"
"       |::|   |             \\:::\\    /:::/    /          |::|\\::::/    /      \\:::\\    /:::/    /          |::|   |          \n"
"       |::|   |              \\:::\\__/:::/    /           |::| \\::/____/        \\:::\\__/:::/    /           |::|   |        \n"
"       |::|   |               \\::::::::/    /            |::|  ~|               \\::::::::/    /            |::|   |          \n"
"       |::|   |                \\::::::/    /             |::|   |                \\::::::/    /             |::|   |          \n"
"       \\::|   |                 \\::::/    /              \\::|   |                 \\::::/    /              \\::|   |          \n"
"        \\:|   |                  \\::/____/                \\:|   |                  \\::/____/                \\:|   |          \n"
"         \\|___|                   ~~                       \\|___|                   ~~                       \\|___|          \n"
"\n\n"
"German: Hallo! Willkommen Kuruk Server von Nicolas de Moraes und Christopher Caroni erstellt.\n"
"English: Hello! Welcome to the Kuruk server created by Nicolas De Moraës and Christopher Caroni.\n"
"Spanish: ¡Hola! servidor Kuruk Bienvenido creado por Nicolás de Moraes y Christopher Caroni.\n"
"French: Bonjour! Bienvenue sur le serveur Kuruk créé par Nicolas De Moraës et Christopher Caroni.\n"
"Hindi: नमस्कार! आपका स्वागत है Kuruk सर्वर निकोलस डे मोरेस और क्रिस्टोफर Caroni द्वारा बनाई गई।\n"
"Italian: Buongiorno! server di benvenuto Kuruk creato da Nicolas de Moraes e Christopher Caroni.\n"
"Japanese: こんにちは！ニコラス・デ・モラエスとクリストファー・カロニによって作成されたウェルカムKurukサーバー\n"
"Norwegian: Hello! Velkommen Kuruk server opprettet av Nicolas de Moraes og Christopher Caroni.\n"
"Polish: Cześć! Witamy serwer Kuruk stworzony przez Nicolasa de Moraes i Christopher Caroni.\n"
"Portuguese: Olá! servidor Kuruk Bem-vindo criado por Nicolas de Moraes e Christopher Caroni.\n";

int display_welcome_message(int socket_client) {
  if (write(socket_client, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE)) == -1) {
    perror("Cannot write welcome message");
    return -1;
  }
  return 0;
}

int read_and_write(FILE* fp) {
  char input[1024];
  if ( fgets(input, 1024, fp) == NULL) {
    perror("fgets");
    return -1;
  }

  int status;
  if ( (status = fprintf(fp, "<Kuruk> : %s", input)) < 0)
  {
    perror("fprintf");
    return -1;
  }
  return 1;
}

/*
* read un message jusqua 1024 de longueur et réécrit ce message
* Lance perror en cas d'erreur. Stocke dans connected la valeur de
* read ou write, lequel a été fait en dernier avant l'erreur.
*/
int repeat_messages(int socket_client) {
  int status = 1;
  FILE * fp = fdopen(socket_client, "w+");
  if (fp == NULL) {
    perror("fdopen");
    return -1;
  }
  while (status > 0)
  {
    status = read_and_write(fp);
  }
  fclose(fp);
  return 0;
}

int treatHTTP(int socket_client) {
  FILE * fp = fdopen(socket_client, "w+");
  char input[1024];
  if ( fgets(input, 1024, fp) == NULL) {
    perror("fgets");
    return -1;
  }

  regex_t regex;
  int reti;

  reti = regcomp(&regex, "GET\\s\\/\\sHTTP\\/[1].[0-1]", 0);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return -1;
  }

  reti = regexec(&regex, input, 0, NULL, 0);
  if (!reti) {
    printf("matched\n");
  }
  else if (reti == REG_NOMATCH) {
    printf("did not match\n");
  }
  return 0;
}
