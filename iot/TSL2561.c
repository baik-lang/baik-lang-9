/**
 * Copyright 2014 Dino Ciuffetti <dino@tuxweb.it>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#include "TSL2561.h"

/**
 * read two bytes from i2c bus getting a 16 bit unsigned integer
 */
static inline uint16_t tsl2561_read16(TSL2561 *sensor, uint8_t reg) {
	uint16_t x;
	
	if(sensor->adapter_fd == -1) { // not opened
		// TODO: choose a valid errno error
		sensor->lasterr = -1;
		return 0;
	}
	
	// ask for reading
	sensor->buf[0] = reg;
	if(write(sensor->adapter_fd, sensor->buf, 1) != 1) {
		sensor->lasterr = errno;
		return -1;
	}
	
	if(read(sensor->adapter_fd, sensor->buf, 2) != 2) {
		sensor->lasterr = errno;
		return 0;
	}
	
	//printf("x1: 0x%0x, x2: 0x%0x\n", sensor->buf[1], sensor->buf[0]);
	x = sensor->buf[1];
	x <<= 8;
	x |= sensor->buf[0];
	
	//printf("test: 0x%02x%02x: 0x%04x\n", sensor->buf[1], sensor->buf[0], x);
	
	return x;
}
/**
 * read one byte from i2c bus getting a 8 bit unsigned integer
 */
static inline uint8_t tsl2561_read8(TSL2561 *sensor, uint8_t reg) {
	uint8_t x;
	
	if(sensor->adapter_fd == -1) { // not opened
		// TODO: choose a valid errno error
		sensor->lasterr = -1;
		return 0;
	}
	
	// ask for reading
	sensor->buf[0] = reg;
	if(write(sensor->adapter_fd, sensor->buf, 1) != 1) {
		sensor->lasterr = errno;
		return -1;
	}
	
	if(read(sensor->adapter_fd, sensor->buf, 1) != 1) {
		sensor->lasterr = errno;
		return 0;
	}
	x = sensor->buf[0];
	
	return x;
}
/**
 * write one byte to i2c bus getting
 */
static inline int tsl2561_write8(TSL2561 *sensor, uint8_t reg, uint32_t byte_value) {
	if(sensor->adapter_fd == -1) { // not opened
		// TODO: choose a valid errno error
		sensor->lasterr = -1;
		return -1;
	}
	
	// we mask with (& 0xFF) to get the last 8 bits from a 32 bit unsigned integer
	sensor->buf[0] = reg;
	sensor->buf[1] = (byte_value & 0xFF );
	if(write(sensor->adapter_fd, sensor->buf, 2) != 2) {
		sensor->lasterr = errno;
		return -1;
	}
	return 0;
}
// TSL2561 Functions (inspired on Adafruit_TSL2561_U.cpp at https://github.com/adafruit/Adafruit_TSL2561)
// wake up TSL2561 by setting the control bit
static inline int TSL2561_ON(TSL2561 *sensor) {
	int rc;
	
	if(sensor->adapter_fd == -1) { // not opened
		// TODO: choose a valid errno error
		sensor->lasterr = -1;
		return -1;
	}
	
	rc = tsl2561_write8(sensor, TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL, TSL2561_CONTROL_POWERON);
	return rc;
}
// turn TSL2561 into power saving mode
static inline int TSL2561_OFF(TSL2561 *sensor) {
	int rc;
	
	if(sensor->adapter_fd == -1) { // not opened
		// TODO: choose a valid errno error
		sensor->lasterr = -1;
		return -1;
	}
	
	rc = tsl2561_write8(sensor, TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL, TSL2561_CONTROL_POWEROFF);
	return rc;
}
// this is a private function that is used to get data from the sensor (infrared + full spectrum including infrared)
static inline int tsl2561_getdata(TSL2561 *sensor, uint16_t *full_spectrum, uint16_t *infrared) {
	TSL2561_ON(sensor);
	// wait for the internal ADC to complete conversion
	switch(sensor->integration_time) {
	case TSL2561_INTEGRATIONTIME_13MS:
		usleep(20000);
		break;
	case TSL2561_INTEGRATIONTIME_101MS:
		usleep(150000);
		break;
	case TSL2561_INTEGRATIONTIME_402MS:
		usleep(450000);
		break;
	}
	//usleep(450000);
	// reads two bytes from channel 0 (full spectrum + infrared)
	//*full_spectrum = wiringPiI2CReadReg16(_fd, TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN0_LOW);
	*full_spectrum = tsl2561_read16(sensor, TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN0_LOW);
	//fprintf(stdout, "got 0x%04X for full spectrum light\n", *full_spectrum);
	
	// reads two bytes from channel 1 (infrared)
	//*infrared = wiringPiI2CReadReg16(_fd, TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN1_LOW);
	*infrared = tsl2561_read16(sensor, TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN1_LOW);
	//fprintf(stdout, "got 0x%04X for ir light\n", *infrared);
	
	// turn the device off to save power
	TSL2561_OFF(sensor);
	
	return 0;
}
/**
 * converts the raw sensor values to the standard SI lux equivalent.
 * returns 0 if the sensor is saturated and the values are unreliable.
 */
