//
//  main.cpp
//  ColorTransformCPP
//
//  Created by Zerong Xi on 2/16/16.
//  Copyright © 2016 iLab, USC. All rights reserved.
//

#include <iostream>
#include <vector>

#define COLOR_RANGE 256

std::vector<float> get_curve() {
    std::vector<float> curve(3*COLOR_RANGE);
    for(int rgb = 0; rgb < 3; rgb++) {
        for(float val = 0; val < COLOR_RANGE; val++) {
            curve[rgb*COLOR_RANGE+val] = val+1;
        }
    }
    return curve;
}

std::vector<float> get_sat_mat(float saturation) {
    std::vector<float> sat_mat(9, 0);
    float tmp = (1-saturation)*0.3333;
    for(int i=0; i < 9; i++) {
        sat_mat[i] = tmp;
    }
    for (int i=0; i < 9; i=i+4) {
        sat_mat[i] += saturation;
    }
    return sat_mat;
    
}



std::vector<float> transfer_pixel(const std::vector<float>& in, const std::vector<float>& curve, const std::vector<float> sat_mat) {
    
    static std::vector<float> temp(3);
    static std::vector<float> out(3);
    temp[0] = curve[in[0]];
    temp[1] = curve[in[1]+COLOR_RANGE];
    temp[2] = curve[in[2]+COLOR_RANGE*2];
    
    out[0] = temp[0]*sat_mat[0] + temp[1]*sat_mat[1] + temp[2]*sat_mat[2];
    out[1] = temp[0]*sat_mat[3] + temp[1]*sat_mat[4] + temp[2]*sat_mat[5];
    out[2] = temp[0]*sat_mat[6] + temp[1]*sat_mat[7] + temp[2]*sat_mat[8];

    return out;
}



int main(int argc, const char * argv[]) {

    float saturation = 0.98;
    std::vector<float> curve = get_curve();
    std::vector<float> sat_mat = get_sat_mat(saturation);
    
    std::vector<float> in = {3, 145, 39};
    std::vector<float> out = transfer_pixel(in, curve, sat_mat);
    std::cout << out[0] << out[1] << out[2] << std::endl;
    
    return 0;
}