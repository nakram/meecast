/* vim: set sw=4 ts=4 et: */
/*
 * This file is part of Other Maemo Weather(omweather)
 *
 * Copyright (C) 2006-2011 Vlad Vasiliev
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

#include "configqml.h"
#include "stationmodel.h"

#include "omweatherintf.h"
#include "omweatheradaptor.h"

#define DATA_XSD_PATH "/opt/com.meecast.omweather/share/xsd/data.xsd"

ConfigQml::ConfigQml() : QObject() {    
    try {
        Core::Config(Core::AbstractConfig::getConfigPath()+"config.xml",
					Core::AbstractConfig::prefix+Core::AbstractConfig::schemaPath+"config.xsd");

    }catch (const std::string &str){
        Core::Config();
        ConfigQml::Config::saveConfig();
    }
    catch (const char *str){
        Core::Config();
        ConfigQml::Config::saveConfig();
    }
    
    db = new Core::DatabaseSqlite("");
    stationlist = new Core::StationsList;
    *stationlist = ConfigQml::Config::stationsList();

    new OmweatherAdaptor(this);
    QDBusConnection::sessionBus().registerObject("/", this);

    com::meecast::omweather *iface;
    iface = new com::meecast::omweather(QString(), QString(), QDBusConnection::sessionBus(), this);
    //QDBusConnection::sessionBus().connect(QString(), QString(), "com.meecast.omweather", "configChange", this, SLOT(configChangeSlot()));

    temperature_list << "C" << "F";
    update_list << "2 hour" << "1 hour" << "30 min" << "10 min" << "never";
    wind_list << "m/s" << "km/h" << "mi/h";

    Dirent *dp = 0;
    DIR *dir_fd = opendir((Core::AbstractConfig::prefix+Core::AbstractConfig::iconsPath).c_str());
    if(dir_fd){
        while((dp = readdir(dir_fd))){
            std::string name = dp->d_name;
            if(name == "." || name == "..")
                continue;
            if(dp->d_type == DT_DIR && name[0] != '.'){
                try{
                    icon_list << QString::fromStdString(name);
                }
                catch(std::string& err){
                    std::cerr << "error " << err << std::endl;
                    continue;
                }
                catch(const char *err){
                    std::cerr << "error " << err << std::endl;
                    continue;
                }
            }
        }
        closedir(dir_fd);
    }
    
}
ConfigQml::~ConfigQml(){
    delete db;
    delete stationlist;
}
/*
void
ConfigQml::configChangeSlot()
{
    //makeQmlData(false);
    //emit reload();
    QString c = "mi/h";
    ConfigQml::Config::WindSpeedUnit(c.toStdString());
    ConfigQml::Config::saveConfig();
}*/

QStringList
ConfigQml::icons()
{
    return icon_list;
}

int
ConfigQml::iconSet(){
    return icon_list.indexOf(ConfigQml::Config::iconSet().c_str());
}
void
ConfigQml::iconSet(QString c){
    ConfigQml::Config::iconSet(c.toStdString());
    saveConfig();
}
QStringList
ConfigQml::UpdatePeriods()
{
    return update_list;
}

void
ConfigQml::UpdatePeriod(QString str){
    int period = INT_MAX;
    if (str == "2 hour")
        period = 2*60*60;
    else if (str == "1 hour")
        period = 60*60;
    else if (str == "30 min")
        period = 30*60;
    else if (str == "10 min")
        period = 10*60;
    else if (str == "never")
        period = INT_MAX;
    ConfigQml::Config::UpdatePeriod(period);
    saveConfig();
}
int
ConfigQml::UpdatePeriod(){
    int val = ConfigQml::Config::UpdatePeriod();
    QString res;
    if (val == 2*60*60)
        res = "2 hour";
    else if (val == 60*60)
        res = "1 hour";
    else if (val == 30*60)
        res = "30 min";
    else if (val == 10*60)
        res = "10 min";
    else if (val == INT_MAX)
        res = "never";
    return update_list.indexOf(res);

}
void
ConfigQml::UpdateConnect(bool uc)
{
    ConfigQml::Config::UpdateConnect(uc);
    saveConfig();
}
bool
ConfigQml::UpdateConnect()
{
    return ConfigQml::Config::UpdateConnect();
}
QStringList
ConfigQml::TemperatureUnits()
{
    return temperature_list;
}
int
ConfigQml::TemperatureUnit()
{
    return temperature_list.indexOf(ConfigQml::Config::TemperatureUnit().c_str());
}
void
ConfigQml::TemperatureUnit(QString c)
{
    ConfigQml::Config::TemperatureUnit(c.toStdString());
    saveConfig();
}
QStringList
ConfigQml::WindSpeedUnits()
{
    return wind_list;
}
int
ConfigQml::WindSpeedUnit()
{
    return wind_list.indexOf(ConfigQml::Config::WindSpeedUnit().c_str());
}
void
ConfigQml::WindSpeedUnit(QString c)
{
    ConfigQml::Config::WindSpeedUnit(c.toStdString());
    saveConfig();
}

