
// WarpBrush.cpp

#include "WarpBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

extern float frand();

using namespace std;

WarpBrush::WarpBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name) {}



GLubyte* getColor(unsigned char* vp, int x, int y, int w, int h) {
	x = max(0, min(x, w - 1));
	y = max(0, min(y, h - 1));
	return vp + (y * w + x) * 3;
};



void setColor(ImpressionistDoc* pDoc, GLubyte* color3) {
	GLubyte color4[4];

	memcpy(color4, color3, 3);

	color4[3] = GLubyte(255 * pDoc->m_pUI->getAlpha());

	glColor4ubv(color4);
}


vector<vector<float>> getGaussianValue(float sigma, int size) {

	vector<vector<float>> k;

	for (int i = 0; i < size; i++) {
		vector<float> row;
		for (int j = 0; j < size; j++) {
			int x = i - size / 2;
			int y = j - size / 2;
			float v = (1 / (2 * M_PI * sigma)) * exp(-(x * x + y * y) / (2 * sigma));
			row.push_back(v);
		}
		k.push_back(row);
	}
	return k;
}



void WarpBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	prePoint = source;

	BrushMove(source, target);
}


void WarpBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("WarpBrush::BrushMove  document is NULL\n");
		return;
	}

	if (source.x > pDoc->m_nPaintWidth || source.y < 0) return;

	Point curPoint = source;
	int size = pDoc->getSize();
	int scatteredSize = size / 2;
	int width = pDoc->m_nWidth;
	int height = pDoc->m_nHeight;

	//kernel = getGaussianValue(dlg->getWarp(), size);

	//for (int i = 0; i < size; i++) {
	//	for (int j = 0; j < size; j++) {
	//		if (sqrt(pow((GLdouble)i - scatteredSize, 2) + pow((GLdouble)j - scatteredSize, 2)) > scatteredSize)
	//			kernel[i][j] = 0;
	//	}
	//}

	unsigned char* viewport = pDoc->m_ucPainting;

	int deltaX = curPoint.x - prePoint.x;
	int deltaY = curPoint.y - prePoint.y;

	double rad = atan2(deltaY, deltaX);
	double cosR = cos(rad);
	double sinR = sin(rad);
	double d = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

	glPointSize(1.0);
	glBegin(GL_POINTS);
	
	/*for (int xp = prePoint.x - scatteredSize, i = 0; xp < prePoint.x + scatteredSize; xp++, i++) {
		
		if (xp < 0 || xp > width - 1) 
			continue;

		for (int yp = prePoint.y - scatteredSize, j = 0; yp < prePoint.y + scatteredSize; yp++, j++) {
			if (yp < 0 || yp > height - 1) 
				continue;

			if (sqrt(pow((GLdouble)xp - prePoint.x, 2) + pow((GLdouble)yp - prePoint.y, 2)) > scatteredSize)
				continue;

			double x = (GLdouble)xp - kernel[i][j] * deltaX / kernel[scatteredSize][scatteredSize];
			double y = (GLdouble)yp - kernel[i][j] * deltaY / kernel[scatteredSize][scatteredSize];

			GLubyte buf[3];
			memcpy(buf, getColor(viewport, x, y, width, height), 3);
			setColor(pDoc, buf);
			glVertex2d(xp, yp);
		}
	}*/

	glEnd();
	//dlg->m_paintView->SaveCurrentContent();

	prePoint = curPoint;
}


void WarpBrush::BrushEnd(const Point source, const Point target) {
}



