
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

#include "apatchgui.h"
#include "autoconf.h"
#include "automation.h"
#include "autos.h"
#include "bcwindowbase.h"
#include "cpanel.h"
#include "cwindowgui.h" 
#include "cwindow.h"
#include "edl.h"
#include "edlsession.h"
#include "filexml.h"
#include "gwindow.h"
#include "gwindowgui.h"
#include "keyframe.h"
#include "keyframegui.h"
#include "keyframepopup.h"
#include "language.h"
#include "localsession.h"
#include "maincursor.h"
#include "mainmenu.h"
#include "mainundo.h"
#include "mwindowgui.h"
#include "mwindow.h"
#include "patchbay.h"
#include "patchgui.h" 
#include "track.h"
#include "vpatchgui.h"

KeyframePopup::KeyframePopup(MWindow *mwindow, MWindowGUI *gui)
 : BC_PopupMenu(0, 
		0, 
		0, 
		"", 
		0)
{
	this->mwindow = mwindow;
	this->gui = gui;
	key_hide = 0;
	key_delete = 0;
	key_copy = 0;
	edit = 0;
	tan_smooth=tan_linear=tan_free = 0;
	tangent_mode_displayed = false;
}

KeyframePopup::~KeyframePopup()
{
	if(!tangent_mode_displayed)
	{
		delete tan_smooth;
		delete tan_linear;
		delete tan_free_t;
		delete tan_free  ;
		delete __hline__ ;
	}
}	// if they are currently displayed, the menu class will delete them automatically

void KeyframePopup::create_objects()
{
	add_item(key_hide = new KeyframePopupHide(mwindow, this));
	
    __hline__  = new BC_MenuItem("-");
    tan_smooth = new KeyframePopupTangentMode(mwindow, this, FloatAuto::SMOOTH);
    tan_linear = new KeyframePopupTangentMode(mwindow, this, FloatAuto::LINEAR);
    tan_free_t = new KeyframePopupTangentMode(mwindow, this, FloatAuto::TFREE );
    tan_free   = new KeyframePopupTangentMode(mwindow, this, FloatAuto::FREE  );
}

int KeyframePopup::update(Plugin *plugin, KeyFrame *keyframe)
{
	this->keyframe_plugin = plugin;
	this->keyframe_auto = keyframe;
	this->keyframe_autos = keyframe->autos;
	this->keyframe_automation = 0;
	handle_tangent_mode(0, 0);

// Suspect this routine is only used for plugins so this is never reached
	if(plugin)
	{
		if(!edit) add_item(edit = new KeyframePopupEdit(mwindow, this));
	}
	else
	{
		delete edit;
		edit = 0;
	}
	return 0;
}

int KeyframePopup::update(Automation *automation, 
	Autos *autos, 
	Auto *auto_keyframe)
{
	this->keyframe_plugin = 0;
	this->keyframe_automation = automation;
	this->keyframe_autos = autos;
	this->keyframe_auto = auto_keyframe;

	if(auto_keyframe)
	{
		if(!key_delete) add_item(key_delete = new KeyframePopupDelete(mwindow, this));
		if(!key_copy) add_item(key_copy = new KeyframePopupCopy(mwindow, this));
	}
	else
	{
		if(key_delete) delete key_delete;
		if(key_copy) delete key_copy;
		key_delete = 0;
		key_copy = 0;
	}
	
	if(edit)
	{
		delete edit;
		edit = 0;
	}

	handle_tangent_mode(autos, auto_keyframe);

/* snap to cursor */
	if(keyframe_auto)
	{
		double current_position = mwindow->edl->local_session->get_selectionstart(1);
		double new_position = keyframe_automation->track->from_units(keyframe_auto->position);
		mwindow->edl->local_session->set_selectionstart(new_position);
		mwindow->edl->local_session->set_selectionend(new_position);

		if (current_position != new_position)
		{
			mwindow->edl->local_session->set_selectionstart(new_position);
			mwindow->edl->local_session->set_selectionend(new_position);
			mwindow->gui->lock_window();
			mwindow->gui->update(1, 1, 1, 1, 1, 1, 0);	
			mwindow->gui->unlock_window();
		}
	}
	
	return 0;
}

