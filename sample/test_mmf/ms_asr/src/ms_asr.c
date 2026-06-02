#include "speech/ms_asr.h"

int  ms_asr_init(int device_type, char* device_name, am_args_t* am_args, int dbg_flag)
{
	return -1;
}

void ms_asr_deinit(void)
{
	return;
}

int  ms_asr_decoder_cfg(int decoder_type, decoder_cb_t decoder_cb, void* decoder_args, int decoder_argc)
{
	return -1;
}

void ms_asr_clear(void)
{
	return;
}

int  ms_asr_run(int frame)
{
	return 0;
}

int ms_asr_get_frame_time(void)
{
	return 0;
}

void ms_asr_get_am_vocab(char** vocab, int* cnt)
{
	return;
}

int ms_asr_set_dev(int device_type, char* device_name)
{
	return -1;
}

int ms_asr_kws_reg_similar(char* pny, char** similar_pnys, int similar_cnt)
{
	return -1;
}

void ms_asr_wfst_run(pnyp_t* pnyp_list)
{
	return;
}
