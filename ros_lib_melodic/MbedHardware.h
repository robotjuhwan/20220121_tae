/*
 * MbedHardware
 *
 *  Created on: Aug 17, 2011
 *      Author: nucho
 */

#ifndef ROS_MBED_HARDWARE_H_
#define ROS_MBED_HARDWARE_H_

#include "mbed.h"

class MbedHardware {
  public:
    MbedHardware(PinName tx, PinName rx, long baud = 57600)
      :iostream(tx, rx){
      baud_ = baud;
      t.start();
    }

    MbedHardware()
      :iostream(USBTX, USBRX) {
        baud_ = 57600;
        t.start();
    }

    void setBaud(long baud){
      this->baud_= baud;
    }

    int getBaud(){return baud_;}

    void init(){
        iostream.set_baud(baud_);
    }

    int read(){
        if (iostream.readable()) {
          iostream.read(rdata,1);
            return rdata[0];
        } else {
            return -1;
        }
    };
    void write(uint8_t* data, int length) {
      iostream.write(data,length);
    }

    unsigned long time(){return duration_cast<milliseconds>(t.elapsed_time()).count();}

protected:
    uint8_t rdata[1];
    BufferedSerial iostream;
    long baud_;
    Timer t;
};


#endif /* ROS_MBED_HARDWARE_H_ */
