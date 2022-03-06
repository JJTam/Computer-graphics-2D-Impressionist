
// ScatteredPolygonBrush.h
//
// The header file for Scattered Polygon Brush. 
//

#ifndef SCATTEREDPOLYGONBRUSH_H
#define SCATTEREDPOLYGONBRUSH_H

#include "ImpBrush.h"



class ScatteredPolygonBrush : public ImpBrush {
public:
	ScatteredPolygonBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);

};


#endif
