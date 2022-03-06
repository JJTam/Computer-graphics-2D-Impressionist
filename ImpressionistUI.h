//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <fl/Fl_Color_Chooser.H>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;
	OriginalView*		m_origView;

	// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Choice*			m_BrushTypeChoice;

	Fl_Choice*			m_strokeDirectionChoice;

	Fl_Slider*			m_BrushSizeSlider;
	Fl_Button*          m_ClearCanvasButton;

	Fl_Slider*			m_LineWidthSlider;
	Fl_Slider*			m_LineAngleSlider;
	Fl_Slider*			m_AlphaValueSlider;
	Fl_Slider*			m_WarpValueSlider;

	Fl_Light_Button*	m_EdgeClipping;
	Fl_Light_Button*	m_AnotherGradient;

	Fl_Slider*			m_Spacing;
	Fl_Light_Button*	m_SizeRandom;
	Fl_Button*			m_Paint;

	Fl_Slider*			m_EdgeThreshold;
	Fl_Button*			m_DoIt;

	// mosaic bonus
	Fl_Window*			m_MosaicDialog;
	Fl_Button*			m_loadImageButton1;
	Fl_Button*			m_loadImageButton2;
	Fl_Button*			m_loadImageButton3;
	Fl_Button*			m_loadImageButton4;
	Fl_Button*			m_drawMosaicButton;

	// TODO add mores UI widgets here
	// for Color Selection



	// for Paintly Dialog





	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	void				setSize(int size);

	int					getWidth();
	void				setWidth(int width);

	int					getAngle();
	void				setAngle(int angle);

	double				getAlpha();
	void				setAlpha(double alpha);

	int					getSpacing();
	bool				getSizeRandom();

	double				getWarp();
	void				setWarp(double warp);

	bool				getAnotherGradient();


private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	int		m_nWidth;
	int		m_nAngle;
	double	m_nAlpha;

	bool	m_nEdgeClipping;
	bool	m_nAnotherGradient;

	double	m_nWarpValue;
	int		m_nSpacing;
	bool	m_nSizeRandom;

	int		m_nEdgeThreshold;


	// Static class members
	static Fl_Menu_Item	menuitems[];
	static Fl_Menu_Item	brushTypeMenu[NUM_BRUSH_TYPE+1];
	static Fl_Menu_Item strokeDirectionMenu[NUM_STROKE_DIRECTION_TYPE+1];
	// TODO 
	static Fl_Menu_Item paintlyTypeMenu[6];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	
	// File
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_colors(Fl_Menu_* o, void* v);
	static void cb_paintly(Fl_Menu_* o, void* v);
	static void	cb_load_another_image(Fl_Menu_* o, void* v);

	// Brush Dialog
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void	cb_sizeSlides(Fl_Widget* o, void* v);
	static void cb_widthSlides(Fl_Widget* o, void* v);
	static void cb_angleSlides(Fl_Widget* o, void* v);
	static void cb_alphaSlides(Fl_Widget* o, void* v);
	static void	cb_warpValueSlides(Fl_Widget* o, void* v);
	static void cb_edgeClippingLightButton(Fl_Widget* o, void* v);
	static void cb_anotherGradientLightButton(Fl_Widget* o, void* v);
	
	static void cb_spacingSides(Fl_Widget* o, void* v);
	static void cb_sizeRandomLightButton(Fl_Widget* o, void* v);
	static void cb_paint(Fl_Widget* o, void* v);

	static void cb_edgeThresholdSlides(Fl_Widget* o, void* v);
	static void cb_doIt(Fl_Widget* o, void* v);


	// Stroke Direction
	static void cb_strokeDirection(Fl_Widget* o, void* v);
	

	// Bonus
	static void cb_swapContent(Fl_Menu_* o, void* v);
	static void cb_undo(Fl_Menu_* o, void* v);
	static void cb_autoPaint(Fl_Menu_* o, void* v);


	static void cb_mosaic(Fl_Menu_* o, void* v);
	static void cb_loadMosaicImage1(Fl_Widget* o, void* v);
	static void cb_loadMosaicImage2(Fl_Widget* o, void* v);
	static void cb_loadMosaicImage3(Fl_Widget* o, void* v);
	static void cb_loadMosaicImage4(Fl_Widget* o, void* v);
	static void cb_drawMosaic(Fl_Widget* o, void* v);

	// TODO
	// Color Selection
	static void	cb_colorSelect(Fl_Widget* o, void* v);


	// TODO
	// Paintly Dialog
	static void	cb_paintlyChoice(Fl_Widget* o, void* v);

	static void	cb_exit(Fl_Menu_* o, void* v);


	// Display
	static void cb_display_original_image(Fl_Menu_* o, void* v);
	static void cb_display_edge_image(Fl_Menu_* o, void* v);
	static void cb_display_another_image(Fl_Menu_* o, void* v);

	// Options
	static void cb_faster_option(Fl_Menu_* o, void* v);
	static void cb_safer_option(Fl_Menu_* o, void* v);


	// Help
	static void	cb_about(Fl_Menu_* o, void* v);

};

#endif