/**************************************************************************/
static uint32_t TSL2561_CALCULATE_LUX(TSL2561 *sensor, uint16_t broadband, uint16_t ir) {
	unsigned long chScale;
	unsigned long channel1;
	unsigned long channel0;  
	uint16_t clipThreshold;
	unsigned long ratio1 = 0;
	unsigned long ratio;
	unsigned int b, m;
	unsigned long temp;
	uint32_t lux;
  	
	// Make sure the sensor isn't saturated!
	switch (sensor->integration_time) {
	case TSL2561_INTEGRATIONTIME_13MS:
		clipThreshold = TSL2561_CLIPPING_13MS;
		break;
	case TSL2561_INTEGRATIONTIME_101MS:
		clipThreshold = TSL2561_CLIPPING_101MS;
		break;
	case TSL2561_INTEGRATIONTIME_402MS:
		clipThreshold = TSL2561_CLIPPING_402MS;
		break;
	default:
		clipThreshold = TSL2561_CLIPPING_402MS;
		break;
	}
	
	// return 0 lux if the sensor is saturated
	if ((broadband > clipThreshold) || (ir > clipThreshold)) {
		return 0;
	}
	
	// get the correct scale depending on the intergration time
	switch (sensor->integration_time) {
	case TSL2561_INTEGRATIONTIME_13MS:
		chScale = TSL2561_LUX_CHSCALE_TINT0;
		break;
	case TSL2561_INTEGRATIONTIME_101MS:
		chScale = TSL2561_LUX_CHSCALE_TINT1;
		break;
	case TSL2561_INTEGRATIONTIME_402MS:
		chScale = (1 << TSL2561_LUX_CHSCALE);
		break;
	default: /* No scaling ... integration time = 402ms */
		chScale = (1 << TSL2561_LUX_CHSCALE);
		break;
	}
	
	// scale for gain (1x or 16x)
	if (!sensor->gain) chScale = chScale << 4;
	
	// scale the channel values
	channel0 = (broadband * chScale) >> TSL2561_LUX_CHSCALE;
	channel1 = (ir * chScale) >> TSL2561_LUX_CHSCALE;
	
	/* find the ratio of the channel values (Channel1/Channel0) */
	if (channel0 != 0) ratio1 = (channel1 << (TSL2561_LUX_RATIOSCALE+1)) / channel0;
	
	// round the ratio value
	ratio = (ratio1 + 1) >> 1;
	
	#ifdef TSL2561_PACKAGE_CS
	if ((ratio >= 0) && (ratio <= TSL2561_LUX_K1C))
		{b=TSL2561_LUX_B1C; m=TSL2561_LUX_M1C;}
	else if (ratio <= TSL2561_LUX_K2C)
		{b=TSL2561_LUX_B2C; m=TSL2561_LUX_M2C;}
	else if (ratio <= TSL2561_LUX_K3C)
		{b=TSL2561_LUX_B3C; m=TSL2561_LUX_M3C;}
	else if (ratio <= TSL2561_LUX_K4C)
		{b=TSL2561_LUX_B4C; m=TSL2561_LUX_M4C;}
	else if (ratio <= TSL2561_LUX_K5C)
		{b=TSL2561_LUX_B5C; m=TSL2561_LUX_M5C;}
	else if (ratio <= TSL2561_LUX_K6C)
		{b=TSL2561_LUX_B6C; m=TSL2561_LUX_M6C;}
	else if (ratio <= TSL2561_LUX_K7C)
		{b=TSL2561_LUX_B7C; m=TSL2561_LUX_M7C;}
	else if (ratio > TSL2561_LUX_K8C)
		{b=TSL2561_LUX_B8C; m=TSL2561_LUX_M8C;}
	#else
	if ((ratio >= 0) && (ratio <= TSL2561_LUX_K1T))
		{b=TSL2561_LUX_B1T; m=TSL2561_LUX_M1T;}
	else if (ratio <= TSL2561_LUX_K2T)
		{b=TSL2561_LUX_B2T; m=TSL2561_LUX_M2T;}
	else if (ratio <= TSL2561_LUX_K3T)
		{b=TSL2561_LUX_B3T; m=TSL2561_LUX_M3T;}
	else if (ratio <= TSL2561_LUX_K4T)
		{b=TSL2561_LUX_B4T; m=TSL2561_LUX_M4T;}
	else if (ratio <= TSL2561_LUX_K5T)
		{b=TSL2561_LUX_B5T; m=TSL2561_LUX_M5T;}
	else if (ratio <= TSL2561_LUX_K6T)
		{b=TSL2561_LUX_B6T; m=TSL2561_LUX_M6T;}
	else if (ratio <= TSL2561_LUX_K7T)
		{b=TSL2561_LUX_B7T; m=TSL2561_LUX_M7T;}
	else if (ratio > TSL2561_LUX_K8T)
		{b=TSL2561_LUX_B8T; m=TSL2561_LUX_M8T;}
	#endif
	
	temp = ((channel0 * b) - (channel1 * m));
	
	// do not allow negative lux value
	if (temp < 0) temp = 0;
	
	// round lsb (2^(LUX_SCALE-1))
	temp += (1 << (TSL2561_LUX_LUXSCALE-1));
	
	// strip off fractional portion
	lux = temp >> TSL2561_LUX_LUXSCALE;
	
	// Signal I2C had no errors */
	return lux;
}


