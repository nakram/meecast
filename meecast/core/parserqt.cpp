/* vim: set sw=4 ts=4 et: */
/*
 * This file is part of Other Maemo Weather(omweather)
 *
 * Copyright (C) 2006-2011 Vlad Vasiliev
 * Copyright (C) 2006-2011 Pavel Fialko
 * Copyright (C) 2010-2011 Tanya Makova
 *     for the code
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
 * General Public License for more details.
 *
 * You should have received a copy of the GNU weather-config.h General Public
 * License along with this software; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
*/
/*******************************************************************************/


#include "parserqt.h"
////////////////////////////////////////////////////////////////////////////////
namespace Core {
////////////////////////////////////////////////////////////////////////////////
    ParserQt::ParserQt(const std::string& filename, const std::string& schema_filename)
    {
        QXmlSchema schema;
        if (!schema.load(QUrl(":" + QString::fromStdString(schema_filename)))){
            throw("Invalid schema file");
            return;
        }
        if (!schema.isValid()){
            throw("Schema is invalid");
            return;
        }
        QFile file(QString::fromStdString(filename));
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            throw("Invalid source file");
            return;
        }
        QXmlSchemaValidator validator(schema);
        if (!validator.validate(&file, QUrl::fromLocalFile(file.fileName()))){
            //qDebug() << "File " << filename << " is invalid";
            file.close();
            throw("Xml file is invalid");
            return;
        }
        file.close();
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        if (!_doc.setContent((&file))){
            file.close();
            throw("Error set content");
            return;
        }
        file.close();

    }
////////////////////////////////////////////////////////////////////////////////
} // namespace Core
