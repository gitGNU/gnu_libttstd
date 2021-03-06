/*
    This file is part of libttstd.

    libttstd is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libttstd is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libttstd.  If not, see <http://www.gnu.org/licenses/>.

	Copyright (C) 2008,
		Niclas Hoyer
*/

/*!
 * \file gps.h
 * \brief functions for getting lat and lon from NMEA Strings passed by gpspipe
 */

#ifndef TTSTD_GPS_H
#define TTSTD_GPS_H

#include <nmea/nmea.h>
#include <stdio.h>
#include <fcntl.h>

/*!
 * \brief path to gps device
 * \details defines path to GPS FIFO-BUFFER pipe that contains NMEA data
 * \note On TomTom ONE usually /var/run/gpspipe (tested with TTONEv2 and golinux-tt1518115)\n
 * On other TomTom models maybe different
 */
#define GPS_DEVICE "/var/run/gpspipe"

/*!
 * \brief struct containing GPS data
 */
typedef struct _ttstdGPS
{
	FILE *pipe;
    nmeaPARSER parser;
    nmeaINFO info;
    nmeaPOS dpos;
	double lat;
	double lon;
	char buffer[100];
} ttstdGPS;

int ttstd_OpenGPS(ttstdGPS *gps, int mode);
inline void ttstd_CloseGPS(ttstdGPS *gps);
int ttstd_UpdateGPS(ttstdGPS *gps);

#endif
