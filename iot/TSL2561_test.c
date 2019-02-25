/*
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
*/

#include <stdio.h>
#include <string.h>
#include "TSL2561.h"

int main() {
	int rc;
	uint16_t broadband, ir;
	uint32_t lux=0;
	// prepare the sensor
	// (the first parameter is the raspberry pi i2c master controller attached to the TSL2561, the second is the i2c selection jumper)
	// The i2c selection address can be one of: TSL2561_ADDR_LOW, TSL2561_ADDR_FLOAT or TSL2561_ADDR_HIGH
	TSL2561 light1 = TSL2561_INIT(1, TSL2561_ADDR_FLOAT);
	
	// initialize the sensor
	rc = TSL2561_OPEN(&light1);
	if(rc != 0) {
		fprintf(stderr, "Error initializing TSL2561 sensor (%s). Check your i2c bus (es. i2cdetect)\n", strerror(light1.lasterr));
		// you don't need to TSL2561_CLOSE() if TSL2561_OPEN() failed, but it's safe doing it.
		TSL2561_CLOSE(&light1);
		return 1;
	}
	
	// set the gain to 1X (it can be TSL2561_GAIN_1X or TSL2561_GAIN_16X)
	// use 16X gain to get more precision in dark ambients, or enable auto gain below
	rc = TSL2561_SETGAIN(&light1, TSL2561_GAIN_1X);
	
	// set the integration time 
	// (TSL2561_INTEGRATIONTIME_402MS or TSL2561_INTEGRATIONTIME_101MS or TSL2561_INTEGRATIONTIME_13MS)
	// TSL2561_INTEGRATIONTIME_402MS is slower but more precise, TSL2561_INTEGRATIONTIME_13MS is very fast but not so precise
	rc = TSL2561_SETINTEGRATIONTIME(&light1, TSL2561_INTEGRATIONTIME_101MS);
	
	// sense the luminosity from the sensor (lux is the luminosity taken in "lux" measure units)
	// the last parameter can be 1 to enable library auto gain, or 0 to disable it
	rc = TSL2561_SENSELIGHT(&light1, &broadband, &ir, &lux, 1);
	printf("Test. RC: %i(%s), broadband: %i, ir: %i, lux: %i\n", rc, strerror(light1.lasterr), broadband, ir, lux);
	
	TSL2561_CLOSE(&light1);
	
	return 0;
}
