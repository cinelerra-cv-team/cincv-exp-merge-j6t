
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

#include "clip.h"
#include "motion.h"
#include "motionscan.h"
#include "mutex.h"
#include "vframe.h"

// The module which does the actual scanning

MotionScanPackage::MotionScanPackage()
 : LoadPackage()
{
	valid = 1;
}






MotionScanUnit::MotionScanUnit(MotionScan *server, 
	MotionMain *plugin)
 : LoadClient(server)
{
	this->plugin = plugin;
	this->server = server;
	cache_lock = new Mutex("MotionScanUnit::cache_lock");
}

MotionScanUnit::~MotionScanUnit()
{
	delete cache_lock;
}



void MotionScanUnit::process_package(LoadPackage *package)
{
	MotionScanPackage *pkg = (MotionScanPackage*)package;
	int w = server->current_frame->get_w();
	int h = server->current_frame->get_h();
	int color_model = server->current_frame->get_color_model();
	int pixel_size = cmodel_calculate_pixelsize(color_model);
	int row_bytes = server->current_frame->get_bytes_per_line();












// Single pixel
	if(!server->subpixel)
	{
		int search_x = pkg->scan_x1 + (pkg->pixel % (pkg->scan_x2 - pkg->scan_x1));
		int search_y = pkg->scan_y1 + (pkg->pixel / (pkg->scan_x2 - pkg->scan_x1));

// Try cache
		pkg->difference1 = server->get_cache(search_x, search_y);
		if(pkg->difference1 < 0)
		{
//printf("MotionScanUnit::process_package 1 %d %d\n", 
//search_x, search_y, pkg->block_x2 - pkg->block_x1, pkg->block_y2 - pkg->block_y1);
// Pointers to first pixel in each block
			unsigned char *prev_ptr = server->previous_frame->get_rows()[
				search_y] +	
				search_x * pixel_size;
			unsigned char *current_ptr = server->current_frame->get_rows()[
				pkg->block_y1] +
				pkg->block_x1 * pixel_size;
// Scan block
			pkg->difference1 = plugin->abs_diff(prev_ptr,
				current_ptr,
				row_bytes,
				pkg->block_x2 - pkg->block_x1,
				pkg->block_y2 - pkg->block_y1,
				color_model);
//printf("MotionScanUnit::process_package 2\n");
			server->put_cache(search_x, search_y, pkg->difference1);
		}
	}







	else








// Sub pixel
	{
		int sub_x = pkg->pixel % (OVERSAMPLE * 2 - 1) + 1;
		int sub_y = pkg->pixel / (OVERSAMPLE * 2 - 1) + 1;

		if(plugin->config.horizontal_only)
		{
			sub_y = 0;
		}

		if(plugin->config.vertical_only)
		{
			sub_x = 0;
		}

		int search_x = pkg->scan_x1 + sub_x / OVERSAMPLE;
		int search_y = pkg->scan_y1 + sub_y / OVERSAMPLE;
		sub_x %= OVERSAMPLE;
		sub_y %= OVERSAMPLE;


		unsigned char *prev_ptr = server->previous_frame->get_rows()[
			search_y] +
			search_x * pixel_size;
		unsigned char *current_ptr = server->current_frame->get_rows()[
			pkg->block_y1] +
			pkg->block_x1 * pixel_size;

// With subpixel, there are two ways to compare each position, one by shifting
// the previous frame and two by shifting the current frame.
		pkg->difference1 = plugin->abs_diff_sub(prev_ptr,
			current_ptr,
			row_bytes,
			pkg->block_x2 - pkg->block_x1,
			pkg->block_y2 - pkg->block_y1,
			color_model,
			sub_x,
			sub_y);
		pkg->difference2 = plugin->abs_diff_sub(current_ptr,
			prev_ptr,
			row_bytes,
			pkg->block_x2 - pkg->block_x1,
			pkg->block_y2 - pkg->block_y1,
			color_model,
			sub_x,
			sub_y);
// printf("MotionScanUnit::process_package sub_x=%d sub_y=%d search_x=%d search_y=%d diff1=%lld diff2=%lld\n",
// sub_x,
// sub_y,
// search_x,
// search_y,
// pkg->difference1,
// pkg->difference2);
	}




}










