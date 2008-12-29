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
 * \file battery.c
 */

#include <ttstd/battery.h>

/*!
 * \brief Filles BATTERY_STATUS struct with Information of current Battery Status
 * \return Returns negative values if BATTERY_DEVICE couldn't be opened
 */
int ttstd_UpdateBattery(BATTERY_STATUS *bat)
{
	int ret;
	ret = open(BATTERY_DEVICE,O_RDONLY|O_NOCTTY);
	if (ret >= 0)
		ioctl(ret, IOR_BATTERY_STATUS, bat);
	return ret;
}
