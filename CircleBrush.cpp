
// CircleBrush.cpp
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"
#include <math.h>

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) 
	: ImpBrush(pDoc, name) {}


void CircleBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();


	glPointSize((float)size);

	BrushMove(source, target);
}


void CircleBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	GLfloat theta;

	int radius = pDoc->getSize();

	glBegin(GL_POLYGON);
	SetColor(source);
	for (int i = 0; i < 360; i++) {
		theta = i * M_PI / 180;
		glVertex2f(cos(theta) * radius + target.x, sin(theta) * radius + target.y);
	}

	glEnd();
}



void CircleBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}