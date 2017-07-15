
#define nl     L"\r\n"
#define nl2    L"\r\n\r\n"
#define tab    L"\t"

wchar_t startup_text[] =
   L"Welcome to ITS Music 101." nl2
   L"This is your one stop to learn everything you need to know "
   L"about reading music." nl2
   L"To begin please select a learning category."
   ;

wchar_t note_length_info_text[] =
   L"Music notes can vary in length. This is indicated by the symbols displayed." nl
   L"The following are a few of the music note types:" nl
   tab L"* Whole Notes (W): are played for 4 beats. " nl
   tab L"* Half Notes (H): are played for 2 beats." nl
   tab L"* Quarter Notes (Q): are played for 1 beat." nl
   tab L"* Eighth Notes (E): are played for 1/2 a beat." nl
   tab L"* Sixteenth Notes (S): are played for 1/4 beat." nl2
   L"The value names are based on a 4/4 time signiture. " nl
   L"This means there are 4 beats per measure with a quarter note being a single beat." nl
   L"Different time signitures will be included in futures expansions of ITS Music 101."
   ;

wchar_t rest_length_info_text[] =
   L"Music rests are a period of time in which no sound is played." nl
   L"Rests can vary in length. This is indicated by the symbols displayed." nl
   L"The following are a few of the music rest types:" nl
   tab L"* Whole Rests: are held for 4 beats. " nl
   tab L"* Half Rests: are held for 2 beats." nl
   tab L"* Quarter Rests: are held for 1 beat." nl
   tab L"* Eighth Rests: are held for 1/2 a beat." nl
   tab L"* Sixteenth Rests: are held for 1/4 beat." nl2
   L"There is a rest type to correspond to each note type." nl2
   L"The value names are based on a 4/4 time signiture. " nl
   L"This means there are 4 beats per measure with a quarter note being a single beat." nl
   L"Different time signitures will be included in futures expansions of ITS Music 101."
   ;

wchar_t note_value_info_text[] =
   L"Music note values range from A to G." nl
   L"Thse notes can be are part of an octave. " nl
   L"Octaves range from a note to the note of the same name "
   L"above or below." nl2
   L"The notes displayed about range from C to G, covering 2 octaves." nl
   L"The notes are shown for both treble clef and bass clef." nl
   tab L"* Treble clef is generally used for instruments that use the middle "
       L"of the musical range, " nl
   tab L"   such as guitar." nl
   tab tab L"* Notes on the spaces read from the bottom up as F-A-C-E" nl
   tab tab L"* Notes on the lines read from the bottom up as E-G-B-D-F" nl
   tab L"* Bass cleff is generally used for instruments that use the low end "
       L"of the musical range," nl
   tab L"   such as tuba." nl
       tab tab L"* Notes on the spaces read from the bottom up as A-C-E-G" nl
       tab tab L"* Notes on the line read from the bottom up as G-B-D-F-A" nl2
   L"ITS Music 101 will display music in both treble and bass clef so that" nl
   L"the user may choose which to learn for themselves."
   ;


wchar_t rhythms_info_text[] =
   L"ITS Music 101 contains several practice rhythms for learning how to play"
   L"different patterns." nl
   L"The rhythm patterns get progressively harder." nl2
   L"Future work includes an option for auto-generating patterns"
   ;

wchar_t scales_info_text[] =
   L"A musical scale is a natural progression of notes that occur over differnt note intervals." nl
   L"These intervals consist of whole and half steps:"nl
   tab L"Whole Step: Moves 2 notes interval (skipping a note)"nl
   tab L"Whole Step: Moves 1 note interval"nl
   L"There are hundreds of different scales. Only a few will be covered here." nl
   L"The scales consist of the following intervals:" nl
   tab L"Major:"    tab tab L"{ start, whole, whole, half, whole, whole, whole, half }" nl
   tab L"Dorian:"   tab tab L"{ start, whole, half, whole, whole, whole, half, whole }" nl
   tab L"Phrygian:" tab tab L"{ start, half, whole, whole, whole, half, whole, whole }" nl
   tab L"Lydian:"   tab tab L"{ start, whole, whole, whole, half, whole, whole, half }" nl
   tab L"Mixolydian:"   tab L"{ start, whole, whole, half, whole, whole, half, whole }" nl
   tab L"Minor:"    tab tab L"{ start, whole, half, whole, whole, half, whole, whole }" nl
   tab L"Locrian:"  tab tab L"{ start, half, whole, whole, half, whole, whole, whole }" nl
   tab L"Chromatic:"    tab L"Progression of half steps over an octave" nl
   L"It can be noted that the scales listed (other than chromatic) are just a shifted" nl
   L"version of the scale preceeding it."
   ;

wchar_t keys_info_text[] =
   L"Keys are a way of telling the reader that all of a certain note are either sharp or flat." nl
   L"If a note is marked as sharp/flat in the key, all of the future times that note is played" nl
   L"it is sharp/flat. This removes the need to constantly write out the sharp/flat symbols as" nl
   L"is done with the scalese portion of ITS Music"
   ;

wchar_t mapping_info_text[] =
   L"The mapping between notes and their locations on a guitar fret can be seen here." nl
   L"The numbers at the top indicate fret number." nl
   L"It can be seen that a note can be played in many positions on a guitar."nl2
   L"Change the selected note to see all locations for that note."
;


#define startup_progress_text \
   L"Welcome back to ITS Music 101. \r\n  \r\n\
You last left off at category %s. \r\n \r\n\
Based on your progress it is recommened that you select\r\n\
Category %s. \r\n\
You are at %i mastery of that topic."