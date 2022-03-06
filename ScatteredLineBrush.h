
// ScatteredLineBrush.h
//
// The header file for Scattered Line Brush. 
//

#ifndef SCATTEREDLINEBRUSH_H
#define SCATTEREDLINEBRUSH_H

#include "ImpBrush.h"

class ScatteredLineBrush : public ImpBrush {
public:
	ScatteredLineBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void DrawLines(const Point source, const Point target, const int angle, const int size);
	int CalculateDirectionPerpendicularToGradient(Point source);
	char* BrushName(void);

	Point m_previousTargetCoordinate;
};


#endif