#include "TeachingCategories.h"

// C - Major
static const note_info_t C_Major_Scale[8] =
{
   { C, e_no_sign, 4, e_quarter, false },
   { D, e_no_sign, 4, e_quarter, false },
   { E, e_no_sign, 4, e_quarter, false },
   { F, e_no_sign, 4, e_quarter, false },
   { G, e_no_sign, 4, e_quarter, false },
   { A, e_no_sign, 4, e_quarter, false },
   { B, e_no_sign, 4, e_quarter, false },
   { C, e_no_sign, 5, e_quarter, false },
};

// D - Major
static const note_info_t D_Major_Scale[8] =
{
   { D, e_no_sign, 4, e_quarter, false },
   { E, e_no_sign, 4, e_quarter, false },
   { F, e_sharp, 4, e_quarter, false },
   { G, e_no_sign, 4, e_quarter, false },
   { A, e_no_sign, 4, e_quarter, false },
   { B, e_no_sign, 4, e_quarter, false },
   { C, e_sharp, 5, e_quarter, false },
   { D, e_no_sign, 5, e_quarter, false },
};

// E - Major
static const note_info_t E_Major_Scale[8] =
{
   { E, e_no_sign, 4, e_quarter, false },
   { F, e_sharp, 4, e_quarter, false },
   { G, e_sharp, 4, e_quarter, false },
   { A, e_no_sign, 4, e_quarter, false },
   { B, e_no_sign, 4, e_quarter, false },
   { C, e_sharp, 5, e_quarter, false },
   { D, e_sharp, 5, e_quarter, false },
   { E, e_no_sign, 5, e_quarter, false },
};

// F - Major
static const note_info_t F_Major_Scale[8] =
{
   { F, e_no_sign, 4, e_quarter, false },
   { G, e_no_sign, 4, e_quarter, false },
   { A, e_no_sign, 4, e_quarter, false },
   { B, e_flat, 4, e_quarter, false },
   { C, e_no_sign, 5, e_quarter, false },
   { D, e_no_sign, 5, e_quarter, false },
   { E, e_no_sign, 5, e_quarter, false },
   { F, e_no_sign, 5, e_quarter, false },
};

// G - Major
static const note_info_t G_Major_Scale[8] =
{
   { G, e_no_sign, 4, e_quarter, false },
   { A, e_no_sign, 4, e_quarter, false },
   { B, e_no_sign, 4, e_quarter, false },
   { C, e_no_sign, 5, e_quarter, false },
   { D, e_no_sign, 5, e_quarter, false },
   { E, e_no_sign, 5, e_quarter, false },
   { F, e_sharp, 5, e_quarter, false },
   { G, e_no_sign, 5, e_quarter, false },
};

// A - Major
static const note_info_t A_Major_Scale[8] =
{
   { A, e_no_sign, 4, e_quarter, false },
   { B, e_no_sign, 4, e_quarter, false },
   { C, e_sharp, 5, e_quarter, false },
   { D, e_no_sign, 5, e_quarter, false },
   { E, e_no_sign, 5, e_quarter, false },
   { F, e_sharp, 5, e_quarter, false },
   { G, e_sharp, 5, e_quarter, false },
   { A, e_no_sign, 5, e_quarter, false },
};

// B - Major
static const note_info_t B_Major_Scale[8] =
{
   { B, e_no_sign, 4, e_quarter, false },
   { C, e_sharp, 5, e_quarter, false },
   { D, e_sharp, 5, e_quarter, false },
   { E, e_no_sign, 5, e_quarter, false },
   { F, e_sharp, 5, e_quarter, false },
   { G, e_sharp, 5, e_quarter, false },
   { A, e_sharp, 5, e_quarter, false },
   { B, e_no_sign, 5, e_quarter, false },
};


static const note_info_t *Major_Scales[7] =
{
   C_Major_Scale,
   D_Major_Scale,
   E_Major_Scale,
   F_Major_Scale,
   G_Major_Scale,
   A_Major_Scale,
   B_Major_Scale,
};