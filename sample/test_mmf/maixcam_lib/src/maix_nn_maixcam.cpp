#include "maix_nn_maixcam.hpp"

namespace maix::nn
{
	NN_MaixCam::NN_MaixCam(bool dual_buff)
	{
		//
	}

	NN_MaixCam::NN_MaixCam()
	{
		//
	}

	NN_MaixCam::~NN_MaixCam()
	{
		//
	}

	err::Err NN_MaixCam::load(const MUD &mud, const std::string &dir)
	{
		return err::ERR_NOT_IMPL;
	}

	err::Err NN_MaixCam::unload()
	{
		return err::ERR_NOT_IMPL;
	}

	bool NN_MaixCam::loaded()
	{
		return false;
	}

	void NN_MaixCam::set_dual_buff(bool enable)
	{
		//
	}

	std::vector<LayerInfo> NN_MaixCam::inputs_info()
	{
		//return nullptr;
	}

	std::vector<LayerInfo> NN_MaixCam::outputs_info()
	{
		//return nullptr;
	}

	err::Err NN_MaixCam::forward(tensor::Tensors &inputs, tensor::Tensors &outputs, bool copy_result, bool dual_buff_wait)
	{
		return err::ERR_NOT_IMPL;
	}

	tensor::Tensors *NN_MaixCam::forward(tensor::Tensors &inputs, bool copy_result, bool dual_buff_wait)
	{
		return nullptr;
	}

	err::Err mud_load_raw_model(const std::string &model_path, MUD *mud_obj)
	{
		return err::ERR_NOT_IMPL;
	}

	int maix_nn_self_learn_classifier_learn(std::vector<float *> &features, std::vector<float *> &features_samples, int feature_num)
	{
		return 0;
	}
}
