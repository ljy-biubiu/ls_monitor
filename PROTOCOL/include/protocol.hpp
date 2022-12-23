#ifndef PROTOCOL_H
#define PROTOCOL_H

/*recv ring buffer size*/
#define RECEIVE_BUFFER_SIZE 1024

#define ASK_READ_DATA_BUFFER_SIZE 12
#define ASK_WRITE_DATA_BUFFER_SIZE 572

#define RECEIVE_DATA_SIZE 1024
#define BUF_SIZE 16

#include "memory.h"
#include "poms.hpp"
#include "my_Util.h"


struct ReadData
{
  float lidar_x{0};
  float lidar_y{0};
  float lidar_z{0};
  float shipyard_safe_distance{0};
  float resolution{0};
  float build_map_signal{0};
  float comnunication_flag{0};
  float device_status{0};
  float material_area_x{0};
  float material_area_y{0};
  float meterial_area_length{0};
  float meterial_area_width{0};
  float technology{0};
  float angle{0};
  float x_roll{0};
  float y_pitch{0};
  float z_yaw{0};
  float quaternion_w{0};
  float quaternion_x{0};
  float quaternion_y{0};
  float quaternion_z{0};
  float unused_1{0};
  float unused_2{0};
  float unused_3{0};
};

struct InCabinArea
{
  float inCabin_A_X{33};    
  float inCabin_A_Y{5};
  float inCabin_A_Z{5};
  float inCabin_B_X{5};
  float inCabin_B_Y{5};
  float inCabin_B_Z{5};
  float inCabin_C_X{5};
  float inCabin_C_Y{5};
  float inCabin_C_Z{5};
  float inCabin_D_X{5};
  float inCabin_D_Y{5};
  float inCabin_D_Z{5};
};

struct HatchArea
{
  float hatch_A_X{0};
  float hatch_A_Y{0};
  float hatch_A_Z{0};
  float hatch_B_X{0};
  float hatch_B_Y{0};
  float hatch_B_Z{0};
  float hatch_C_X{0};
  float hatch_C_Y{0};
  float hatch_C_Z{0};
  float hatch_D_X{0};
  float hatch_D_Y{0};
  float hatch_D_Z{0};
};

struct AisleArea
{
  float aisle_A_X{25};
  float aisle_A_Y{26};
  float aisle_B_X{0};
  float aisle_B_Y{0};
  float aisle_C_X{0};
  float aisle_C_Y{0};
  float aisle_D_X{0};
  float aisle_D_Y{0};
};

struct DeckArea
{
  float deck_A_X{2};
  float deck_A_Y{2};
  float deck_B_X{2};
  float deck_B_Y{2};
  float deck_C_X{2};
  float deck_C_Y{2};
  float deck_D_X{2};
  float deck_D_Y{2};
};

struct MterialArea
{
  float mterial_A_X{0};
  float mterial_A_Y{0};
  float mterial_B_X{0};
  float mterial_B_Y{0};
  float mterial_C_X{0};
  float mterial_C_Y{0};
  float mterial_D_X{0};
  float mterial_D_Y{0};
};

struct GrabMaterialArea
{
  float area1_X{0};
  float area1_Y{50};
  float area1_Z{0};
  float area2_X{0};
  float area2_Y{0};
  float area2_Z{0};
  float area3_X{0};
  float area3_Y{0};
  float area3_Z{0};
  float area4_X{0};
  float area4_Y{0};
  float area4_Z{0};
  float area5_X{0};
  float area5_Y{0};
  float area5_Z{0};
  float area6_X{0};
  float area6_Y{0};
  float area6_Z{0};
  float area7_X{0};
  float area7_Y{0};
  float area7_Z{0};
  float area8_X{0};
  float area8_Y{0};
  float area8_Z{0};
  float area9_X{0};
  float area9_Y{0};
  float area9_Z{0};
  float area10_X{0};
  float area10_Y{0};
  float area10_Z{0};

