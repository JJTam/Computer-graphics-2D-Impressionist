
// ScatteredLineBrush.cpp

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredLineBrush.h"
#include <math.h>

extern float frand();
extern int irand(int max);

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name)
	: ImpBrush(pDoc, name) {}




void ScatteredLineBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int width = pDoc->getWidth();

	glLineWidth((float)width);

	BrushMove(source, target);
}


void ScatteredLineBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredLineBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int angle = pDoc->getAngle();
	int strokeDirectionType = pDoc->m_nCurrentStrokeDirectionType;
	
	if (pDoc->getAnotherGradient())
	{
		strokeDirectionType = STROKE_DIRECTION_GRADIENT;
	}

	switch (strokeDirectionType) {
		case STROKE_DIRECTION_SLIDER_OR_RIGHT_MOUSE:
			DrawLines(source, target, angle, size);
			break;	

		case STROKE_DIRECTION_GRADIENT:
			angle = CalculateDirectionPerpendicularToGradient(source);
			DrawLines(source, target, angle, size);
			break;

		case STROKE_DIRECTION_BRUSH_DIRECTION:
			angle = atan2((GLdouble)m_previousTargetCoordinate.y - target.y, (GLdouble)m_previousTargetCoordinate.x - target.x) * 180 / M_PI;
			DrawLines(source, target, angle, size);
			m_previousTargetCoordinate = target;
			break;

		default:
			break;
	}

}


void ScatteredLineBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}



void ScatteredLineBrush::DrawLines(const Point source, const Point target, const int angle, const int size) {

	int scatteredSize = size / 2;

	glPushMatrix();
	glTranslatef(target.x, target.y, 0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glTranslatef(-target.x, -target.y, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_LINES);

	for (int y = target.y - scatteredSize; y <= target.y + scatteredSize; y++) {
		if (rand() % 8 == 0) {
			Point newSource(target.x, y);
			SetColor(newSource);
			glVertex2d(target.x - (GLdouble)irand(size), y);
			glVertex2d(target.x + (GLdouble)irand(size), y);
		}
	}

	glEnd();
	glPopMatrix();

}


// apply filter to the pixel
GLubyte addfilterNoise(GLubyte pixels[5][5], int x, int y)
{
	int sum = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sum += pixels[x - 1 + i][y - 1 + j];
		}
	}
	return sum / 9;
}



int ScatteredLineBrush::CalculateDirectionPerpendicularToGradient(Point source) {

	ImpressionistDoc* pDoc = GetDocument();

	const int sobel_x[3][3] = { {1, 0, -1},
								{2, 0, -2},
								{1, 0, -1} };

	const int sobel_y[3][3] = { { 1,  2,  1},
								{ 0,  0,  0},
								{-1, -2, -1} };


	GLubyte grayLevelPixel[5][5];
	Point gradient(0, 0);

	// convert RGB tuple into a gray level
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			GLubyte color[3]{ 0,0,0 };

			// get pixel color
			if (pDoc->getAnotherGradient()) {
				memcpy(color, pDoc->GetAnotherImagePixel(source.x + i - 1, source.y + j - 1), 3);
			}
			else {
				// get pixel color
				memcpy(color, pDoc->GetOriginalPixel(source.x - 1 + i, source.y - 1 + j), 3);
			}

			grayLevelPixel[i][j] = (GLubyte)((0.299 * color[0] + 0.587 * color[1] + 0.114 * color[2]) / 3);
		}
	}


	GLubyte grayLevelAfterFilterPixel[3][3];

	// blur the gray-level image
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			grayLevelAfterFilterPixel[i][j] = addfilterNoise(grayLevelPixel, i + 1, j + 1);
		}
	}

	int gradient_x = 0;
	int gradient_y = 0;

	// calculate gradient
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			gradient_x += grayLevelAfterFilterPixel[i][j] * sobel_x[j][i];
			gradient_y += grayLevelAfterFilterPixel[i][j] * sobel_y[j][i];
		}
	}


	// calculate gradient angle
	int angle = atan2(gradient_y, gradient_x) * 180 / M_PI;


	// convert to perpendicular
	angle = angle + 90;
	if (angle < 0)
		angle += 360;
	
	return angle;
}