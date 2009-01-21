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
 * \file battery.h
 * \brief function for getting battery information
 * \details see kernel-header file barcelona/Barc_Battery.h for more information on the struct
 */

#ifndef TTSTD_BATTERY_H
#define TTSTD_BATTERY_H

#include <fcntl.h>
#include <barcelona/Barc_Battery.h>

#define ttstdBAT BATTERY_STATUS

/*!
 * \brief defines battery device
 * \note On TomTom ONE usually /dev/battery (tested with TTONEv2 and golinux-tt1518115)\n
 * On other TomTom models maybe different
 */
#define BATTERY_DEVICE "/dev/battery"

int ttstd_UpdateBattery(ttstdBAT *bat);

#endif
