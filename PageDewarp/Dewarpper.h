#pragma once
#include "PageImage.h"
#include <numeric>
#include <opencv2/opencv.hpp>

class Dewarpper {
	/*
	Dewarpper类
	矫正算法的实现。整个流程的本质是对像素的分析、调整。利用PageImage提供的接口，可以不考虑图片的数据结构，便于未来版本更迭。
	流程分如下几步：1.版面分析。得到一系列文字块。2.预处理。灰度化、二值化。3.矫正。包括计算行高、拟合文本线、图像重构，是算法核心。
	以上流程都用私有函数、私有变量实现。外部接口仅有setImage和dewarp两个，用户输入图片，调用dewarp得到矫正结果，非常简单。
	*/
public:
	Dewarpper();
	Dewarpper(const char *);
	~Dewarpper();

	int dewarp(); 
	//int setImage(const char *);  // 载入书页图像
	void save(const char *);  // 保存图像

	static enum ERROR_TYPE;

private:
	PageImage img;  // 图片
	PageImage ret;
	shared_ptr<vector<cv::Rect>> *bounds;  // 保存版面分析的结果
	vector<cv::Rect> *LayoutRecognization();  // 版面分析算法
	int preProcedure();  // 预处理算法
	int calcLineHeight();  // 计算行高
	int getTextLine(const int &);  // 文本线拟合算法
	int reshape(const int &);  // 重新构图算法
	void doSave(const PageImage *, const char *) const ;  // 执行保存图像
	list<list<double>> coefficientM;
	int lineHeight;


	inline void setElem(pair<int, int> &elem, const int &a, const int &b) { elem.first = a; elem.second = b; }
	//assist function
	bool bufcnt(bool cond,int buf, int threshold,int maxBuf = 50);
};