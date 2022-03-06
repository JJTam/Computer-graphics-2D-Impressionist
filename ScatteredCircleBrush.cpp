#include "ScatteredCircleBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <math.h>

extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	glPointSize((float)size);
	BrushMove(source, target);
}

int randomNumberWithinRange(int min, int max)
{
	return (max - min) * rand() / (RAND_MAX + 1.0) + min;
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredCircleBrush::BrushMove  document is NULL\n");
		return;
	}
	
	int radius = pDoc->getSize();

	int randomNumberOfCircle = rand() % 3 + 2;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < randomNumberOfCircle; i++)
	{
		int scatteredSize1 = randomNumberWithinRange(-radius, radius);
		int scatteredSize2 = randomNumberWithinRange(-radius, radius);
		Point newSource(source.x + scatteredSize1, source.y + scatteredSize2);
		Point newTarget(target.x + scatteredSize1, target.y + scatteredSize2);

		SetColor(newSource);
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f(newTarget.x, newTarget.y); // center of circle
			for (int j = 0; j <= 20; j++) 
			{
				glVertex2f(
					(newTarget.x + (radius * cos(j * 2.0 * 3.142 / 20))), (newTarget.y + (radius * sin(j * 2.0 * 3.142 / 20)))
				);
			}
		glEnd();
	}
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target)
{
}
