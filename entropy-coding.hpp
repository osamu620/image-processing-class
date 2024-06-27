#pragma once

#include <stdint.h>
#include <stdio.h>

#include <opencv2/core.hpp>
#include <vector>

#include "ycctype.hpp"

void encode_block(cv::Mat &, int &);

std::vector<uint8_t> Encode_MCU(std::vector<cv::Mat> &in, int YCC = YUV420) {
  std::vector<uint8_t> bytestream(10, 0);
  constexpr int BS = 8;
  const int width = in[0].cols;
  const int height = in[0].rows;

  int Hblk = HV[YCC] & 0xF;  // 下位4bitは水平
  int Vblk = HV[YCC] >> 4;   // 上位4bitは垂直
  if (in.size() == 1) {
    Hblk = 1;
    Vblk = 1;
  }
  int prev_dc[3] = {0};
  for (int y = 0, cy = 0; y < height; y += BS * Vblk, cy += BS) {
    for (int x = 0, cx = 0; x < width; x += BS * Hblk, cx += BS) {
      cv::Mat blk;
      // Y
      for (int v = 0; v < Vblk; ++v) {
        for (int h = 0; h < Hblk; ++h) {
          blk = in[0](cv::Rect(x + BS * h, y + BS * v, BS, BS)).clone();
          encode_block(blk, prev_dc[0]);
        }
      }
      if (in.size() == 3) {
        // Cb
        blk = in[2](cv::Rect(cx + BS, cy + BS, BS, BS)).clone();
        encode_block(blk, prev_dc[2]);
        // Cr
        blk = in[1](cv::Rect(cx + BS, cy + BS, BS, BS)).clone();
        encode_block(blk, prev_dc[1]);
      }
    }
  }
  return bytestream;
}

void encode_block(cv::Mat &in, int &prev_dc) {
  int16_t *p = (int16_t *)in.data;
  // DPCM
  int diff = p[0] - prev_dc;
  prev_dc = p[0];
}
