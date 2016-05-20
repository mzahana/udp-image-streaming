//////////////////////////////////////////////////////////////////////////
// Creates C++ MEX-file for OpenCV routine descodeUDPimg. 
// This routine decodes an uint8 input buffer to output image,
// using opencv functions
//
// Copyright 2016 Mohamed Abdelkader
//////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
// Check inputs
///////////////////////////////////////////////////////////////////////////
#include "opencvmex.hpp"


///////////////////////////////////////////////////////////////////////////
// Check inputs
///////////////////////////////////////////////////////////////////////////
void checkInputs(int nrhs, const mxArray *prhs[])
{ 
    // Check number of inputs
    // Expecting 2 inputs: uint8 buffer, and size of buffer
    if (nrhs != 2)
    {
        mexErrMsgTxt("Incorrect number of inputs. Function expects 2 inputs.");
    }
    
    // Check buffer data type
    if (!mxIsUint8(prhs[0]))
    {
        mexErrMsgTxt("Buffer must be UINT8.");
    }
}


///////////////////////////////////////////////////////////////////////////
// Main entry point to a MEX function
///////////////////////////////////////////////////////////////////////////
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{  
	// Check inputs to mex function
    checkInputs(nrhs, prhs);
    
    // Convert mxArray inputs into OpenCV types
    cv::Ptr<cv::Mat> templateImgCV = ocvMxArrayToImage_uint8(prhs[0], true);
    cv::Ptr<cv::Mat> imgCV         = ocvMxArrayToImage_uint8(prhs[1], true);
    
    // Allocate output matrix
    int outRows = imgCV->rows - templateImgCV->rows + 1;
    int outCols = imgCV->cols - templateImgCV->cols + 1;
    
    cv::Mat outCV((int)outRows, (int)outCols, CV_32FC1);
    
    // Run the OpenCV template matching routine
    cv::matchTemplate(*imgCV, *templateImgCV, outCV, CV_TM_CCOEFF_NORMED );
    
    // Put the data back into the output MATLAB array
    plhs[0] = ocvMxArrayFromImage_single(outCV);
}