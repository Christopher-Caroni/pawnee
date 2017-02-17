# include <stdio.h>
# include <string.h>
# include <regex.h>

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
