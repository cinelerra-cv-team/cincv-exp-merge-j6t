
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

#include "bcsignals.h"
#include "clip.h"
#include "cwindowgui.h"
#include "bluedottheme.h"
#include "edl.h"
#include "edlsession.h"
#include "mainmenu.h"
#include "mainsession.h"
#include "mbuttons.h"
#include "meterpanel.h"
#include "mwindow.h"
#include "mwindowgui.h"
#include "new.h"
#include "patchbay.h"
#include "preferencesthread.h"
#include "recordgui.h"
#include "recordmonitor.h"
#include "setformat.h"
#include "statusbar.h"
#include "timebar.h"
#include "trackcanvas.h"
#include "vframe.h"
#include "vwindowgui.h"
#include "zoombar.h"


#define BGREY	0xc0c0e0		//MEGEY with a shade of blue
#define DDBLUE	0x000050		//Dark blue with the shade of grey


PluginClient* new_plugin(PluginServer *server)
{
	return new BlueDotThemeMain(server);
}







BlueDotThemeMain::BlueDotThemeMain(PluginServer *server)
 : PluginTClient(server)
{
}

BlueDotThemeMain::~BlueDotThemeMain()
{
}

const char* BlueDotThemeMain::plugin_title()
{
	return "Blue Dot";
}

Theme* BlueDotThemeMain::new_theme()
{
	theme = new BlueDotTheme;
	extern unsigned char _binary_bluedottheme_data_start[];
	theme->set_data(_binary_bluedottheme_data_start);
	return theme;
}








BlueDotTheme::BlueDotTheme()
 : Theme()
{
}

BlueDotTheme::~BlueDotTheme()
{
}

