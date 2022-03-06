// reference
// https://github.com/peterwongny/Impressionist/tree/c537519b3515f3e0d78e8b2ccc0fa89610d7780c
#include "impressionistUI.h"
#pragma once
#include "impressionistDoc.h"
#include "impressionistUI.h"
class Mosaic
{
public:
	Mosaic(ImpressionistDoc* pDoc);
	~Mosaic();

	int findBestFitImage(GLubyte** imagecolor, GLubyte* averageColor);
	void generateMosaic(double alpha = 0.3, int size = 24);
	static GLubyte* findImageAverageColor(int size, unsigned char* bitmap);
	GLubyte* findAverageColor(Point upLeft, Point bottomRight, unsigned char* image, int width, int height);
	GLubyte* findAverageColor(Point upLeft, Point bottomRight);
	void drawMosaic(int image, Point upLeft, double alpha, int size);

private:
	ImpressionistDoc* m_pDoc;
};

