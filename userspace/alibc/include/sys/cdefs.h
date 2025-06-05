#ifndef _SYS_CDEFS_H
#define _SYS_CDEFS_H

#if defined(__cplusplus)
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif

#define __strong_alias(alias, sym)
#define _Nonnull
#define weak_alias(alias, sym);
#define _Nullable
#define __FBSDID(r)
#define __INTRODUCED_IN(V)
#define __RENAME(N)
#define __unused
#define __printflike(a, b)
#define __dead2
#define __printf0like(a, b)
#define PRIdMAX "ld"
#define __cdecl

#endif