void BlueDotTheme::initialize()
{
	BC_Resources *resources = BC_WindowBase::get_resources();

//	about_bg = new_image("about_bg.png");


	// COPIED FROM DEFAULT THEME 1>>
	resources->text_default = 0x000000;
	resources->text_background = 0xffffff;
		//listbox borders
	resources->text_border1 = 0x4a484a; // (top outer)
	resources->text_border2 = 0x000000; // (top inner)
	resources->text_border3 = 0xacaeac; // (bottom inner)
	resources->text_border4 = 0xffffff; // (bottom outer)
	resources->text_inactive_highlight = 0xacacac;
	resources->text_highlight = BGREY;
	// COPIED FROM DEFAULT THEME <<1

	resources->bg_color = FGGREY;			//bg of windows (where no pics...
	// COPIED FROM DEFAULT THEME 2>>
	resources->default_text_color = 0x000000;
	resources->menu_title_text    = 0x000000;
	resources->popup_title_text   = 0x000000;
	// COPIED FROM DEFAULT THEME <<2
	resources->menu_item_text = BLACK;

	// COPIED FROM DEFAULT THEME 3>>
	resources->generic_button_margin = 15;		//Length of buttons and color tabs
	resources->pot_needle_color = resources->text_default;
	resources->pot_offset = 0;
	resources->progress_text = resources->text_default;
	// COPIED FROM DEFAULT THEME <<3
	resources->meter_font = SMALLFONT;  //Specific to BD
	resources->meter_font_color = BLACK;
	resources->meter_title_w = 20;  //Specific to BD
	resources->meter_3d = 0;   //Specific to BD

	resources->menu_light = FTGREY; 	//menu
	resources->menu_highlighted = BGREY;		//NMBLUE
	resources->menu_down = BGREY;
	resources->menu_up = FGGREY;
	resources->menu_shadow = FTGREY;

	// MIHA: COPIED FROM DEFAULT THEME M1>>
	resources->popupmenu_margin = 10;          // ugly
	resources->popupmenu_triangle_margin = 15; // ugly
	// MIHA: COPIED FROM DEFAULT THEME M1<<


	// COPIED FROM DEFAULT THEME 4>>
	resources->listbox_title_color = 0x000000;

	resources->listbox_title_margin = 0;
	resources->listbox_title_hotspot = 5;  // No. of pixels around the borders to allow dragging
	resources->listbox_border1 = 0x4a484a; // (top outer)
	resources->listbox_border2 = 0x000000; // (top inner)
	resources->listbox_border3 = 0xffe200; // (bottom inner)
	resources->listbox_border4 = 0xffffff; // (bottom outer)
	resources->listbox_highlighted = 0xeee6ee;
	resources->listbox_inactive = 0xffffffff; // (background)
	resources->listbox_bg = new_image("list_bg.png"); //NOT COPIED!
	resources->listbox_text = 0x000000;
	resources->listbox_selected = BGREY;

	resources->dirbox_margin = 50;
	resources->filebox_margin = 101;
	resources->file_color = 0x000000;
	resources->directory_color = DKBLUE;
	// COPIED FROM DEFAULT THEME <<4
	resources->menu_highlighted_fontcolor = DDBLUE;    //Specific to BD


//There are differences here, but we won't change until the end.	
//Specific to BD
	resources->filebox_icons_images = new_image_set(3,
		"file_icons_up.png",
		"file_icons_uphi.png",
		"file_icons_dn.png");

	resources->filebox_text_images = new_image_set(3,
		"file_text_up.png",
		"file_text_uphi.png",
		"file_text_dn.png");

	resources->filebox_newfolder_images = new_image_set(3,
		"file_newfolder_up.png",
		"file_newfolder_uphi.png",
		"file_newfolder_dn.png");

	resources->filebox_updir_images = new_image_set(3,
		"file_updir_up.png",
		"file_updir_uphi.png",
		"file_updir_dn.png");

	resources->filebox_delete_images = new_image_set(3,
		"file_delete_up.png",
		"file_delete_uphi.png",
		"file_delete_dn.png");

	resources->filebox_reload_images = new_image_set(3,
		"file_reload_up.png",
		"file_reload_uphi.png",
		"file_reload_dn.png");


	resources->filebox_descend_images = new_image_set(3,
		"file_openfolder_up.png",
		"file_openfolder_uphi.png", 
		"file_openfolder_dn.png");
//Specific to BD

	resources->usethis_button_images = 
		resources->ok_images = new_button("ok.png",
		"generic_up.png", 
		"generic_hi.png", 
		"generic_dn.png");

	new_button("ok.png",
		"generic_up.png", 
		"generic_hi.png", 
		"generic_dn.png",
		"new_ok_images");

	resources->cancel_images = new_button("cancel.png",
		"generic_up.png", 
		"generic_hi.png", 
		"generic_dn.png");

	new_button("cancel.png",
		"generic_up.png", 
		"generic_hi.png", 
		"generic_dn.png",
		"new_cancel_images");

	resources->bar_data = new_image("bar", "bar.png");


	resources->min_menu_w = 0;
	resources->menu_popup_bg = 0;  // if (0) use menu_light, menu_up, menu_shadow
	resources->menu_item_bg = 0;   // if (0) use menu_light, menu_highlighted, menu_down, menu_shadow
	resources->menu_bar_bg = 0;    // if (0) use menu_light, menu_shadow, and height of MEDIUMFONT + 8
	resources->menu_title_bg =  0; // if (0) use menu_light, menu_highlighted, menu_down, menu_shadow


	resources->popupmenu_images = 0; // if (0) get_resources()->use generic_button_images

	resources->toggle_highlight_bg = 0; // if (0) "Draw a plain box" as per bctoggle.C

	resources->generic_button_images = new_image_set(3, 
			"generic_up.png", 
			"generic_hi.png", 
			"generic_dn.png");
	resources->horizontal_slider_data = new_image_set(6,
			"hslider_fg_up.png",
			"hslider_fg_hi.png",
			"hslider_fg_dn.png",
			"hslider_bg_up.png",
			"hslider_bg_hi.png",
			"hslider_bg_dn.png");
	resources->vertical_slider_data = new_image_set(6,
			"vertical_slider_fg_up.png",
			"vertical_slider_fg_hi.png",
			"vertical_slider_fg_dn.png",
			"vertical_slider_bg_up.png",
			"vertical_slider_bg_hi.png",
			"vertical_slider_bg_dn.png");
	resources->progress_images = new_image_set(2,
			"progress_bg.png",
			"progress_hi.png");
	resources->tumble_data = new_image_set(4,
		"tumble_up.png",
		"tumble_hi.png",
		"tumble_bottom.png",
		"tumble_top.png");
	resources->listbox_button = new_image_set(4,
		"listbox_button_up.png",
		"listbox_button_hi.png",
		"listbox_button_dn.png",
		"listbox_button_disabled.png"); // probably need to make this for the suv theme
	resources->listbox_column = new_image_set(3,
		"column_up.png",
		"column_hi.png",
		"column_dn.png");
	resources->listbox_expand = new_image_set(5,
		"listbox_expandup.png",
		"listbox_expanduphi.png",
		"listbox_expandchecked.png",
		"listbox_expanddn.png",
		"listbox_expandcheckedhi.png");
	resources->listbox_up = new_image("listbox_up.png");
	resources->listbox_dn = new_image("listbox_dn.png");
	resources->pan_data = new_image_set(7,
			"pan_up.png", 
			"pan_hi.png", 
			"pan_popup.png", 
			"pan_channel.png", 
			"pan_stick.png", 
			"pan_channel_small.png", 
			"pan_stick_small.png");
	resources->pan_text_color = WHITE;

	resources->pot_images = new_image_set(3,
		"pot_up.png",
		"pot_hi.png",
		"pot_dn.png");   //Graphic Copied from default. Improve!!

	resources->checkbox_images = new_image_set(5,
		"checkbox_up.png",
		"checkbox_uphi.png",
		"checkbox_checked.png",
		"checkbox_down.png",
		"checkbox_checkedhi.png");

	resources->radial_images = new_image_set(5,
		"radial_up.png",
		"radial_uphi.png",
		"radial_checked.png",
		"radial_down.png",
		"radial_checkedhi.png");

	resources->xmeter_images = new_image_set(6, 
		"xmeter_normal.png",
		"xmeter_green.png",
		"xmeter_red.png",
		"xmeter_yellow.png",
		"xmeter_normal.png",
		"xmeter_over.png");
	resources->ymeter_images = new_image_set(6, 
		"ymeter_normal.png",
		"ymeter_green.png",
		"ymeter_red.png",
		"ymeter_yellow.png",
		"ymeter_normal.png",
		"ymeter_over.png");

	resources->hscroll_data = new_image_set(10,
			"hscroll_center_up.png",
			"hscroll_center_hi.png",
			"hscroll_center_dn.png",
			"hscroll_bg.png",
			"hscroll_back_up.png",
			"hscroll_back_hi.png",
			"hscroll_back_dn.png",
			"hscroll_fwd_up.png",
			"hscroll_fwd_hi.png",
			"hscroll_fwd_dn.png");

	resources->vscroll_data = new_image_set(10,
			"vscroll_center_up.png",
			"vscroll_center_hi.png",
			"vscroll_center_dn.png",
			"vscroll_bg.png",
			"vscroll_back_up.png",
			"vscroll_back_hi.png",
			"vscroll_back_dn.png",
			"vscroll_fwd_up.png",
			"vscroll_fwd_hi.png",
			"vscroll_fwd_dn.png");

//Graphic Copied from default. Improve!!
//To make this work better, it may be neccessary to replace new_button with new_image_set
	new_button("prevtip.png", "tipbutton_up.png", "tipbutton_hi.png", "tipbutton_dn.png", "prev_tip");
	new_button("nexttip.png", "tipbutton_up.png", "tipbutton_hi.png", "tipbutton_dn.png", "next_tip");
	new_button("closetip.png", "tipbutton_up.png", "tipbutton_hi.png", "tipbutton_dn.png", "close_tip");
	new_button("swap_extents.png",
		"editpanel_up.png",
		"editpanel_hi.png",
		"editpanel_dn.png",
		"swap_extents");
//swap_extents.png not copied

// Record windows
	rgui_batch = new_image("recordgui_batch.png");
	rgui_controls = new_image("recordgui_controls.png");
	rgui_list = new_image("recordgui_list.png");
	rmonitor_panel = new_image("recordmonitor_panel.png");
	rmonitor_meters = new_image("recordmonitor_meters.png");


//COPY START >>
	preferences_category_overlap = 0;
	preferencescategory_x = 5;
	preferencescategory_y = 5;
	preferencestitle_x = 5;
	preferencestitle_y = 10;
	preferencesoptions_x = 5;
	preferencesoptions_y = 0;
//COPY END<<

// MWindow
//COPY START >>
	message_normal = resources->text_default;
	audio_color = BLACK;
	mtransport_margin = 11;
	toggle_margin = 11;
//COPY END >>

	new_image("mbutton_left","mbutton_left.png");
	new_image("mbutton_right","mbutton_right.png");
	new_image("timebar_bg", "timebar_bg.png");
	new_image("timebar_brender", "timebar_brender.png");
	new_image("clock_bg", "mclock.png");
	new_image("patchbay_bg", "patchbay_bg.png");
	new_image("tracks_bg","tracks_bg.png");
	new_image("zoombar_left","zoombar_left.png");
	new_image("zoombar_right","zoombar_right.png");
	new_image("statusbar_left","statusbar_left.png");
	new_image("statusbar_right","statusbar_right.png");

	//Here an improvement may be needed
	new_image_set("zoombar_menu", 3, "generic_up.png", "generic_hi.png", "generic_dn.png");
	new_image_set("zoombar_tumbler", 4, "tumble_up.png", "tumble_hi.png", "tumble_bottom.png", "tumble_top.png");

//Graphic Copied from default. Improve!!	
	new_image_set("mode_popup", 3, "generic_up.png", "generic_hi.png", "generic_dn.png");
	new_image("mode_add", "mode_add.png");
	new_image("mode_divide", "mode_divide.png");
	new_image("mode_multiply", "mode_multiply.png");
	new_image("mode_normal", "mode_normal.png");
	new_image("mode_replace", "mode_replace.png");
	new_image("mode_subtract", "mode_subtract.png");
	new_image("mode_max", "mode_max.png");

//Graphic Copied from default. Improve!!	
	new_toggle("plugin_on.png", 
		"pluginbutton_hi.png", 
		"pluginbutton_hi.png", 
		"pluginbutton_select.png", 
		"pluginbutton_dn.png", 
		"pluginbutton_selecthi.png", 
		"plugin_on");

//Graphic Copied from default. Improve!!
	new_toggle("plugin_show.png", 
		"plugin_show.png", 
		"pluginbutton_hi.png", 
		"pluginbutton_select.png", 
		"pluginbutton_dn.png", 
		"pluginbutton_selecthi.png", 
		"plugin_show");

// CWindow
	new_image("cpanel_bg", "cpanel_bg.png");
	new_image("cbuttons_left", "cbuttons_left.png");
	new_image("cbuttons_right", "cbuttons_right.png");
	new_image("cmeter_bg", "cmeter_bg.png");

// VWindow
	new_image("vbuttons_left", "vbuttons_left.png");
	new_image("vbuttons_right","vbuttons_right.png");
	new_image("vmeter_bg","vmeter_bg.png");

	new_image("preferences_bg", "preferences_bg.png");


	new_image("new_bg", "new_bg.png");
	new_image("setformat_bg", "setformat_bg2.png");


//	timebar_view_data = new_image("timebar_view.png");

// x, y of Format dialog box
	setformat_w = 600;
	setformat_h = 560;
	setformat_x1 = 15;
	setformat_x2 = 100;

	setformat_x3 = 315;
	setformat_x4 = 415;
	setformat_y1 = 20;
	setformat_y2 = 85;
	setformat_y3 = 125;
	setformat_margin = 30;
	setformat_channels_x = 25;
	setformat_channels_y = 242;
	setformat_channels_w = 250;
	setformat_channels_h = 250;

	loadfile_pad = 70;
	browse_pad = 20;

//This buttons miss a bit. May need to be improved
	new_image_set("playpatch_data", 
		5,
		"playpatch_up.png",
		"playpatch_hi.png",
		"playpatch_checked.png",
		"playpatch_dn.png",
		"playpatch_checkedhi.png");

	new_image_set("recordpatch_data", 
		5,
		"recordpatch_up.png",
		"recordpatch_hi.png",
		"recordpatch_checked.png",
		"recordpatch_dn.png",
		"recordpatch_checkedhi.png");

	new_image_set("gangpatch_data", 
		5,
		"gangpatch_up.png",
		"gangpatch_hi.png",
		"gangpatch_checked.png",
		"gangpatch_dn.png",
		"gangpatch_checkedhi.png");

	new_image_set("drawpatch_data", 
		5,
		"drawpatch_up.png",
		"drawpatch_hi.png",
		"drawpatch_checked.png",
		"drawpatch_dn.png",
		"drawpatch_checkedhi.png");


	new_image_set("mutepatch_data", 
		5,
		"mutepatch_up.png",
		"mutepatch_hi.png",
		"mutepatch_checked.png",
		"mutepatch_dn.png",
		"mutepatch_checkedhi.png");

	new_image_set("expandpatch_data", 
		5,
		"expandpatch_up.png",
		"expandpatch_hi.png",
		"expandpatch_checked.png",
		"expandpatch_dn.png",
		"expandpatch_checkedhi.png");

	build_icons();
	build_bg_data();
	build_overlays();



//Graphic Copied from default. Improve!! -> See outpoint.png/inpoint.png
	out_point = new_image_set(5,
		"out_up.png", 
		"out_hi.png", 
		"out_checked.png", 
		"out_dn.png", 
		"out_checkedhi.png");
	in_point = new_image_set(5,
		"in_up.png", 
		"in_hi.png", 
		"in_checked.png", 
		"in_dn.png", 
		"in_checkedhi.png");

//Graphic Copied from default. Improve!! -> see label.png
	label_toggle = new_image_set(5,
		"labeltoggle_up.png", 
		"labeltoggle_uphi.png", 
		"label_checked.png", 
		"labeltoggle_dn.png", 
		"label_checkedhi.png");


	statusbar_cancel_data = new_image_set(3,
		"statusbar_cancel_up.png",
		"statusbar_cancel_hi.png",
		"statusbar_cancel_dn.png");

//Graphic Copied from default. Improve!! -> make transparent edges
	VFrame *editpanel_up = new_image("editpanel_up.png");
	VFrame *editpanel_hi = new_image("editpanel_hi.png");
	VFrame *editpanel_dn = new_image("editpanel_dn.png");
	VFrame *editpanel_checked = new_image("editpanel_checked.png");
	VFrame *editpanel_checkedhi = new_image("editpanel_checkedhi.png");

//Graphic Copied from default. Improve!!
	new_image("panel_divider", "panel_divider.png");
	new_button("bottom_justify.png", editpanel_up, editpanel_hi, editpanel_dn, "bottom_justify");
	new_button("center_justify.png", editpanel_up, editpanel_hi, editpanel_dn, "center_justify");
	new_button("channel.png", editpanel_up, editpanel_hi, editpanel_dn, "channel");


	new_button("copy.png", editpanel_up, editpanel_hi, editpanel_dn, "copy");
	new_button("cut.png", editpanel_up, editpanel_hi, editpanel_dn, "cut");
	new_button("fit.png", editpanel_up, editpanel_hi, editpanel_dn, "fit");
	new_button("fitautos.png", editpanel_up, editpanel_hi, editpanel_dn, "fitautos");
	new_button("inpoint.png", editpanel_up, editpanel_hi, editpanel_dn, "inbutton");
//	indelete_data = new_button("clearinpoint.png", editpanel_up, editpanel_hi, editpanel_dn);   //Specific to BD 
	new_button("label.png", editpanel_up, editpanel_hi, editpanel_dn, "labelbutton");
	new_button("left_justify.png", editpanel_up, editpanel_hi, editpanel_dn, "left_justify");
	new_button("magnifyS.png", "editpanelW_up.png", "editpanelW_hi.png", "editpanelW_dn.png", "magnify_button");
	new_button("middle_justify.png", editpanel_up, editpanel_hi, editpanel_dn, "middle_justify");
	new_button("nextlabel.png", editpanel_up, editpanel_hi, editpanel_dn, "nextlabel");
	new_button("outpoint.png", editpanel_up, editpanel_hi, editpanel_dn, "outbutton");
//	outdelete_data = new_button("clearoutpoint.png", editpanel_up, editpanel_hi, editpanel_dn);   //Specific to BD
	over_button = new_button("over.png", editpanel_up, editpanel_hi, editpanel_dn);
	overwrite_data = new_button("overwrite.png", editpanel_up, editpanel_hi, editpanel_dn);
	new_button("paste.png", editpanel_up, editpanel_hi, editpanel_dn, "paste");
	new_button("prevlabel.png", editpanel_up, editpanel_hi, editpanel_dn, "prevlabel");
	new_button("redo.png", editpanel_up, editpanel_hi, editpanel_dn, "redo");
	new_button("right_justify.png", editpanel_up, editpanel_hi, editpanel_dn, "right_justify");
	splice_data = new_button("splice.png", editpanel_up, editpanel_hi, editpanel_dn);
	new_button("toclip.png", editpanel_up, editpanel_hi, editpanel_dn, "toclip");
	new_button("goto.png", editpanel_up, editpanel_hi, editpanel_dn, "goto");
	new_button("top_justify.png", editpanel_up, editpanel_hi, editpanel_dn, "top_justify");
	new_button("undo.png", editpanel_up, editpanel_hi, editpanel_dn, "undo");
	new_button("wrench.png", "editpanelW_up.png", "editpanelW_hi.png", "editpanelW_dn.png", "wrench");

//Make transparent borders
#define TRANSPORT_LEFT_IMAGES  "transport_left_up.png", "transport_left_hi.png", "transport_left_dn.png"
#define TRANSPORT_CENTER_IMAGES  "transport_center_up.png", "transport_center_hi.png", "transport_center_dn.png"
#define TRANSPORT_RIGHT_IMAGES  "transport_right_up.png", "transport_right_hi.png", "transport_right_dn.png"
//	build_transport(duplex_data, get_image_data("duplex.png"), transport_bg, 1);    //Specific to BD
	new_button("end.png", TRANSPORT_RIGHT_IMAGES, "end");
	new_button("fastfwd.png",TRANSPORT_CENTER_IMAGES, "fastfwd");
	new_button("fastrev.png",TRANSPORT_CENTER_IMAGES, "fastrev");
	new_button("play.png",TRANSPORT_CENTER_IMAGES, "play");
	new_button("framefwd.png", TRANSPORT_CENTER_IMAGES, "framefwd");
	new_button("framerev.png", TRANSPORT_CENTER_IMAGES, "framerev");
//Graphic Copied from default. Improve!!	
	new_button("pause.png", TRANSPORT_CENTER_IMAGES, "pause");
	new_button("record.png", TRANSPORT_CENTER_IMAGES, "record");
//Graphic Copied from default. Improve!!
	new_button("singleframe.png", TRANSPORT_CENTER_IMAGES, "recframe");
	new_button("reverse.png", TRANSPORT_CENTER_IMAGES, "reverse");
	new_button("rewind.png", TRANSPORT_LEFT_IMAGES, "rewind");
	new_button("stop.png", TRANSPORT_CENTER_IMAGES, "stop");
	new_button("stoprec.png", TRANSPORT_RIGHT_IMAGES, "stoprec");



// CWindow icons
//Graphic Copied from default. Improve!!
	new_image("cwindow_inactive", "cwindow_inactive.png");
	new_image("cwindow_active", "cwindow_active.png");


	new_image_set("batch_render_start",
		3,
		"batchstart_up.png",
		"batchstart_hi.png",
		"batchstart_dn.png");
	new_image_set("batch_render_stop",
		3,
		"batchstop_up.png",
		"batchstop_hi.png",
		"batchstop_dn.png");
	new_image_set("batch_render_cancel",
		3,
		"batchcancel_up.png",
		"batchcancel_hi.png",
		"batchcancel_dn.png");

// MIHA: COPIED FROM DEFAULT THEME M2>>
//Graphic Copied from default. Improve!!
	new_image_set("category_button",
		3,
		"preferencesbutton_dn.png",
		"preferencesbutton_dnhi.png",
		"preferencesbutton_dnlo.png");

	new_image_set("category_button_checked",
		3,
		"preferencesbutton_up.png",
		"preferencesbutton_uphi.png",
		"preferencesbutton_dnlo.png");
// MIHA: COPIED FROM DEFAULT THEME M2<<


	new_toggle("arrow.png", editpanel_up, editpanel_hi, editpanel_checked, editpanel_dn, editpanel_checkedhi, "arrow");
	new_toggle("autokeyframe.png", editpanel_up, editpanel_hi, editpanel_checked, editpanel_dn, editpanel_checkedhi, "autokeyframe");
	new_toggle("ibeam.png", editpanel_up, editpanel_hi, editpanel_checked, editpanel_dn, editpanel_checkedhi, "ibeam");
	new_toggle("show_meters.png", editpanel_up, editpanel_hi, editpanel_checked, editpanel_dn, editpanel_checkedhi, "meters");
	new_toggle("blank30x30.png", 
		   new_image("locklabels_locked.png"),
		   new_image("locklabels_lockedhi.png"),
		   new_image("locklabels_unlocked.png"),
		   new_image("locklabels_dn.png"), // can't have seperate down for each!!??
		   new_image("locklabels_unlockedhi.png"),
		   "locklabels");

// MIHA: COPIED FROM DEFAULT THEME M3>>
//Is that necessary??
	VFrame *cpanel_up = new_image("editpanel_up.png");
	VFrame *cpanel_hi = new_image("editpanel_hi.png");
	VFrame *cpanel_dn = new_image("editpanel_dn.png");
	VFrame *cpanel_checked = new_image("editpanel_checked.png");
	VFrame *cpanel_checkedhi = new_image("editpanel_checkedhi.png");

	new_toggle("camera.png", cpanel_up, cpanel_hi, cpanel_checked, cpanel_dn, cpanel_checkedhi, "camera");
	new_toggle("crop.png", cpanel_up, cpanel_hi, cpanel_checked, cpanel_dn, cpanel_checkedhi, "crop");
	new_toggle("eyedrop.png", cpanel_up, cpanel_hi, cpanel_checked, cpanel_dn, cpanel_checkedhi, "eyedrop");
	new_toggle("magnify.png", cpanel_up, cpanel_hi, cpanel_checked, cpanel_dn, cpanel_checkedhi, "magnify");
	new_toggle("mask.png", cpanel_up, cpanel_hi, cpanel_checked, cpanel_dn, cpanel_checkedhi, "mask");
	new_toggle("ruler.png", cpanel_up, cpanel_hi, cpanel_checked, cpanel_dn, cpanel_checkedhi, "ruler");
	new_toggle("projector.png", cpanel_up, cpanel_hi, cpanel_checked, cpanel_dn, cpanel_checkedhi, "projector");
	new_toggle("protect.png", cpanel_up, cpanel_hi, cpanel_checked, cpanel_dn, cpanel_checkedhi, "protect");
	new_toggle("titlesafe.png", cpanel_up, cpanel_hi, cpanel_checked, cpanel_dn, cpanel_checkedhi, "titlesafe");
	new_toggle("toolwindow.png", cpanel_up, cpanel_hi, cpanel_checked, cpanel_dn, cpanel_checkedhi, "tool");

// MIHA: COPIED FROM DEFAULT THEME M3<<

// Maybe we can live without the commented part
// MIHA: Commented out in favor of default version M4>>
//	new_toggle("camera.png", editpanel_up, editpanel_hi, editpanel_checked, editpanel_dn, editpanel_checkedhi,"camera");
//	new_toggle("crop.png", editpanel_up, editpanel_hi, editpanel_checked, editpanel_dn, editpanel_checkedhi,"crop");
//	new_toggle("eyedrop.png", editpanel_up, editpanel_hi, editpanel_checked, editpanel_dn, editpanel_checkedhi,"eyedrop");
//	new_toggle("magnify.png", editpanel_up, editpanel_hi, editpanel_checked, editpanel_dn, editpanel_checkedhi,"magnify");
//	new_toggle("mask.png", editpanel_up, editpanel_hi, editpanel_checked, editpanel_dn, editpanel_checkedhi,"mask");
//	new_toggle("projector.png", editpanel_up, editpanel_hi, editpanel_checked, editpanel_dn, editpanel_checkedhi,"projector");
//	new_toggle("protect.png", editpanel_up, editpanel_hi, editpanel_checked, editpanel_dn, editpanel_checkedhi,"protect");
//	new_toggle("titlesafe.png", editpanel_up, editpanel_hi, editpanel_checked, editpanel_dn, editpanel_checkedhi,"titlesafe");
//	new_toggle("toolwindow.png", editpanel_up, editpanel_hi, editpanel_checked, editpanel_dn, editpanel_checkedhi,"tool");
// MIHA: Commented out in favor of default version M4<<


	flush_images();

	title_font = MEDIUMFONT;
	title_color = BLACK;
	recordgui_fixed_color = BLACK;
	recordgui_variable_color = RED;
	resources->medium_font = N_("-*-helvetica-medium-r-normal-*-14-*");

	channel_position_color = MEYELLOW;
	resources->meter_title_w = 25;

	// (asset) edit info text color
	edit_font_color = BLACK;

//Specific to BD
	//clock
	resources->draw_clock_background = 0;

//Specific to BD
	//buttons
	resources->button_highlighted = LTGREY;
	resources->button_uphighlighted = DKGREY;
	resources->button_light = WHITE;   
	resources->button_up = LTGREY;
	resources->button_shadow = DKGREY;
	resources->button_down = MDGREY;

//Specific to BD
	//listbox

	//labels
 	resources->label_images = new_image_set(5,
  		"radial_up.png", 
  		"radial_uphi.png", 
  		"radial_checked.png", 
  		"radial_down.png", 
  		"radial_checkedhi.png");

	/*	resources->type_to_icon = new_image_set(5,
            "file_folder.png",
	        "file_unknown.png",
          	"file_film.png",
	        "file_sound.png",
	        "file_column.png"); 
   */

//Specific to BD
	resources->audiovideo_color = DKGREY;

//Specific to BD - Copied from Blonde, replace letters
	//clock font
	resources->medium_7segment =  new_image_set(20,
  		"black_0.png", "black_1.png",  "black_2.png",  "black_3.png",  "black_4.png",  "black_5.png",  "black_6.png",  "black_7.png",  "black_8.png",  "black_9.png",  "black_colon.png",    "black_period.png",    "black_a.png",  "black_b.png",  "black_c.png",  "black_d.png",  "black_e.png",  "black_f.png",  "black_space.png",  "black_dash.png");      

//Specific to BD
	//tooltip
	resources->tooltip_bg_color = 0xfff7e3;
}

