#include <cstdio>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("An input image file is missing.\n");
    return EXIT_FAILURE;
  }
  cv::Mat image;
  image = cv::imread(argv[1], cv::ImreadModes::IMREAD_COLOR);
  if (image.empty()) {
    printf("Image file is not found.\n");
    return EXIT_FAILURE;
  }
  const int WIDTH = image.cols;
  const int HEIGHT = image.rows;
  const int NC = image.channels();
  printf("width = %d, height = %d", WIDTH, HEIGHT);
  for (int y = 0; y < HEIGHT; ++y) {
    const int STRIDE = WIDTH * NC;
    for (int x = 0; x < WIDTH; ++x) {
      for (int c = 0; c < NC; ++c) {
        int val = image.data[y * STRIDE + x * NC + c];
        val = (c != 0) ? 0 : val;
        image.data[y * STRIDE + x * NC + c] = val;
      }
    }
  }
  cv::imshow("image", image);
  cv::waitKey();
  cv::destroyAllWindows();

  return EXIT_SUCCESS;
}
