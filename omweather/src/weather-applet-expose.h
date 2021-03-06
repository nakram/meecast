/* vim: set sw=4 ts=4 et: */
/*
 * This file is part of Other Maemo Weather(omweather)
 *
 * Copyright (C) 2006-2009 Vlad Vasiliev
 * Copyright (C) 2006-2009 Pavel Fialko
 * 	for the code
 *        
 * Copyright (C) 2008 Andrew Zhilin
 *		      az@pocketpcrussia.com 
 *	for default icon set (Glance)
 * 
 * Parts of this file are based on:
 * desktop-plugin-example - Example Desktop Plugin with real transparency
 * Copyright (C) 2008  Tommi Saviranta  <wnd@iki.fi>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses>.
 */
/*******************************************************************************/
#ifndef _weather_applet_expose_h
#define _weather_applet_expose_h 1
/*******************************************************************************/
#include "weather-common.h"
#include "weather-home.h"
/*******************************************************************************/
#ifdef OS2008
    gboolean expose_parent(GtkWidget *widget, GdkEventExpose *event);
#endif
#ifdef OS2009
    void omweather_plugin_realize (GtkWidget *widget);
    gboolean omweather_plugin_expose_event(GtkWidget * widget, GdkEventExpose * event);
#endif
/*******************************************************************************/
#endif