#define VWINDOW_METER_MARGIN 5


void BlueDotTheme::build_bg_data()
{
// Audio settings
	channel_position_data = new VFrame(get_image_data("channel_position.png"));

// Track bitmaps
	new_image("resource1024", "resource1024.png");
	new_image("resource512", "resource512.png");
	new_image("resource256", "resource256.png");
	new_image("resource128", "resource128.png");
	new_image("resource64", "resource64.png");
	new_image("resource32", "resource32.png");
//Graphic Copied from default. Improve!!
	new_image("plugin_bg_data", "plugin_bg.png");
	new_image("title_bg_data", "title_bg.png");
	new_image("vtimebar_bg_data", "vwindow_timebar.png");
}


//Graphic Copied from default. Improve!!  -- use your imagination
void BlueDotTheme::build_overlays()
{
	keyframe_data = new VFrame(get_image_data("keyframe3.png"));
	camerakeyframe_data = new VFrame(get_image_data("camerakeyframe.png"));
	maskkeyframe_data = new VFrame(get_image_data("maskkeyframe.png"));
	modekeyframe_data = new VFrame(get_image_data("modekeyframe.png"));
	pankeyframe_data = new VFrame(get_image_data("pankeyframe.png"));
	projectorkeyframe_data = new VFrame(get_image_data("projectorkeyframe.png"));
}









