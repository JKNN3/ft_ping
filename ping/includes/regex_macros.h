#ifndef REGEX_MACROS_H
# define REGEX_MACROS_H


// ip regex
// uns string pour check si c'est une option booléen

# define REGEX_CHECK_ARG_TYPE_BOOLEEN_OPTION "$(-[a|c|d|f|?|v])|(--[debug|count|flood|help|print|quiet|usage|verbose])^"
# define REGEX_CHECK_ARG_TYPE_OPTION "$(--[count|inetrval|timeout|ttl])|(-[c|i|w])^"
# define REGEX_CHECK_ARG_TYPE_OPTION_AND_VALUE "$--[count|inetrval|timeout|ttl]=[*]*^"
# define REGEX_CHECK_ARG_DEST "$([0-9]{3}.[0-9]{3}.[0-9]{3}.[0-9]{3})|[*]*.[*]*^"

# define MAXGROUP         2
# define NB_OF_BOOLEAN_OPTIONS  8

extern inline char *regex_tab_option_without_value[4] = {
    "$(-c)|(--count)^",
    "$(-i)|(--interval)^",
    "$(-w)|(--timeout)^",
    "$--ttl^",
};

extern inline char *regex_tab_bool_option[]={
    "$-a^",
    "$(-d)|(--debug)^",
    "$(-c)|(--count)^",
    "$(-f)|(--flood)^",
    "$(-?)|(--help)^",
    "$--print^",
    "$--quiet^",
    "$--usage^",
    "$(-v)|(--verbose)^",
};

extern inline char *regex_tab_option_value[4] = {
    "$^",   // u long int
    "$^",   // double
    "$^",   // u long int
    "$^",   // int mais short, juste regarder si il est pas trop long genre pas plus de 4 chiffres pour pas que atoi overflow
};

extern inline char *regex_tab_fullname_option[4] = {
    "$(--count)=([*]*)^",
    "$(--interval)=([*]*)^",
    "$(--timeout)=([*]*)^"
    "$(--ttl)=([*]*)^"
};

enum{
    BOOLEEN,
    OPTION_WITH_VALUE,
    OPTION_WITHOUT_VALUE,
    DEST,
    ERROR,
};
enum{
    COUNT,
    INTERVAL,
    TIMEOUT,
    TTL,
    IP,
};

#endif