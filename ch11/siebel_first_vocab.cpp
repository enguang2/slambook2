#include "DBoW3/DBoW3.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For std::setw and std::setfill

using namespace cv;
using namespace std;

/***************************************************
 * 本节演示了如何根据data/目录下的十张图训练字典
 * ************************************************/

int main( int argc, char** argv ) {
    // read the image 
    cout<<"reading images... "<<endl;
    vector<Mat> images; 

    for (int i = 1; i <= 138; i++) {
        // Generate the file name with leading zeros (e.g., siebel_0001.png)
        stringstream ss;
        ss << "./data/sisbel_first_floor_loop_closure_2fps/siebel_" << setw(4) << setfill('0') << i << ".png";
        string path = ss.str();

        // Load the image and store it
        images.push_back(imread(path));
    }
    // detect ORB features
    cout<<"detecting ORB features ... "<<endl;
    Ptr< Feature2D > detector = ORB::create();
    vector<Mat> descriptors;

    for ( Mat& image:images )
    {
        vector<KeyPoint> keypoints; 
        Mat descriptor;
        detector->detectAndCompute( image, Mat(), keypoints, descriptor );
        descriptors.push_back( descriptor );
    }
    
    // create vocabulary 
    cout<<"creating vocabulary ... "<<endl;
    DBoW3::Vocabulary vocab;
    vocab.create( descriptors );
    cout<<"vocabulary info: "<<vocab<<endl;
    vocab.save( "siebel_first.yml.gz" );
    cout<<"done"<<endl;
    
    return 0;
}