int64_t MotionScanUnit::get_cache(int x, int y)
{
	int64_t result = -1;
	cache_lock->lock("MotionScanUnit::get_cache");
	for(int i = 0; i < cache.total; i++)
	{
		MotionScanCache *ptr = cache.values[i];
		if(ptr->x == x && ptr->y == y)
		{
			result = ptr->difference;
			break;
		}
	}
	cache_lock->unlock();
	return result;
}

void MotionScanUnit::put_cache(int x, int y, int64_t difference)
{
	MotionScanCache *ptr = new MotionScanCache(x, y, difference);
	cache_lock->lock("MotionScanUnit::put_cache");
	cache.append(ptr);
	cache_lock->unlock();
}











MotionScan::MotionScan(MotionMain *plugin, 
	int total_clients,
	int total_packages)
 : LoadServer(
//1, 1 
total_clients, total_packages 
)
{
	this->plugin = plugin;
	cache_lock = new Mutex("MotionScan::cache_lock");
}

MotionScan::~MotionScan()
{
	delete cache_lock;
}


void MotionScan::init_packages()
{
// Set package coords
	for(int i = 0; i < get_total_packages(); i++)
	{
		MotionScanPackage *pkg = (MotionScanPackage*)get_package(i);

		pkg->block_x1 = block_x1;
		pkg->block_x2 = block_x2;
		pkg->block_y1 = block_y1;
		pkg->block_y2 = block_y2;
		pkg->scan_x1 = scan_x1;
		pkg->scan_x2 = scan_x2;
		pkg->scan_y1 = scan_y1;
		pkg->scan_y2 = scan_y2;
		pkg->pixel = (int64_t)i * (int64_t)total_pixels / (int64_t)total_steps;
		pkg->difference1 = 0;
		pkg->difference2 = 0;
		pkg->dx = 0;
		pkg->dy = 0;
		pkg->valid = 1;
	}
}

LoadClient* MotionScan::new_client()
{
	return new MotionScanUnit(this, plugin);
}

LoadPackage* MotionScan::new_package()
{
	return new MotionScanPackage;
}


