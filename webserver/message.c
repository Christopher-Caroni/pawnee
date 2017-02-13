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

const char* MESSAGE_404 =
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
"EEEEEEEEEEEEEEEEEEEEEE                                                                                         444444444       000000000            444444444\n"
"E::::::::::::::::::::E                                                                                        4::::::::4     00:::::::::00         4::::::::4  \n"
"E::::::::::::::::::::E                                                                                       4:::::::::4   00:::::::::::::00      4:::::::::4  \n"
"EE::::::EEEEEEEEE::::E                                                                                      4::::44::::4  0:::::::000:::::::0    4::::44::::4  \n"
"  E:::::E       EEEEEErrrrr   rrrrrrrrr   rrrrr   rrrrrrrrr      ooooooooooo   rrrrr   rrrrrrrrr           4::::4 4::::4  0::::::0   0::::::0   4::::4 4::::4  \n"
"  E:::::E             r::::rrr:::::::::r  r::::rrr:::::::::r   oo:::::::::::oo r::::rrr:::::::::r         4::::4  4::::4  0:::::0     0:::::0  4::::4  4::::4  \n"
"  E::::::EEEEEEEEEE   r:::::::::::::::::r r:::::::::::::::::r o:::::::::::::::or:::::::::::::::::r       4::::4   4::::4  0:::::0     0:::::0 4::::4   4::::4  \n"
"  E:::::::::::::::E   rr::::::rrrrr::::::rrr::::::rrrrr::::::ro:::::ooooo:::::orr::::::rrrrr::::::r     4::::444444::::4440:::::0 000 0:::::04::::444444::::444\n"
"  E:::::::::::::::E    r:::::r     r:::::r r:::::r     r:::::ro::::o     o::::o r:::::r     r:::::r     4::::::::::::::::40:::::0 000 0:::::04::::::::::::::::4\n"
"  E::::::EEEEEEEEEE    r:::::r     rrrrrrr r:::::r     rrrrrrro::::o     o::::o r:::::r     rrrrrrr     4444444444:::::4440:::::0     0:::::04444444444:::::444\n"
"  E:::::E              r:::::r             r:::::r            o::::o     o::::o r:::::r                           4::::4  0:::::0     0:::::0          4::::4  \n"
"  E:::::E       EEEEEE r:::::r             r:::::r            o::::o     o::::o r:::::r                           4::::4  0::::::0   0::::::0          4::::4  \n"
"EE::::::EEEEEEEE:::::E r:::::r             r:::::r            o:::::ooooo:::::o r:::::r                           4::::4  0:::::::000:::::::0          4::::4  \n"
"E::::::::::::::::::::E r:::::r             r:::::r            o:::::::::::::::o r:::::r                         44::::::44 00:::::::::::::00         44::::::44\n"
"E::::::::::::::::::::E r:::::r             r:::::r             oo:::::::::::oo  r:::::r                         4::::::::4   00:::::::::00           4::::::::4\n"
"EEEEEEEEEEEEEEEEEEEEEE rrrrrrr             rrrrrrr               ooooooooooo    rrrrrrr                         4444444444     000000000             4444444444\n"
"\n\n"
"German: Seite nicht gefunden!\n"
"English: Page not found!\n"
"Spanish: ¡Página no encontrada!\n"
"French: Page non trouvée!\n"
"Hindi: पृष्ठ नहीं मिला!\n"
"Italian: Pagina non trovata!\n"
"Japanese: ページが見つかりません！\n"
"Norwegian: Side ikke funnet!\n"
"Polish: Strona nie znaleziona!\n"
"Portuguese: Página não encontrada!\n";

int display_welcome_message(FILE * fp) {
  char* response = "HTTP/1.1 200 OK\n"
  "Connection: close\n"
  "Content-Length: 3788\n"
  "\n";
  if (fprintf(fp, "%s%s", response, WELCOME_MESSAGE) < 0)
  {
    perror("fprintf");
    return -1;
  }
  return 0;
}

