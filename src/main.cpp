#include "CameraPerspective.h"

#include "PrimSphere.h"
#include "PrimPlane.h"
#include "PrimTriangle.h"

Mat RenderFrame(ICamera& camera)
{
	// scene objects
	
	CPrimSphere s1(RGB(.5, 0, 0), Vec3f(-2, 1.7f, 0), 2); //assigning position and color values to the constructor
	CPrimSphere s2(RGB(0, 1, 0), Vec3f(1, -1, 1), 2.2f);
	CPrimSphere s3(RGB(0, 0, 0.5), Vec3f(3, 0.8f, -2), 2);
	CPrimPlane p1(RGB(0, .5, 1), Vec3f(0, -1, 0), Vec3f(0, 1, 0));
	
	CPrimTriangle t1(RGB(0.5, 1, 0.5), Vec3f(-2, 3.7f, 0), Vec3f(1, 2, 1), Vec3f(3, 2.8f, -2));
	CPrimTriangle t2(RGB(0.5, 1, 0.5), Vec3f(3, 2, 3), Vec3f(3, 2, -3), Vec3f(-3, 2, -3));
	
	std::vector<CPrim*> objects = {&s1, &s2, &s3, &t1, &t2, &p1}; //defining a vector to store all the child objects

	Mat img(camera.getResolution(), CV_32FC3); 	// image array
	Ray ray;                            		// primary ray
	
	for(int y = 0; y< img.rows; y++)
		for (int x = 0; x < img.cols; x++) {
			
			// Initialize your ray here
			if (!camera.InitRay(x, y, ray)){
				continue;
			}
			
			// Your code
			
			Vec3f col = RGB(0, 0, 0); // background color
			
			/*
			 * Find closest intersection with scene
			 * objects and calculate color
			 */
			
			// Your code
			for(auto object : objects){
				if (object->Intersect(ray)){
					col = object->getcolor(); //if object intersects with the ray, extract the respecrtive pixel color
				}
			}

			
			img.at<Vec3f>(y, x) = col; // store pixel color
		}
	
	img.convertTo(img, CV_8UC3, 255);
	return img;
}

int main(int argc, char* argv[])
{
	const Size resolution(800, 600);
	// render three images with different camera settings
	
	CCameraPerspective c1(Vec3f(0, 0, 10), Vec3f(0, 0, -1), Vec3f(0, 1, 0), 60, resolution);
	Mat img1 = RenderFrame(c1);
	imwrite("perspective1.jpg", img1);
	
	CCameraPerspective c2(Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(0, 1, 0), 45, resolution);
	Mat img2 = RenderFrame(c2);
	imwrite("perspective2.jpg", img2);
	
	CCameraPerspective c3(Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(1, 1, 0), 45, resolution);
	Mat img3 = RenderFrame(c3);
	imwrite("perspective3.jpg", img3);
	return 0;
}