void BlueDotTheme::draw_rwindow_bg(RecordGUI *gui)
{
// 	int y;
// 	int margin = 50;
// 	int margin2 = 80;
// 	gui->draw_9segment(recordgui_batch_x - margin,
// 		0,
// 		mwindow->session->rwindow_w - recordgui_status_x + margin,
// 		recordgui_buttons_y,
// 		rgui_batch);
// 	gui->draw_3segmenth(recordgui_options_x - margin2,
// 		recordgui_buttons_y - 5,
// 		mwindow->session->rwindow_w - recordgui_options_x + margin2,
// 		rgui_controls);
// 	y = recordgui_buttons_y - 5 + rgui_controls->get_h();
// 	gui->draw_9segment(0,
// 		y,
// 		mwindow->session->rwindow_w,
// 		mwindow->session->rwindow_h - y,
// 		rgui_list);
}

void BlueDotTheme::draw_rmonitor_bg(RecordMonitorGUI *gui)
{
// 	int margin = 45;
// 	int panel_w = 300;
// 	int x = rmonitor_meter_x - margin;
// 	int w = mwindow->session->rmonitor_w - x;
// 	if(w < rmonitor_meters->get_w()) w = rmonitor_meters->get_w();
// 	gui->clear_box(0, 
// 		0, 
// 		mwindow->session->rmonitor_w, 
// 		mwindow->session->rmonitor_h);
// 	gui->draw_9segment(x,
// 		0,
// 		w,
// 		mwindow->session->rmonitor_h,
// 		rmonitor_meters);
}





