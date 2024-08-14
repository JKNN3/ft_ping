#include "ping.h"

bool regexCheckFormat(const char *testedStr, const char *regex)
{
    regex_t reg;

    if (regcomp(&reg, regex, REG_EXTENDED) != 0)
    {
        std::cout << "A problem occured compiling regex.\n";
        return (0);
    }
    int res = regexec(&reg, testedStr, (size_t) 0, NULL, 0);
    regfree(&reg);
    if (res == 0)
        return (1);
    return (0);
}