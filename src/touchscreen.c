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
 * \file touchscreen.c
 */

#include <ttstd/touchscreen.h>

/*!
 * \brief Opens touchscreen device
 */
inline int ttstd_OpenTouchscreen(ttstdTS *ts)
{
	ts->x = 0;
	ts->y = 0;
	ts->pressure = 0;
	ts->tsfd = -1;
	ts->tsfd = open(TOUCHSCREEN_DEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (ts->tsfd < 0)
		return -1;

	ioctl(ts->tsfd,TS_SET_RAW_OFF,NULL);
	ts->maxfd = ts->tsfd + 1;
	FD_ZERO(&ts->fdset);
	FD_SET(ts->tsfd, &ts->fdset);

	return 0;
}

/*!
 * \brief Closes touchscreen device
 */
void ttstd_CloseTouchscreen(ttstdTS *ts)
{
  if (ts->tsfd>=0)
    close(ts->tsfd);
}

/*!
 * \brief Updates data in ttstdTS struct
 * \returns Returns 0 if there was a new touchscreen event\n
 * Returns -1 if there was no new event
 */
int ttstd_UpdateTouchscreen(ttstdTS *ts)
{
	int read_len;
	TS_EVENT new_event;

	static int have_previous = 0;
	static TS_EVENT prev_event;

	//ts->x = 0;
	//ts->y = 0;
	ts->pressure = 0;

	if (!have_previous)
	{
		read_len = read(ts->tsfd, &prev_event, sizeof(TS_EVENT));
		if (read_len == sizeof(TS_EVENT))
			have_previous = 1;
	}

	// if we still don't have an event, there are no events pending, and we can just return
	if (!have_previous)
		return -1;

	// We have an event
	memcpy(&new_event, &prev_event,sizeof(TS_EVENT));
	have_previous = 0;

	read_len = read(ts->tsfd, &prev_event, sizeof(TS_EVENT));
	if (read_len == sizeof(TS_EVENT))
		have_previous = 1;

	//iterate through all events
	while (have_previous && (prev_event.pressure != 0) == (new_event.pressure != 0))
	{
		memcpy(&new_event, &prev_event,sizeof(TS_EVENT));
		have_previous = 0;
		read_len = read(ts->tsfd, &prev_event, sizeof(TS_EVENT));
		if (read_len == sizeof(TS_EVENT))
			have_previous = 1;
	}

	//store information in ttstdTS struct
	ts->x = new_event.x;
	ts->y = new_event.y;
	ts->pressure = new_event.pressure;

	return 0;
}
