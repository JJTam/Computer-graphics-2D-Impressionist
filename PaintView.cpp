//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//

#include "impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "paintview.h"
#include "ImpBrush.h"
#include <chrono>
#include <ctime>
#include <math.h>
#include <vector>
#include <algorithm>
#include <random>


#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6
#define AUTO_PAINT			7
#define DRAW_MOSAIC			8

#define PI 3.14159265

#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif


extern int irand(int max);
extern float frand();

static int		eventToDo;
static int		isAnEvent=0;
static Point	coord;
static Point	startDrag;

PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;

}



void PaintView::draw()
{
	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
	#endif // !MESA

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if(!valid())
	{

		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		ortho();

		glClear( GL_COLOR_BUFFER_BIT );
	}

	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y	= 0;

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
	drawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if ( startrow < 0 ) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting + 
		3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;

	m_nStartRow		= startrow;
	m_nEndRow		= startrow + drawHeight;
	m_nStartCol		= scrollpos.x;
	m_nEndCol		= m_nStartCol + drawWidth;

	bool autoSave = false;


	if ( m_pDoc->m_ucPainting && !isAnEvent) {
		RestoreContent();
	}

	if ( m_pDoc->m_ucPainting && isAnEvent) 
	{

		// Clear it after processing.
		isAnEvent	= 0;	
		//Point source;
		//Point target;

		//if (m_pDoc->getSwap())
		//{
		//	source.x = coord.x;
		//	source.y = m_nWindowHeight - coord.y;
		//	target.x = coord.x + m_nStartCol;
		//	target.y = m_nEndRow - coord.y;
		//}
		//else
		//{
		//	source.x = coord.x + m_nStartCol;
		//	source.y = m_nEndRow - coord.y;
		//	target.x = coord.x;
		//	target.y = m_nWindowHeight - coord.y;
		//}
		Point source( coord.x + m_nStartCol, m_nEndRow - coord.y );
		Point target( coord.x, m_nWindowHeight - coord.y );

		int deltaY;
		int deltaX;
		int angle;
		// This is the event handler
		switch (eventToDo) 
		{
		case LEFT_MOUSE_DOWN:
			m_pDoc->savePastPainting();
			m_pDoc->m_pCurrentBrush->BrushBegin( source, target );
			break;
		case LEFT_MOUSE_DRAG:
			if (isWithinBoundary(target))
			{
				m_pDoc->m_pCurrentBrush->BrushMove( source, target );
			}
			break;
		case LEFT_MOUSE_UP:
			m_pDoc->m_pCurrentBrush->BrushEnd( source, target );

			SaveCurrentContent();
			RestoreContent();
			break;
		case RIGHT_MOUSE_DOWN:
			// save the current content for future use
			SaveCurrentContent();
			
			startDrag.x = target.x;
			startDrag.y = target.y;
			break;
		case RIGHT_MOUSE_DRAG:
			// restore the content before dragging a line everytime
			RestoreContent();

			// draw line
			glLineWidth(2);
			glBegin(GL_LINES);
				glColor3ub(255, 0, 0);
				glVertex2d(startDrag.x, startDrag.y);
				glVertex2d(target.x, target.y);
			glEnd();
			break;
		case RIGHT_MOUSE_UP:
			// to dismiss the line that just drew, restore the content
			// that we save in the beginning (after right mouse down)
			RestoreContent();

			// calculate the angle by the start and end coordinates
			deltaX = startDrag.x - target.x;
			deltaY = startDrag.y - target.y;
			angle = atan2(deltaY, deltaX) * 180 / PI;
			if (angle < 0)
			{
				angle += 360;
			}
			m_pDoc->setAngle(angle);
			break;
		case AUTO_PAINT:
			autoPaint();
			break;
		case DRAW_MOSAIC:
			m_pDoc->drawMosaic();
			break;

		default:
			printf("Unknown event!!\n");		
			break;
		}
	}

	//if (isAutoPaint) {
	//	autoPaint();
	//	setAutoPaint(false);
	//	autoSave = true;
	//}


	glFlush();

	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA


	if (autoSave) {
		SaveCurrentContent();
		glFlush();
	}

	
}


int PaintView::handle(int event)
{
	switch(event)
	{
	case FL_ENTER:
	    redraw();
		break;
	case FL_PUSH:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DOWN;
		else
			eventToDo=LEFT_MOUSE_DOWN;
		isAnEvent=1;
		redraw();
		break;
	case FL_DRAG:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DRAG;
		else
			eventToDo=LEFT_MOUSE_DRAG;
		isAnEvent=1;
		redraw();
		m_pDoc->m_pUI->m_origView->setMarker(coord);
		break;
	case FL_RELEASE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_UP;
		else
			eventToDo=LEFT_MOUSE_UP;
		isAnEvent=1;
		redraw();
		break;
	case FL_MOVE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		m_pDoc->m_pUI->m_origView->setMarker(coord);
		break;
	default:
		return 0;
		break;

	}

	return 1;
}


void PaintView::refresh()
{
	redraw();
}


void PaintView::setAutoPaint(bool ap) {
	isAutoPaint = ap;
	refresh();
}


void PaintView::setPaint() {
	isAnEvent = 1;
	eventToDo = AUTO_PAINT;
	refresh();
}


// Auto paint
void PaintView::autoPaint() {
	m_pDoc->savePastPainting();

	setAutoPaint(false);

	const int size  = m_pDoc->getSize();
	int randomSize = size % 4 + 2;
	const int width = m_pDoc->m_nWidth;
	const int height = m_pDoc->m_nHeight;

	std::vector<Point> points;

	//Point target(0,0);

	for (int i = 0; i < width; i+= randomSize) {
		for (int j = 0; j < height; j += randomSize) {
			//target.x = i;
			//target.y = j;
			points.push_back(Point(i,j));
		}
		/*target.y = 0;*/
	}

	unsigned const seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(points.begin(), points.end(), default_random_engine(seed));

	random_shuffle(points.begin(), points.end());

	//m_pDoc->m_pCurrentBrush->BrushBegin(points.front(), points.front());

	for (auto& point : points) {
		Point randomPoint(point.x, point.y + m_nWindowHeight - m_nDrawHeight);
		m_pDoc->m_pCurrentBrush->BrushBegin(randomPoint, randomPoint);
		m_pDoc->m_pCurrentBrush->BrushEnd(randomPoint, randomPoint);
	}

	SaveCurrentContent();
	RestoreContent();

}


void PaintView::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}


void PaintView::SaveCurrentContent()
{
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	
	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );
}


void PaintView::RestoreContent()
{
	glDrawBuffer(GL_BACK);

	glClear( GL_COLOR_BUFFER_BIT );

	glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	glDrawPixels( m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart);

//	glDrawBuffer(GL_FRONT);
}

void PaintView::drawMosaic()
{
	isAnEvent = 1;
	eventToDo = DRAW_MOSAIC;
	refresh();
}

bool PaintView::isWithinBoundary(const Point target)
{
	if (target.x > m_nDrawWidth || (m_nWindowHeight - target.y) > m_nDrawHeight)
	{
		return false;
	}
	return true;
}
