#include "stdafx.h"
#include <iostream>
#include "EyeDetection.h"

using namespace std;

Eye::Eye()
{

}

int Eye::detect_faces(IplImage* img)
{
	
	CvHaarClassifierCascade* cascade = 0;
	CvMemStorage* storage = 0;
	IplImage* gray;
	

	  /* Load the face detector and create memory storage*/
	 if (!cascade)
	{
		char* file = "C:/Program Files/OpenCV2.1/data/haarcascades/haarcascade_frontalface_alt2.xml";
		cascade = (CvHaarClassifierCascade*) cvLoad(file, 0, 0, 0);
		storage = cvCreateMemStorage(0);
	}
	

	/* Convert multichannel to 1-channel for faster processing */
	if (img->nChannels == 1)
	{
		gray = (IplImage*) cvClone(img);
	} 
	else 
	{
		gray = cvCreateImage(cvGetSize(img), img->depth, 1);
	    cvCvtColor(img, gray, CV_RGB2GRAY);
	}
	
	/* detect faces */
	CvSeq* faces = cvHaarDetectObjects(
	     gray,
	     cascade,
	     storage,
	     1.1,
	     3,
	     CV_HAAR_DO_CANNY_PRUNING,
	     cvSize(20, 20)
	   );

	  int i;
	  IplImage* detectface;

	   /* Draw red boxes on the faces found */
	for( i = 0; i < (faces ? faces->total : 0); i++ )
	{
		CvRect* r = (CvRect*)cvGetSeqElem(faces, i);
		cvSetImageROI(img, *r);
		detectface = cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
		cvCopy(img,detectface, NULL);
		cvResetImageROI(img);
		 
	     cvRectangle(
	      img,
	      cvPoint(r->x, r->y),
	       cvPoint(r->x + r->width, r->y + r->height),
	      CV_RGB(255, 0, 0),
	     1, 8, 0
	     );
	}
	
	return faces->total;
}

int Eye::detect_eyes(IplImage* img)
{
	
	CvHaarClassifierCascade* cascade = 0;
	CvMemStorage* storage = 0;

	/* Load the face detector and create empty memory storage */
	if (!cascade)
	{
		char* file = "C:/Program Files/OpenCV2.1/data/haarcascades/haarcascade_eye.xml";
		cascade = (CvHaarClassifierCascade*) cvLoad(file, 0, 0, 0);
		storage = cvCreateMemStorage(0);
	}

	/* Detect eyes */
	CvSeq* eyes = cvHaarDetectObjects(
		img,                       /* the input image */
		cascade,                   /* the classifier */
		storage,                   /* memory storage */
		1.1,                       /* scale factor */
		3,                         /* minimum number of neighbor rectangles */
		CV_HAAR_DO_CANNY_PRUNING,  /* mode of operation */
		cvSize(20, 20)             /* min window size */
		);

	int i;
	/* Draw green boxes around the eyes found */
	for( i = 0; i < (eyes ? eyes->total : 0); i++ )
	{
		CvRect* r = (CvRect*)cvGetSeqElem(eyes, i);
		cvRectangle(
			img,
			cvPoint(r->x, r->y),
			cvPoint(r->x + r->width, r->y + r->height),
			CV_RGB(0, 255, 0),
			2, 8, 0
			);
	}
	return eyes->total;
}


/////////////////////authenticate///////////////////////////

int Eye::match_templates(IplImage* sampleEye,IplImage* face,double d)
{
	double THRESHOLD_VAL =d;
	IplImage	*img;
	IplImage	*tpl;
	IplImage	*res;
	CvPoint		minloc, maxloc;
	double		minval, maxval;
	int			img_width, img_height;
	int			tpl_width, tpl_height;
	int			res_width, res_height;

	/* load template  */
	tpl=sampleEye;

	/* load reference image */
	img=face;
	
	if( img == 0 ) 
	{
		MessageBox(NULL,L"Load Faild 'img' @EyeDetection.cpp",L"Error",MB_OK);	
		return 1; 
	}

	if( tpl == 0 ) 
	{
		MessageBox(NULL,L"Load Faild 'tpl' @EyeDetection.cpp",L"Error",MB_OK);
		return 1;
	}

	/* get image's properties */
	img_width  = img->width;
	img_height = img->height;
	tpl_width  = tpl->width;
	tpl_height = tpl->height;
	res_width  = img_width - tpl_width + 1;
	res_height = img_height - tpl_height + 1;

	/* create new image for template matching computation */
	res = cvCreateImage( cvSize( res_width, res_height ), IPL_DEPTH_32F, 1 );

	cvMatchTemplate( img, tpl, res, CV_TM_SQDIFF_NORMED );
	
	//set properties
	cvMinMaxLoc( res, &minval, &maxval, &minloc, &maxloc, 0 );

	/*
	*The main point of validation...
	*set sutable THRESHOLD_VAL from front end..
	*hint- for an eye the value should be smaller one (0.1,.03,0.2..ect)
	*/

	if(minval<THRESHOLD_VAL)
	{
		//draw red color box
		cvRectangle( img, 
		cvPoint( minloc.x, minloc.y ), 
		cvPoint( minloc.x + tpl_width, minloc.y + tpl_height ),
		cvScalar( 0, 0, 255, 0 ), 1, 0, 0 );
		
		//This image will load when successive loggin
		cvSaveImage("success.jpg",img);
		MessageBox(NULL,L"Loggin Success",L"Login",MB_OK);

		cvReleaseImage( &img );
		cvReleaseImage( &tpl );
		cvReleaseImage( &res );
		return 0;
	}

	MessageBox(NULL,L"Not success",L"Login",MB_OK);	
	cvReleaseImage( &img );
	cvReleaseImage( &tpl );
	cvReleaseImage( &res );
	return 1;
} 