  float area11_X{0};
  float area11_Y{0};
  float area11_Z{0};
  float area12_X{0};
  float area12_Y{0};
  float area12_Z{0};
  float area13_X{0};
  float area13_Y{0};
  float area13_Z{0};
  float area14_X{0};
  float area14_Y{0};
  float area14_Z{0};
  float area15_X{0};
  float area15_Y{0};
  float area15_Z{0};
  float area16_X{0};
  float area16_Y{0};
  float area16_Z{0};
  float area17_X{0};
  float area17_Y{0};
  float area17_Z{0};
  float area18_X{0};
  float area18_Y{0};
  float area18_Z{0};
  float area19_X{0};
  float area19_Y{0};
  float area19_Z{0};
  float area20_X{0};
  float area20_Y{0};
  float area20_Z{0};

  float area21_X{0};
  float area21_Y{0};
  float area21_Z{0};
  float area22_X{0};
  float area22_Y{0};
  float area22_Z{0};
  float area23_X{0};
  float area23_Y{0};
  float area23_Z{0};
  float area24_X{0};
  float area24_Y{0};
  float area24_Z{0};
  float area25_X{0};
  float area25_Y{0};
  float area25_Z{0};
};

struct SetMaterialArea
{
  float area1_X{0};
  float area1_Y{0};
  float area1_Z{0};

  float area2_Z{0};
  float area3_Z{0};
  float area4_Z{0};
  float area5_Z{0};
  float area6_Z{0};
  float area7_Z{0};
  float area8_Z{0};
  float area9_Z{0};
};

struct Status
{
  float build_map_signal{0};
  float comnunication_flag{11};
  float data_cnt{11};
  float fault{11};
  float board_angle{0};
  float backgound_z{0};
};

struct Unused
{
  float unused1{0};
  float unused2{0};
  float unused3{0};
  float unused4{0};
  float unused5{0};
  float unused6{0};
  float unused7{0};
  float unused8{0};
  float unused9{66};
  float unused10{55};
};

struct WriteData
{
  InCabinArea inCabinArea; //12  
  HatchArea hatchArea; //12
  AisleArea aisleArea; //8
  DeckArea deckArea;//8
  MterialArea mterialArea;//8
  GrabMaterialArea grabMaterialArea;
  SetMaterialArea setMaterialArea;
  Status status;
  Unused unused;  //暂时用于补全600字节
};

struct ComunicationData
{
  ReadData read_data;
  WriteData write_data;
  GPFPD_INFO gpfpd_info;
};

//  00 00 00 00 00 06 01 03 00 00 00 02
struct AskPlcReadHead
{
  unsigned char data1{0};
  unsigned char data2{0};
  unsigned char data3{0};
  unsigned char data4{0};
  unsigned char data5{0};
  unsigned char data6{6};
  unsigned char data7{1};
  unsigned char data8{3};
  unsigned char data9{0};
  unsigned char data10{0};
  unsigned char data11{0};
  unsigned char data12{48};
};

// 包头
// 01 02 00 00 00 07 01 03 04
struct ReturnAskPlcReadHead
{
  unsigned char data1{0};
  unsigned char data2{0};
  unsigned char data3{0};
  unsigned char data4{0};
  unsigned char data5{0};
  unsigned char data6{96};
  unsigned char data7{1};
  unsigned char data8{3};
  unsigned char data9{4};
};

// 包头  //每次只能发200个字节
struct PlcWriteHead
{
  unsigned char data1{0};
  unsigned char data2{0};

  unsigned char data3{0};
  unsigned char data4{0};

  unsigned char data5{0x00};
  unsigned char data6{0xcf};

  unsigned char data7{0x01};
  unsigned char data8{0x10};

  unsigned char data9{0x00};
  unsigned char data10{0x54};

  unsigned char data11{0x00};
  unsigned char data12{0x64};

  unsigned char data13{0xc8};
};

// 包头

struct ReturnPlcWriteHead
{
  unsigned char data1{0};
  unsigned char data2{0};

  unsigned char data3{10};
  unsigned char data4{4};

  unsigned char data5{2}; // data5 + data6  **字节
  unsigned char data6{37};

  unsigned char data7{1};
  unsigned char data8{16};

  unsigned char data9{0};
  unsigned char data10{3};

  unsigned char data11{1};
  unsigned char data12{14};
};

#endif