//Specific to BD
void BlueDotTheme::draw_mwindow_bg(MWindowGUI *gui)
{
// Button bar (not menu bar)
#define MBUTTONS_RIGHTEDGE 290 + 11 + 2*30 + 11 + 2*30 + 11 + 14*30
	gui->draw_3segmenth(mbuttons_x, 
		mbuttons_y, 
		MBUTTONS_RIGHTEDGE, 
		get_image("mbutton_left"),
		0);
	gui->draw_3segmenth(mbuttons_x + MBUTTONS_RIGHTEDGE, 
		mbuttons_y, 
		mbuttons_w - 500, 
		get_image("mbutton_right"));

// MIHA: COPIED FROM DEFAULT THEME M6>>
	gui->draw_vframe(get_image("panel_divider"),
		mbuttons_x + 290 + 5,
		mbuttons_y - 1);

	gui->draw_vframe(get_image("panel_divider"),
		mbuttons_x + 290 + 11 + 30 * 2 + 5,
		mbuttons_y - 1);

	gui->draw_vframe(get_image("panel_divider"),
		mbuttons_x + 290 + 11 +  30 * 2 + 11 + 30 * 2 + 5,
		mbuttons_y - 1);


// MIHA: COPIED FROM DEFAULT THEME M6<<

//Specific to BD
// Clock (here the background of the clock is drawn)
	gui->draw_3segmenth(0, 
		mbuttons_y + get_image("mbutton_left")->get_h(),
		get_image("patchbay_bg")->get_w(), 
		get_image("clock_bg"));

//Specific to BD
// Patchbay
	gui->draw_3segmentv(patchbay_x, 
		patchbay_y, 
		patchbay_h, 
		get_image("patchbay_bg"));

//patchbay_h + 10, 


//Specific to BD
//Drawing of Track's canvas
	gui->draw_9segment(mcanvas_x, 
		mcanvas_y, 
		mcanvas_w, 
		patchbay_h + 26, 
		get_image("tracks_bg"));
//patchbay_h + 10, 

// Timebar
	gui->draw_3segmenth(mtimebar_x, 
		mtimebar_y, 
		mtimebar_w, 
		get_image("timebar_bg"));

//Specific to BD
// Zoombar
#define ZOOMBAR_CENTER 1100
	gui->draw_3segmenth(mzoom_x, 
		mzoom_y,
		ZOOMBAR_CENTER, 
		get_image("zoombar_left"));
	if(mzoom_w > ZOOMBAR_CENTER)
		gui->draw_3segmenth(mzoom_x + ZOOMBAR_CENTER, 
			mzoom_y, 
			mzoom_w - ZOOMBAR_CENTER, 
			get_image("zoombar_right"));


// Status
	gui->draw_3segmenth(mstatus_x, 
		mstatus_y,
		ZOOMBAR_CENTER, 
		get_image("statusbar_left"));

	if(mstatus_w > ZOOMBAR_CENTER)
	  gui->draw_3segmenth(mstatus_x + ZOOMBAR_CENTER, 
			      mstatus_y,
			      mstatus_w - ZOOMBAR_CENTER, 
			      get_image("statusbar_right"));

}

