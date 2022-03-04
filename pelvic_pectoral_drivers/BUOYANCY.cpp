#include "BUOYANCY.h"

BUOYANCY::BUOYANCY(uint8_t id1, uint8_t id2, XH430 *dxl) : led(LED2)
{
	id1_ = id1;
	id2_ = id2;
	dxl_ = dxl;
}

BUOYANCY::~BUOYANCY(){};

void BUOYANCY::set_current(int32_t current) //EPPROM setting => Torque off �ʼ�
{
	//dxl_->make_2byte_packet(id1_, WRITE, CURRENT_LIMIT, current_);
	//ThisThread::sleep_for(300ms);
	//dxl_->make_2byte_packet(id1_, WRITE, CURRENT_LIMIT, current_);
	//ThisThread::sleep_for(300ms);
	dxl_->make_2byte_packet_2motor(id1_, id2_, CURRENT_LIMIT, current);
}

void BUOYANCY::off(void)
{
	//dxl_->make_1byte_packet(id1_, WRITE, TORQUE_ENABLE, 0); // front buoyancy controller id : 98
	//ThisThread::sleep_for(300ms);
	//dxl_->make_1byte_packet(id_2, WRITE, TORQUE_ENABLE, 0); // rear buoyancy controller id : 99
	//ThisThread::sleep_for(300ms);

	//void make_1byte_packet_2motor(uint8_t id1, uint8_t id2, uint16_t address,int8_t data);
	dxl_->make_1byte_packet_2motor(id1_, id2_, TORQUE_ENABLE, 0);
}

void BUOYANCY::on(void)
{
	//dxl_->make_1byte_packet(id1_, WRITE, TORQUE_ENABLE, 1); // front buoyancy controller id : 98
	//ThisThread::sleep_for(300ms);
	//dxl_->make_1byte_packet(id_2, WRITE, TORQUE_ENABLE, 1); // rear buoyancy controller id : 99
	//ThisThread::sleep_for(300ms);
	dxl_->make_1byte_packet_2motor(id1_, id2_, TORQUE_ENABLE, 1);
}

void BUOYANCY::write_ang(int fr_ang, int rr_ang)
{
	dxl_->make_4byte_packet_sync(id1_, id2_, fr_ang, rr_ang);
}

void BUOYANCY::initialization(void)
{
	uint8_t ping1, ping2;
	// step1 : torque enable
	BUOYANCY::off();
	ThisThread::sleep_for(100ms);
	printf("step1 : torque enable\r\n");
	BUOYANCY::on();
	ThisThread::sleep_for(100ms);
	printf("step2\r\n");
	// step2 : set goal current
	BUOYANCY::set_current(650);
	ThisThread::sleep_for(100ms);
	printf("step3 ---\r\n");
	BUOYANCY::write_ang(-5000, -5000);
	ThisThread::sleep_for(5s);
	BUOYANCY::set_current(125);
	ThisThread::sleep_for(100ms);
	printf("step3\r\n");
	// step3 : go to min buoyancy position
	BUOYANCY::write_ang(105000, 105000);
	ThisThread::sleep_for(100ms);
	while (1)
	{
		dxl_->read_moving_status(id1_, ping1);
		ThisThread::sleep_for(100ms);
		//dxl_->read_ping_status(id2_, ping2);
		//ThisThread::sleep_for(100ms);
		//if (ping1 != 0 && ping2 != 0)
		printf("ping1 %u\r\n", ping1);
		if (ping1 != 1)
		{
			break;
		}
	}
	printf("step4\r\n");
	// step 4: reboot dynamixel
	BUOYANCY::off();
	ThisThread::sleep_for(100ms);
	BUOYANCY::on();
	ThisThread::sleep_for(100ms);
	printf("step5\r\n");
	// step5 : set goal current
	BUOYANCY::set_current(650);
	ThisThread::sleep_for(100ms);
	printf("step6\r\n");
	// step6 : set zero point
	BUOYANCY::write_ang(0, 0);
	printf("step7\r\n");
	// step7 : set randomic position
	ThisThread::sleep_for(100ms);
	while (1)
	{
		dxl_->read_moving_status(id1_, ping1);
		ThisThread::sleep_for(100ms);
		//dxl_->read_ping_status(id2_, ping2);
		//ThisThread::sleep_for(100ms);
		//if (ping1 != 0 && ping2 != 0)
		printf("ping1 %u\r\n", ping1);
		if (ping1 != 1)
		{
			break;
		}
	}
	printf("end\r\n");
}
