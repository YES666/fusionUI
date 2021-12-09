#pragma once
#ifndef DETECTOR_H
#define DETECTOR_H
#include <opencv2/opencv.hpp>
#include <inference_engine.hpp>
#include <iostream>
#include <chrono>
#include <opencv2/dnn/dnn.hpp>
#include <cmath>
using namespace std;
using namespace cv;
using namespace InferenceEngine;

class Detector {
public:
	typedef struct {
		float prob;
		std::string name;
		cv::Rect rect;
	} Object;
	bool init(string);
	bool process_frame(Mat& inframe, Mat& detectedObj);
private:

	ExecutableNetwork _network;
	OutputsDataMap _outputinfo;
	string _input_name;
	string _xml_path;

};
#endif