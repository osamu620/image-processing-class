#pragma once
#include <functional>
#include <opencv2/core.hpp>

#define BSIZE 8
// ブロック処理のための関数: 実際の処理はfuncで決まる
void blkproc(cv::Mat &in, std::function<void(cv::Mat &)> func) {
  for (int y = 0; y < in.rows; y += BSIZE) {
    for (int x = 0; x < in.cols; x += BSIZE) {
      cv::Mat blk_in = in(cv::Rect(x, y, BSIZE, BSIZE)).clone();
      cv::Mat blk_out = in(cv::Rect(x, y, BSIZE, BSIZE));
      func(blk_in);
      blk_in.convertTo(blk_out, blk_out.type());
    }
  }
}

void testfunc(cv::Mat &in) {
  for (int y = 0; y < in.rows; ++y) {
    for (int x = 0; x < in.cols; ++x) {
      in.data[y * in.cols + x] = in.data[0];
    }
  }
}

void iminfo(cv::Mat &in) {
  int width = in.cols;
  int height = in.rows;
  int num_components = in.channels();
  std::cout << "width = " << width << ", ";
  std::cout << "height = " << height << ", ";
  if (num_components == 3) {
    std::cout << "COLOR" << std::endl;
  } else if (num_components == 1) {
    std::cout << "GRAYSCALE" << std::endl;
  } else {
    std::cout << "UNKOWN COLORSPACE" << std::endl;
  }
}

template <class T>
T clip(T pixel) {
  if (pixel < 0) {
    pixel = 0;
  } else if (pixel > 255) {
    pixel = 255;
  }
  return pixel;
}
template <>
float clip(float pixel) {
  if (pixel < 0.0f) {
    pixel = 0.0f;
  } else if (pixel > 255.0f) {
    pixel = 255.0f;
  }
  return pixel;
}
template <>
double clip(double pixel) {
  if (pixel < 0.0) {
    pixel = 0.0;
  } else if (pixel > 255.0) {
    pixel = 255.0;
  }
  return pixel;
}
