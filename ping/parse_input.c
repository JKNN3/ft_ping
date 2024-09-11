# include "includes/ping.h"

static bool regex_get_and_set_boolean_value(bool *opt, char *option);
static bool regex_get_and_set_option_and_value(t_option *opt, char *option_value);
static bool regex_get_and_set_option_value(t_option *opt,  t_conf *conf, char *option, char *value);


bool regexParseInput(int argc, char ** argv, t_option *opt, t_conf *conf)
{
    for(int i = 0 ; argv[i]; i++){

        int ret = regex_check_option(argv[i]);

        switch (ret)
        {
        case BOOLEEN:
            regex_get_and_set_boolean_value((bool*)opt, argv[i]);
            break;
        case OPTION_WITH_VALUE:
            regex_get_and_set_option_and_value(opt, argv[i]);
            break;
        case OPTION_WITHOUT_VALUE:
            if (!argv[i + 1])
                return puterr(ERROR_OPTION_REQUIRE_ARG(argv[i]));
            regex_get_and_set_option_value(opt, conf, argv[i], argv[++i]);
            break;
        case DEST:
            regex_get_ip_adress(argv[i], conf);
            break;
        case ERROR:
            return puterr(ERROR_INVALID_OPTION(argv[i]));
        }
    }
    return TRUE;
}

static bool regex_get_and_set_option_and_value(t_option *opt, char *option_value){
    regex_t reg;
    regmatch_t groupArray[MAXGROUP + 1];

    memset(groupArray, 0, sizeof(groupArray));

    if (regcomp(&reg, regex, REG_EXTENDED) != 0){
        perror("A problem occured compiling regex ");
        return FALSE;
    }
    int res = regexec(&reg, option_value, MAXGROUP, groupArray, 0);
    if (res == 0)
    {

    }
    regfree(&reg);
    return 0;
}

static bool regex_get_and_set_option_value(t_option *opt, t_conf *conf, char *option, char *value){
    int index_opt;

    for (index_opt = 0; index_opt < 4; index_opt++){
        if (regexCheckFormat(index_opt, regex_tab_fullname_option[index_opt]));
            break;
    }

    switch (index_opt)
    {
    case COUNT:
        if (!regexCheckFormat(value, regex_tab_bool_short_option_value[COUNT]))
            return puterr(ERROR_INVALID_VALUE(value));
        conf->nb_packets_to_send = strtoull(value, NULL, 10);
        opt->count = TRUE;
        break;
    case INTERVAL:
        if (!regexCheckFormat(value, regex_tab_bool_short_option_value[INTERVAL]))
            return puterr(ERROR_INVALID_VALUE(value));
        conf->interval_time = strtold(value, NULL);
        break;
    case TIMEOUT:
        if (!regexCheckFormat(value, regex_tab_bool_short_option_value[TIMEOUT]))
            return puterr(ERROR_INVALID_VALUE(value));
        conf->interval_time = strtold(value, NULL);
        break;
    case TTL:
        if (!regexCheckFormat(value, regex_tab_bool_short_option_value[TTL]))
            return puterr(ERROR_INVALID_VALUE(value));
        conf->ttl = atoi(value);
        if (conf->ttl > 255)
            return puterr(ERROR_TTL_TOO_BIG(conf->ttl));
        break;
    }
    return TRUE;
}

static bool regex_get_and_set_boolean_value(bool *opt, char *option){
    for( int i = 0; i < NB_OF_BOOLEAN_OPTIONS; i++){
        if (regexCheckFormat(option, regex_tab_bool_short_option[i])){
                opt[i] = true;
            return TRUE;
        }
    }
    return FALSE;
}

static bool regex_get_ip_adress(char *dest , t_conf *conf){
    return TRUE;
}

int regex_check_option(char* arg){
    if (regexCheckFormat(arg, REGEX_CHECK_ARG_OPTION_TYPE_BOOLEEN))
        return BOOLEEN;
    else if (regexCheckFormat(arg, REGEX_CHECK_ARG_OPTION_TYPE_FULLNAME))
        return OPTION_WITH_VALUE;
    else if (regexCheckFormat(arg, REGEX_CHECK_ARG_OPTION_TYPE_SHORTNAME))
        return OPTION_WITHOUT_VALUE;
    else if (regexCheckFormat(arg, REGEX_CHECK_ARG_DEST))
        return DEST;
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
        return TRUE;
    return FALSE;
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