void KeyframePopup::handle_tangent_mode(Autos *autos, Auto *auto_keyframe)
// determines the type of automation node. if floatauto, adds
// menu entries showing the tangent mode of the node
{
	if(!tangent_mode_displayed && autos && autos->get_type() == Autos::AUTOMATION_TYPE_FLOAT)
	{ // append additional menu entries showing the tangent-mode
		add_item(__hline__);
		add_item(tan_smooth);
		add_item(tan_linear);
		add_item(tan_free_t);
		add_item(tan_free  );
		tangent_mode_displayed = true;
	}
	if(tangent_mode_displayed && (!autos || autos->get_type() != Autos::AUTOMATION_TYPE_FLOAT))
	{ // remove additional menu entries
		remove_item(tan_free  );
		remove_item(tan_free_t);
		remove_item(tan_linear);
		remove_item(tan_smooth);
		remove_item(__hline__ );
		tangent_mode_displayed = false;
	}
	if(tangent_mode_displayed && auto_keyframe)
	{ // set checkmarks to display current mode
		tan_smooth->toggle_mode((FloatAuto*)auto_keyframe);
		tan_linear->toggle_mode((FloatAuto*)auto_keyframe);
		tan_free_t->toggle_mode((FloatAuto*)auto_keyframe);
		tan_free  ->toggle_mode((FloatAuto*)auto_keyframe);
	}
}

KeyframePopupDelete::KeyframePopupDelete(MWindow *mwindow, KeyframePopup *popup)
 : BC_MenuItem(_("Delete keyframe"))
{
	this->mwindow = mwindow;
	this->popup = popup;
}

KeyframePopupDelete::~KeyframePopupDelete()
{
}

int KeyframePopupDelete::handle_event()
{
	delete popup->keyframe_auto;
	popup->keyframe_auto = 0;
	mwindow->save_backup();
	mwindow->undo->update_undo_after(_("delete keyframe"), LOAD_ALL);

	mwindow->gui->update(0,
	        1,      // 1 for incremental drawing.  2 for full refresh
	        0,
	        0,
	        0,
            0,   
            0);
	mwindow->update_plugin_guis();
	mwindow->restart_brender();
	mwindow->sync_parameters(CHANGE_EDL);

	return 1;
}

KeyframePopupHide::KeyframePopupHide(MWindow *mwindow, KeyframePopup *popup)
 : BC_MenuItem(_("Hide keyframe type"))
{
	this->mwindow = mwindow;
	this->popup = popup;
}

int KeyframePopupHide::handle_event()
{
// Get the array index of the curve
	int update_gui = 0;
	if(popup->keyframe_autos)
	{
		if(popup->keyframe_autos->type == Autos::AUTOMATION_TYPE_PLUGIN)
		{
			mwindow->edl->session->auto_conf->plugins = 0;
			update_gui = 1;
		}
		else
		{
			Track *track = popup->keyframe_autos->track;
			if(track)
			{
				Automation *automation = track->automation;
				if(automation)
				{
					for(int i = 0; i < AUTOMATION_TOTAL; i++)
					{
						if(automation->autos[i] == popup->keyframe_autos)
						{
							mwindow->edl->session->auto_conf->autos[i] = 0;
							update_gui = 1;
							break;
						}
					}
				}
			}
		}
	}

	if(update_gui)
	{
		mwindow->gui->update(0,
	        	1,      // 1 for incremental drawing.  2 for full refresh
	        	0,
	        	0,
	        	0,
            	0,   
            	0);
		mwindow->gui->mainmenu->update_toggles(1);
		mwindow->gui->unlock_window();
		mwindow->gwindow->gui->update_toggles(1);
		mwindow->gui->lock_window("KeyframePopupHide::handle_event");
	}

	return 1;
}



KeyframePopupCopy::KeyframePopupCopy(MWindow *mwindow, KeyframePopup *popup)
 : BC_MenuItem(_("Copy"))
{
	this->mwindow = mwindow;
	this->popup = popup;
}