void MotionScan::scan_frame(VFrame *previous_frame,
	VFrame *current_frame)
{
	this->previous_frame = previous_frame;
	this->current_frame = current_frame;
	subpixel = 0;

	cache.remove_all_objects();


// Single macroblock
	int w = current_frame->get_w();
	int h = current_frame->get_h();

// Initial search parameters
	int scan_w = w * plugin->config.global_range_w / 100;
	int scan_h = h * plugin->config.global_range_h / 100;
	int block_w = w * plugin->config.global_block_w / 100;
	int block_h = h * plugin->config.global_block_h / 100;

// Location of block in previous frame
	block_x1 = (int)(w * plugin->config.block_x / 100 - block_w / 2);
	block_y1 = (int)(h * plugin->config.block_y / 100 - block_h / 2);
	block_x2 = (int)(w * plugin->config.block_x / 100 + block_w / 2);
	block_y2 = (int)(h * plugin->config.block_y / 100 + block_h / 2);

// Offset to location of previous block.  This offset needn't be very accurate
// since it's the offset of the previous image and current image we want.
	if(plugin->config.mode3 == MotionConfig::TRACK_PREVIOUS)
	{
		block_x1 += plugin->total_dx / OVERSAMPLE;
		block_y1 += plugin->total_dy / OVERSAMPLE;
		block_x2 += plugin->total_dx / OVERSAMPLE;
		block_y2 += plugin->total_dy / OVERSAMPLE;
	}

	skip = 0;

	switch(plugin->config.mode2)
	{
// Don't calculate
		case MotionConfig::NO_CALCULATE:
			dx_result = 0;
			dy_result = 0;
			skip = 1;
			break;

		case MotionConfig::LOAD:
		{
// Load result from disk
			char string[BCTEXTLEN];
			sprintf(string, "%s%06d", MOTION_FILE, plugin->get_source_position());
			FILE *input = fopen(string, "r");
			if(input)
			{
				fscanf(input, 
					"%d %d", 
					&dx_result,
					&dy_result);
				fclose(input);
				skip = 1;
			}
			break;
		}

// Scan from scratch
		default:
			skip = 0;
			break;
	}

// Perform scan
	if(!skip)
	{
// Location of block in current frame
		int x_result = block_x1;
		int y_result = block_y1;

// printf("MotionScan::scan_frame 1 %d %d %d %d %d %d %d %d\n",
// block_x1 + block_w / 2,
// block_y1 + block_h / 2,
// block_w,
// block_h,
// block_x1,
// block_y1,
// block_x2,
// block_y2);

		while(1)
		{
			scan_x1 = x_result - scan_w / 2;
			scan_y1 = y_result - scan_h / 2;
			scan_x2 = x_result + scan_w / 2;
			scan_y2 = y_result + scan_h / 2;



// Zero out requested values
			if(plugin->config.horizontal_only)
			{
				scan_y1 = block_y1;
				scan_y2 = block_y1 + 1;
			}
			if(plugin->config.vertical_only)
			{
				scan_x1 = block_x1;
				scan_x2 = block_x1 + 1;
			}

// printf("MotionScan::scan_frame 1 %d %d %d %d %d %d %d %d\n",
// block_x1,
// block_y1,
// block_x2,
// block_y2,
// scan_x1,
// scan_y1,
// scan_x2,
// scan_y2);
// Clamp the block coords before the scan so we get useful scan coords.
			MotionMain::clamp_scan(w, 
				h, 
				&block_x1,
				&block_y1,
				&block_x2,
				&block_y2,
				&scan_x1,
				&scan_y1,
				&scan_x2,
				&scan_y2,
				0);
// printf("MotionScan::scan_frame 1\n    block_x1=%d block_y1=%d block_x2=%d block_y2=%d\n    scan_x1=%d scan_y1=%d scan_x2=%d scan_y2=%d\n    x_result=%d y_result=%d\n", 
// block_x1,
// block_y1,
// block_x2,
// block_y2,
// scan_x1, 
// scan_y1, 
// scan_x2, 
// scan_y2, 
// x_result, 
// y_result);


// Give up if invalid coords.
			if(scan_y2 <= scan_y1 ||
				scan_x2 <= scan_x1 ||
				block_x2 <= block_x1 ||
				block_y2 <= block_y1)
				break;

// For subpixel, the top row and left column are skipped
			if(subpixel)
			{
				if(plugin->config.horizontal_only ||
					plugin->config.vertical_only)
				{
					total_pixels = 4 * OVERSAMPLE * OVERSAMPLE - 4 * OVERSAMPLE;
				}
				else
				{
					total_pixels = 4 * OVERSAMPLE;
				}

				total_steps = total_pixels;

				set_package_count(total_steps);
				process_packages();

// Get least difference
				int64_t min_difference = -1;
				for(int i = 0; i < get_total_packages(); i++)
				{
					MotionScanPackage *pkg = (MotionScanPackage*)get_package(i);
					if(pkg->difference1 < min_difference || min_difference == -1)
					{
						min_difference = pkg->difference1;

						if(plugin->config.vertical_only)
							x_result = scan_x1 * OVERSAMPLE;
						else
							x_result = scan_x1 * OVERSAMPLE + 
								(pkg->pixel % (OVERSAMPLE * 2 - 1)) + 1;
						
						if(plugin->config.horizontal_only)
							y_result = scan_y1 * OVERSAMPLE;
						else
							y_result = scan_y1 * OVERSAMPLE + 
								(pkg->pixel / (OVERSAMPLE * 2 - 1)) + 1;


// Fill in results
						dx_result = block_x1 * OVERSAMPLE - x_result;
						dy_result = block_y1 * OVERSAMPLE - y_result;
					}

					if(pkg->difference2 < min_difference)
					{
						min_difference = pkg->difference2;

						if(plugin->config.vertical_only)
							x_result = scan_x1 * OVERSAMPLE;
						else
							x_result = scan_x2 * OVERSAMPLE -
								((pkg->pixel % (OVERSAMPLE * 2 - 1)) + 1);

						if(plugin->config.horizontal_only)
							y_result = scan_y1 * OVERSAMPLE;
						else
							y_result = scan_y2 * OVERSAMPLE -
								((pkg->pixel / (OVERSAMPLE * 2 - 1)) + 1);

						dx_result = block_x1 * OVERSAMPLE - x_result;
						dy_result = block_y1 * OVERSAMPLE - y_result;
					}
				}

//printf("MotionScan::scan_frame 1 %d %d %d %d\n", block_x1, block_y1, x_result, y_result);
				break;
			}
			else
			{
				total_pixels = (scan_x2 - scan_x1) * (scan_y2 - scan_y1);
				total_steps = MIN(plugin->config.global_positions, total_pixels);

				set_package_count(total_steps);
				process_packages();

// Get least difference
				int64_t min_difference = -1;
				for(int i = 0; i < get_total_packages(); i++)
				{
					MotionScanPackage *pkg = (MotionScanPackage*)get_package(i);
					if(pkg->difference1 < min_difference || min_difference == -1)
					{
						min_difference = pkg->difference1;
						x_result = scan_x1 + (pkg->pixel % (scan_x2 - scan_x1));
						y_result = scan_y1 + (pkg->pixel / (scan_x2 - scan_x1));
						x_result *= OVERSAMPLE;
						y_result *= OVERSAMPLE;
					}
				}

// printf("MotionScan::scan_frame 10 total_steps=%d total_pixels=%d subpixel=%d\n",
// total_steps, 
// total_pixels,
// subpixel);
// 
// printf("	scan w=%d h=%d scan x1=%d y1=%d x2=%d y2=%d\n",
// scan_w,
// scan_h, 
// scan_x1,
// scan_y1,
// scan_x2,
// scan_y2);
// 
// printf("MotionScan::scan_frame 2 block x1=%d y1=%d x2=%d y2=%d result x=%.2f y=%.2f\n", 
// block_x1, 
// block_y1, 
// block_x2,
// block_y2,
// (float)x_result / 4, 
// (float)y_result / 4);


// If a new search is required, rescale results back to pixels.
				if(total_steps >= total_pixels)
				{
// Single pixel accuracy reached.  Now do exhaustive subpixel search.
					if(plugin->config.mode1 == MotionConfig::STABILIZE ||
						plugin->config.mode1 == MotionConfig::TRACK ||
						plugin->config.mode1 == MotionConfig::NOTHING)
					{
						x_result /= OVERSAMPLE;
						y_result /= OVERSAMPLE;
						scan_w = 2;
						scan_h = 2;
						subpixel = 1;
					}
					else
					{
// Fill in results and quit
						dx_result = block_x1 * OVERSAMPLE - x_result;
						dy_result = block_y1 * OVERSAMPLE - y_result;
						break;
					}
				}
				else
// Reduce scan area and try again
				{
					scan_w = (scan_x2 - scan_x1) / 2;
					scan_h = (scan_y2 - scan_y1) / 2;
					x_result /= OVERSAMPLE;
					y_result /= OVERSAMPLE;
				}
			}
		}

		dx_result *= -1;
		dy_result *= -1;

		// Add offsets from the "tracked single frame"
		if (plugin->config.addtrackedframeoffset) {
		  int tf_dx_result, tf_dy_result;
		  char string[BCTEXTLEN];
		  sprintf(string, "%s%06d", MOTION_FILE, plugin->config.track_frame);
		  FILE *input = fopen(string, "r");
		  if(input)
		    {
		      fscanf(input, 
			     "%d %d", 
			     &tf_dx_result,
			     &tf_dy_result);
		      dx_result += tf_dx_result;
		      dy_result += tf_dy_result;
		      fclose(input);
		    }
		}

	}






// Write results
	if(plugin->config.mode2 == MotionConfig::SAVE)
	{
		char string[BCTEXTLEN];
		sprintf(string, 
			"%s%06d", 
			MOTION_FILE, 
			plugin->get_source_position());
		FILE *output = fopen(string, "w");
		if(output)
		{
			fprintf(output, 
				"%d %d\n",
				dx_result,
				dy_result);
			fclose(output);
		}
		else
		{
			perror("MotionScan::scan_frame SAVE 1");
		}
	}

#ifdef DEBUG
printf("MotionScan::scan_frame 10 dx=%.2f dy=%.2f\n", 
(float)this->dx_result / OVERSAMPLE,
(float)this->dy_result / OVERSAMPLE);
#endif
}

















int64_t MotionScan::get_cache(int x, int y)
{
	int64_t result = -1;
	cache_lock->lock("MotionScan::get_cache");
	for(int i = 0; i < cache.total; i++)
	{
		MotionScanCache *ptr = cache.values[i];
		if(ptr->x == x && ptr->y == y)
		{
			result = ptr->difference;
			break;
		}
	}
	cache_lock->unlock();
	return result;
}

void MotionScan::put_cache(int x, int y, int64_t difference)
{
	MotionScanCache *ptr = new MotionScanCache(x, y, difference);
	cache_lock->lock("MotionScan::put_cache");
	cache.append(ptr);
	cache_lock->unlock();
}





MotionScanCache::MotionScanCache(int x, int y, int64_t difference)
{
	this->x = x;
	this->y = y;
	this->difference = difference;
}



