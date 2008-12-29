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
 * \file gps.c
 */

#include <ttstd/gps.h>

/*!
 * \brief Opens gpspipe and initialisizes nmea parser
 * \details first inits gpsinfo struct and then initialisizes nmea parser. 
 * The GPS FIFO is then opened and if mode is set to 1 the pipe is set in 
 * nonblocking mode, meaning that ttstd_UpdateGPS doesn't wait until new
 * data is on the FIFO and immediately returns 1
 * \return returns -1 if opening of the gpspipe failed
 */
int ttstd_OpenGPS(ttstdGPS *gps, int mode)
{
    nmea_zero_INFO(&gps->info);
    nmea_parser_init(&gps->parser);

	gps->pipe = fopen(GPS_DEVICE, "r");
	if (gps->pipe == NULL)
		return -1;

	if (mode>0)
	{
		//nonblocking mode
		int fd = fileno(gps->pipe);
		int flags = fcntl(fd, F_GETFL, 0);
		flags |= O_NONBLOCK;
		fcntl(fd, F_SETFL, flags);
	}

	return 0;
}

/*!
 * \brief Closes GPS pipe
 */
inline void ttstd_CloseGPS(ttstdGPS *gps)
{
	fclose(gps->pipe);
}

/*!
 * \brief Updates data in GPS struct
 * \details fetches one line from the GPS FIFO and parses them with
 * the help of nmealib.
 * \return 0: a new line has been parsed\n
 * -1: there was no new line in the FIFO
 */
int ttstd_UpdateGPS(ttstdGPS *gps)
{
	if(fgets(gps->buffer,100,gps->pipe)!=NULL)
	{
		nmea_parse(&gps->parser, gps->buffer, 100, &gps->info);
		nmea_info2pos(&gps->info,&gps->dpos);

		gps->lat = nmea_radian2degree(gps->dpos.lat);
		gps->lon = nmea_radian2degree(gps->dpos.lon);

		return 0;
	}
	return -1;
}
