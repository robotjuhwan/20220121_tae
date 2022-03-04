#include "XH430_Driver.h"

XH430::XH430(uint32_t baud, PinName tx, PinName rx, PinName rts)
    : sXH430(tx, rx), RTS_out(rts)
{
  baudrate = baud;
  //sXH430.set_baud(baudrate);
  sXH430.baud(baudrate);
  sXH430.format(
      /* bits */ 8,
      /* parity */ SerialBase::None,
      /* stop bit */ 1);
  RTS_out.write(1);
}

XH430::~XH430(){};

void XH430::Send_Reboot(uint8_t id)
{
  uint8_t packet[10];

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = id;
  packet[5] = 0x03;
  packet[6] = 0x00;
  packet[7] = 0x08;
  packet[8] = 0x2f;
  packet[9] = 0x4e;

  sXH430.write(packet, 10);
}

void XH430::make_4byte_packet(uint8_t id, uint8_t inst, uint16_t address,
                              int32_t data)
{
  uint8_t packet[16];
  unsigned short CRC;
  wchar_t packet_len = 9; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = id;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = inst;                  // Instruction 0x03 is write
  packet[8] = address & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (address >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = data & 0xff;          // data
  packet[11] = (data >> 8) & 0xff;   // data
  packet[12] = (data >> 16) & 0xff;  // data
  packet[13] = (data >> 24) & 0xff;  // data

  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[14] = (CRC & 0x00ff);
  packet[15] = (CRC >> 8) & 0x00ff;

  sXH430.write(packet, 16);
}

void XH430::make_2byte_packet(uint8_t id, uint8_t inst, uint16_t address,
                              int16_t data)
{

  uint8_t packet[14];
  unsigned short CRC;
  wchar_t packet_len = 7; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = id;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = inst;                  // Instruction 0x03 is write
  packet[8] = address & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (address >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = data & 0xff;          // data
  packet[11] = (data >> 8) & 0xff;   // data

  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[12] = (CRC & 0x00ff);
  packet[13] = (CRC >> 8) & 0x00ff;

  sXH430.write(packet, 14);
}

void XH430::make_1byte_packet(uint8_t id, uint8_t inst, uint16_t address,
                              int8_t data)
{

  uint8_t packet[13];
  unsigned short CRC;
  wchar_t packet_len = 6; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = id;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = inst;                  // Instruction 0x03 is write
  packet[8] = address & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (address >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = data & 0xff;          // data

  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[11] = (CRC & 0x00ff);
  packet[12] = (CRC >> 8) & 0x00ff;

  sXH430.write(packet, 13);
}

// for 9 motor//
void XH430::make_4byte_packet_sync(uint16_t address, uint32_t data1,
                                   uint32_t data2, uint32_t data3,
                                   uint32_t data4, uint32_t data5,
                                   uint32_t data6, uint32_t data7,
                                   uint32_t data8, uint32_t data9)
{
  uint8_t packet[59];
  unsigned short CRC;
  wchar_t packet_len = 52; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = 0xfe;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = 0x83;                  // Instruction 0x83 is sync_write
  packet[8] = address & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (address >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = 0x04;                 // data length = 4 byte
  packet[11] = 0x00;
  packet[12] = 0x01; // id1
  packet[13] = data1 & 0xff;
  packet[14] = (data1 >> 8) & 0xff;
  packet[15] = (data1 >> 16) & 0xff;
  packet[16] = (data1 >> 24) & 0xff;
  packet[17] = 0x02; // id2
  packet[18] = data2 & 0xff;
  packet[19] = (data2 >> 8) & 0xff;
  packet[20] = (data2 >> 16) & 0xff;
  packet[21] = (data2 >> 24) & 0xff;
  packet[22] = 0x03; // id3
  packet[23] = data3 & 0xff;
  packet[24] = (data3 >> 8) & 0xff;
  packet[25] = (data3 >> 16) & 0xff;
  packet[26] = (data3 >> 24) & 0xff;
  packet[27] = 0x04; // id4
  packet[28] = data4 & 0xff;
  packet[29] = (data4 >> 8) & 0xff;
  packet[30] = (data4 >> 16) & 0xff;
  packet[31] = (data4 >> 24) & 0xff;
  packet[32] = 0x0b; // id11
  packet[33] = data5 & 0xff;
  packet[34] = (data5 >> 8) & 0xff;
  packet[35] = (data5 >> 16) & 0xff;
  packet[36] = (data5 >> 24) & 0xff;
  packet[37] = 0x0c; // id12
  packet[38] = data6 & 0xff;
  packet[39] = (data6 >> 8) & 0xff;
  packet[40] = (data6 >> 16) & 0xff;
  packet[41] = (data6 >> 24) & 0xff;
  packet[42] = 0x0d; // id13
  packet[43] = data7 & 0xff;
  packet[44] = (data7 >> 8) & 0xff;
  packet[45] = (data7 >> 16) & 0xff;
  packet[46] = (data7 >> 24) & 0xff;
  packet[47] = 0x0e; // id14
  packet[48] = data8 & 0xff;
  packet[49] = (data8 >> 8) & 0xff;
  packet[50] = (data8 >> 16) & 0xff;
  packet[51] = (data8 >> 24) & 0xff;
  packet[52] = 0x37; // id55
  packet[53] = data9 & 0xff;
  packet[54] = (data9 >> 8) & 0xff;
  packet[55] = (data9 >> 16) & 0xff;
  packet[56] = (data9 >> 24) & 0xff;

  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[57] = (CRC & 0x00ff);
  packet[58] = (CRC >> 8) & 0x00ff;

  sXH430.write(packet, 59);
}

// for 4 motor// //0.003 s
void XH430::make_4byte_packet_sync(uint8_t id, uint32_t data1, uint32_t data2,
                                   uint32_t data3, uint32_t data4)
{
  uint8_t packet[34];
  unsigned short CRC;
  wchar_t packet_len = 27; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = 0xfe;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = 0x83;              // Instruction 0x83 is sync_write
  packet[8] = 116 & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (116 >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = 0x04;             // data length = 4 byte
  packet[11] = 0x00;
  packet[12] = id; // id1
  packet[13] = data1 & 0xff;
  packet[14] = (data1 >> 8) & 0xff;
  packet[15] = (data1 >> 16) & 0xff;
  packet[16] = (data1 >> 24) & 0xff;
  packet[17] = id + 1; // id2
  packet[18] = data2 & 0xff;
  packet[19] = (data2 >> 8) & 0xff;
  packet[20] = (data2 >> 16) & 0xff;
  packet[21] = (data2 >> 24) & 0xff;
  packet[22] = id + 2; // id3
  packet[23] = data3 & 0xff;
  packet[24] = (data3 >> 8) & 0xff;
  packet[25] = (data3 >> 16) & 0xff;
  packet[26] = (data3 >> 24) & 0xff;
  packet[27] = id + 3; // id4
  packet[28] = data4 & 0xff;
  packet[29] = (data4 >> 8) & 0xff;
  packet[30] = (data4 >> 16) & 0xff;
  packet[31] = (data4 >> 24) & 0xff;
  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[32] = (CRC & 0x00ff);
  packet[33] = (CRC >> 8) & 0x00ff;

  sXH430.write(packet, 34);
}

// for 4 motor// //0.003 s
void XH430::make_4byte_packet_sync(uint8_t id1, uint8_t id2, uint8_t id3, uint8_t id4, uint32_t data1, uint32_t data2,
                                   uint32_t data3, uint32_t data4)
{
  uint8_t packet[34];
  unsigned short CRC;
  wchar_t packet_len = 27; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = 0xfe;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = 0x83;              // Instruction 0x83 is sync_write
  packet[8] = 116 & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (116 >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = 0x04;             // data length = 4 byte
  packet[11] = 0x00;
  packet[12] = id1; // id1
  packet[13] = data1 & 0xff;
  packet[14] = (data1 >> 8) & 0xff;
  packet[15] = (data1 >> 16) & 0xff;
  packet[16] = (data1 >> 24) & 0xff;
  packet[17] = id2; // id2
  packet[18] = data2 & 0xff;
  packet[19] = (data2 >> 8) & 0xff;
  packet[20] = (data2 >> 16) & 0xff;
  packet[21] = (data2 >> 24) & 0xff;
  packet[22] = id3; // id3
  packet[23] = data3 & 0xff;
  packet[24] = (data3 >> 8) & 0xff;
  packet[25] = (data3 >> 16) & 0xff;
  packet[26] = (data3 >> 24) & 0xff;
  packet[27] = id4; // id4
  packet[28] = data4 & 0xff;
  packet[29] = (data4 >> 8) & 0xff;
  packet[30] = (data4 >> 16) & 0xff;
  packet[31] = (data4 >> 24) & 0xff;
  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[32] = (CRC & 0x00ff);
  packet[33] = (CRC >> 8) & 0x00ff;

  sXH430.write(packet, 34);
}

// for 2 motor// //0.003 s
void XH430::make_4byte_packet_sync(uint8_t id1, uint8_t id2, uint32_t data1, uint32_t data2)
{
  uint8_t packet[24];
  unsigned short CRC;
  wchar_t packet_len = 17; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = 0xfe;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = 0x83;              // Instruction 0x83 is sync_write
  packet[8] = 116 & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (116 >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = 0x04;             // data length = 4 byte
  packet[11] = 0x00;
  packet[12] = id1; // id1
  packet[13] = data1 & 0xff;
  packet[14] = (data1 >> 8) & 0xff;
  packet[15] = (data1 >> 16) & 0xff;
  packet[16] = (data1 >> 24) & 0xff;
  packet[17] = id2; // id2
  packet[18] = data2 & 0xff;
  packet[19] = (data2 >> 8) & 0xff;
  packet[20] = (data2 >> 16) & 0xff;
  packet[21] = (data2 >> 24) & 0xff;

  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[22] = (CRC & 0x00ff);
  packet[23] = (CRC >> 8) & 0x00ff;

  sXH430.write(packet, 24);
}

// 0.003 s
void XH430::make_4byte_packet_sync_velocity(uint8_t id, uint32_t data1,
                                            uint32_t data2, uint32_t data3,
                                            uint32_t data4)
{
  uint8_t packet[34];
  unsigned short CRC;
  wchar_t packet_len = 27; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = 0xfe;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = 0x83;              // Instruction 0x83 is sync_write
  packet[8] = 112 & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (112 >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = 0x04;             // data length = 4 byte
  packet[11] = 0x00;
  packet[12] = id; // id1
  packet[13] = data1 & 0xff;
  packet[14] = (data1 >> 8) & 0xff;
  packet[15] = (data1 >> 16) & 0xff;
  packet[16] = (data1 >> 24) & 0xff;
  packet[17] = id + 1; // id2
  packet[18] = data2 & 0xff;
  packet[19] = (data2 >> 8) & 0xff;
  packet[20] = (data2 >> 16) & 0xff;
  packet[21] = (data2 >> 24) & 0xff;
  packet[22] = id + 2; // id3
  packet[23] = data3 & 0xff;
  packet[24] = (data3 >> 8) & 0xff;
  packet[25] = (data3 >> 16) & 0xff;
  packet[26] = (data3 >> 24) & 0xff;
  packet[27] = id + 3; // id4
  packet[28] = data4 & 0xff;
  packet[29] = (data4 >> 8) & 0xff;
  packet[30] = (data4 >> 16) & 0xff;
  packet[31] = (data4 >> 24) & 0xff;
  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[32] = (CRC & 0x00ff);
  packet[33] = (CRC >> 8) & 0x00ff;

  sXH430.write(packet, 34);
}

void XH430::make_4byte_packet_sync_velocity(uint8_t id1, uint8_t id2, uint8_t id3, uint8_t id4,
                                            uint32_t data1, uint32_t data2,
                                            uint32_t data3, uint32_t data4)
{
  uint8_t packet[34];
  unsigned short CRC;
  wchar_t packet_len = 27; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = 0xfe;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = 0x83;              // Instruction 0x83 is sync_write
  packet[8] = 112 & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (112 >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = 0x04;             // data length = 4 byte
  packet[11] = 0x00;
  packet[12] = id1; // id1
  packet[13] = data1 & 0xff;
  packet[14] = (data1 >> 8) & 0xff;
  packet[15] = (data1 >> 16) & 0xff;
  packet[16] = (data1 >> 24) & 0xff;
  packet[17] = id2; // id2
  packet[18] = data2 & 0xff;
  packet[19] = (data2 >> 8) & 0xff;
  packet[20] = (data2 >> 16) & 0xff;
  packet[21] = (data2 >> 24) & 0xff;
  packet[22] = id3; // id3
  packet[23] = data3 & 0xff;
  packet[24] = (data3 >> 8) & 0xff;
  packet[25] = (data3 >> 16) & 0xff;
  packet[26] = (data3 >> 24) & 0xff;
  packet[27] = id4; // id4
  packet[28] = data4 & 0xff;
  packet[29] = (data4 >> 8) & 0xff;
  packet[30] = (data4 >> 16) & 0xff;
  packet[31] = (data4 >> 24) & 0xff;
  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[32] = (CRC & 0x00ff);
  packet[33] = (CRC >> 8) & 0x00ff;

  sXH430.write(packet, 34);
}

void XH430::make_4byte_packet_sync_velocity(uint8_t id1, uint8_t id2, uint32_t data1,
                                            uint32_t data2)
{
  uint8_t packet[24];
  unsigned short CRC;
  wchar_t packet_len = 17; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = 0xfe;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = 0x83;              // Instruction 0x83 is sync_write
  packet[8] = 112 & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (112 >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = 0x04;             // data length = 4 byte
  packet[11] = 0x00;
  packet[12] = id1; // id1
  packet[13] = data1 & 0xff;
  packet[14] = (data1 >> 8) & 0xff;
  packet[15] = (data1 >> 16) & 0xff;
  packet[16] = (data1 >> 24) & 0xff;
  packet[17] = id2; // id2
  packet[18] = data2 & 0xff;
  packet[19] = (data2 >> 8) & 0xff;
  packet[20] = (data2 >> 16) & 0xff;
  packet[21] = (data2 >> 24) & 0xff;
  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[22] = (CRC & 0x00ff);
  packet[23] = (CRC >> 8) & 0x00ff;

  sXH430.write(packet, 24);
}

uint8_t XH430::read_4byte_packet_sync(uint8_t id, uint16_t &data1,
                                      uint16_t &data2, uint16_t &data3,
                                      uint16_t &data4)
{
  uint8_t packet[60];
  int packet_count = 0;
  Timer dy_t;
  unsigned short CRC;
  wchar_t packet_len = 11; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = 0xfe;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = 0x82;              // Instruction 0x83 is sync_write
  packet[8] = 132 & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (132 >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = 0x04;             // data length = 4 byte
  packet[11] = 0x00;
  packet[12] = id;                             // id1
  packet[13] = id + 1;                         // id2
  packet[14] = id + 2;                         // id3
  packet[15] = id + 3;                         // id4
  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[16] = (CRC & 0x00ff);
  packet[17] = (CRC >> 8) & 0x00ff;

  // 0.0016 s
  sXH430.write(packet, 18);
  dy_t.reset();
  dy_t.start();
  while (duration_cast<microseconds>(dy_t.elapsed_time()).count() < 1062)
  {
  }
  RTS_out.write(0);
  int replySize = 60;

  // we'll only get a reply if it was not broadcast (and status reply option is
  // selected in servo)
  bool statusReceived = false;
  if (id != 0xFE)
  {
    // 0.0046 s
    dy_t.reset();
    while (duration_cast<milliseconds>(dy_t.elapsed_time()).count() < 10)
    {
      if (sXH430.readable())
      {
        // BUGBUG: unsigned char b = _uart.getc();
        // Bug with _uart.getc() on FRDM-K64F. Instead read directly from uart
        sXH430.read(packet + packet_count, 1);
        packet_count++;
        if (packet_count == replySize)
        {
          statusReceived = true;
          break;
        }
      }
    }
  }
  // 0.0053
  dy_t.stop();
  if (statusReceived)
  {
    data1 = packet[9] + packet[10] * 256;
    data2 = packet[24] + packet[25] * 256;
    data3 = packet[39] + packet[40] * 256;
    data4 = packet[54] + packet[55] * 256;
  }
  RTS_out.write(1);
  return statusReceived;
}

uint8_t XH430::read_4byte_packet_sync(uint8_t id[9],
                                      uint16_t data[9])
{
  uint8_t packet[135];
  int packet_count = 0;
  Timer dy_t;
  unsigned short CRC;
  wchar_t packet_len = 16; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = 0xfe;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = 0x82;              // Instruction 0x83 is sync_write
  packet[8] = 132 & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (132 >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = 0x04;             // data length = 4 byte
  packet[11] = 0x00;
  packet[12] = id[0];                          // id1
  packet[13] = id[1];                          // id2
  packet[14] = id[2];                          // id3
  packet[15] = id[3];                          // id4
  packet[16] = id[4];                          // id4
  packet[17] = id[5];                          // id4
  packet[18] = id[6];                          // id4
  packet[19] = id[7];                          // id4
  packet[20] = id[8];                          // id4
  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[21] = (CRC & 0x00ff);
  packet[22] = (CRC >> 8) & 0x00ff;

  // 0.0016 s
  sXH430.write(packet, 23);
  dy_t.reset();
  dy_t.start();
  while (duration_cast<microseconds>(dy_t.elapsed_time()).count() < 1062)
  {
  }
  RTS_out.write(0);
  int replySize = 135;

  // we'll only get a reply if it was not broadcast (and status reply option is
  // selected in servo)
  bool statusReceived = false;


  dy_t.reset();
  // 0.0046 s
  while (duration_cast<milliseconds>(dy_t.elapsed_time()).count() < 20)
  {
    if (sXH430.readable())
    {
      // BUGBUG: unsigned char b = _uart.getc();
      // Bug with _uart.getc() on FRDM-K64F. Instead read directly from uart
      sXH430.read(packet + packet_count, 1);
      packet_count++;
      if (packet_count == replySize)
      {
        statusReceived = true;
        break;
      }
    }
  }
  dy_t.stop();

  // 0.0053

  if (statusReceived)
  {
    data[0] = packet[9] + packet[10] * 256;
    data[1] = packet[24] + packet[25] * 256;
    data[2] = packet[39] + packet[40] * 256;
    data[3] = packet[54] + packet[55] * 256;
    data[4] = packet[69] + packet[70] * 256;
    data[5] = packet[84] + packet[85] * 256;
    data[6] = packet[99] + packet[100] * 256;
    data[7] = packet[114] + packet[115] * 256;
    data[8] = packet[129] + packet[130] * 256;
  }
  RTS_out.write(1);
  return statusReceived;
}

uint8_t XH430::read_2byte_packet_sync(uint8_t id, uint16_t &data1,
                                      uint16_t &data2, uint16_t &data3,
                                      uint16_t &data4)
{
  uint8_t packet[52];

  unsigned short CRC;
  wchar_t packet_len = 11; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = 0xfe;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = 0x82;              // Instruction 0x83 is sync_write
  packet[8] = 126 & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (126 >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = 0x02;             // data length = 4 byte
  packet[11] = 0x00;
  packet[12] = id;                             // id1
  packet[13] = id + 1;                         // id2
  packet[14] = id + 2;                         // id3
  packet[15] = id + 3;                         // id4
  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[16] = (CRC & 0x00ff);
  packet[17] = (CRC >> 8) & 0x00ff;

  // 0.0016 s
  sXH430.write(packet, 18);

  int replySize = 52;
  int i_count = 0;
  // we'll only get a reply if it was not broadcast (and status reply option is
  // selected in servo)
  bool statusReceived = false;
  Timer dy_t;
  if (id != 0xFE)
  {
    dy_t.start();
    // 0.0046 s
    while (duration_cast<milliseconds>(dy_t.elapsed_time()).count() < 1)
    {
    }
    RTS_out.write(0);

    while (duration_cast<milliseconds>(dy_t.elapsed_time()).count() < 20)
    {
      if (sXH430.readable())
      {
        // BUGBUG: unsigned char b = _uart.getc();
        // Bug with _uart.getc() on FRDM-K64F. Instead read directly from uart
        return sXH430.read(packet, replySize);
        if (sXH430.read(packet, replySize) == replySize)
        {
          statusReceived = true;
          break;
        }
      }
    }
    dy_t.stop();
  }

  if (statusReceived)
  {
    data1 = packet[9] + packet[10] * 256;
    data2 = packet[22] + packet[23] * 256;
    data3 = packet[35] + packet[36] * 256;
    data4 = packet[48] + packet[49] * 256;
  }
  else
  {
  }
  RTS_out.write(1);
  return statusReceived;
}

uint8_t XH430::read_2byte_packet_sync(uint8_t id, uint16_t &data)
{
  uint8_t packet[52];
  Timer dy_t;
  unsigned short CRC;
  wchar_t packet_len = 7; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = id;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = 0x02;              // Instruction 0x83 is sync_write
  packet[8] = 126 & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (126 >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = 0x02;             // data length = 4 byte
  packet[11] = 0x00;
  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[12] = (CRC & 0x00ff);
  packet[13] = (CRC >> 8) & 0x00ff;

  // 0.0016 s
  sXH430.write(packet, 14);
  dy_t.start();
  while (duration_cast<microseconds>(dy_t.elapsed_time()).count() < 1215)
  {
  }

  RTS_out.write(0);

  int replySize = 13;
  int i_count = 0;
  // we'll only get a reply if it was not broadcast (and status reply option is
  // selected in servo)
  bool statusReceived = false;

  if (id != 0xFE)
  {
    // 0.0046 s

    while (duration_cast<milliseconds>(dy_t.elapsed_time()).count() < 10)
    {
      if (sXH430.readable())
      {
        // BUGBUG: unsigned char b = _uart.getc();
        // Bug with _uart.getc() on FRDM-K64F. Instead read directly from uart

        if (sXH430.read(packet, replySize) == replySize)
        {
          statusReceived = true;
          break;
        }
      }
    }
    dy_t.stop();
  }

  if (statusReceived)
  {
    data = packet[9] + packet[10] * 256;
  }
  else
  {
  }
  RTS_out.write(1);

  return statusReceived;
}

uint8_t XH430::read_ping_status(uint8_t id)
{
  uint8_t packet[52];
  Timer dy_t;
  unsigned short CRC;
  wchar_t packet_len = 3; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = id;
  packet[5] = 0x03;
  packet[6] = 0x00;
  packet[7] = 0x01;              // Instruction 0x01 is ping
  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[8] = (CRC & 0x00ff);
  packet[9] = (CRC >> 8) & 0x00ff;

  // 0.0016 s
  sXH430.write(packet, 10);
  dy_t.start();
  while (duration_cast<microseconds>(dy_t.elapsed_time()).count() < 1215)
  {
  }

  RTS_out.write(0);

  int replySize = 13;
  int i_count = 0;
  // we'll only get a reply if it was not broadcast (and status reply option is
  // selected in servo)
  bool statusReceived = false;

  if (id != 0xFE)
  {
    // 0.0046 s

    while (duration_cast<milliseconds>(dy_t.elapsed_time()).count() < 10)
    {
      if (sXH430.readable())
      {
        // BUGBUG: unsigned char b = _uart.getc();
        // Bug with _uart.getc() on FRDM-K64F. Instead read directly from uart

        if (sXH430.read(packet, replySize) == replySize)
        {
          statusReceived = true;
          break;
        }
      }
    }
    dy_t.stop();
  }

  if (statusReceived)
  {
    data = packet[9] + packet[10] * 256;
  }
  else
  {
  }
  RTS_out.write(1);

  return statusReceived;
}

uint8_t XH430::read_2byte_packet_sync(uint8_t id[9],
                                      int16_t data[9])
{
  uint8_t packet[117];
int packet_count = 0;
  Timer dy_t;
  unsigned short CRC;
  wchar_t packet_len = 16; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = 0xfe;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = 0x82;              // Instruction 0x83 is sync_write
  packet[8] = 126 & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (126 >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = 0x02;             // data length = 4 byte
  packet[11] = 0x00;
  packet[12] = id[0];                          // id1
  packet[13] = id[1];                          // id2
  packet[14] = id[2];                          // id3
  packet[15] = id[3];                          // id4
  packet[16] = id[4];                          // id4
  packet[17] = id[5];                          // id4
  packet[18] = id[6];                          // id4
  packet[19] = id[7];                          // id4
  packet[20] = id[8];                          // id4
  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[21] = (CRC & 0x00ff);
  packet[22] = (CRC >> 8) & 0x00ff;

  // 0.0016 s
  sXH430.write(packet, 23);
  dy_t.reset();
  dy_t.start();
  while (duration_cast<microseconds>(dy_t.elapsed_time()).count() < 1062)
  {
  }
  RTS_out.write(0);
  int replySize = 117;

  // we'll only get a reply if it was not broadcast (and status reply option is
  // selected in servo)
  bool statusReceived = false;


  dy_t.reset();
  // 0.0046 s
  while (duration_cast<milliseconds>(dy_t.elapsed_time()).count() < 20)
  {
    if (sXH430.readable())
    {
      // BUGBUG: unsigned char b = _uart.getc();
      // Bug with _uart.getc() on FRDM-K64F. Instead read directly from uart

      sXH430.read(packet + packet_count, 1);
      packet_count++;
      if (packet_count == replySize)
      {
        statusReceived = true;
        break;
      }
    }
  }
  dy_t.stop();

  // 0.0053

  if (statusReceived)
  {
    data[0] = packet[9] + packet[10] * 256;
    data[1] = packet[22] + packet[23] * 256;
    data[2] = packet[35] + packet[36] * 256;
    data[3] = packet[48] + packet[49] * 256;
    data[4] = packet[61] + packet[62] * 256;
    data[5] = packet[74] + packet[75] * 256;
    data[6] = packet[87] + packet[88] * 256;
    data[7] = packet[100] + packet[101] * 256;
    data[8] = packet[113] + packet[114] * 256;
  }
  RTS_out.write(1);
  return statusReceived;
}

void XH430::make_2byte_packet_sync(uint16_t address, uint16_t data1,
                                   uint16_t data2, uint16_t data3,
                                   uint16_t data4, uint16_t data5,
                                   uint16_t data6, uint16_t data7,
                                   uint16_t data8, uint16_t data9)
{

  uint8_t packet[41];
  unsigned short CRC;
  wchar_t packet_len = 34; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = 0xfe;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = 0x83;                  // Instruction 0x83 is sync_write
  packet[8] = address & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (address >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = 0x02;                 // data length = 2 byte
  packet[11] = 0x00;
  packet[12] = 0x01; // id1
  packet[13] = data1 & 0xff;
  packet[14] = (data1 >> 8) & 0xff;
  packet[15] = 0x02; // id2
  packet[16] = data2 & 0xff;
  packet[17] = (data2 >> 8) & 0xff;
  packet[18] = 0x03; // id3
  packet[19] = data3 & 0xff;
  packet[20] = (data3 >> 8) & 0xff;
  packet[21] = 0x04; // id4
  packet[22] = data4 & 0xff;
  packet[23] = (data4 >> 8) & 0xff;
  packet[24] = 0x0b; // id11
  packet[25] = data5 & 0xff;
  packet[26] = (data5 >> 8) & 0xff;
  packet[27] = 0x0c; // id12
  packet[28] = data6 & 0xff;
  packet[29] = (data6 >> 8) & 0xff;
  packet[30] = 0x0d; // id13
  packet[31] = data7 & 0xff;
  packet[32] = (data7 >> 8) & 0xff;
  packet[33] = 0x0e; // id14
  packet[34] = data8 & 0xff;
  packet[35] = (data8 >> 8) & 0xff;
  packet[36] = 0x09; // id9
  packet[37] = data9 & 0xff;
  packet[38] = (data9 >> 8) & 0xff;

  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[39] = (CRC & 0x00ff);
  packet[40] = (CRC >> 8) & 0x00ff;

  sXH430.write(packet, 41);
}

void XH430::make_1byte_packet_2motor(uint8_t id1, uint8_t id2, uint16_t address,
	int8_t data)
{

	uint8_t packet[18];
	unsigned short CRC;
	wchar_t packet_len = 11; // packet_len = number of parameter +3

	packet[0] = 0xff;
	packet[1] = 0xff;
	packet[2] = 0xfd;
	packet[3] = 0x00;
	packet[4] = 0xfe;
	packet[5] = packet_len & 0xff;
	packet[6] = (packet_len >> 8) & 0xff;
	packet[7] = 0x83;                  // Instruction 0x83 is sync_write
	
	packet[8] = address & 0xff;        // Address goal position 116, 0x0074
	packet[9] = (address >> 8) & 0xff; // Address goal position 116, 0x0074
	packet[10] = 0x01;	               // data byte 
	packet[11] = 0x00; 
	packet[12] = id1;
	packet[13] = data;
	packet[14] = id2; 
	packet[15] = data; 

	CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
	packet[16] = (CRC & 0x00ff);
	packet[17] = (CRC >> 8) & 0x00ff;

	sXH430.write(packet, 18);
}

void XH430::make_2byte_packet_2motor(uint8_t id1, uint8_t id2, uint16_t address,
	int8_t data)
{

	uint8_t packet[20];
	unsigned short CRC;
	wchar_t packet_len = 13; // packet_len = number of parameter +3

	packet[0] = 0xff;
	packet[1] = 0xff;
	packet[2] = 0xfd;
	packet[3] = 0x00;
	packet[4] = 0xfe;
	packet[5] = packet_len & 0xff;
	packet[6] = (packet_len >> 8) & 0xff;
	packet[7] = 0x83;                  // Instruction 0x83 is sync_write

	packet[8] = address & 0xff;        // Address goal position 116, 0x0074
	packet[9] = (address >> 8) & 0xff; // Address goal position 116, 0x0074
	packet[10] = 0x01;	               // data byte 
	packet[11] = 0x00;
	packet[12] = id1;
	packet[13] = data & 0xff;
	packet[14] = (data >> 8) & 0xff;
	packet[15] = id2;
	packet[16] = data & 0xff;
	packet[17] = (data >> 8) & 0xff;


	CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
	packet[18] = (CRC & 0x00ff);
	packet[19] = (CRC >> 8) & 0x00ff;

	sXH430.write(packet, 20);
}


void XH430::make_1byte_packet_sync(uint16_t address, uint8_t data1,
                                   uint8_t data2, uint8_t data3, uint8_t data4,
                                   uint8_t data5, uint8_t data6, uint8_t data7,
                                   uint8_t data8, uint8_t data9)
{

  uint8_t packet[32];
  unsigned short CRC;
  wchar_t packet_len = 25; // packet_len = number of parameter +3

  packet[0] = 0xff;
  packet[1] = 0xff;
  packet[2] = 0xfd;
  packet[3] = 0x00;
  packet[4] = 0xfe;
  packet[5] = packet_len & 0xff;
  packet[6] = (packet_len >> 8) & 0xff;
  packet[7] = 0x83;                  // Instruction 0x83 is sync_write
  
  packet[8] = address & 0xff;        // Address goal position 116, 0x0074
  packet[9] = (address >> 8) & 0xff; // Address goal position 116, 0x0074
  packet[10] = 0x01;                 // data length = 1 byte
  packet[11] = 0x00;
  packet[12] = 0x01; // id1
  packet[13] = data1;
  packet[14] = 0x02; // id2
  packet[15] = data2;
  packet[16] = 0x03; // id3
  packet[17] = data3;
  packet[18] = 0x04; // id4
  packet[19] = data4;
  packet[20] = 0x0b; // id11
  packet[21] = data5;
  packet[22] = 0x0c; // id12
  packet[23] = data6;
  packet[24] = 0x0d; // id13
  packet[25] = data7;
  packet[26] = 0x0e; // id14
  packet[27] = data8;
  packet[28] = 0x09; // id9
  packet[29] = data9;

  CRC = update_crc(0, packet, packet_len + 5); // packet length + 5
  packet[30] = (CRC & 0x00ff);
  packet[31] = (CRC >> 8) & 0x00ff;

  sXH430.write(packet, 32);
}

unsigned short XH430::update_crc(unsigned short crc_accum,
                                 unsigned char *data_blk_ptr,
                                 unsigned short data_blk_size)
{
  unsigned short i, j;
  unsigned short crc_table[256] = {
      0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011, 0x8033,
      0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022, 0x8063, 0x0066,
      0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072, 0x0050, 0x8055, 0x805F,
      0x005A, 0x804B, 0x004E, 0x0044, 0x8041, 0x80C3, 0x00C6, 0x00CC, 0x80C9,
      0x00D8, 0x80DD, 0x80D7, 0x00D2, 0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB,
      0x00EE, 0x00E4, 0x80E1, 0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE,
      0x00B4, 0x80B1, 0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087,
      0x0082, 0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192,
      0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1, 0x01E0,
      0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1, 0x81D3, 0x01D6,
      0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2, 0x0140, 0x8145, 0x814F,
      0x014A, 0x815B, 0x015E, 0x0154, 0x8151, 0x8173, 0x0176, 0x017C, 0x8179,
      0x0168, 0x816D, 0x8167, 0x0162, 0x8123, 0x0126, 0x012C, 0x8129, 0x0138,
      0x813D, 0x8137, 0x0132, 0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E,
      0x0104, 0x8101, 0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317,
      0x0312, 0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
      0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371, 0x8353,
      0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342, 0x03C0, 0x83C5,
      0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1, 0x83F3, 0x03F6, 0x03FC,
      0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2, 0x83A3, 0x03A6, 0x03AC, 0x83A9,
      0x03B8, 0x83BD, 0x83B7, 0x03B2, 0x0390, 0x8395, 0x839F, 0x039A, 0x838B,
      0x038E, 0x0384, 0x8381, 0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E,
      0x0294, 0x8291, 0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7,
      0x02A2, 0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2,
      0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1, 0x8243,
      0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252, 0x0270, 0x8275,
      0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261, 0x0220, 0x8225, 0x822F,
      0x022A, 0x823B, 0x023E, 0x0234, 0x8231, 0x8213, 0x0216, 0x021C, 0x8219,
      0x0208, 0x820D, 0x8207, 0x0202};

  for (j = 0; j < data_blk_size; j++)
  {
    i = ((unsigned short)(crc_accum >> 8) ^ data_blk_ptr[j]) & 0xFF;
    crc_accum = (crc_accum << 8) ^ crc_table[i];
  }
  return crc_accum;
}
