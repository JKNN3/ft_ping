#ifndef REGEX_MACROS_H
# define REGEX_MACROS_H


// ip regex
// uns string pour check si c'est une option booléen

# define REGEX_CHECK_OPTION_TYPE_BOOLEEN "str"
# define REGEX_CHECK_OPTION_TYPE_OPT_WITH_VALUE "str"
# define REGEX_CHECK_OPTION_TYPE_OPT_WITHOUT_VALUE "str"

# define NB_OPTION_TYPE         3
# define NB_OF_BOOLEAN_OPTIONS  8

extern inline char regex_check_bool_option[4][8] = {
    "str",\
    "str",\
    "str",\
    "str",\
};

enum{
    BOOLEEN,
    OPTION_WITH_VALUE,
    OPTION_WITHOUT_VALUE,
    ERROR,
};
enum{
    AUDIBLE,    // bool
    COUNT,
    DEBUG,      // bool
    FLOOD,      // bool
    HELP,       // bool
    INTERVAL,
    PRINT,      // bool
    QUIET,      // bool
    TIMEOUT,
    TTL,
    USAGE,      // bool
    VERBOSE,     // bool
    IP,
};

#endif