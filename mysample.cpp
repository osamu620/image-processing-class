#include <iostream>
#include <opencv2/opencv.hpp>

#include "mytools.hpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Input file is not specified." << std::endl;
    return EXIT_FAILURE;
  }
  cv::Mat image;
  image = cv::imread(argv[1], cv::ImreadModes::IMREAD_ANYCOLOR);
  if (image.empty()) {
    std::cerr << "Image file is not found." << std::endl;
    return EXIT_FAILURE;
  }

  iminfo(image);

  blkproc(image, testfunc);

  cv::imshow("Output", image);
  int keycode = 0;
  while (keycode != 'q') {
    keycode = cv::waitKey(0);
  }
}
