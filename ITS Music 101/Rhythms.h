
#include "TeachingCategories.h"

enum
{
   nw,
   nh,
   nq,
   ne,
   ns,
   rw,
   rh,
   rq,
   re,
   rs,
};

static int pattern1[] = 
{
   nw,
   nh, nh,
   nq, nq, nq, nq,
   ne, ne, ne, ne, ne, ne, ne, ne,
};

static int pattern2[] =
{
   nw, nh, nh, nw, nh, nh
};

static int pattern3[] =
{
   nw, rh, nh, nh, rh, nw
};

static int pattern4[] =
{
   nh, nh, rw, nh, nh, rh, nh
};

static int pattern5[] =
{
   nq, nh, nq,
   nq, nq, nh,
   nh, nq, nq,
   nq, nq, nq, nq
};

static int pattern6[] =
{
   nq, nq, rq, nq,  nw, 
   rh, nq, rq,  nq, nq, rq, nq
};

static int pattern7[] =
{
   nq, rh, nq, 
   nq, rh, nq,
   rq, nh, rq,
   rh, nq, nq
};

static int pattern8[] =
{
   nw, nq, rq, nh, rh, nq, rq, nq, rq, nh
};

static int pattern9[] =
{
   ne, ne, nq, ne, ne, nq,
   ne, ne, nq, ne, ne, nq,
   ne, ne, nq, ne, ne, nq,
   ne, ne, nq, ne, ne, nq,
};

static int pattern10[] =
{
   nq, ne, ne, nq, ne, ne,
   nq, ne, ne, nq, ne, ne,
   nq, ne, ne, nq, ne, ne,
   nq, ne, ne, nq, ne, ne,
};

static int pattern11[] =
{
   nq, nh, ne, ne, nq, re, ne, rq, ne, ne, nq, nh, ne, ne, nq, nh, ne, ne
};

static int pattern12[] =
{
   nq, nq, nq, re, ne, ne, ne, re, ne, ne, re, ne, ne, ne, ne, nq, ne, ne, re, ne, ne, ne, nq, nh
};

static int pattern13[] =
{
   nq, re, ne, ne, re, ne, ne, nh, ne, ne, nq, nq, nh, ne, ne, re, ne, ne, re, nq, ne, ne
};
