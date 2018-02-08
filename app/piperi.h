#ifndef PIPERI_H
#define PIPERI_H

#ifdef WITH_TRACE
#ifndef TRACE_H_
#include "trace.h"
#endif
#else
#define get_trace_level() "N/A"
#define is_tracing(x) true
#endif

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif /* PIPERI_H */

