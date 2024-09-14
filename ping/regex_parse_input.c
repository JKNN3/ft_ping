# include "includes/ping.h"

static int  regex_check_option(char* arg);
static bool regex_get_and_set_boolean_value(bool *opt, char *option);
static bool regex_get_and_set_opt_and_value(t_opt *opt, t_conf *conf, char *option_value);
static bool regex_get_and_set_value(t_opt *opt,  t_conf *conf, char *option, char *value);
static bool regex_check_format(const char *testedStr, const char *regex);
static void set_value(t_opt *opt, t_conf *conf, int index_opt,  char*value);

bool regex_parse_input(char ** argv, t_opt *opt, t_conf *conf)
{
    for(int i = 1 ; argv[i]; i++){

        int ret = regex_check_option(argv[i]);
        // printf("ret regex_check_option is : %d\n", ret);
        switch (ret)
        {
        case BOOLEEN:
            regex_get_and_set_boolean_value((bool*)opt, argv[i]);
            break;
        case OPTION_WITH_VALUE:
            regex_get_and_set_opt_and_value(opt, conf, argv[i]);
            break;
        case OPTION_WITHOUT_VALUE:
            if (!argv[i + 1])
                return puterr(ERROR_OPTION_REQUIRE_ARG(argv[i]));
            regex_get_and_set_value(opt, conf, argv[i], argv[++i]);
            break;
        case DEST:
            resolve_dest_address(argv[i], conf);
            break;
        case ERROR:
            return puterr(ERROR_INVALID_OPTION(argv[i]));
        }
    }
    return TRUE;
}

/*      check the arg format : boolean option, option and value, option=value   */
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

/*      check and set bool true for '-a' '--flood' options   */
static bool regex_get_and_set_boolean_value(bool *opt, char *option){

    const char *regex_tab_bool_option[] = REGEX_LIST_BOOL_OPTION;

    for( int i = 0; i < NB_OF_BOOLEAN_OPTIONS; i++){
        if (regex_check_format(option, regex_tab_bool_option[i])){
            opt[i] = true;
            return TRUE;
        }
    }
    return FALSE;
}

/*      check and get args from '-c 12' '--count 3' options   */
static bool regex_get_and_set_value(t_opt *opt, t_conf *conf, char *option, char *value){

    int index_opt;
    const char *regex_tab_option_without_value[] = REGEX_LIST_OPTION;

    for (index_opt = 0; index_opt < 4; index_opt++){
        if (regex_check_format(option, regex_tab_option_without_value[index_opt]))
            break;
    }
    set_value(opt, conf, index_opt, value);

    return TRUE;
}

/*      check and get args from '--ttl=8978' options   */
static bool regex_get_and_set_opt_and_value(t_opt *opt, t_conf *conf, char *option_value){

    regex_t reg;
    regmatch_t matches[MAXGROUP + 1];

    const char *regex_tab_fullname_option[4] = REGEX_LIST_FULLNAME_OPTION;

    for(int i = 0; i < 4; i++){

        memset(matches, 0, (3 * sizeof(regmatch_t)));
        if (regcomp(&reg, regex_tab_fullname_option[i], REG_EXTENDED) != 0)
            return FALSE;
            // printf("je passe ici nb %d, option value is %s\n", i, option_value);
        int res = regexec(&reg, option_value, MAXGROUP + 1, matches, 0);
        if (res == 0)
        {
            if  (matches[1].rm_so == -1 || matches[2].rm_so == -1){
                regfree(&reg);
                return FALSE;
            }

            int length = matches[1].rm_eo - matches[1].rm_so;
            char option[length + 1];
            strncpy(option, option_value + matches[1].rm_so, length);
            option[length] = '\0';
            // printf("option: %s\n", option);
            length = matches[2].rm_eo - matches[2].rm_so;
            char value[length + 1];
            strncpy(value, option_value + matches[2].rm_so, length);
            value[length] = '\0';
            // printf("value: %s\n", value);

            regex_get_and_set_value(opt, conf, option, value);
        }
        // else
            // printf("no match\n");
        regfree(&reg);
    }
    return TRUE;
}

/*      utils       */

static void set_value(t_opt *opt, t_conf *conf, int index_opt,  char*value){

    const char *regex_tab_option_value[] = REGEX_LIST_VALUE;

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
        conf->timeout = strtoul(value, NULL, 10);
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
/*      return true if the arg match with the regex, false otherwise    */
static bool regex_check_format(const char *testedStr, const char *regex)
{
    regex_t reg;

    if (regcomp(&reg, regex, REG_EXTENDED | REG_NOSUB) != 0)
        puterr_and_exit("An error occured compiling regex.\n", 1);
    int res = regexec(&reg, testedStr, (size_t) 0, NULL, 0);
    regfree(&reg);
    if (res == 0)
        return TRUE;
    return FALSE;
}