QList<QObject*>
ConfigQml::Stations()
{
    QList<QObject*> st;
    for (unsigned int i=0; i<stationlist->size(); i++){
        st.append(new StationModel(QString::fromStdString(stationlist->at(i)->name()), i));
    }

    return st;
}
int
ConfigQml::StationsCount()
{
    return stationlist->size();
}

QStringList
ConfigQml::Sources()
{
    std::string path(Core::AbstractConfig::prefix);
    path += Core::AbstractConfig::sourcesPath;
    Core::SourceList *sourcelist = new Core::SourceList(path);
    QStringList l;
    for (unsigned int i=0; i<sourcelist->size(); i++){
        l << QString::fromStdString(sourcelist->at(i)->name());
    }
    return l;
}
QStringList
ConfigQml::Countries(QString source, bool isKeys)
{
    QStringList l;
    std::string path(Core::AbstractConfig::prefix);
    path += Core::AbstractConfig::sharePath;
    path += "db/";

    if (source == "") return l;
    QString filename(source);
    filename.append(".db");
    filename.prepend(path.c_str());
    if (!this->db) {
        this->db->set_databasename(filename.toStdString());
    }else {
        this->db->set_databasename(filename.toStdString());

    }

    if (!this->db->open_database()){
        l << "error open db";
        return l;
    }

    Core::listdata * list = db->create_countries_list();

    Core::listdata::iterator cur;

    if (!list)
        return l;
    if (isKeys) l << "0";
    else l << "";
    for (cur=list->begin(); cur<list->end(); cur++)
        if (isKeys) {
            l << QString::fromStdString((*cur).first);
        }else {
            l << QString::fromStdString((*cur).second);
        }

    return l;
}
QStringList
ConfigQml::Regions(QString country, bool isKeys)
{
    QStringList l;

    Core::listdata * list = db->create_region_list(country.toInt());

    if (list->size() == 0) return l;
    Core::listdata::iterator cur;
    for (cur=list->begin(); cur<list->end(); cur++)
        if (isKeys) l << QString::fromStdString((*cur).first);
        else l << QString::fromStdString((*cur).second);
    return l;
}
QStringList
ConfigQml::Cities(QString region, bool isKeys)
{
    QStringList l;
    Core::listdata * list = db->create_stations_list(region.toInt());

    if (list->size() == 0) return l;
    Core::listdata::iterator cur;
    if (isKeys) l << "0";
    else l << "";
    for (cur=list->begin(); cur<list->end(); cur++)
        if (isKeys) l << QString::fromStdString((*cur).first);
        else l << QString::fromStdString((*cur).second);
    return l;
}

void
ConfigQml::saveStation(QString city_id, QString city_name, QString region, QString country, QString source, int source_id)
{
    Core::Station *station;
    std::string code = city_id.toStdString();

    std::string path(Core::AbstractConfig::prefix);
    path += Core::AbstractConfig::sourcesPath;
    Core::SourceList *sourcelist = new Core::SourceList(path);

    std::string url_template = sourcelist->at(source_id)->url_template();

    char forecast_url[4096];
    snprintf(forecast_url, sizeof(forecast_url)-1, url_template.c_str(), code.c_str());
    station = new Core::Station(
                source.toStdString(),
                code,
                city_name.toStdString(),
                country.toStdString(),
                region.toStdString(),
                forecast_url);
    std::string filename(Core::AbstractConfig::getConfigPath());
    filename += source.toStdString();
    filename += "_";
    filename += code;
    station->fileName(filename);
    station->converter(sourcelist->at(source_id)->binary());

    stationlist->push_back(station);
    ConfigQml::Config::stationsList(*stationlist);
    saveConfig();
}
void
ConfigQml::removeStation(int index)
{
    stationlist->erase(stationlist->begin()+index);
    ConfigQml::Config::stationsList(*stationlist);
    saveConfig();
}

void
ConfigQml::saveConfig()
{
    ConfigQml::Config::saveConfig();
    emit configChange();
    //emit change();

}
