#include <map>

enum
{
   e_viewed,
   e_attempts,
   e_accuracy
};

typedef std::map < int, std::map < int, int[3] >> Prog_Map_t;

void write_progress_log(int current_category, Prog_Map_t progress_map);
void read_progress_log(int *current_category, Prog_Map_t *progress_map);
