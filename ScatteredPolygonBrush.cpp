// ScatteredPolygonBrush.cpp



#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredPolygonBrush.h"
#include <math.h>

extern int irand(int max);


ScatteredPolygonBrush::ScatteredPolygonBrush(ImpressionistDoc* pDoc, char* name)
	: ImpBrush(pDoc, name) {}



void ScatteredPolygonBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}


void ScatteredPolygonBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredPolygonBrush::BrushMove document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int scatteredSize = size / 2;


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	for (int i = 0; i < irand(size); i++) {
		double deltaX = (GLdouble)-scatteredSize + irand(size);
		double deltaY = (GLdouble)-scatteredSize + irand(size);
		Point newSource(source.x + deltaX, source.y + deltaY);
		Point newTarget(target.x + deltaX, target.y + deltaY);
		SetColor(newSource);

		glBegin(GL_POLYGON);

		double incre = 360.f / irand(10);
		int offset = irand(360);

		for (double i = 0.f; i < 360.f; i += incre) {
			double r = (i + offset) * M_PI / 180;
			glVertex2f(
				(GLfloat)(newTarget.x) + cos(r) * scatteredSize,
				(GLfloat)(newTarget.y) + sin(r) * scatteredSize
			);
		}

		glEnd();
	}

}




void ScatteredPolygonBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}