int TSL2561_SETINTEGRATIONTIME(TSL2561 *sensor, tsl2561IntegrationTime_t time) {
	int rc;
	
	if(sensor->adapter_fd == -1) { // not opened
		// TODO: choose a valid errno error
		sensor->lasterr = -1;
		return -1;
	}
	
	TSL2561_ON(sensor);
	rc = tsl2561_write8(sensor, TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING, time | sensor->gain);
	TSL2561_OFF(sensor);
	if(rc == 0) {
		sensor->integration_time = time;
		//fprintf(stderr, "setting integration time: 0x%02x to 0x%02x\n", TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING, time | sensor->gain);
		return 0;
	} else {
		//fprintf(stderr, "Error setting integration time: 0x%02x to 0x%02x\n", TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING, time | sensor->gain);
		return -1;
	}
	return -1;
}
int TSL2561_SETGAIN(TSL2561 *sensor, tsl2561Gain_t gain) {
	int rc;
	
	if(sensor->adapter_fd == -1) { // not opened
		// TODO: choose a valid errno error
		sensor->lasterr = -1;
		return -1;
	}
	
	TSL2561_ON(sensor);
	rc = tsl2561_write8(sensor, TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING, sensor->integration_time | gain);
	TSL2561_OFF(sensor);
	if(rc == 0) {
		sensor->gain = gain;
		//fprintf(stderr, "setting gain: 0x%02x to 0x%02x\n", TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING, sensor->integration_time | gain);
		return 0;
	} else {
		//fprintf(stderr, "Error setting gain: 0x%02x to 0x%02x\n", TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING, sensor->integration_time | gain);
		return -1;
	}
	return -1;
}
int TSL2561_OPEN(TSL2561 *sensor) {
	char filename[20];
	
	if(sensor->adapter_fd != -1) { // already opened
		// TODO: choose a valid errno error
		sensor->lasterr = -1;
		return -1;
	}
	snprintf(filename, 20, "/dev/i2c-%d", sensor->adapter_nr);
	if ((sensor->adapter_fd = open(filename, O_RDWR)) < 0) { // open the device file (requests i2c-dev kernel module loaded)
		sensor->lasterr = errno;
		return -1;
	}
	
	if (ioctl(sensor->adapter_fd, I2C_SLAVE, sensor->sensor_addr) < 0) { // talk to the requested device
		sensor->lasterr = errno;
		close(sensor->adapter_fd);
		sensor->adapter_fd = -1;
		return -1;
	}
	
	TSL2561_SETINTEGRATIONTIME(sensor, TSL2561_INTEGRATIONTIME_402MS);
	TSL2561_SETGAIN(sensor, TSL2561_GAIN_16X);
	
	/*
	TSL2561_ON(sensor);
        tsl2561_write8(sensor, 0x81, 0x11);
	TSL2561_OFF(sensor);
	*/
	
	return 0;
}
void TSL2561_CLOSE(TSL2561 *sensor) {
	if(sensor->adapter_fd != -1) {
		close(sensor->adapter_fd);
		sensor->adapter_fd = -1;
	}
}

