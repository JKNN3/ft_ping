#ifndef REGEX_MACROS_H
# define REGEX_MACROS_H


# define MAXGROUP               2
# define NB_OF_BOOLEAN_OPTIONS  7

# define REGEX_CHECK_ARG_QUEUE "^-[adf\?qvciw]{2,}$"
# define REGEX_CHECK_ARG_TYPE_BOOLEAN_OPTION "^(-[adf\?qv]{1}$)|(--(debug)|(flood)|(help)|(quiet)|(usage)|(verbose)$)$"
# define REGEX_CHECK_ARG_TYPE_OPTION_AND_VALUE "^--(count|interval|timeout|ttl$)=([ -~]*)$"
# define REGEX_CHECK_ARG_TYPE_OPTION "^(--(count|interval|timeout|ttl)$)|(-[ciw]{1}$)$"
# define REGEX_CHECK_ARG_DEST "^[^-][ -~]*$"
# define REGEX_CHECK_OPTION "^-[ -~]*$"

# define REGEX_LIST_OPTION {\
    "^(-?c)|(--count)$",\
    "^(-?i)|(--interval)$",\
    "^(-?w)|(--?timeout)$",\
    "^--ttl$"\
};

# define REGEX_LIST_BOOL_OPTION {\
    "^-?a$",\
    "^(-?d)|(--debug$)$",\
    "^(-?f)|(--flood$)$",\
    "^(-?q)|(--quiet$)$",\
    "^--usage$",\
    "^(-?v)|(--verbose$)$",\
    "^(-[?]{1}\?$)|(--help$)$",\
};

# define REGEX_LIST_VALUE {\
    "^[+-]{0,1}([0-9]{1,20})$",\
    "^[+-]{0,1}([0-9]*[.])?[0-9]+?([eE][+-]?[0-9]+)?$",\
    "^[+-]{0,1}([0-9]{1,20})$",\
    "^[+-]{0,1}([0-9]+)$",\
};

# define REGEX_LIST_FULLNAME_OPTION {\
    "^(--count)=([ -~]*)$",\
    "^(--interval)=([ -~]*)$",\
    "^(--timeout)=([ -~]*)$",\
    "^(--ttl)=([ -~]*)$"\
};

enum{
    BOOLEAN,
    OPTION_WITH_VALUE,
    OPTION_WITHOUT_VALUE,
    OPTION_QUEUE,
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