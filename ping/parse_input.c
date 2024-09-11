# include "includes/ping.h"

bool regexParseInput(int argc, char ** argv, t_option *opt)
{
    for(int i = 0 ; argv[i]; i++){

        int ret = regex_check_option(argv[i]);
        if (ret == ERROR)
            return;
        
        
    }
}

char *regexGetOption(char *arg, char *regex, int maxGroup){
    regex_t reg;
    regmatch_t groupArray[maxGroup + 1];

    memset(groupArray, 0, sizeof(groupArray));

    if (regcomp(&reg, regex, REG_EXTENDED) != 0){
        perror("A problem occured compiling regex ");
        return FALSE;
    }
    int res = regexec(&reg, arg, maxGroup, groupArray, 0);

    if (res == 0)
    {

    }
    regfree(&reg);
}

int regex_get_and_set_boolean_value(bool *opt, char *arg){
    int (*pf)[3]();
    for( int i = 0; i < NB_OF_BOOLEAN_OPTIONS; i++){
        if (regexCheckFormat(arg, regex_check_bool_option[i])){
                opt[i] = true;
            return true;
        }
    }
    return false;
}
// 

int regex_check_option(char* arg){
    if (regexCheckFormat(arg, REGEX_CHECK_OPTION_TYPE_BOOLEEN))
        return BOOLEEN;
    else if (regexCheckFormat(arg, REGEX_CHECK_OPTION_TYPE_OPT_WITH_VALUE))
        return OPTION_WITH_VALUE;
    else if (regexCheckFormat(arg, REGEX_CHECK_OPTION_TYPE_OPT_WITHOUT_VALUE))
        return OPTION_WITHOUT_VALUE;
    return (-1); // handle error
}

bool regexCheckFormat(const char *testedStr, const char *regex)
{
    regex_t reg;

    if (regcomp(&reg, regex, REG_EXTENDED) != 0){
        perror("A problem occured compiling regex ");
        return FALSE;
    }
    int res = regexec(&reg, testedStr, (size_t) 0, NULL, 0);
    regfree(&reg);
    if (res == 0)
        return (1);
    return (0);
}