#include "ping.h"

static int  regex_check_option(char* arg);
static bool regex_get_and_set_boolean_value(bool *opt, char *option);
static bool regex_get_and_set_opt_and_value(t_opt *opt, t_conf *conf, char *option_value);
static bool regex_get_and_set_value(t_opt *opt,  t_conf *conf, char *option, char *value);
static bool regex_check_format(const char *testedStr, const char *regex);
static void set_value(t_opt *opt, t_conf *conf, int index_opt,  char*value);
static void check_timeout_value(unsigned long int value, t_opt *opt);
static void manage_options_queue(t_opt *opt, t_conf *conf, char **argv, int *index);
static void resolve_dest_address(char *addr, t_conf *conf);
static void set_dest_name_and_addr(t_conf *conf, char *addr, struct addrinfo *res);

bool regex_parse_input(char ** argv, t_opt *opt, t_conf *conf)
{
    for(int i = 1 ; argv[i]; i++){

        int ret = regex_check_option(argv[i]);
        switch (ret)
        {
        case BOOLEAN:
            regex_get_and_set_boolean_value((bool*)opt, argv[i]);
            break;
        case OPTION_WITH_VALUE:
            regex_get_and_set_opt_and_value(opt, conf, argv[i]);
            break;
        case OPTION_WITHOUT_VALUE:
            if (!argv[i + 1])
                puterr_and_exit(ERROR_OPTION_REQUIRE_ARG(argv[i]), 64);
            regex_get_and_set_value(opt, conf, argv[i], argv[i + 1]);
            i++;
            break;
        case OPTION_QUEUE:
            manage_options_queue(opt, conf, argv, &i);
            break;
        case DEST:
            resolve_dest_address(argv[i], conf);
            break;
        case ERROR:
            puterr_and_exit(ERROR_INVALID_OPTION(argv[i]), 64);
        }
    }
    return TRUE;
}

/*      check the arg format : boolean option, option and value, option=value, -optoptopt   */
static int regex_check_option(char* arg){

    if (regex_check_format(arg, REGEX_CHECK_ARG_TYPE_BOOLEAN_OPTION))
        return BOOLEAN;
    else if (regex_check_format(arg, REGEX_CHECK_ARG_TYPE_OPTION_AND_VALUE))
        return OPTION_WITH_VALUE;
    else if (regex_check_format(arg, REGEX_CHECK_ARG_TYPE_OPTION))
        return OPTION_WITHOUT_VALUE;
    else if (regex_check_format(arg, REGEX_CHECK_ARG_QUEUE))
        return OPTION_QUEUE;
    else if (regex_check_format(arg, REGEX_CHECK_OPTION))
        return ERROR;
    else if (regex_check_format(arg, REGEX_CHECK_ARG_DEST))
        return DEST;
    return (ERROR);
}

/*      check and set bool true for '-a' '--flood' options              */
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

/*      check and get args from '-c 12' '--count 3' options             */
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

/*      check and get args from '--ttl=8978' options                    */
static bool regex_get_and_set_opt_and_value(t_opt *opt, t_conf *conf, char *option_value){

    regex_t reg;
    regmatch_t matches[MAXGROUP + 1];

    const char *regex_tab_fullname_option[4] = REGEX_LIST_FULLNAME_OPTION;

    for(int i = 0; i < 4; i++){

        memset(matches, 0, (3 * sizeof(regmatch_t)));
        if (regcomp(&reg, regex_tab_fullname_option[i], REG_EXTENDED) != 0)
            return FALSE;
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
            length = matches[2].rm_eo - matches[2].rm_so;
            char value[length + 1];
            strncpy(value, option_value + matches[2].rm_so, length);
            value[length] = '\0';

            regex_get_and_set_value(opt, conf, option, value);
        }
        regfree(&reg);
    }
    return TRUE;
}

