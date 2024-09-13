#ifndef REGEX_MACROS_H
# define REGEX_MACROS_H


// ip regex
// uns string pour check si c'est une option booléen

# define REGEX_CHECK_ARG_TYPE_BOOLEEN_OPTION "^(-[a|d|f|?|v])|(--(debug)|(flood)|(help)|(print)|(quiet)|(usage)|(verbose))$"
# define REGEX_CHECK_ARG_TYPE_OPTION_AND_VALUE "^--(count|interval|timeout|ttl)=([ -~]*)$"
# define REGEX_CHECK_ARG_TYPE_OPTION "^(--(count|inetrval|timeout|ttl))|(-[ciw]{1})$"
# define REGEX_CHECK_ARG_DEST "^([0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3})|([*]*.[*]*)$"

# define MAXGROUP               2
# define NB_OF_BOOLEAN_OPTIONS  8

# define REGEX_LIST_OPTION {\
    "^(-c)|(--count)$",\
    "^(-i)|(--interval)$",\
    "^(-w)|(--timeout)$",\
    "^--ttl$"\
};

# define REGEX_LIST_BOOL_OPTION {\
    "^-a$",\
    "^(-d)|(--debug)$",\
    "^(-c)|(--count)$",\
    "^(-f)|(--flood)$",\
    "^(-?)|(--help)$",\
    "^--print$",\
    "^--quiet$",\
    "^--usage$",\
    "^(-v)|(--verbose)$"\
};

# define REGEX_LIST_VALUE {\
    "^[+-]{0,1}([0-9]{1,20})$",\
    "^[+-]{0,1}([0-9]*[.])?[0-9]+?([eE][+-]?[0-9]+)?$",\
    "^[+-]{0,1}([0-9]{1,20})$",\
    "^[+-]{0,1}([0-9]{1,10})$",\
};

// u long int
  // double
   // u long int
  // int mais short, juste regarder si il est pas trop long genre pas plus de 4 chiffres pour pas que atoi overflow


# define REGEX_LIST_FULLNAME_OPTION {\
    "^(--count)=([ -~]*)$",\
    "^(--interval)=([ -~]*)$",\
    "^(--timeout)=([ -~]*)$",\
    "^(--ttl)=([ -~]*)$"\
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