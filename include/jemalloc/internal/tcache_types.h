#ifndef JEMALLOC_INTERNAL_TCACHE_TYPES_H
#define JEMALLOC_INTERNAL_TCACHE_TYPES_H

#include "jemalloc/internal/sc.h"

typedef struct tcache_slow_s tcache_slow_t;
typedef struct tcache_s tcache_t;
typedef struct tcaches_s tcaches_t;

/*
 * tcache pointers close to NULL are used to encode state information that is
 * used for two purposes: preventing thread caching on a per thread basis and
 * cleaning up during thread shutdown.
 */
#define TCACHE_STATE_DISABLED		((tcache_t *)(uintptr_t)1)
#define TCACHE_STATE_REINCARNATED	((tcache_t *)(uintptr_t)2)
#define TCACHE_STATE_PURGATORY		((tcache_t *)(uintptr_t)3)
#define TCACHE_STATE_MAX		TCACHE_STATE_PURGATORY

/* (1U << opt_lg_tcache_max) is used to compute tcache_maxclass. */
#define LG_TCACHE_MAXCLASS_DEFAULT	15

/*
 * TCACHE_GC_SWEEP is the approximate number of allocation events between
 * full GC sweeps.  Integer rounding may cause the actual number to be
 * slightly higher, since GC is performed incrementally.
 */
#define TCACHE_GC_SWEEP			8192

/* Number of tcache deallocation events between incremental GCs. */
#define TCACHE_GC_INCR							\
    ((TCACHE_GC_SWEEP / SC_NBINS) + ((TCACHE_GC_SWEEP / SC_NBINS == 0) ? 0 : 1))

/* Number of allocation bytes between tcache incremental GCs. */
#define TCACHE_GC_INCR_BYTES 65536U

/* Used in TSD static initializer only. Real init in tsd_tcache_data_init(). */
#define TCACHE_ZERO_INITIALIZER {0}
#define TCACHE_SLOW_ZERO_INITIALIZER {0}

/* Used in TSD static initializer only. Will be initialized to opt_tcache. */
#define TCACHE_ENABLED_ZERO_INITIALIZER false

/* Used for explicit tcache only. Means flushed but not destroyed. */
#define TCACHES_ELM_NEED_REINIT ((tcache_t *)(uintptr_t)1)

#endif /* JEMALLOC_INTERNAL_TCACHE_TYPES_H */
