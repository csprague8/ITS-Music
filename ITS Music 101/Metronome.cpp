
#include "stdafx.h"
#include "Metronome.h"

#include <stdio.h>
#include <Windows.h>
#include <thread>

void timer(Metronome *metronome, bool *stop_flag);




Metronome::Metronome()
{
}

Metronome::Metronome(int tempo)
{
   m_tempo = tempo;
}

Metronome::~Metronome()
{
   end();
}


void Metronome::start()
{
   stop_flag = false;
   m_timer = new std::thread(timer, this, &stop_flag);
}

void Metronome::end()
{
   stop_flag = true;
}

void Metronome::set_tempo(int tempo)
{
   m_tempo = tempo;
}

int Metronome::get_tempo()
{
   return m_tempo;
}

void timer(Metronome *metronome, bool *stop_flag)
{
   int tempo = metronome->get_tempo();
   int sleep_time = 60000 / tempo;

   while (!*stop_flag)
   {
      Beep(784, 100);
      Sleep(sleep_time);
      tempo = metronome->get_tempo();
      if (tempo != 0)
         sleep_time = 60000 / tempo;
   }
}
