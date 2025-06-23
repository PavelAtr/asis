#ifndef _ASSERT_H
#define _ASSERT_H

void aassert(int e);

#define assert(e) aasert((int)(e))
#define static_assert(e, msg) aasert((int)(e))

#endif