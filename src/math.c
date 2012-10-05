#include <limits.h>
#include "hutil.h"


unsigned int pow_uint (const unsigned int base,  const unsigned int exp)
{
    unsigned int result = base;
    const unsigned int limit = UINT_MAX/base;

    for (unsigned int i=1; i<exp; ++i) {
        if (result <= limit)
            result *= base;
        else
            return 0;
    }

    return result;
}

