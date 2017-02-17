# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

# include "regmatch.h"
# include "input.h"
# include "message.h"
# include "http.h"


// Répond sur le fp soit avec le message de Bienvenue soit avec une erreur 404
int respond(FILE *fp, char *ressource) {
  char *base = "/";
  printf("compare to base: %d\n", strcmp(ressource, base));
  if (strcmp(ressource, base) == 0) {
    write_welcome_message(fp);
    return 0;
  } else {
    write_404_message(fp);
    return 0;
  }
  return -1;
}

// LEGACY
// Lit jusqu'à 1024 chars sur une ligne et puis les réécris avec "<Kuruk> : " devant
int read_and_write(FILE *fp) {
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

// Returns 0 if invalid request, 1 if correct
int parse_http_request(const char *request_line, http_request *request) {
  char *token = "";
  char *request_line_for_token = strdup(request_line);
  int tokenIndex = 0;
  int correct = 1;

  token = strtok(request_line_for_token, " ");

  while (token && correct) {
    if (tokenIndex == 0) {
      if (strcmp(token, "GET") == 0) {
        request->method = HTTP_GET;
      } else {
        request->method = HTTP_UNSUPPORTED;
        correct = 0;
      }
    } else if (tokenIndex == 1) {
      request->target = strdup(token);
    } else if (tokenIndex == 2) {
      if ((strcmp(token, "HTTP/1.0\r\n") == 0) || (strcmp(token, "HTTP/1.0\n") == 0) ) {
        request->major_version = 1;
        request->minor_version= 0;
      } else if ((strcmp(token, "HTTP/1.1\r\n") == 0) || (strcmp(token, "HTTP/1.1\n") == 0) ) {
        request->major_version = 1;
        request->minor_version= 1;
      } else {
        correct = 0;
      }
    }
    tokenIndex++;
    token = strtok(NULL, " "); // continues the orignal call to strtok on the same char*
  }
  printf("method : %d\n", request->method);
  printf("ressource: \"%s\"\n", request->target);
  printf("HTTP version: %d/%d\n", request->major_version, request->minor_version);
  return correct;
}

void skip_headers(FILE *client)
{

  char input[1024];
  while (fgets_or_exit(input, 1024, client))
  {
    if (match_empty_line(input) == 0)
    {
      return;
    }
  }
}

int treatHTTP(int socket_client) {
  FILE * fp = fdopen(socket_client, "w+");
  char input[1024];
  http_request request = {HTTP_UNSUPPORTED, 0, 0, ""};

  fgets_or_exit(input, 1024, fp);
  if (parse_http_request(input, &request) == 0) {
    printf("bad req, terminating connection\n");
    send_bad_request(fp);
    return -1;
  }

  skip_headers(fp);
  return respond(fp, request.target);
}
