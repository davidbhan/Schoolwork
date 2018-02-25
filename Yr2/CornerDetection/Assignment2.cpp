#include "stdAfx.h"
#include "Assignment2.h"

/////////////////////////////
// CCorner Source File //
/////////////////////////////


// this function convert a given CImage to a GrayScale image
void CCorner::RGBToGrayScale(CImage* pIn, CImage* pOut)
{
	//
	// INPUT:
	//     CImage* pIn:		The input image with 24bit depth
	//
	// OUTPUT:
	//     CImage* pOut:	The output image. It has ALREADY been initialized
	//                      with the same dimension as the input image (pIN) and 
	//                      formatted to 8bit depth (256 gray levels). So, please
	//                      use 'SetIndex' instead of 'SetRGB'.
	//
	
	// Begin your code here: //

}

// this function obtains the corners from a given GrayScale image
void CCorner::ObtainCorners(CImage* pIn, double sigma, double threshold, vector<C2DPoint*>* pResultCorners)
{
//
	// INPUT:
	//     CImage* pIn:		The input grayscale image, which is exactly the output of
	//                      RGBToGrayScale function.
	//     double sigma:    The sigma value for your convolve function
	//     double threhold: The minimum value for qualifying a corner. Please refers to the lecture 3's notes
	//
	// OUTPUT:
	//     vector<C2DPoint*>* pResultCorners:	
	//                      A std::vector object that holds all detected corners. Each corner is represented by
	//                      a C2DPoint structure. An example is given below, showing how a corner object is
	//                      initialized and stored in pResultCorners:
	//                      
	//                      	C2DPoint* pPnt = new C2DPoint(x, y);
	//                      	pResultCorners.push_back(pPnt);
	//
	//
	
	// Begin your code here: //

	////
	// Step 1: Compute a proper size for Gaussian filter

	////
	// Step 2: Define the Gaussian filter and partial filter

	////
	// Step 3: Compute Ix, Iy

	////
	// Step 4: Compute Ixx, Iyy, Ixy

	////
	// Step 5: Smooth Ixx, Iyy, Ixy

	////
	// Step 6: Compute R

	////
	// Step 7: Locate Maxima in R

	////
	// Step 8: Compute corner candidates up to sub-pixel accuracy and interpolate R value for corner candidates.

	////
	// Step 9: Use the threshold value to identify strong corners for output
}