int display_404(FILE *fp) {
  char* response = "HTTP/1.1 404 Not Found\n"
  "Connection: close\n"
  "Content-Length: 5542\n"
  "\n";
  if (fprintf(fp, "%s%s", response, MESSAGE_404) < 0)
  {
    perror("fprintf");
    return -1;
  }
  return 0;
}

int respond(FILE * fp, char *ressource) {
  char *base = "/";
  printf("result comparison = %d\n", strcmp(ressource, base));
  if (strcmp(ressource, base) == 0) {
    display_welcome_message(fp);
    return 0;
  } else {
    display_404(fp);
    return 0;
  }
  return -1;
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

int match_get_request(char *str_request, char* ressource) {
  int match_result;
  int compile_result;
  regex_t compiled_regex;
  regmatch_t pmatch[4]; // We have 3 capturing groups + the whole match_result group
  size_t nb_matches = 4; // Same as above

  const char *str_regex = "(GET) (/.*)+ (HTTP/1[.][0-1])\r\n";
  compile_result = regcomp(&compiled_regex, str_regex, REG_EXTENDED);
  if (compile_result == 0)
  {
    match_result = regexec(&compiled_regex, str_request, nb_matches, pmatch, 0);
    nb_matches = compiled_regex.re_nsub;
    regfree(&compiled_regex);
    if (match_result == 0)
    {
      printf("matched HTTP GET request\n");
      // pmatch[x].rm_so = offset
      // pmatch[x].rm_eo = end offset
      // printf(.*) -> specify length of string to print instead of whole string

      int startRessource = (int) (pmatch[2].rm_so);
      int lengthRessource = (int) ( (pmatch[2].rm_eo) - (pmatch[2].rm_so) );
      strncpy(ressource, str_request + startRessource, lengthRessource);

      printf("request protocol : \"%.*s\"\n", (int) (pmatch[1].rm_eo - pmatch[1].rm_so), &str_request[pmatch[1].rm_so]);
      printf("requested ressource : \"%.*s\"\n", (int) (pmatch[2].rm_eo - pmatch[2].rm_so), &str_request[pmatch[2].rm_so]);
      printf("http version : \"%.*s\"\n", (int) (pmatch[3].rm_eo - pmatch[3].rm_so), &str_request[pmatch[3].rm_so]);
      return 0;
    } else if (match_result == REG_NOMATCH)
    {
      printf("Did not match HTTP GET request\n");
      return -1;
    }
  }
  return -1;
}

int match_empty_line(char* str_request) {
  int match_result;
  int compile_result;
  regex_t compiled_regex;

  const char *str_regex = "^(\n|\r\n)";
  compile_result = regcomp(&compiled_regex, str_regex, REG_EXTENDED);
  if (compile_result == 0)
  {
    match_result = regexec(&compiled_regex, str_request, 0, NULL, 0);
    regfree(&compiled_regex);
    if (match_result == 0)
    {
      printf("matched empty line\n");
      return 0;
    } else if (match_result == REG_NOMATCH)
    {
      return -1;
    }
  }
  return -1;
}

int send_bad_request(FILE *fp) {
  char* bad_request_message = "HTTP/1.1 400 Bad Request\n"
  "Connection: close\n"
  "Content-Length: 17\n"
  "\n"
  "400 Bad request\n";
  if (fprintf(fp, "%s", bad_request_message) < 0)
  {
    perror("fprintf");
    return -1;
  }
  return 0;
}


int treatHTTP(int socket_client) {
  FILE * fp = fdopen(socket_client, "w+");
  char input[1024];
  int lineCount = 0;
  char ressource[1024] = "";

  while (fgets(input, 1024, fp) != NULL)
  {
    printf("message received : \"%s\"\n", input);
    if (lineCount == 0) {
      if (match_get_request(input, ressource) == -1) {
        send_bad_request(fp);
        return -1;
      }
    } else if (lineCount > 0) {
      if (match_empty_line(input) == 0)
      {
        respond(fp, ressource);
        return 0;
      }
    }
    lineCount++;
  }
  return -1;
}
