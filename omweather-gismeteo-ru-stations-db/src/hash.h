/* vim: set sw=4 ts=4 et: */
/*
 * This file is part of Other Maemo Weather(omweather) - MeeCast
 *
 * Copyright (C) 2006-2012 Vlad Vasilyeu
 * Copyright (C) 2006-2009 Pavel Fialko
 * 	for the code
 *        
 * Copyright (C) 2008 Andrew Zhilin
 *		      az@pocketpcrussia.com 
 *	for default icon set (Glance)
 *
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 * You should have received a copy of the GNU  General Public
 * License along with this software; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
*/
/*******************************************************************************/
#ifndef _hash_h
#define _hash_h 1
/*******************************************************************************/
/*******************************************************************************/
#ifdef GLIB
    GHashTable* hash_description_gismeteo_table_create(void);
    GHashTable* hash_icons_gismeteo_table_create(void);
    gchar * hash_gismeteo_table_find(GHashTable *hash, char *key, gboolean search_short_name);
#endif
#ifdef QT    
#include <QHash>
   QHash<QString, QString> *hash_icons_gismeteo_table_create(void);
   QHash<QString, QString> *hash_description_gismeteo_table_create(void);
   QString hash_gismeteo_icon_table_find(QHash<QString, QString> *hash, char *key);
   QString hash_gismeteo_description_table_find(QHash<QString, QString> *hash, char *key);
#endif
/*******************************************************************************/
#endif
