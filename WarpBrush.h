
#include "ImpBrush.h"
#include <vector>

using namespace std;

class WarpBrush : public ImpBrush {

public:
	WarpBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);
	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);


	vector<std::vector<float>> kernel;

	Point prePoint;

};

