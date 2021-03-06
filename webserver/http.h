enum http_method
{
  HTTP_GET,
  HTTP_UNSUPPORTED,
};

typedef struct
{
  enum http_method method;
  int major_version;
  int minor_version;
  char *target;
} http_request;

int treatHTTP(int socket_client);