int KeyframePopupCopy::handle_event()
{
/*
	FIXME:
	we want to copy just keyframe under cursor, NOT all keyframes at this frame
	- very hard to do, so this is good approximation for now...
*/
	
// 	if (popup->keyframe_automation)
// 	{
// 		FileXML file;
// 		EDL *edl = mwindow->edl;
// 		Track *track = popup->keyframe_automation->track;
// 		int64_t position = popup->keyframe_auto->position;
// 		AutoConf autoconf;
// // first find out type of our auto
// 		autoconf.set_all(0);
// 		if (popup->keyframe_autos == (Autos *)popup->keyframe_automation->projector_autos)
// 			autoconf.projector = 1;
// 		else if (popup->keyframe_autos == (Autos *)popup->keyframe_automation->pzoom_autos)
// 			autoconf.pzoom = 1;
// 		else if (popup->keyframe_autos == (Autos *)popup->keyframe_automation->camera_autos)
// 			autoconf.camera = 1;
// 		else if (popup->keyframe_autos == (Autos *)popup->keyframe_automation->czoom_autos)
// 			autoconf.czoom = 1;		
// 		else if (popup->keyframe_autos == (Autos *)popup->keyframe_automation->mode_autos)
// 		   	autoconf.mode = 1;
// 		else if (popup->keyframe_autos == (Autos *)popup->keyframe_automation->mask_autos)
// 			autoconf.mask = 1;
// 		else if (popup->keyframe_autos == (Autos *)popup->keyframe_automation->pan_autos)
// 			autoconf.pan = 1;		   
// 		else if (popup->keyframe_autos == (Autos *)popup->keyframe_automation->fade_autos)
// 			autoconf.fade = 1;
// 		else if (popup->keyframe_autos == (Autos *)popup->keyframe_automation->mute_autos)
// 			autoconf.mute = 1;		
// 
// 
// // now create a clipboard
// 		file.tag.set_title("AUTO_CLIPBOARD");
// 		file.tag.set_property("LENGTH", 0);
// 		file.tag.set_property("FRAMERATE", edl->session->frame_rate);
// 		file.tag.set_property("SAMPLERATE", edl->session->sample_rate);
// 		file.append_tag();
// 		file.append_newline();
// 		file.append_newline();
// 
// /*		track->copy_automation(position, 
// 			position, 
// 			&file,
// 			0,
// 			0);
// 			*/
// 		file.tag.set_title("TRACK");
// // Video or audio
// 		track->save_header(&file);
// 		file.append_tag();
// 		file.append_newline();
// 
// 		track->automation->copy(position, 
// 			position, 
// 			&file,
// 			0,
// 			0,
// 			&autoconf);
// 		
// 		
// 		
// 		file.tag.set_title("/TRACK");
// 		file.append_tag();
// 		file.append_newline();
// 		file.append_newline();
// 		file.append_newline();
// 		file.append_newline();
// 
// 
// 
// 		file.tag.set_title("/AUTO_CLIPBOARD");
// 		file.append_tag();
// 		file.append_newline();
// 		file.terminate_string();
// 
// 		mwindow->gui->lock_window();
// 		mwindow->gui->get_clipboard()->to_clipboard(file.string, 
// 			strlen(file.string), 
// 			SECONDARY_SELECTION);
// 		mwindow->gui->unlock_window();
// 
// 	} else

	mwindow->copy_automation();
	return 1;
}


KeyframePopupEdit::KeyframePopupEdit(MWindow *mwindow, KeyframePopup *popup)
 : BC_MenuItem(_("Presets..."))
{
	this->mwindow = mwindow;
	this->popup = popup;
}

int KeyframePopupEdit::handle_event()
{
	mwindow->show_keyframe_gui(popup->keyframe_plugin);
	return 1;
}



KeyframePopupTangentMode::KeyframePopupTangentMode(
	MWindow *mwindow, 
	KeyframePopup *popup, 
	int tangent_mode)
 : BC_MenuItem( get_labeltext(tangent_mode))
{
    this->tangent_mode = tangent_mode;
    this->mwindow = mwindow;
    this->popup = popup;
}

KeyframePopupTangentMode::~KeyframePopupTangentMode() { }


const char* KeyframePopupTangentMode::get_labeltext(int mode)
{
	switch(mode)
	{   case FloatAuto::SMOOTH: return _("smooth curve");
	    case FloatAuto::LINEAR: return _("linear segments");
	    case FloatAuto::TFREE:  return _("tangent edit");
	    case FloatAuto::FREE:   return _("disjoint edit");
	}
	return "misconfigured";
}


void KeyframePopupTangentMode::toggle_mode(FloatAuto *keyframe)
{
	set_checked(tangent_mode == keyframe->tangent_mode);
}


int KeyframePopupTangentMode::handle_event()
{
	if (popup->keyframe_autos && 
	    popup->keyframe_autos->get_type() == Autos::AUTOMATION_TYPE_FLOAT)
	{
		((FloatAuto*)popup->keyframe_auto)->
			change_tangent_mode((FloatAuto::t_mode)tangent_mode);
		
		// if we switched to some "auto" mode, this may imply a
		// real change to parameters, so this needs to be undoable...
		mwindow->save_backup();
		mwindow->undo->update_undo_after(_("change keyframe tangent mode"), LOAD_ALL);
		
		mwindow->gui->update(0, 1, 0,0,0,0,0); // incremental redraw for canvas
		mwindow->cwindow->update(0,0, 1, 0,0); // redraw tool window in compositor
		mwindow->update_plugin_guis();
		mwindow->restart_brender();
		mwindow->sync_parameters(CHANGE_EDL);
	}
	return 1;
}