/**
 * sense the ambient light. Returns 0 on success, -1 on errors.
 * the parameter pointer fullspectrum is the quantity og light at full spectrum (including infrared)
 * the parameter pointer infrared is the quantity of infrared light
 * if autogain is 0 a single sensor reading is done with the gain and integration time previously selected by invoking
 * the TSL2561_SETINTEGRATIONTIME() and TSL2561_SETGAIN() functions. It autogain is 1 and automatic gain adjustment alghoritm is used
 */
int TSL2561_SENSELIGHT(TSL2561 *sensor, uint16_t *full_spectrum, uint16_t *infrared, uint32_t *lux, int autogain) {
	int rc=1;
	uint16_t fs, ir, hi, lo;
	//tsl2561Gain_t old_gain;
	
	if(sensor->adapter_fd == -1) {
		// TODO: choose a valid errno error
		sensor->lasterr = -1;
		return -1;
	}
	if (autogain == 0) { // autogain not requested. Executing a single sensor read
		rc = tsl2561_getdata(sensor, full_spectrum, infrared);
		*lux = TSL2561_CALCULATE_LUX(sensor, *full_spectrum, *infrared);
		return rc;
	}
	
	// autogain requested
	switch(sensor->integration_time) {
	case TSL2561_INTEGRATIONTIME_13MS:
		hi = TSL2561_AGC_THI_13MS;
		lo = TSL2561_AGC_TLO_13MS;
		break;
	case TSL2561_INTEGRATIONTIME_101MS:
		hi = TSL2561_AGC_THI_101MS;
		lo = TSL2561_AGC_TLO_101MS;
		break;
	case TSL2561_INTEGRATIONTIME_402MS:
		hi = TSL2561_AGC_THI_402MS;
		lo = TSL2561_AGC_TLO_402MS;
		break;
	default:
		hi = TSL2561_AGC_THI_402MS;
		lo = TSL2561_AGC_TLO_402MS;
		break;
	}
	
	// save the old gain
	//old_gain = sensor->gain;
	
	// try to adjust the gain
	rc = tsl2561_getdata(sensor, &fs, &ir);
	if(rc != 0) {
		return -1; // invalid read or sensor error
	}
	if ((fs < lo) && (sensor->gain == TSL2561_GAIN_1X)) { // light too low with this gain
		// raise the gain and redo the reading
		TSL2561_SETGAIN(sensor, TSL2561_GAIN_16X);
		//printf("gain raised\n");
		rc = tsl2561_getdata(sensor, &fs, &ir);
		// restore the previous gain
		//TSL2561_SETGAIN(sensor, old_gain);
		if(rc != 0) { // invalid read or sensor error
			return -1;
		} else {
			// now consider the reading valid after being adjusted
			*full_spectrum = fs;
			*infrared = ir;
			*lux = TSL2561_CALCULATE_LUX(sensor, *full_spectrum, *infrared);
			return 0;
		}
	}
	if ((fs > hi) && (sensor->gain == TSL2561_GAIN_16X)) { // light too high with this gain
		// lower the gain and redo the reading
		TSL2561_SETGAIN(sensor, TSL2561_GAIN_1X);
		//printf("gain lowered\n");
		rc = tsl2561_getdata(sensor, &fs, &ir);
		// restore the previous gain
		//TSL2561_SETGAIN(sensor, old_gain);
		if(rc != 0) { // invalid read or sensor error
			return -1;
		} else {
			// now consider the reading valid after being adjusted
			*full_spectrum = fs;
			*infrared = ir;
			*lux = TSL2561_CALCULATE_LUX(sensor, *full_spectrum, *infrared);
			return 0;
		}
	}
	
	// the reading was valid without gain adjustment (or chip limits encountered!)
	*full_spectrum = fs;
	*infrared = ir;
	*lux = TSL2561_CALCULATE_LUX(sensor, *full_spectrum, *infrared);
	return 0;
}

