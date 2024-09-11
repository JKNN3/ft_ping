#ifndef REGEX_MACROS_H
# define REGEX_MACROS_H


// ip regex
// uns string pour check si c'est une option booléen

# define REGEX_CHECK_ARG_OPTION_TYPE_BOOLEEN "str"
# define REGEX_CHECK_ARG_OPTION_TYPE_SHORTNAME "str"
# define REGEX_CHECK_ARG_OPTION_TYPE_FULLNAME "str"
# define REGEX_CHECK_ARG_DEST "str"

# define MAXGROUP         2
# define NB_OF_BOOLEAN_OPTIONS  8

extern inline char *regex_tab_bool_short_option[4] = {
    "$-c^",
    "$-i^",
    "$-w^",
    "$--ttl^",
};

extern inline char *regex_tab_bool_short_option_value[4] = {
    "$^",   // u long int
    "$^",   // double
    "$^",   // u long int
    "$^",   // int mais short, juste regarder si il est pas trop long genre pas plus de 4 chiffres pour pas que atoi overflow
};

extern inline char *regex_tab_fullname_option[3] = {
    "$--count[*]*^",
    "$--interval[*]*^",
    "$--timeout[*]*^"
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