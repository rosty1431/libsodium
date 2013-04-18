
#include <sys/types.h>

#include <assert.h>
#include <inttypes.h>
#include <limits.h>

#include "randombytes.h"
#include "randombytes_sysrandom.h"

static randombytes_implementation implementation = {
    .implementation_name = sysrandom_implementation_name,
    .random = sysrandom,
    .stir = sysrandom_stir,
    .uniform = sysrandom_uniform,
    .buf = sysrandom_buf,
    .close = sysrandom_close
};

int
randombytes_set_implementation(randombytes_implementation *impl)
{
    implementation = *impl;

    return 0;
}

const char *
randombytes_implementation_name(void)
{
    return implementation.implementation_name();
}

uint32_t
randombytes_random(void)
{
    return implementation.random();
}

void
randombytes_stir(void)
{
    return implementation.stir();
}

uint32_t
randombytes_uniform(const uint32_t upper_bound)
{
    return implementation.uniform(upper_bound);
}

void
randombytes_buf(void * const buf, const size_t size)
{
    return implementation.buf(buf, size);
}

int
randombytes_close(void)
{
    return implementation.close();
}

void
randombytes(unsigned char * const buf, const unsigned long long buf_len)
{
    assert(buf_len <= SIZE_MAX);
    randombytes_buf(buf, (size_t) buf_len);
}
