# if defined(CCOMMONTOOLS_LIB)
#  define CCOMMONTOOLS_EXPORT __declspec(dllexport)
# else
#  define CCOMMONTOOLS_EXPORT __declspec(dllimport)
# endif
