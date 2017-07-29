#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <map>
#include "ProgressLogging.h"
#include "TeachingCategories.h"


void write_progress_log(int current_category, Prog_Map_t progress_map)
{
   std::ofstream log("Progress_Log.txt");

   // Current postion

   log << "Current " << current_category << std::endl;

   // Categroy [Subcategory] Viewed Attempts Accuracy

   for (int i = 0; i < e_max_lengths; i++)
   {
      log << "NoteLength " << i << " "
         << progress_map[e_note_lengths][i][e_viewed] << " " 
         << progress_map[e_note_lengths][i][e_attempts] << " "
         << progress_map[e_note_lengths][i][e_accuracy] 
         << std::endl;
   }

   log << "NoteValues " << 0 << " "
      << progress_map[e_note_values][0][e_viewed] << " "
      << progress_map[e_note_values][0][e_attempts] << " "
      << progress_map[e_note_values][0][e_accuracy]
      << std::endl;

   for (int i = 0; i < e_max_lengths; i++)
   {
      log << "RestTypes " << i << " "
         << progress_map[e_note_lengths][i][e_viewed] << " "
         << progress_map[e_note_lengths][i][e_attempts] << " "
         << progress_map[e_note_lengths][i][e_accuracy]
         << std::endl;
   }

   for (int i = 0; i < e_max_rhythm_patterns; i++)
   {
      log << "RhythmPatterns " << i << " "
         << progress_map[e_rhythm_patterns][i][e_viewed] << " "
         << progress_map[e_rhythm_patterns][i][e_attempts] << " "
         << progress_map[e_rhythm_patterns][i][e_accuracy]
         << std::endl;
   }

   for (int i = 0; i < e_max_scales; i++)
   {
      log << "Scales " << i << " "
         << progress_map[e_scales][i][e_viewed] << " "
         << progress_map[e_scales][i][e_attempts] << " "
         << progress_map[e_scales][i][e_accuracy]
         << std::endl;
   }

   for (int i = 0; i < e_max_note2; i++)
   {
      log << "MusicKeys " << i << " "
         << progress_map[e_music_keys][i][e_viewed] << " "
         << progress_map[e_music_keys][i][e_attempts] << " "
         << progress_map[e_music_keys][i][e_accuracy]
         << std::endl;
   }
   
   log << "NoteMapping ";


   log.close();
}

void read_progress_log(int *current_category, Prog_Map_t *progress_map)
{
   std::ifstream log("Progress_Log.txt");

   char word[256];
   Prog_Map_t temp;

   while (log >> word)
   {
      if (strcmp(word, "Current") == 0)
      {
         if (log >> word)
            *current_category = atoi(word);
      }
      else
      {
         int cat = 0;

         if (strcmp(word, "NoteLength") == 0)
            cat = e_note_lengths;
         else if (strcmp(word, "NoteValues") == 0)
            cat = e_note_values;
         else if (strcmp(word, "RestTypes") == 0)
            cat = e_rest_types;
         else if (strcmp(word, "RhythmPatterns") == 0)
            cat = e_rhythm_patterns;
         else if (strcmp(word, "Scales") == 0)
            cat = e_scales;
         else if (strcmp(word, "MusicKeys") == 0)
            cat = e_music_keys;
         else if (strcmp(word, "NoteMapping") == 0)
            cat = e_note_mapping;

         int sub = 0;
         int viewed = 0;
         int attempts = 0;
         int accuracy = 0;

         if (log >> word) sub = atoi(word);
         if (log >> word) viewed = atoi(word);
         if (log >> word) attempts = atoi(word);
         if (log >> word) accuracy = atoi(word);

         temp[cat][sub][e_viewed] = viewed;
         temp[cat][sub][e_attempts] = attempts;
         temp[cat][sub][e_accuracy] = accuracy;
      }
   }

   log.close();

   *progress_map = temp;
}
