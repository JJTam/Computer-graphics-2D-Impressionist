#include "SingleLineBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <math.h>

#define PI 3.14159265

extern float frand();

SingleLineBrush::SingleLineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void SingleLineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int width = pDoc->getWidth();
	m_previousTargetCoordinate = target;

	glLineWidth(width);
	BrushMove(source, target);
}

void SingleLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int angle = pDoc->getAngle();
	int strokeDirectionType = pDoc->m_nCurrentStrokeDirectionType;

	if (pDoc->getAnotherGradient())
	{
		strokeDirectionType = STROKE_DIRECTION_GRADIENT;
	}

	switch (strokeDirectionType)
	{
	case STROKE_DIRECTION_SLIDER_OR_RIGHT_MOUSE:
		drawLine(source, target, angle, size);
		break;
	
	case STROKE_DIRECTION_GRADIENT:
		angle = calculateDirectionPerpendicularToGradient(source);
		drawLine(source, target, angle, size);
		break;

	case STROKE_DIRECTION_BRUSH_DIRECTION:
		angle = atan2(m_previousTargetCoordinate.y - target.y, m_previousTargetCoordinate.x - target.x) * 180 / PI;
		drawLine(source, target, angle, size);
		m_previousTargetCoordinate = target;
		break;

	default:
		break;
	}
}

void SingleLineBrush::BrushEnd(const Point source, const Point target)
{
}

void SingleLineBrush::drawLine(const Point source, const Point target, const int angle, const int size)
{
	// rotate the line
	glPushMatrix();
	// this 3 instructions go in last in first out order
	glTranslatef(target.x, target.y, 0);
	glRotatef(angle, 0, 0, 1.0);
	glTranslatef(-1 * target.x, -1 * target.y, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_LINES);
	SetColor(source);
	glVertex2d(target.x - (GLdouble)size / 2, target.y);
	glVertex2d(target.x + (GLdouble)size / 2, target.y);
	glEnd();
	glPopMatrix();
}

// apply filter to the pixel
GLubyte filterNoise(GLubyte pixels[5][5], int x, int y)
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

int SingleLineBrush::calculateDirectionPerpendicularToGradient(Point source)
{
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
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			GLubyte color[3]{ 0,0,0 };

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
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3 ;j++)
		{
			grayLevelAfterFilterPixel[i][j] = filterNoise(grayLevelPixel, i + 1, j + 1);
		}
	}

	int gradient_x = 0;
	int gradient_y = 0;

	// calculate gradient
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0;j < 3;j++)
		{
			gradient_x += grayLevelAfterFilterPixel[i][j] * sobel_x[j][i];
			gradient_y += grayLevelAfterFilterPixel[i][j] * sobel_y[j][i];
		}
	}

	// calculate gradient angle
	int angle = atan2(gradient_y, gradient_x) * 180 / PI;
	
	// convert to perpendicular
	angle = angle + 90;
	if (angle < 0)
	{
		angle += 360;
	}
	return angle;
}

