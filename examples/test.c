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
 * \file test.c
 * \brief just a test application
 * \note should give an example to every ttstd function
 * \details <pre> /  /
 * o O
 *  v
 * I CAN HAS TEST APPZ?
 * I IS PROPURR PROGRAMMAR NOW</pre>
 */

#include <stdio.h>
#include <ttstd/battery.h>
#include <ttstd/framebuffer.h>
#include <ttstd/gps.h>
#include <ttstd/touchscreen.h>

int main(int argc, char** argv)
{
	int tmp; //temporary variable

	//Example for battery functions////////////////////////////
/*	BATTERY_STATUS test;

	tmp = ttstd_UpdateBattery(&test);
	
	printf("ttstd_UpdateBattery returned %d\n",tmp);

	printf("BatteryVoltage: %d\n",test.u16BatteryVoltage);
	printf("ChargeCurrent: %d\n",test.u16ChargeCurrent);
	printf("ChargeStatus: %d\n",test.u8ChargeStatus);
	printf("VoltageSource: %d\n\n",test.u8VoltageSource);
*/	//End Example for battery functions////////////////////////



/*	//Example for framebuffer functions////////////////////////
	ttstdFB test2;
	tmp = ttstd_OpenFramebuffer(&test2);
	
	printf("ttstd_OpenFramebuffer returned %d\n\n",tmp);

	ttstd_PutPixel(&test2,100,100,0xFFFF); //Put 1 white pixel at 100,100

	ttstd_Flush(&test2);

	ttstd_CloseFramebuffer(&test2);
*/	//End Example for framebuffer functions////////////////////



/*	//Example for GPS functions////////////////////////////////
	ttstdGPS test3;
	tmp = ttstd_OpenGPS(&test3,0);

	printf("ttstd_OpenGPS returned %d\n",tmp);

	//fetch 10 lines from gpspipe and parse them
	int tmp2;
	for(tmp2=0;tmp2<10;tmp2++)
	{
		tmp = ttstd_UpdateGPS(&test3);
		printf("%s",test3.buffer);
		printf("ttstd_UpdateGPS returned %d\n",tmp);
	}

	printf("lat,lon: %2.6f,%2.6f - satellites: %d in use %d in view\n\n",test3.lat,test3.lon,test3.info.satinfo.inuse,test3.info.satinfo.inview);
	ttstd_CloseGPS(&test3);
*/	//End Example for GPS functions////////////////////////////



	//Example for touchscreen functions////////////////////////
	ttstdTS test4;

	tmp = ttstd_OpenTouchscreen(&test4);
	printf("ttstd_OpenTouchscreen returned %d\n",tmp);

	tmp = ttstd_UpdateTouchscreen(&test4);
	printf("ttstd_UpdateTouchscreen returned %d\n",tmp);

	printf("Touchscreen x: %d\n", test4.x);
	printf("Touchscreen y: %d\n", test4.y);
	printf("Touchscreen pressure: %d\n\n", test4.pressure);

	ttstd_CloseTouchscreen(&test4);
	//End Example for touchscreen functions////////////////////

	return 0;
}
