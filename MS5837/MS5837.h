#ifndef MS5837_H
#define MS5837_H

#include "mbed.h"

class MS5837 {
public:
	static const float Pa;
	static const float bar;
	static const float mbar;

	static const uint8_t MS5837_30BA;
	static const uint8_t MS5837_02BA;
	static const uint8_t MS5837_UNRECOGNISED;

	MS5837 (PinName sda, PinName scl,
            char ms5837_addr = 0x76  )
            : i2c( sda, scl ), device_address( ms5837_addr << 1 ) {
                fluidDensity = 1029;
    }

	bool init(void);

	/** Set model of MS5837 sensor. Valid options are MS5837::MS5837_30BA (default)
	 * and MS5837::MS5837_02BA.
	 */
	void setModel(uint8_t model);
	uint8_t getModel();

	/** Provide the density of the working fluid in kg/m^3. Default is for
	 * seawater. Should be 997 for freshwater.
	 */
	void setFluidDensity(float density);

	/** The read from I2C takes up to 40 ms, so use sparingly is possible.
	 */
	void read();

	/** Pressure returned in mbar or mbar*conversion rate.
	 */
	float pressure(float conversion = 1.0f);

	/** Temperature returned in deg C.
	 */
	float temperature();

	/** Depth returned in meters (valid for operation in incompressible
	 *  liquids only. Uses density that is set for fresh or seawater.
	 */
	float depth();

	/** Altitude returned in meters (valid for operation in air only).
	 */
	float altitude();

private:

	//This stores the requested i2c port
	I2C     i2c;

	uint16_t C[8];
	uint32_t D1_pres, D2_temp;
	int32_t TEMP;
	int32_t P;
	uint8_t _model;

	float fluidDensity;

    char ms5837_rx_data[3];
    char ms5837_tx_data[2];

    char    device_address;
	/** Performs calculations per the sensor data sheet for conversion and
	 *  second order compensation.
	 */
	void calculate();

	uint8_t crc4(uint16_t n_prom[]);
};

#endif