#include "DBoW3/DBoW3.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // for std::setw and std::setfill
#include <sstream>

using namespace cv;
using namespace std;

/***************************************************
 * This example demonstrates how to train a dictionary
 * using the ten images from the data/ directory.
 * ************************************************/
// KITTI seq 00 has 4541 frames
int main(int argc, char** argv) {
    // read the images 
    cout << "Reading images... " << endl;
    vector<Mat> images; 
    for (int i = 0; i <= 4540; i++) // Looping up to 4540
    {
        stringstream pathStream;
        pathStream << "./dataset/KITTI/data_odometry_gray/dataset/sequences/00/image_0/" 
                   << setw(6) << setfill('0') << i << ".png";
        string path = pathStream.str();
        Mat image = imread(path);
        if (!image.empty()) {
            images.push_back(image);
        } else {
            cerr << "Failed to load image at: " << path << endl;
        }
    }

    // detect ORB features
    cout << "Detecting ORB features ... " << endl;
    Ptr<Feature2D> detector = ORB::create();
    vector<Mat> descriptors;
    for (Mat& image : images) {
        vector<KeyPoint> keypoints; 
        Mat descriptor;
        detector->detectAndCompute(image, Mat(), keypoints, descriptor);
        descriptors.push_back(descriptor);
    }
    
    // create vocabulary 
    cout << "Creating vocabulary ... " << endl;
    DBoW3::Vocabulary vocab;
    vocab.create(descriptors);
    cout << "Vocabulary info: " << vocab << endl;
    vocab.save("kitti_00_all.yml.gz");
    cout << "Done" << endl;
    
    return 0;
}
