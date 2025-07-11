#ifndef _ASSERT_H
#define _ASSERT_H

void aassert(int e);

#define assert(e) aassert((int)(e))
#define static_assert(e, msg)

#endif