/*          sets the option value in the conf struct                    */
static void set_value(t_opt *opt, t_conf *conf, int index_opt, char*value){

    const char *regex_tab_option_value[] = REGEX_LIST_VALUE;
    switch (index_opt)
    {
        case COUNT:
            if (!regex_check_format(value, regex_tab_option_value[COUNT])){
                puterr_and_exit(ERROR_INVALID_VALUE(value), 1);
            }
            conf->nb_packets_to_send = strtoull(value, NULL, 10);
            opt->count = TRUE;
            break;
        case INTERVAL:
            if (!regex_check_format(value, regex_tab_option_value[INTERVAL])){
                puterr_and_exit(ERROR_INVALID_VALUE(value), 1);
            }
            conf->interval_time = strtold(value, NULL);
            opt->interval = TRUE;
            break;
        case TIMEOUT:
            if (!regex_check_format(value, regex_tab_option_value[TIMEOUT])){
                puterr_and_exit(ERROR_INVALID_VALUE(value), 1);
            }
            conf->timeout = strtoul(value, NULL, 10);
            check_timeout_value(conf->timeout, opt);
            break;
        case TTL:{
            if (!regex_check_format(value, regex_tab_option_value[TTL]))
                puterr_and_exit(ERROR_INVALID_VALUE(value), 1);
            
            conf->ttl = strtoul(value, NULL, 10);
            if (strlen(value) > 4 || conf->ttl > 255)
                puterr_and_exit(ERROR_TTL_TOO_BIG(value), 1);
            break;
        }
    }
}

/*      return true if the arg match with the regex, false otherwise    */
static bool regex_check_format(const char *testedStr, const char *regex){

    regex_t reg;

    if (regcomp(&reg, regex, REG_EXTENDED | REG_NOSUB) != 0)
        puterr_and_exit(ERROR_COMPILING_REGEX, 1);
    int res = regexec(&reg, testedStr, (size_t) 0, NULL, 0);
    regfree(&reg);
    if (res == 0)
        return TRUE;
    return FALSE;
}

/*      timeout option value must fit in an int                         */
static void check_timeout_value(unsigned long int value, t_opt *opt){

    if (value > 2147483647)
        puterr_and_exit(ERROR_TIMEOUT_VALUE_TOO_BIG(value), 1);
    if (value == 0)
        puterr_and_exit(ERROR_TIMEOUT_VALUE_TOO_SMALL(value), 1);
    opt->timeout = true;
}

/*      manage stuck together options like -qfc                        */
static void manage_options_queue(t_opt *opt, t_conf *conf, char **argv, int *index){

    for(int i = 1; argv[*index][i]; i++){
        char arg[2] = {argv[*index][i], '\0'};

        if (regex_get_and_set_boolean_value((bool*)opt, arg))
            continue;
        else if (!argv[*index + 1])
            return puterr_and_exit(ERROR_OPTION_REQUIRE_ARG(argv[*index]), 64);
        else if (argv[*index][i + 1])
            return puterr_and_exit(ERROR_INVALID_VALUE(&argv[*index][i + 1]), 1);
        else if (regex_get_and_set_value(opt, conf, arg, argv[++(*index)])){
            return;
        }
    }
}

static void resolve_dest_address(char *addr, t_conf *conf){

    if (conf->adress_resolved) return;

    struct addrinfo hints;
    struct addrinfo *res = NULL;

    memset(&conf->dest_addr, 0, sizeof(struct sockaddr_in));
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_CANONNAME;

    conf->dest_addr.sin_family = AF_INET;
    if (getaddrinfo(addr, NULL, &hints, &res)){
        freeaddrinfo(res);
        puterr_and_exit(ERROR_UNKNOWN_HOST, 1);
    }
    set_dest_name_and_addr(conf, addr, res);
    freeaddrinfo(res);
}

static void set_dest_name_and_addr(t_conf *conf, char *addr, struct addrinfo *res){

    t_stats *stats = get_stats(true, NULL);

    conf->adress_resolved = TRUE;
    conf->dest_addr = *((struct sockaddr_in*)res->ai_addr);
    if (res->ai_canonname == NULL){
        stats->dest_name = strdup(addr);
        return;
    }
    stats->dest_name = strdup(res->ai_canonname);
}