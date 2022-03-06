// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"
#include <string>

using namespace std;

class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image
	int		loadAnotherImage(char* iname);	// called by the UI to load another image


	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	setBrushType(int type);			// called by the UI to set the brushType
	int		getSize();						// get the UI size
	void	setSize(int size);				// set the UI size
	char*	getImageName();					// get the current image name

	void	setStrokeDirectionType(int type);

	int		getWidth();						// get the line width
	int		getAngle();						// get the line angle
	void	setAngle(int angle);			// set the line angle
	double	getAlpha();						// the the alpha value

	void	savePastPainting();				// save the record
	void	undo();							// undo 1 level
	void	swapContent();					// swap paint view and original view
	bool	getSwap();						// swap status
	void	setSwap(bool status);			// set swap status

	void	paint();						// auto paint
	int		getSpacing();					// get spacing for autopaint
	bool	getSizeRandom();				// if auto paint need random spacing

	bool	getAnotherGradient();			// use gradient of another image
	unsigned char* getCurrentOriginalImage();	// show the Image

	// for bonus Mosaic
	void	drawMosaic();					// draw a mosaic
	void	loadImageBitmap(char* image, int loader, int size);	// load an image for mosaic

	void	autoPaint();					// auto paint


// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image and painting.
	unsigned char*	m_ucHistory;
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucOriginal;
	unsigned char*	m_ucPainting;
	unsigned char*	m_ucAnotherImage;
	unsigned char*	m_ucEdgeImage;

	unsigned char*	m_ucPastPainting;

	// for bonus Mosaic
	unsigned char**	m_ucImages;
	GLubyte**		imageColors;

	// The current active brush.
	ImpBrush* m_pCurrentBrush;	
	// Size of the brush.
	int m_nSize;				
	// Width of the line brush
	int m_nLineWidth;
	// Angle of the line brush
	int m_nAngle;
	// Alpha of the brush
	double m_nAlpha;
	// The current stroke direction choice
	int m_nCurrentStrokeDirectionType;
	// swap status
	bool m_nSwap;

	bool			m_ncolorIsSelected;
	GLubyte			colorSelected[3];

	int m_nCurrentDisplay;

	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );  
	// Get the color of the target picture at the specified coord
	GLubyte* GetTargetPixel(int x, int y, unsigned char* image, int width, int height);

	GLubyte* GetAnotherImagePixel(int x, int y);
	

private:
	char m_imageName[256];

};

extern void MessageBox(char *message);

#endif
