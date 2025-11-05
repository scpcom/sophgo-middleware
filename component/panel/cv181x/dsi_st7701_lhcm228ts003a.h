#ifndef _MIPI_TX_PARAM_ST_7701_LHCM228TS003A_H_
#define _MIPI_TX_PARAM_ST_7701_LHCM228TS003A_H_

#ifndef __UBOOT__
#include <linux/vo_mipi_tx.h>
#include <linux/cvi_comm_mipi_tx.h>
#else
#include <cvi_mipi.h>
#endif

// vendor
/*
#define ST7701_LHCM228TS003A_VACT	552
#define ST7701_LHCM228TS003A_VSA		2
#define ST7701_LHCM228TS003A_VBP		20
#define ST7701_LHCM228TS003A_VFP		20

#define ST7701_LHCM228TS003A_HACT		368
#define ST7701_LHCM228TS003A_HSA		8
#define ST7701_LHCM228TS003A_HBP		160
#define ST7701_LHCM228TS003A_HFP		160
*/

// calc 2
#define ST7701_LHCM228TS003A_VACT		552
#define ST7701_LHCM228TS003A_VSA		10
#define ST7701_LHCM228TS003A_VBP		20
#define ST7701_LHCM228TS003A_VFP		20

#define ST7701_LHCM228TS003A_HACT		368
#define ST7701_LHCM228TS003A_HSA		8
#define ST7701_LHCM228TS003A_HBP		160
#define ST7701_LHCM228TS003A_HFP		160




// calc
/*
#define ST7701_LHCM228TS003A_VACT	552
#define ST7701_LHCM228TS003A_VSA	10
#define ST7701_LHCM228TS003A_VBP	6
#define ST7701_LHCM228TS003A_VFP	3

#define ST7701_LHCM228TS003A_HACT	368
#define ST7701_LHCM228TS003A_HSA	32
#define ST7701_LHCM228TS003A_HBP	80
#define ST7701_LHCM228TS003A_HFP	48
*/

