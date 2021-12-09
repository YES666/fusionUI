#include "detector.h"

#define IMAGE_LEN 256


bool Detector::init(std::string xml_path) {
	_xml_path = xml_path;
	// 加载推理引擎Core，该引擎需要从当前路径加载plugins.xml文件
	InferenceEngine::Core ie;
	
	//查询支持硬件设备
	std::vector<std::string> availableDev = ie.GetAvailableDevices();
	for (int i = 0; i < availableDev.size(); i++) {
		cout << "supported device name: " << availableDev[i].c_str() << endl;
	}
	
	//从IR加载检测模型
	InferenceEngine::CNNNetwork cnnNetwork = ie.ReadNetwork(_xml_path);
	cnnNetwork.setBatchSize(1);
	
	// 网络输入头参数设置
	InferenceEngine::InputsDataMap inputInfo(cnnNetwork.getInputsInfo());
	InferenceEngine::InputInfo::Ptr input = inputInfo.begin()->second;
	_input_name = inputInfo.begin()->first;//输入头的名称
	input->setPrecision(InferenceEngine::Precision::FP32);
	input->getInputData()->setLayout(InferenceEngine::Layout::NCHW);


	InferenceEngine::ICNNNetwork::InputShapes inputShapes = cnnNetwork.getInputShapes();
	InferenceEngine::SizeVector& inSizeVector = inputShapes.begin()->second;
	cnnNetwork.reshape(inputShapes);
	
	//网络输出设置，YOLOV5包含三个输出
	_outputinfo = InferenceEngine::OutputsDataMap(cnnNetwork.getOutputsInfo());
	for (auto& output : _outputinfo) {
		cout << output.first << endl;
		output.second->setPrecision(InferenceEngine::Precision::FP32);
	}
	
	//获取可执行网络
	//_network = ie.LoadNetwork(cnnNetwork, "GPU");
	_network = ie.LoadNetwork(cnnNetwork, "CPU");
	return true;
}

bool Detector::process_frame(Mat &curFrame, Mat &detectedObj)
{
	//cv::Mat resize_img = letterBox(curFrame);

	std::size_t img_size = 256 * 256;

	//建立推理请求
	//InferenceEngine::InferRequest::Ptr infer_request = _network.CreateInferRequestPtr();
	InferenceEngine::InferRequest infer_request = _network.CreateInferRequest();
	
	//InferenceEngine::Blob::Ptr frameBlob = infer_request->GetBlob(_input_name);
	InferenceEngine::Blob::Ptr frameBlob = infer_request.GetBlob(_input_name);
	
	InferenceEngine::LockedMemory<void> blobMapped = InferenceEngine::as<InferenceEngine::MemoryBlob>(frameBlob)->wmap();
	float* blob_data = blobMapped.as<float*>();

	//nchw
	//将输入图像关联到Blob
	//Mat*pArr = curFrame;
	for (std::size_t row = 0; row < IMAGE_LEN; row++) {
		for (std::size_t col = 0; col < IMAGE_LEN; col++) {
			for (std::size_t ch = 0; ch < 2; ch++) {
				//遍历输入图像的每个像素保存到blob_data，目前不理解blob_data的索引值
				blob_data[img_size*ch + row * IMAGE_LEN + col] = float(curFrame.at<cv::Vec3b>(row, col)[ch] / 255.0f);
			}
		}
	}
	//执行推理
	//infer_request->Infer();
	infer_request.Infer();
	
	//大规模计算之前先收集指针
	std::vector<InferenceEngine::Blob::Ptr> blobs;
	//blobs保存推理结果，用于输入到parseYolov5方法进行解析
	for (auto &output : _outputinfo) {
		auto output_name = output.first;
		
		//InferenceEngine::Blob::Ptr blob = infer_request->GetBlob(output_name);
		InferenceEngine::Blob::Ptr blob = infer_request.GetBlob(output_name);
		
		blobs.push_back(blob);
	}



	size_t num_images = blobs[0]->getTensorDesc().getDims()[0];
	size_t num_channels = blobs[0]->getTensorDesc().getDims()[1];
	size_t H = blobs[0]->getTensorDesc().getDims()[2];
	size_t W = blobs[0]->getTensorDesc().getDims()[3];
	//size_t nPixels = W * H;

	//输出内存分配
	InferenceEngine::LockedMemory<const void> blobMap = InferenceEngine::as<InferenceEngine::MemoryBlob>(blobs[0])->rmap();
	const float* output_data = blobMap.as<float*>();

	cout << "Output size [N,C,H,W]: " << num_images << ", " << num_channels << ", " << H << ", " << W << endl;


	{
		const float* pArr = output_data;
		for (size_t n = 0; n < num_images; n++) {
			std::vector<float> data_img(H*W * num_channels);
			//std::string out_img_name = std::string("out" + std::to_string(n + 1) + ".png");
			Mat mat_image(H, W, CV_8UC1);
			for (size_t i = 0; i < H; i++) {
				for (size_t j = 0; j < W; j++) {
					//data_img[n * H * W * num_channels + i * W + j] = static_cast<float>(output_data[i*H+j + n * nPixels * num_channels] * 255.0f);
					//mat_image.at<unsigned char>(i, j) = (unsigned char)data_img[n * H * W * num_channels + i * W + j];

					mat_image.at<unsigned char>(i, j) = static_cast<float>(*(pArr+i * H + j + n * H*W * num_channels) * 255.0f);
				}
			}
			detectedObj.release();
			detectedObj.push_back(mat_image);
		}
	}

	return true;
}


