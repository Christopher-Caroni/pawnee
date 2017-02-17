# include <stdio.h>
# include <string.h>
# include <regex.h>

// Returns 0 for an empty line match, else -1
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
