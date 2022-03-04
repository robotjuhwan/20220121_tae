#include "BUOYANCY.h"

BUOYANCY::BUOYANCY(uint8_t id1, uint8_t id2, XH430 *dxl):led(LED2)
{
    id1_ = id1;
    id2_ = id2;
    dxl_ = dxl;
	
}

BUOYANCY::~BUOYANCY(){};

void BUOYANCY::set_current(int32_t current) //EPPROM setting => Torque off ÇÊ¼ö 
{
	current_ = current;
	//dxl_->make_2byte_packet(id1_, WRITE, CURRENT_LIMIT, current_);
	//ThisThread::sleep_for(300ms);
	//dxl_->make_2byte_packet(id1_, WRITE, CURRENT_LIMIT, current_);
	//ThisThread::sleep_for(300ms);
	dxl->make_2byte_packet_2motor(id1_, id2_, CURRENT_LIMIT, current_);
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
	fr_ang_ = fr_ang; 
	rr_ang_ = rr_ang; 

	dxl_->make_4byte_packet_sync(id1_, id2_, motor_ang_arr1, motor_ang_arr2);
}

