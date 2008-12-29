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
 * \file touchscreen.h
 * \brief functions for interfacing the touchscreen
 * \note mostly based on HelloWorld example by Gothi\n
 * http://ghotidigital.sourceforge.net/pages/TomTomGoEN.html released under GPL
 */

#ifndef TTSTD_TOUCHSCREEN_H
#define TTSTD_TOUCHSCREEN_H

#include <barcelona/Barc_ts.h>
#include <stdio.h>
#include <fcntl.h>

/*!
 * \brief defines touchscreen device
 * \note On TomTom ONE usually /dev/ts (tested with TTONEv2 and golinux-tt1518115)\n
 * On other TomTom models maybe different
 */
#define TOUCHSCREEN_DEVICE "/dev/ts"

/*!
 * \brief struct containing touchscreen data
 */
typedef struct _ttstdTS
{
	int tsfd;
	int maxfd;
	fd_set fdset;
	int x;
	int y;
	int pressure;
} ttstdTS;

int ttstd_OpenTouchscreen(ttstdTS *ts);
void ttstd_CloseTouchscreen(ttstdTS *ts);
int ttstd_UpdateTouchscreen(ttstdTS *ts);

#endif
