#include "Mosaic.h"
#include <math.h>

Mosaic::Mosaic(ImpressionistDoc* pDoc)
{
	m_pDoc = pDoc;
}

Mosaic::~Mosaic()
{
}

int Mosaic::findBestFitImage(GLubyte** imageColors, GLubyte* averageColor)
{
	double minimumDifference = 2e10;
	int bestImage = 0;
	for (int i = 0; i < 4; i++)
	{
		// check if the image is not null
		if (!imageColors[i])
		{
			continue;
		}

		// start calculate minimum difference
		double difference = 0;

		for (int j = 0; j < 3; j++)
		{
			difference += (imageColors[i][j] - averageColor[j]) * (imageColors[i][j] - averageColor[j]);
		}
		
		if (difference < minimumDifference)
		{
			minimumDifference = difference;
			bestImage = i;
		}
	}
	return bestImage;
}

void Mosaic::generateMosaic(double alpha, int size)
{
	int imageWidth = m_pDoc->m_nWidth;
	int imageHeight = m_pDoc->m_nHeight;

	int numberOfImageInWidth = imageWidth / size;
	int numberOfImageInHeight = imageHeight / size;

	ImpressionistUI* m_pUI = m_pDoc->m_pUI;

	for (int i = 0; i < numberOfImageInWidth; i++)
	{
		for (int j = 0; j < numberOfImageInHeight; j++)
		{
			Point upLeft(size * i, size * j);
			Point bottomRight(size * (i + 1) - 1, size * (j + 1) - 1);

			GLubyte* averageColor = findAverageColor(upLeft, bottomRight, m_pDoc->m_ucBitmap, m_pDoc->m_nWidth, m_pDoc->m_nHeight);
			
			int bestImage = findBestFitImage(m_pDoc->imageColors, averageColor);

			drawMosaic(bestImage, upLeft, alpha, size);

			delete[] averageColor;
		}
	}
	m_pUI->m_paintView->SaveCurrentContent();
}

GLubyte* Mosaic::findImageAverageColor(int size, unsigned char* bitmap)
{
	float color_sum[3] = { 0.0, 0.0, 0.0 };
	for (int i = 0; i != size * size; i++) {
		color_sum[0] += bitmap[3 * i];
		color_sum[1] += bitmap[3 * i + 1];
		color_sum[2] += bitmap[3 * i + 2];
	}
	GLubyte* color = new GLubyte[3];

	for (int i = 0; i != 3; i++) {
		color_sum[i] = color_sum[i] / size / size;
		color[i] = (GLubyte)((int)color_sum[i]);
	}

	return color;
}

GLubyte* Mosaic::findAverageColor(Point upLeft, Point bottomRight, unsigned char* image, int width, int height)
{
	GLubyte* color = new GLubyte[3];
	int colorSum[3] = { 0, 0, 0 };
	for (int i = upLeft.y; i < bottomRight.y; i++) {
		for (int j = upLeft.x; j < bottomRight.x; j++) {
			Point target(j, i);

			memcpy(color, m_pDoc->GetTargetPixel(target.x, target.y, image, width, height), 3);

			//printf(" ok after copy\n");
			colorSum[0] += color[0];
			colorSum[1] += color[1];
			colorSum[2] += color[2];
		}
	}
	delete[] color; 

	GLubyte* avergeColor = new GLubyte[3];

	int size = bottomRight.y - upLeft.y + 1;

	for (int i = 0; i != 3; i++) {
		avergeColor[i] = colorSum[i] / size / size;
	}

	return avergeColor;
}

void Mosaic::drawMosaic(int tail, Point up_left, double alpha, int size)
{
	glPointSize(1.0);
	glDisable(GL_POINT_SMOOTH);
	Point target(0, 0);
	glBegin(GL_POINTS);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j != size; j++) {
			target.x = up_left.x + j;
			target.y = up_left.y + i;
			// Find dissolve color
			GLubyte color[3];
			memcpy(color, m_pDoc->GetTargetPixel(j, i, m_pDoc->m_ucImages[tail], size, size), 3);
			glColor4ub(color[0], color[1], color[2], (GLubyte)alpha);
			glVertex2i(target.x, target.y);
		}
	}
	glEnd();
}
