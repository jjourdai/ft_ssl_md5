#include "ssl.h"

static char error[][256] = {
  [REQUIRE_ARGUMENT] = "%s: option requires an argument -- %s\n",
  [INVALID_OPTIONS] = "%s: invalid option -- %s\n",
  [INVALID_COMMAND] = "ft_ssl: '%s' is an invalid command.\n",
  [USAGE] = "usage: ft_ssl command [-pqrs] [command args]\n\n"
    "Standard commands:\n\nMessage Digest commands:\nmd5\nsha256\n"
    "\nCipher commands:\nbase64\ndes\ndes-ebc\ndes-cbc",
  [WRONG_LENGTH] = "ft_ssl %s: wrong final block length\n",
  [INVALID_KEY] = "ft_ssl des: non-hex digit\ninvalid hex key value",
};

static char command[][8] = {
  [BASE64] = "base64",
  [MD5] = "md5",
  [SHA256] = "sha256",
  [DES] = "des",
  [DES_ECB] = "des-ecb",
  [DES_CBC] = "des-cbc",
};

void raise_error(int cmd, int value, char *str, int flag)
{
  if (cmd == GENERAL)
    ft_fprintf(STDERR_FILENO, error[value], str);
  else
  {
    if (str)
      ft_fprintf(STDERR_FILENO, error[value], command[cmd], str);
    else
      ft_fprintf(STDERR_FILENO, error[value], command[cmd]);
  }
  if (flag == EXIT)
    exit(EXIT_FAILURE);
}
