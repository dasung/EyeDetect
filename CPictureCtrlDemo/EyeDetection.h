
#include "C:\Program Files\OpenCV2.1\include\opencv\cv.h" 
#include "C:\Program Files\OpenCV2.1\include\opencv\cxcore.h" 
#include "C:\Program Files\OpenCV2.1\include\opencv\highgui.h"
class Eye
{
public:
	Eye();
	int detect_eyes(IplImage* img);
	int detect_faces(IplImage* img);
	int match_templates(IplImage* sampleEye,IplImage *face,double d);

protected:
private:
};


/**
* Given an image, this function will detect,
*human faces on the image and draws red boxes around them.
*human eyes on the image and draws green boxes around them.
*
*/

