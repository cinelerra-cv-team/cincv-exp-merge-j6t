
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

#ifndef MOTIONSCAN_H
#define MOTIONSCAN_H


#include "arraylist.h"
#include "loadbalance.h"
#include "vframe.inc"
#include <stdint.h>

class MotionScan;

#define OVERSAMPLE 4
#define MOTION_FILE "/tmp/motion"

class MotionScanPackage : public LoadPackage
{
public:
	MotionScanPackage();

// For multiple blocks
	int block_x1, block_y1, block_x2, block_y2;
	int scan_x1, scan_y1, scan_x2, scan_y2;
	int dx;
	int dy;
	int64_t max_difference;
	int64_t min_difference;
	int64_t min_pixel;
	int is_border;
	int valid;
// For single block
	int pixel;
	int64_t difference1;
	int64_t difference2;
};

class MotionScanCache
{
public:
	MotionScanCache(int x, int y, int64_t difference);
	int x, y;
	int64_t difference;
};

class MotionScanUnit : public LoadClient
{
public:
	MotionScanUnit(MotionScan *server, MotionMain *plugin);
	~MotionScanUnit();

	void process_package(LoadPackage *package);
	int64_t get_cache(int x, int y);
	void put_cache(int x, int y, int64_t difference);

	MotionScan *server;
	MotionMain *plugin;

	ArrayList<MotionScanCache*> cache;
	Mutex *cache_lock;
};

class MotionScan : public LoadServer
{
public:
	MotionScan(MotionMain *plugin, 
		int total_clients, 
		int total_packages);
	~MotionScan();

	friend class MotionScanUnit;

	void init_packages();
	LoadClient* new_client();
	LoadPackage* new_package();

// Invoke the motion engine for a search
// Frame before motion
	void scan_frame(VFrame *previous_frame,
// Frame after motion
		VFrame *current_frame);
	int64_t get_cache(int x, int y);
	void put_cache(int x, int y, int64_t difference);

// Change between previous frame and current frame multiplied by 
// OVERSAMPLE
	int dx_result;
	int dy_result;

private:
	VFrame *previous_frame;
// Frame after motion
	VFrame *current_frame;
	MotionMain *plugin;
	int skip;
// For single block
	int block_x1;
	int block_x2;
	int block_y1;
	int block_y2;
	int scan_x1;
	int scan_y1;
	int scan_x2;
	int scan_y2;
	int total_pixels;
	int total_steps;
	int subpixel;


	ArrayList<MotionScanCache*> cache;
	Mutex *cache_lock;
};



#endif
