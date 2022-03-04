/*******************************************************************************
This library was developed by Taesik Kim 

This code is inspired from an Mbed library for Dynamixel XL-320 developed by
Muhammad Fajar Adityo.

This library is based on the Dynamixel XH-430 data sheet

Read : Header  RSRV  ID  Length  Inst  Parameters  CRC 
        3        1    1     2      1   n(address+)  2

Write : Header  RSRV  ID  Length  Inst  Parameters  CRC 
         3        1    1     2      1   n(address+) 2

*******************************************************************************/

#ifndef XH430_H
#define XH430_H

#include <stdint.h>
#include "mbed.h"

///INSTRUCTION///
#define PING 0x01
#define READ 0x02
#define WRITE 0x03
#define REBOOT 0x08
#define SYNC_READ 0x82
#define SYNC_WRITE 0x83

///EPPROM data///
#define DRIVE_MODE 10    // 1  CW,CCW
#define OPER_MODE 11     // 1  pos = 3(default) pos+current = 5
#define CURRENT_LIMIT 38 // 2
///RAM ADDRESS///
#define TORQUE_ENABLE 64     // 1
#define GOAL_CURRENT 102     // 2
#define PROFILE_VEL 112      // 4
#define GOAL_POSITION 116    // 4
#define PRESENT_CURRENT 126  // 2
#define PRESENT_POSITION 132 // 4

using namespace std::chrono;

class XH430
{
public:
    XH430(uint32_t baud, PinName tx, PinName rx, PinName rts);
    ~XH430();
    /***Reboot***/

    void Send_Reboot(uint8_t id);

    /***Make & Send 1-8 byte packet***/
    //for 1 motor//
    void make_4byte_packet(uint8_t id, uint8_t inst,
                           uint16_t address, int32_t data);

    void make_2byte_packet(uint8_t id, uint8_t inst,
                           uint16_t address, int16_t data);

    void make_1byte_packet(uint8_t id, uint8_t inst,
                           uint16_t address, int8_t data);

    //for 9 motor//
    void make_4byte_packet_sync(uint16_t address,
                                uint32_t data1, uint32_t data2,
                                uint32_t data3, uint32_t data4,
                                uint32_t data5, uint32_t data6,
                                uint32_t data7, uint32_t data8,
                                uint32_t data9);
    void make_4byte_packet_sync(uint8_t id,
                                uint32_t data1, uint32_t data2,
                                uint32_t data3, uint32_t data4);
    void make_4byte_packet_sync(uint8_t id1, uint8_t id2, uint8_t id3, uint8_t id4,
                                uint32_t data1, uint32_t data2, uint32_t data3, uint32_t data4);
    void make_4byte_packet_sync(uint8_t id1, uint8_t id2,
                                uint32_t data1, uint32_t data2);

    void make_4byte_packet_sync_velocity(uint8_t id,
                                         uint32_t data1, uint32_t data2,
                                         uint32_t data3, uint32_t data4);
    void make_4byte_packet_sync_velocity(uint8_t id1, uint8_t id2, uint8_t id3, uint8_t id4,
                                         uint32_t data1, uint32_t data2,
                                         uint32_t data3, uint32_t data4);
    void make_4byte_packet_sync_velocity(uint8_t id1, uint8_t id2,
                                         uint32_t data1, uint32_t data2);

    uint8_t read_4byte_packet_sync(uint8_t id, uint16_t &data1,
                                   uint16_t &data2, uint16_t &data3,
                                   uint16_t &data4);
    uint8_t read_4byte_packet_sync(uint8_t id[9],
                                   uint16_t data[9]);
    uint8_t read_2byte_packet_sync(uint8_t id,
                                   uint16_t &data1, uint16_t &data2,
                                   uint16_t &data3, uint16_t &data4);
    uint8_t read_2byte_packet_sync(uint8_t id[9],
                                   int16_t data[9]);
    uint8_t read_2byte_packet_sync(uint8_t id, uint16_t &data);
    void make_2byte_packet_sync(uint16_t address,
                                uint16_t data1, uint16_t data2,
                                uint16_t data3, uint16_t data4,
                                uint16_t data5, uint16_t data6,
                                uint16_t data7, uint16_t data8,
                                uint16_t data9);

    void make_1byte_packet_sync(uint16_t address,
                                uint8_t data1, uint8_t data2,
                                uint8_t data3, uint8_t data4,
                                uint8_t data5, uint8_t data6,
                                uint8_t data7, uint8_t data8,
                                uint8_t data9);

	void make_1byte_packet_2motor(uint8_t id1, uint8_t id2, uint16_t address,
								int8_t data);

	void make_2byte_packet_2motor(uint8_t id1, uint8_t id2, uint16_t address,
								int8_t data);

    /***CRC packet****/
    unsigned short update_crc(unsigned short crc_accum, unsigned char *data_blk_ptr,
                              unsigned short data_blk_size);

private:
    uint32_t baudrate;
    UnbufferedSerial sXH430;
    DigitalOut RTS_out;
};

#endif