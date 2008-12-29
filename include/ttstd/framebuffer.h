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
 * \file framebuffer.h
 * \brief framebuffer access functions
 * \note mostly based on HelloWorld example by Gothi\n
 * http://ghotidigital.sourceforge.net/pages/TomTomGoEN.html released under GPL
 */

#ifndef TTSTD_FRAMEBUFFER_H
#define TTSTD_FRAMEBUFFER_H

#include <linux/fb.h>
#include <fcntl.h>
#include <sys/mman.h>

/*!
 * \brief defines battery device
 * \note On TomTom ONE usually /dev/fb (tested with TTONEv2 and golinux-tt1518115)\n
 * On other TomTom models maybe different
 */
#define FRAMEBUFFER_DEVICE "/dev/fb"

/*!
 * \brief struct for framebuffer
 * \details used to store different variables, e.g. screenwidth, -height, Front- and Backbuffer
 */
typedef struct _ttstdFB
{
	int fbfd;
	long int screensize;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	char *fbp;
	char *fbbackp;
} ttstdFB;

int ttstd_OpenFramebuffer(ttstdFB *fb);
inline void ttstd_PutPixel(ttstdFB *fb,int x,int y,unsigned short color);
inline void ttstd_Flush(ttstdFB *fb);

#endif
