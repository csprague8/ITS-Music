

class Metronome
{
public:
   Metronome();
   Metronome(int tempo);
   ~Metronome();

   void start();
   void end();
   void set_tempo(int tempo);
   int get_tempo();

private:
   int m_tempo = 120;
   bool stop_flag = false;
   void *m_timer = 0;

};