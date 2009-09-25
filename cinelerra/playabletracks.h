
/*
 * CINELERRA
 * Copyright (C) 2008 Adam Williams <broadcast at earthling dot net>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 */

#ifndef PLAYABLETRACKS_H
#define PLAYABLETRACKS_H

#include "arraylist.h"
#include "datatype.h"
#include "edl.inc"
#include "mwindow.inc"
#include "track.h"

class PlayableTracks : public ArrayList<Track*>
{
public:
	PlayableTracks(EDL *edl,
		int64_t current_position,  // Position in native units of tracks
		int direction,
		int data_type,
		int use_nudge);
	~PlayableTracks();

// return 1 if the track is playable at the position
	int is_playable(Track *current_track, 
		int64_t position,
		int direction,
		int use_nudge);
// return 1 if the track is in the list
	int is_listed(Track *track);

	int data_type;
	MWindow *mwindow;
};



#endif
