
// ScatteredPointBrush.cpp

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredPointBrush.h"

extern float frand();
extern int irand(int max);


ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc* pDoc, char* name)
	: ImpBrush(pDoc, name) {}



void ScatteredPointBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	glPointSize(1.0);

	BrushMove(source, target);
}


//int GetRandomNumber(int min, int max) {
//	int diff = max - min + 1;
//	int random = rand() % diff + min;
//	return random;
//}

void ScatteredPointBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredPointBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();

	// TODO get alpah value here pDoc ->
	GLfloat alpha = 1.0;

	int scatteredSize = size / 2;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_POINTS);
	
	// base case
	if (size == 1 || size == 2) {
		SetColor(source);
		glVertex2d(target.x, target.y);
	}
	else {
		for (int x = source.x - scatteredSize; x <= source.x + scatteredSize; x++) {
			for (int y = source.y - scatteredSize; y <= source.y + scatteredSize; y++) {
				if (rand() % 8 == 0 && irand(size) >= irand(scatteredSize)) {
					Point newSource(x, y);
					SetColor(newSource);
					glVertex2d(x, y);
				}
			}
		}
	}

	glEnd();

}


void ScatteredPointBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}