// SingleLineBrush.h

#pragma once
#include "ImpBrush.h"
class SingleLineBrush : public ImpBrush
{
public:
	SingleLineBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
	void drawLine(const Point source, const Point target, const int angle, const int size);
	int calculateDirectionPerpendicularToGradient(Point source);

	Point m_previousTargetCoordinate;
};

