/*
    This file is part of ttstd.

    ttstd is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ttstd is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ttstd.  If not, see <http://www.gnu.org/licenses/>.

	Copyright (C) 2008,
		Niclas Hoyer
*/

/*!
 * \file draw.c
 * \brief simple drawing application
 */

#include <stdio.h>
#include <ttstd/battery.h>
#include <ttstd/framebuffer.h>
#include <ttstd/gps.h>
#include <ttstd/touchscreen.h>

int main(int argc, char** argv)
{
	ttstdFB fb;
	ttstdTS ts;
	int tmp;

	ttstd_OpenFramebuffer(&fb);
	ttstd_OpenTouchscreen(&ts);

	do
	{
		tmp = ttstd_UpdateTouchscreen(&ts);
		if (tmp>-1)
		{
			ttstd_Flush(&fb);
			ttstd_PutPixel(&fb,ts.x,ts.y,0xFFFF);
		}

	} while(!((ts.x<15)&&(ts.y<15)&&(tmp==0)));

	ttstd_CloseTouchscreen(&ts);
	ttstd_CloseFramebuffer(&fb);

	return 0;
}
