// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"
#include "Mosaic.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "CircleBrush.h"
#include "ScatteredPointBrush.h"
#include "ScatteredLineBrush.h"
#include "SingleLineBrush.h"
#include "ScatteredCircleBrush.h"
#include "ScatteredPolygonBrush.h"

#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL media name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;
	m_ucAnotherImage = NULL;

	m_ucPastPainting = NULL;

	m_nSwap = false;

	m_ncolorIsSelected = false;

	m_nCurrentDisplay = ORIGINAL_IMAGE;

	m_ucImages = new unsigned char* [4];
	for (int i = 0; i < 4; i++)
	{
		m_ucImages[i] = NULL;
	}

	imageColors = new GLubyte * [4];
	for (int i = 0; i < 4; i++)
	{
		imageColors[i] = NULL;
	}


	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new SingleLineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new ScatteredPointBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new ScatteredLineBrush( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatteredCircleBrush( this, "Scattered Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POLYGONS]
		= new ScatteredPolygonBrush(this, "Scattered Polygon");


	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];
	
	// set first stroke direction
	m_nCurrentStrokeDirectionType = STROKE_DIRECTION_SLIDER_OR_RIGHT_MOUSE;
}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI = ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}


void ImpressionistDoc::setStrokeDirectionType(int type)
{
	m_nCurrentStrokeDirectionType = type;
}

int ImpressionistDoc::getWidth()
{
	return m_pUI->getWidth();
}

int ImpressionistDoc::getAngle()
{
	return m_pUI->getAngle();
}

void ImpressionistDoc::setAngle(int angle)
{
	m_pUI->setAngle(angle);
}

double ImpressionistDoc::getAlpha()
{
	return m_pUI->getAlpha();
}

void ImpressionistDoc::savePastPainting()
{
	memcpy(m_ucPastPainting, m_ucPainting, m_nWidth * m_nHeight * 3 * sizeof(unsigned char));
}

void ImpressionistDoc::undo()
{
	memcpy(m_ucPainting, m_ucPastPainting, m_nWidth * m_nHeight * 3 * sizeof(unsigned char));
	m_pUI->m_paintView->refresh();
}

void ImpressionistDoc::swapContent()
{
	unsigned char* temp = m_ucPainting;
	m_ucPainting = m_ucBitmap;
	m_ucBitmap = temp;
	m_pUI->m_origView->refresh();
	m_pUI->m_paintView->refresh();
}

bool ImpressionistDoc::getSwap()
{
	return m_nSwap;
}

void ImpressionistDoc::setSwap(bool status)
{
	m_nSwap = status;
}

void ImpressionistDoc::paint()
{
	m_pUI->m_paintView->setPaint();
}

int ImpressionistDoc::getSpacing()
{
	return m_pUI->getSpacing();
}

bool ImpressionistDoc::getSizeRandom()
{
	return m_pUI->getSizeRandom();
}

bool ImpressionistDoc::getAnotherGradient()
{
	return m_pUI->getAnotherGradient();
}

unsigned char* ImpressionistDoc::getCurrentOriginalImage()
{
	unsigned char* currentDisplay = m_ucBitmap;

	switch (m_nCurrentDisplay)
	{
	case ORIGINAL_IMAGE:
		if (m_ucBitmap)
			currentDisplay = m_ucBitmap;
		break;
	case ANOTHER_IMAGE:
		if (m_ucAnotherImage)
			currentDisplay = m_ucAnotherImage;
		break;
	case EDGE_IMAGE:
		if (m_ucEdgeImage)
			currentDisplay = m_ucEdgeImage;
		break;
	default:
		currentDisplay = m_ucBitmap;
		break;
	}

	return currentDisplay;

}

void ImpressionistDoc::drawMosaic()
{
	if (!m_ucImages[0]) {
		fl_alert("Tail images are required.");
		return;
	}

	if (!m_ucBitmap) {
		fl_alert("Please load original image");
		return;
	}

	Mosaic mosaic(this);
	mosaic.generateMosaic();
}

void ImpressionistDoc::loadImageBitmap(char* image, int loader, int size)
{
	unsigned char* data;
	int width;
	int height;

	if (!m_ucBitmap) {
		fl_alert("please load original image first");
		return;
	}

	if ((data = readBMP(image, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return;
	}

	if (width < size || height < size) {
		fl_alert("Should be larger than %d * %d", size, size);
		return;
	}


	if (m_ucImages[loader - 1]) {
		delete[] m_ucImages[loader - 1];
	}

	m_ucImages[loader - 1] = new unsigned char[size * size * 3];
	int width_scale = width / size;
	int height_scale = height / size;

	Mosaic mosaic(this);

	for (int i = 0; i != size; i++) {
		for (int j = 0; j != size; j++) {

			Point upLeft(j * width_scale, i * height_scale);
			Point bottomRight((j + 1) * width_scale, (i + 1) * height_scale);


			GLubyte* averageColor;

			averageColor = mosaic.findAverageColor(upLeft, bottomRight, data, width, height);
			m_ucImages[loader - 1][(j + size * i) * 3] = averageColor[0];
			m_ucImages[loader - 1][(j + size * i) * 3 + 1] = averageColor[1];
			m_ucImages[loader - 1][(j + size * i) * 3 + 2] = averageColor[2];

			delete[] averageColor;
		}
	}
	if (imageColors[loader - 1]) delete[] imageColors[loader - 1];

	imageColors[loader - 1] = Mosaic::findImageAverageColor(size, m_ucImages[loader - 1]);

	return;

}


//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	if ( m_ucBitmap ) delete [] m_ucBitmap;
	if ( m_ucPainting ) delete [] m_ucPainting;
	if (m_ucPastPainting) delete[] m_ucPastPainting;

	m_ucBitmap		= data;

	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*3];
	m_ucPastPainting = new unsigned char[width * height * 3];
	memset(m_ucPainting, 0, width*height*3);
	memset(m_ucPastPainting, 0, width * height * 3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();


	return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

int ImpressionistDoc::loadAnotherImage(char* iname)
{
	// try to open the image to read
	unsigned char* data;
	int	width;
	int	height;

	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// check dimension
	if (m_nWidth != width || m_nHeight != height) {
		fl_alert("Different Dimension!");
		delete[] data;
		return 0;
	}

	// release old storage
	if (m_ucAnotherImage) 
		delete[] m_ucAnotherImage;

	m_ucAnotherImage = data;

	return 1;
}



//----------------------------------------------------------------
// Auto paint for user
//----------------------------------------------------------------
void ImpressionistDoc::autoPaint() {

	m_pUI->m_paintView->setAutoPaint(true);
	m_pUI->m_paintView->setPaint();

}


//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}

GLubyte* ImpressionistDoc::GetTargetPixel(int x, int y, unsigned char* image, int width, int height)
{
	if (x < 0)
		x = 0;
	else if (x >= width)
		x = width - 1;

	if (y < 0)
		y = 0;
	else if (y >= height)
		y = height - 1;

	return (GLubyte*)(image + 3 * (y * width + x));
}

GLubyte* ImpressionistDoc::GetAnotherImagePixel(int x, int y)
{
	if (x < 0)
		x = 0;
	else if (x >= m_nWidth)
		x = m_nWidth - 1;

	if (y < 0)
		y = 0;
	else if (y >= m_nHeight)
		y = m_nHeight - 1;

	return (GLubyte*)(m_ucAnotherImage + 3 * (y * m_nWidth + x));
}



