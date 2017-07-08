
#pragma once

enum
{
   e_note_lengths,
   e_note_values,
   e_rest_types,
   e_rhythm_patterns,
   e_scales,
   e_music_keys,
   e_note_mapping,
   e_max_categories // Keep last
};

static const wchar_t categories_text[e_max_categories][32]
{
   L"Note Length",     // e_note_lengths,
   L"Note Values",     // e_note_values,
   L"Rest Types",      // e_rest_types,
   L"Rhythm Patterns", // e_rhythm_patterns,
   L"Scales",          // e_scales,
   L"Music Keys",      // e_music_keys,
   L"Note Mapping",    // e_note_mapping,
};

enum
{
   e_trebble_clef,
   e_bass_clef,
   e_max_clefs // Keep last
};

enum
{
   e_rhythm_pattern_1,
   e_rhythm_pattern_2,
   e_rhythm_pattern_3,
   e_rhythm_pattern_4,
   e_rhythm_pattern_5,
   e_rhythm_pattern_6,
   e_rhythm_pattern_7,
   e_rhythm_pattern_8,
   e_rhythm_pattern_9,
   e_rhythm_pattern_10,
   e_rhythm_pattern_11,
   e_rhythm_pattern_12,
   e_rhythm_pattern_13,
   //e_rhythm_pattern_14,
   //e_rhythm_pattern_15,
   //e_rhythm_pattern_16,
   //e_rhythm_pattern_17,
   //e_rhythm_pattern_18,
   //e_rhythm_pattern_19,
   //e_rhythm_pattern_20,
   e_max_rhythm_patterns // Keep last
};

static wchar_t rhythms_text[e_max_rhythm_patterns][32]
{
   L"Pattern 1",
   L"Pattern 2",
   L"Pattern 3",
   L"Pattern 4",
   L"Pattern 5",
   L"Pattern 6",
   L"Pattern 7",
   L"Pattern 8",
   L"Pattern 9",
   L"Pattern 10",
   L"Pattern 11",
   L"Pattern 12",
   L"Pattern 13",
   //L"Pattern 14",
   //L"Pattern 15",
   //L"Pattern 16",
   //L"Pattern 17",
   //L"Pattern 18",
   //L"Pattern 19",
   //L"Pattern 20",
};

enum
{
   e_major,
   e_dorian,
   e_phrygian,
   e_lydian,
   e_mixolydian,
   e_minor,
   e_locrian,
   e_chromatic,
   e_max_scales // keep last
};


static wchar_t scale_text[e_max_scales][32]
{
   L"major",      // e_major,
   L"dorian",     // e_dorian,
   L"phrygian",   // e_phrygian,
   L"lydian",     // e_lydian,
   L"mixolydian", // e_mixolydian,
   L"minor",      // e_minor,
   L"locrian",    // e_locrian,
   L"chromatic",  // e_chromatic,
};

enum
{
   C = 0,
   D,
   E,
   F,
   G,
   A,
   B,
   e_max_note
};

enum
{
   eC = 0,
   eCS,
   eD,
   eDS,
   eE,
   eF,
   eFS,
   eG,
   eGS,
   eA,
   eAS,
   eB,
   e_max_note2
};

static wchar_t notes_text[e_max_note][2]
{
   L"C",
   L"D",
   L"E",
   L"F",
   L"G",
   L"A",
   L"B",
};

static wchar_t notes_text2[e_max_note2][8]
{
   L"C",
   L"C#/Db",
   L"D",
   L"D#/Eb",
   L"E",
   L"F",
   L"F#/Gb",
   L"G",
   L"G#/Ab",
   L"A",
   L"A#/Bb",
   L"B",
};

enum
{
   e_no_sign,
   e_sharp,
   e_flat,
   e_max_type // Keep last
};

enum
{
   e_whole,
   e_half,
   e_quarter,
   e_eighth,
   e_sixteenth,
   e_max_lengths // Keep last
};

static wchar_t note_length_text[e_max_lengths][32]
{
   L"Whole Note",       // e_whole,
   L"Half Note",        // e_half,
   L"Quarter Note",     // e_quarter,
   L"Eighth Note",      // e_eighth,
   L"Sixteenth Note",   // e_sixteenth,
};

static wchar_t note_length_text_abv[e_max_lengths][2]
{
   L"W", // e_whole,
   L"H", // e_half,
   L"Q", // e_quarter,
   L"E", // e_eighth,
   L"S", // e_sixteenth,
};

static int major_scale_progression[8]        = { 0, 2, 2, 1, 2, 2, 2, 1 };
static int dorian_scale_progression[8]       = { 0, 2, 1, 2, 2, 2, 1, 2 };
static int phrygian_scale_progression[8]     = { 0, 1, 2, 2, 2, 1, 2, 2 };
static int lydian_scale_progression[8]       = { 0, 2, 2, 2, 1, 2, 2, 1 };
static int mixolydian_scale_progression[8]   = { 0, 2, 2, 1, 2, 2, 1, 2 };
static int minor_scale_progression[8]        = { 0, 2, 1, 2, 2, 1, 2, 2 };
static int locrian_scale_progression[8]      = { 0, 1, 2, 2, 1, 2, 2, 2 };
static int chromatic_scale_progression[12]   = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
static int blues_scale_progression[7]        = { 0, 3, 2, 1, 1, 3, 2 };



struct note_info_t
{
   int note;
   int sign;
   int level;
   int type;
   bool isRest;
};

typedef int key_t[e_max_note];

//  key       C, D, E, F, G, A, B
static const key_t key_C = { 0, 0, 0, 0, 0, 0, 0 };
static const key_t key_D = { 1, 0, 0, 1, 0, 0, 0 };
static const key_t key_E = { 1, 1, 0, 1, 1, 0, 0 };
static const key_t key_F = { 0, 0, 0, 0, 0, 0, 2 };
static const key_t key_G = { 0, 0, 0, 1, 0, 0, 0 };
static const key_t key_A = { 1, 0, 0, 1, 1, 0, 0 };
static const key_t key_B = { 1, 1, 0, 1, 1, 1, 0 };

static const key_t keys[7] =
{
   { 0, 0, 0, 0, 0, 0, 0 }, // key_C,
   { 1, 0, 0, 1, 0, 0, 0 }, // key_D,
   { 1, 1, 0, 1, 1, 0, 0 }, // key_E,
   { 0, 0, 0, 0, 0, 0, 2 }, // key_F,
   { 0, 0, 0, 1, 0, 0, 0 }, // key_G,
   { 1, 0, 0, 1, 1, 0, 0 }, // key_A,
   { 1, 1, 0, 1, 1, 1, 0 }, // key_B,
};