void BlueDotTheme::draw_cwindow_bg(CWindowGUI *gui)
{
//Specific to BD
	const int button_division = 530;
	gui->draw_3segmentv(0, 0, ccomposite_h, get_image("cpanel_bg"));

	gui->draw_3segmenth(0, ccomposite_h, cstatus_x, get_image("cbuttons_left"));

	if(mwindow->edl->session->cwindow_meter)
	{
		gui->draw_3segmenth(cstatus_x, 
			ccomposite_h, 
			cmeter_x - widget_border - cstatus_x, 
			get_image("cbuttons_right"));
		gui->draw_9segment(cmeter_x - widget_border, 
			0, 
			mwindow->session->cwindow_w - cmeter_x + widget_border, 
			mwindow->session->cwindow_h, 
			get_image("cmeter_bg"));
	}
	else
	{
		gui->draw_3segmenth(cstatus_x, 
			ccomposite_h, 
			cmeter_x - widget_border - cstatus_x + 100, 
			get_image("cbuttons_right"));
	}
}

void BlueDotTheme::draw_vwindow_bg(VWindowGUI *gui)
{
//Specific to BD
	const int button_division = 535;
	gui->draw_3segmenth(0, 
		vcanvas_h, 
		button_division, 
		get_image("vbuttons_left"));
	if(mwindow->edl->session->vwindow_meter)
	{
		gui->draw_3segmenth(button_division, 
			vcanvas_h, 
			vmeter_x - VWINDOW_METER_MARGIN - button_division, 
			get_image("vbuttons_right"));
		gui->draw_9segment(vmeter_x - VWINDOW_METER_MARGIN,
			0,
			mwindow->session->vwindow_w - vmeter_x + VWINDOW_METER_MARGIN, 
			mwindow->session->vwindow_h, 
			get_image("vmeter_bg"));
	}
	else
	{
		gui->draw_3segmenth(button_division, 
			vcanvas_h, 
			vmeter_x - VWINDOW_METER_MARGIN - button_division + 100, 
			get_image("vbuttons_right"));
	}
}

void BlueDotTheme::get_preferences_sizes()
{
}

//Specific to BD
void BlueDotTheme::draw_preferences_bg(PreferencesWindow *gui)
{
	gui->draw_9segment(0, 0, gui->get_w(), gui->get_h() - 40, get_image("preferences_bg"));
}

void BlueDotTheme::get_new_sizes(NewWindow *gui)
{
}

void BlueDotTheme::draw_new_bg(NewWindow *gui)
{
	gui->draw_vframe(get_image("new_bg"), 0, 0);
}

void BlueDotTheme::draw_setformat_bg(SetFormatWindow *gui)
{
	gui->draw_vframe(get_image("setformat_bg"), 0, 0);
}





