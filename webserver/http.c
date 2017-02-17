# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

# include "regmatch.h"
# include "input.h"
# include "message.h"
# include "http.h"


void send_status(FILE *client, int code, const char *reason_phrase)
{
  fprintf(client, "HTTP/1.1 %d:%s\n", code, reason_phrase);
  return;
}

void send_response(FILE *client, int code, const char *reason_phrase, const char *message_body)
{
  send_status(client, code, reason_phrase);
  fprintf(client, "Connection: close\n");
  int length = strlen(message_body);
  fprintf(client, "Content-Length: %d\n\n", length);
  fprintf(client, "%s\n", message_body);
  return;
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
  FILE *client = fdopen(socket_client, "w+");
  char input[1024];
  http_request request = {HTTP_UNSUPPORTED, 0, 0, ""};
  int bad_request = 0;

  fgets_or_exit(input, 1024, client);
  bad_request = parse_http_request(input, &request);

  skip_headers(client);

  if(request.method == HTTP_UNSUPPORTED)
    send_response(client, 405, "Method Not Allowed", "Method Not Allowed \r\n");
  else if (bad_request == 0)
    send_response(client, 400, "Bad Request" , "Bad request\r\n");
  else if (strcmp(request. target, "/") == 0)
    send_response(client, 200, "OK", WELCOME_MESSAGE);
  else
    send_response(client, 404, "Not Found", MESSAGE_404);
  return 0;
}
