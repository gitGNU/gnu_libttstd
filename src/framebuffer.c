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

	heavily based on HelloGhoti (Hello World example)
	http://ghotidigital.sourceforge.net/pages/TomTomGoEN.html
	Copyright by Frederik De Kegel - ghoti.be

	Copyright (C) 2008,
		Niclas Hoyer
*/

/*!
 * \file framebuffer.c
 */

#include <ttstd/framebuffer.h>

/*!
 * \brief opens framebuffer device
 * \return 0: no errors\n
 * -1: error opening framebuffer device\n
 * -2: error in reading fixed information by ioctl call\n
 * -3: error in reading variable information by ioctl call\n
 * -4: failed to map the framebuffer to memory
 */
int ttstd_OpenFramebuffer(ttstdFB *fb)
{
	fb->fbfd = open(FRAMEBUFFER_DEVICE, O_RDWR);

  	if (!fb->fbfd) 
		return -1;

	if (ioctl(fb->fbfd, FBIOGET_FSCREENINFO, &fb->finfo)) 
		return -2;

	// Get variable screen information
	if (ioctl(fb->fbfd, FBIOGET_VSCREENINFO, &fb->vinfo)) 
		return -3;

	//printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel );

	// Figure out the size of the screen in bytes
	fb->screensize = fb->vinfo.xres * fb->vinfo.yres * fb->vinfo.bits_per_pixel / 8;

	// Map the device to memory
	fb->fbp = (char *)mmap(0, fb->screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb->fbfd, 0);
	if ((int)fb->fbp == -1) 
		return -4;

	fb->fbbackp = (char*)malloc(fb->screensize);
	return 0;
}

/*!
 * \brief Puts a Pixel on the Framebuffer
 */
inline void ttstd_PutPixel(ttstdFB *fb,int x, int y, unsigned short color)
{
  unsigned short *ptr  = (unsigned short*)(fb->fbbackp+y*((fb->vinfo.xres*fb->vinfo.bits_per_pixel)/8));
  ptr+=x;
  *ptr = color;
}

/*!
 * \brief Flips the BackBuffer
 * \details Copies the BackBuffer (fbbackp) to the FrontBuffer (fbp)
 */
inline void ttstd_Flush(ttstdFB *fb)
{
  memcpy(fb->fbp,fb->fbbackp,fb->screensize);
}

/*!
 * \brief closes the framebuffer
*/
void ttstd_CloseFramebuffer(ttstdFB *fb)
{
	if (fb->fbfd > 0)
	{
		munmap(fb->fbp, fb->screensize);
		close(fb->fbfd);
	}
	if (fb->fbbackp) free(fb->fbbackp);
	fb->fbfd = -1;
}
