/*
    ettercap -- sleep / timer functions

    Copyright (C) ALoR & NaGA

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

*/

#include <ec.h>
#include <ec_sleep.h>

#include <unistd.h>
#include <time.h>

/* this function is used to unify *sleep calls within ettercap */
void ec_usleep(unsigned int usecs)
{
#ifndef OS_WINDOWS
   struct timespec ts;
   ts.tv_sec = MICRO2SEC(usecs);
   ts.tv_nsec = MICRO2NANO((usecs % (SEC2MICRO(1))));

   nanosleep(&ts, NULL);
#else
  /* As used from e.g. top_half(), the 1usec sleep there cause approx. 25% usage.
   * So make Sleep() wait for at least 1 msec.
   */
  DWORD msecs = usecs / 1000;
  Sleep (MAX(1, msecs));
#endif
}

/* EOF */

// vim:ts=3:expandtab