#define LHCM22_PIXEL_CLK(x) ((x##_VACT + x##_VSA + x##_VBP + x##_VFP) \
	* (x##_HACT + x##_HSA + x##_HBP + x##_HFP) * 75 / 1000)

struct combo_dev_cfg_s dev_cfg_st7701_368x552lhcm = {
	.devno = 0,
	.lane_id = {MIPI_TX_LANE_0, MIPI_TX_LANE_CLK, MIPI_TX_LANE_1, -1, -1},
	.lane_pn_swap = {false, false, false, false, false},
	.output_mode = OUTPUT_MODE_DSI_VIDEO,
	.video_mode = BURST_MODE,
	.output_format = OUT_FORMAT_RGB_24_BIT,
	.sync_info = {
		.vid_hsa_pixels = ST7701_LHCM228TS003A_HSA,
		.vid_hbp_pixels = ST7701_LHCM228TS003A_HBP,
		.vid_hfp_pixels = ST7701_LHCM228TS003A_HFP,
		.vid_hline_pixels = ST7701_LHCM228TS003A_HACT,
		.vid_vsa_lines = ST7701_LHCM228TS003A_VSA,
		.vid_vbp_lines = ST7701_LHCM228TS003A_VBP,
		.vid_vfp_lines = ST7701_LHCM228TS003A_VFP,
		.vid_active_lines = ST7701_LHCM228TS003A_VACT,
		.vid_vsa_pos_polarity = true,
		.vid_hsa_pos_polarity = false,
	},
	.pixel_clk = LHCM22_PIXEL_CLK(ST7701_LHCM228TS003A),
};

const struct hs_settle_s hs_timing_cfg_st7701_368x552lhcm = { .prepare = 6, .zero = 32, .trail = 1 };

#ifndef CVI_U8
#define CVI_U8 unsigned char
#endif

static CVI_U8 data_st7701_lhcm228ts003a_1[] = { 0xff, 0x77,0x01,0x00,0x00,0x13 }; // 6
static CVI_U8 data_st7701_lhcm228ts003a_2[] = { 0xef, 0x08 }; // 2
static CVI_U8 data_st7701_lhcm228ts003a_3[] = { 0xff, 0x77,0x01,0x00,0x00,0x10 }; // 6
static CVI_U8 data_st7701_lhcm228ts003a_4[] = { 0xc0, 0x44, 0x00 }; // 3
static CVI_U8 data_st7701_lhcm228ts003a_5[] = { 0xc1, 0x0b, 0x02 }; // 3
static CVI_U8 data_st7701_lhcm228ts003a_6[] = { 0xc2, 0x07, 0x1f }; // 3
static CVI_U8 data_st7701_lhcm228ts003a_7[] = { 0xcc, 0x10 }; // 2
static CVI_U8 data_st7701_lhcm228ts003a_8[] = { 0xb0, 0x0F,0x1E,0x25,0x0D,0x11,0x06,0x12,0x08,0x08,0x2A,0x05,0x12,0x10,0x2B,0x32,0x1F }; // 17
static CVI_U8 data_st7701_lhcm228ts003a_9[] = { 0xb1, 0x0F,0x1E,0x25,0x0D,0x11,0x05,0x12,0x08,0x08,0x2B,0x05,0x12,0x10,0x2B,0x32,0x1F }; // 17
static CVI_U8 data_st7701_lhcm228ts003a_10[] = { 0xff, 0x77,0x01,0x00,0x00,0x11 }; // 6
static CVI_U8 data_st7701_lhcm228ts003a_11[] = { 0xb0, 0x35 }; // 2
static CVI_U8 data_st7701_lhcm228ts003a_12[] = { 0xb1, 0x45 }; // 2
static CVI_U8 data_st7701_lhcm228ts003a_13[] = { 0xb2, 0x87 }; // 2
static CVI_U8 data_st7701_lhcm228ts003a_14[] = { 0xb3, 0x80 }; // 2
static CVI_U8 data_st7701_lhcm228ts003a_15[] = { 0xb5, 0x80 }; // 2 
static CVI_U8 data_st7701_lhcm228ts003a_16[] = { 0xb7, 0x85 }; // 2
static CVI_U8 data_st7701_lhcm228ts003a_17[] = { 0xb8, 0x11 }; // 2
static CVI_U8 data_st7701_lhcm228ts003a_18[] = { 0xbb, 0x03 }; // 2
static CVI_U8 data_st7701_lhcm228ts003a_19[] = { 0xc0, 0x07 }; // 2
static CVI_U8 data_st7701_lhcm228ts003a_20[] = { 0xc1, 0x78 }; // 2
static CVI_U8 data_st7701_lhcm228ts003a_21[] = { 0xc2, 0x78 }; // 2
static CVI_U8 data_st7701_lhcm228ts003a_22[] = { 0xd0, 0x88 }; // 2
// 23 delay 100 ms
static CVI_U8 data_st7701_lhcm228ts003a_24[] = { 0xe0, 0x00, 0x00, 0x02}; // 4
static CVI_U8 data_st7701_lhcm228ts003a_25[] = { 0xe1, 0x03,0x30,0x07,0x30,0x02,0x30,0x06,0x30,0x00,0x44,0x44 }; //12
static CVI_U8 data_st7701_lhcm228ts003a_26[] = { 0xe2, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }; //12
static CVI_U8 data_st7701_lhcm228ts003a_27[] = { 0xe3, 0x00,0x00,0x22,0x00 }; // 5
static CVI_U8 data_st7701_lhcm228ts003a_28[] = { 0xe4, 0x22, 0x00 }; // 3
static CVI_U8 data_st7701_lhcm228ts003a_29[] = { 0xe5, 0x0A,0x34,0x30,0xE0,0x08,0x32,0x30,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }; // 17
static CVI_U8 data_st7701_lhcm228ts003a_30[] = { 0xe6, 0x00, 0x00, 0x22, 0x00 }; // 5
static CVI_U8 data_st7701_lhcm228ts003a_31[] = { 0xe7, 0x22, 0x00 }; // 3
static CVI_U8 data_st7701_lhcm228ts003a_32[] = { 0xe8, 0x09,0x33,0x30,0xE0,0x07,0x31,0x30,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }; // 17
static CVI_U8 data_st7701_lhcm228ts003a_33[] = { 0xeb, 0x00,0x01,0x10,0x10,0x11,0x00,0x00 }; // 8
static CVI_U8 data_st7701_lhcm228ts003a_34[] = { 0xed, 0xFF,0xFF,0xF0,0x45,0xBA,0x2F,0xFF,0xFF,0xFF,0xFF,0xF2,0xAB,0x54,0x0F,0xFF,0xFF }; // 17
static CVI_U8 data_st7701_lhcm228ts003a_35[] = { 0xef, 0x08,0x08,0x08,0x45,0x3F,0x54 }; // 7
static CVI_U8 data_st7701_lhcm228ts003a_36[] = { 0xff, 0x77,0x01,0x00,0x00,0x13 }; // 6
static CVI_U8 data_st7701_lhcm228ts003a_37[] = { 0xe8, 0x00, 0x0e }; // 3
static CVI_U8 data_st7701_lhcm228ts003a_38[] = { 0x11 }; // 1
// 39 delay 120 ms
static CVI_U8 data_st7701_lhcm228ts003a_40[] = { 0xe8, 0x00, 0x0c }; // 3
// 41 delay 10 ms
static CVI_U8 data_st7701_lhcm228ts003a_42[] = { 0xe8, 0x00, 0x00 }; // 3
static CVI_U8 data_st7701_lhcm228ts003a_43[] = { 0xff, 0x77,0x01,0x00,0x00,0x00 }; // 6
static CVI_U8 data_st7701_lhcm228ts003a_44[] = { 0x29 }; // 1
// 45 delay 50 ms


// len == 1 , type 0x05
// len == 2 , type 0x15 or type 23
// len >= 3 , type 0x29 or type 0x39
#define TYPE1_DCS_SHORT_WRITE 0x05
#define TYPE2_DCS_SHORT_WRITE 0x15
#define TYPE3_DCS_LONG_WRITE 0x39
#define TYPE3_GENERIC_LONG_WRITE 0x29
const struct dsc_instr dsi_init_cmds_st7701_368x552lhcm[] = {
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 6, .data = data_st7701_lhcm228ts003a_1 },
  {.delay = 0, .data_type = TYPE2_DCS_SHORT_WRITE, .size = 2, .data = data_st7701_lhcm228ts003a_2 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 6, .data = data_st7701_lhcm228ts003a_3 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 3, .data = data_st7701_lhcm228ts003a_4 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 3, .data = data_st7701_lhcm228ts003a_5 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 3, .data = data_st7701_lhcm228ts003a_6 },
  {.delay = 0, .data_type = TYPE2_DCS_SHORT_WRITE, .size = 2, .data = data_st7701_lhcm228ts003a_7 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 17, .data = data_st7701_lhcm228ts003a_8 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 17, .data = data_st7701_lhcm228ts003a_9 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 6, .data = data_st7701_lhcm228ts003a_10 },
  {.delay = 0, .data_type = TYPE2_DCS_SHORT_WRITE, .size = 2, .data = data_st7701_lhcm228ts003a_11 },
  {.delay = 0, .data_type = TYPE2_DCS_SHORT_WRITE, .size = 2, .data = data_st7701_lhcm228ts003a_12 },
  {.delay = 0, .data_type = TYPE2_DCS_SHORT_WRITE, .size = 2, .data = data_st7701_lhcm228ts003a_13 },
  {.delay = 0, .data_type = TYPE2_DCS_SHORT_WRITE, .size = 2, .data = data_st7701_lhcm228ts003a_14 },
  {.delay = 0, .data_type = TYPE2_DCS_SHORT_WRITE, .size = 2, .data = data_st7701_lhcm228ts003a_15 },
  {.delay = 0, .data_type = TYPE2_DCS_SHORT_WRITE, .size = 2, .data = data_st7701_lhcm228ts003a_16 },
  {.delay = 0, .data_type = TYPE2_DCS_SHORT_WRITE, .size = 2, .data = data_st7701_lhcm228ts003a_17 },
  {.delay = 0, .data_type = TYPE2_DCS_SHORT_WRITE, .size = 2, .data = data_st7701_lhcm228ts003a_18 },
  {.delay = 0, .data_type = TYPE2_DCS_SHORT_WRITE, .size = 2, .data = data_st7701_lhcm228ts003a_19 },
  {.delay = 0, .data_type = TYPE2_DCS_SHORT_WRITE, .size = 2, .data = data_st7701_lhcm228ts003a_20 },
  {.delay = 0, .data_type = TYPE2_DCS_SHORT_WRITE, .size = 2, .data = data_st7701_lhcm228ts003a_21 },
  {.delay = 100, .data_type = TYPE2_DCS_SHORT_WRITE, .size = 2, .data = data_st7701_lhcm228ts003a_22 },
  // 23 is delay 100ms
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 4, .data = data_st7701_lhcm228ts003a_24 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 12, .data = data_st7701_lhcm228ts003a_25 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 12, .data = data_st7701_lhcm228ts003a_26 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 5, .data = data_st7701_lhcm228ts003a_27 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 3, .data = data_st7701_lhcm228ts003a_28 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 17, .data = data_st7701_lhcm228ts003a_29 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 5, .data = data_st7701_lhcm228ts003a_30 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 3, .data = data_st7701_lhcm228ts003a_31 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 17, .data = data_st7701_lhcm228ts003a_32 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 8, .data = data_st7701_lhcm228ts003a_33 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 17, .data = data_st7701_lhcm228ts003a_34 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 7, .data = data_st7701_lhcm228ts003a_35 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 6, .data = data_st7701_lhcm228ts003a_36 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 3, .data = data_st7701_lhcm228ts003a_37 },
  {.delay = 120, .data_type = TYPE1_DCS_SHORT_WRITE, .size = 1, .data = data_st7701_lhcm228ts003a_38 },
  // 39 is delay 120ms
  {.delay = 10, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 3, .data = data_st7701_lhcm228ts003a_40 },
  // 41 is delay 10ms
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 3, .data = data_st7701_lhcm228ts003a_42 },
  {.delay = 0, .data_type = TYPE3_GENERIC_LONG_WRITE, .size = 6, .data = data_st7701_lhcm228ts003a_43 },
  {.delay = 50, .data_type = TYPE1_DCS_SHORT_WRITE, .size = 1, .data = data_st7701_lhcm228ts003a_44 },
};

#else
#error "_MIPI_TX_PARAM_ST_7701_LHCM228TS003A_H_ multi-delcaration!!"
#endif // _MIPI_TX_PARAM_ST_7701_LHCM228TS003A_H_
