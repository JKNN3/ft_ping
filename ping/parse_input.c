# include "includes/ping.h"

static bool regex_get_and_set_boolean_value(bool *opt, char *option);
static bool regex_get_and_set_opt_and_value(t_opt *opt, t_conf *conf, char *option_value);
static bool regex_get_and_set_opt_value(t_opt *opt,  t_conf *conf, char *option, char *value);
static int  regex_check_option(char* arg);
static void set_value(t_opt *opt, t_conf *conf, int index_opt,  char*value);

bool regexParseInput(char ** argv, t_opt *opt, t_conf *conf)
{
    for(int i = 0 ; argv[i]; i++){

        int ret = regex_check_option(argv[i]);

        switch (ret)
        {
        case BOOLEEN:
            regex_get_and_set_boolean_value((bool*)opt, argv[i]);
            printf("boolean");
            break;
        case OPTION_WITH_VALUE:
            regex_get_and_set_opt_and_value(opt, conf, argv[i]);
            printf("option with value");
            break;
        case OPTION_WITHOUT_VALUE:
            if (!argv[i + 1])
                return puterr(ERROR_OPTION_REQUIRE_ARG(argv[i]));
            regex_get_and_set_opt_value(opt, conf, argv[i], argv[++i]);
            printf("option without value");
            break;
        case DEST:
            conf->dest_name_or_ip = argv[i];
            printf("ip");
            break;
        case ERROR:
            return puterr(ERROR_INVALID_OPTION(argv[i]));
        }
    }
    return TRUE;
}


static int regex_check_option(char* arg){
    if (regex_check_format(arg, REGEX_CHECK_ARG_TYPE_BOOLEEN_OPTION))
        return BOOLEEN;
    else if (regex_check_format(arg, REGEX_CHECK_ARG_TYPE_OPTION_AND_VALUE))
        return OPTION_WITH_VALUE;
    else if (regex_check_format(arg, REGEX_CHECK_ARG_TYPE_OPTION))
        return OPTION_WITHOUT_VALUE;
    else if (regex_check_format(arg, REGEX_CHECK_ARG_DEST))
        return DEST;
    return (-1); // handle error
}


static void set_value(t_opt *opt, t_conf *conf, int index_opt,  char*value){
    char *regex_tab_option_value[] = REGEX_LIST_OPTION_VALUE;

        switch (index_opt)
    {
    case COUNT:
        if (regex_check_format(value, regex_tab_option_value[COUNT])){
            conf->nb_packets_to_send = strtoull(value, NULL, 10);
            opt->count = TRUE;
        }
        break;
    case INTERVAL:
        if (!regex_check_format(value, regex_tab_option_value[INTERVAL])){
            ERROR_INVALID_VALUE(value); return;
        }
        conf->interval_time = strtold(value, NULL);
        break;
    case TIMEOUT:
        if (!regex_check_format(value, regex_tab_option_value[TIMEOUT])){
            ERROR_INVALID_VALUE(value); return;
        }
        conf->interval_time = strtold(value, NULL);
        break;
    case TTL:
        if (!regex_check_format(value, regex_tab_option_value[TTL])){
            ERROR_INVALID_VALUE(value); return;
        }
        conf->ttl = atoi(value);
        if (conf->ttl > 255){
            ERROR_TTL_TOO_BIG(conf->ttl); return;
        }
        break;
    }
}

static bool regex_get_and_set_opt_value(t_opt *opt, t_conf *conf, char *option, char *value){
    int index_opt;
    char *regex_tab_option_without_value[] = REGEX_LIST_OPTION;

    for (index_opt = 0; index_opt < 4; index_opt++){
        if (regex_check_format(option, regex_tab_option_without_value[index_opt]))
            break;
    }
    set_value(opt, conf, index_opt, value);

    return TRUE;
}

static bool regex_get_and_set_boolean_value(bool *opt, char *option){
    char *regex_tab_bool_option[] = REGEX_LIST_BOOL_OPTION;

    for( int i = 0; i < NB_OF_BOOLEAN_OPTIONS; i++){
        if (regex_check_format(option, regex_tab_bool_option[i])){
            opt[i] = true;
            printf("boolean number %d\n", i);
            return TRUE;
        }
    }
    return FALSE;
}

static bool regex_get_and_set_opt_and_value(t_opt *opt, t_conf *conf, char *option_value){
    regex_t reg;
    regmatch_t groupArray[MAXGROUP + 1];

    char *regex_tab_fullname_option[] = REGEX_LIST_FULLNAME_OPTION;
    char *regex_tab_option_without_value[] = REGEX_LIST_OPTION;
    char *regex_tab_option_value[] = REGEX_LIST_OPTION_VALUE;

    for(int i = 0; i < 4; i++){

        memset(groupArray, 0, sizeof(groupArray));
        if (regcomp(&reg, regex_tab_fullname_option[i], REG_EXTENDED) != 0)
            return FALSE;
        int res = regexec(&reg, option_value, MAXGROUP, groupArray, 0);
        if (res == 0)
        {
            if  (groupArray[0].rm_so == -1 || groupArray[0].rm_so == groupArray[0].rm_eo || \
                groupArray[1].rm_so == -1 || groupArray[1].rm_so == groupArray[1].rm_eo){
                regfree(&reg);
                return FALSE;
            }
            for(int option = 0; option < 4; option++){
                if (regex_check_format(groupArray[0].rm_so, regex_tab_option_without_value[option])){
                    if (!regex_check_format(groupArray[1].rm_so, regex_tab_option_value[option])){
                        regfree(&reg);
                        return puterr(ERROR_INVALID_VALUE(groupArray[1].rm_so));
                    }
                    int length = matches[1].rm_eo - matches[1].rm_so;
            char captured[length + 1];  // +1 pour le caractère nul
            strncpy(captured, input + matches[1].rm_so, length);
            captured[length] = '\0';
                    set_value(opt, conf, option, (char *)groupArray[1].rm_so);
                    break;
                }
            }
        }   
    }
    regfree(&reg);
    return TRUE;
}


bool regex_check_format(const char *testedStr, const char *regex)
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
