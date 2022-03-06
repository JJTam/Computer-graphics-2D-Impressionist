//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o) {
	return ( (ImpressionistUI*)(o->parent()->user_data()));
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc *pDoc=whoami(o)->getDocument();
	
	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp");
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) {
	whoami(o)->m_brushDialog->show();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Brings up the colors selection
// This is called by the UI when the colors menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_colors(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	// TODO
	GLubyte colorValue[3];
	memcpy(colorValue, pDoc->colorSelected, 3);
	bool picked = fl_color_chooser("Color", colorValue[0], colorValue[1], colorValue[2], -1);
	if (picked) {
		memcpy(pDoc->colorSelected, colorValue, 3);
		pDoc->m_ncolorIsSelected = true;
	}

}


//-----------------------------------------------------------
// Brings up the paintly dialog
// This is called by the UI when the paintly menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_paintly(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	// TODO
	printf("To do paintly dialog\n");

}

void ImpressionistUI::cb_load_another_image(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadAnotherImage(newfile);
	}
}



//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;


	pDoc->setBrushType(type);
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v) {
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nSize = int(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_widthSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nWidth = int(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_angleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAngle = int(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_alphaSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAlpha = double(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_edgeClippingLightButton(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nEdgeClipping = bool(((Fl_Light_Button*)o)->value());
}

void ImpressionistUI::cb_anotherGradientLightButton(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAnotherGradient = bool(((Fl_Light_Button*)o)->value());
}

void ImpressionistUI::cb_spacingSides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSpacing = int(((Fl_Slider*)o)->value());

}

void ImpressionistUI::cb_warpValueSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nWarpValue = double(((Fl_Slider*)o)->value());

}

void ImpressionistUI::cb_sizeRandomLightButton(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSizeRandom = bool(((Fl_Light_Button*)o)->value());
}

void ImpressionistUI::cb_paint(Fl_Widget* o, void* v)
{
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->paint();
}


void ImpressionistUI::cb_edgeThresholdSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nEdgeThreshold = int(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_doIt(Fl_Widget* o, void* v)
{
	//
}


//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of stroke direction to use to the one chosen in the stroke direction choice.  
// Called by the UI when a stroke directioni is chosen in the stroke direction choice
//------------------------------------------------------------
void ImpressionistUI::cb_strokeDirection(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	int type = (int)v;


	pDoc->setStrokeDirectionType(type);
}

void ImpressionistUI::cb_swapContent(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	pDoc->swapContent();
}

void ImpressionistUI::cb_undo(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	pDoc->undo();
}


//-----------------------------------------------------------
// Auto paint
// Called by the UI when the auto paint item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_autoPaint(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	pDoc->autoPaint();
}



void ImpressionistUI::cb_mosaic(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	whoami(o)->m_MosaicDialog->show();
}

void ImpressionistUI::cb_loadMosaicImage1(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	char* newfile = fl_file_chooser("Open 24 bit depth bmp file for Mosaic", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadImageBitmap(newfile, 1, 24);
		pUI->m_loadImageButton2->activate();
	}
}

void ImpressionistUI::cb_loadMosaicImage2(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	char* newfile = fl_file_chooser("Open 24 bit depth bmp file for Mosaic", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadImageBitmap(newfile, 2, 24);
		pUI->m_loadImageButton3->activate();
	}
}

void ImpressionistUI::cb_loadMosaicImage3(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	char* newfile = fl_file_chooser("Open 24 bit depth bmp file for Mosaic", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadImageBitmap(newfile, 3, 24);
		pUI->m_loadImageButton4->activate();
	}
}

void ImpressionistUI::cb_loadMosaicImage4(Fl_Widget * o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	char* newfile = fl_file_chooser("Open 24 bit depth bmp file for Mosaic", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadImageBitmap(newfile, 4, 24);
	}
}

void ImpressionistUI::cb_drawMosaic(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = (ImpressionistUI*)(o->user_data());
	pUI->m_paintView->drawMosaic();
	pUI->m_paintView->refresh();
}



//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of color to use to the one chosen in the color selection.  
// Called by the UI when a color is chosen in the color selection
//-------------------------------------------------------------
void ImpressionistUI::cb_colorSelect(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	int type = (int)v;

	// TODO
}





//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of paintly to use to the one chosen in the paintly choice.  
// Called by the UI when a paintly is chosen in the paintly selection.  
//-------------------------------------------------------------
void ImpressionistUI::cb_paintlyChoice(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	int type = (int)v;

	// TODO


}




//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) {
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();

}



//-----------------------------------------------------------
// Display the original image
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_display_original_image(Fl_Menu_* o, void* v) {
	ImpressionistUI* pUI = whoami(o);
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	// TODO
	pDoc->m_nCurrentDisplay = ORIGINAL_IMAGE;
	pUI->m_origView->refresh();

}


//-----------------------------------------------------------
// Display the edge image
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_display_edge_image(Fl_Menu_* o, void* v) {
	ImpressionistUI* pUI = whoami(o);
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

    // TODO
	pDoc->m_nCurrentDisplay = EDGE_IMAGE;
	pUI->m_origView->refresh();
}


//-----------------------------------------------------------
// Display the another image
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_display_another_image(Fl_Menu_* o, void* v) {
	ImpressionistUI* pUI = whoami(o);
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	// TODO
	pDoc->m_nCurrentDisplay = ANOTHER_IMAGE;
	pUI->m_origView->refresh();

}



//-----------------------------------------------------------
// Faster option
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_faster_option(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	// TODO
	printf("To do faster option\n");
}



//-----------------------------------------------------------
// Safer option
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_safer_option(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	// TODO
	printf("To do safer option\n");
}


//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) {
	fl_message("Impressionist FLTK version for COMP4411, Spring 2022");
}



//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument() {
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc) {
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize() {
	return m_nSize;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize(int size) {
	m_nSize=size;

	if (size <= 40)
		m_BrushSizeSlider->value(m_nSize);
}

int ImpressionistUI::getWidth()
{
	return m_nWidth;
}

void ImpressionistUI::setWidth(int width)
{
	m_nWidth = width;

	if (width <= 40)
		m_BrushSizeSlider->value(m_nSize);
}

int ImpressionistUI::getAngle()
{
	return m_nAngle;
}


void ImpressionistUI::setAngle(int angle)
{
	m_nAngle = angle;

	if (angle <= 359)
	{
		m_LineAngleSlider->value(m_nAngle);
	}
}

// Set alpha value
void ImpressionistUI::setAlpha(double alpha) {
	m_nAlpha = alpha;

	if (alpha <= 1.00)
		m_AlphaValueSlider->value(m_nAlpha);

}

int ImpressionistUI::getSpacing()
{
	return m_nSpacing;
}

bool ImpressionistUI::getSizeRandom()
{
	return m_nSizeRandom;
}

bool ImpressionistUI::getAnotherGradient()
{
	return m_nAnotherGradient;
}



double ImpressionistUI::getAlpha()
{
	return m_nAlpha;
}

double ImpressionistUI::getWarp() {
	return m_nWarpValue;
}

void ImpressionistUI::setWarp(double warp) {
	m_nWarpValue = warp;

	if (warp <= 20.00)
		m_WarpValueSlider->value(warp);
}



// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{"&File", 0, 0, 0, FL_SUBMENU },
		{"&Load Image...",			FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image},
		{"&Save Image...",			FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image},
		{"&Brushes...",				FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes}, 
		{"&Clear Canvas",			FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER},
		{"&Colors...",				FL_ALT + 'k', (Fl_Callback*)ImpressionistUI::cb_colors},
		{"&Paintly...",				FL_ALT + 'p', (Fl_Callback*)ImpressionistUI::cb_paintly, 0, FL_MENU_DIVIDER},
		{"&Load Edge Image...",		FL_ALT + 'e', (Fl_Callback*)ImpressionistUI::cb_load_image},
		{"&Load Another Image...",	FL_ALT + 'a', (Fl_Callback*)ImpressionistUI::cb_load_another_image},
		{"&Quit",					FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit},
		{0},

	{"&Display", 0, 0, 0, FL_SUBMENU },
		{"&Orignal Image...",	FL_ALT + 'o', (Fl_Callback*)ImpressionistUI::cb_display_original_image},
		{"&Edge Image...",		FL_ALT + 'e', (Fl_Callback*)ImpressionistUI::cb_display_edge_image},
		{"&Another Image...",	FL_ALT + 'a', (Fl_Callback*)ImpressionistUI::cb_display_another_image},
		{0},

	{"&Options", 0, 0, 0, FL_SUBMENU },
		{"&Faster",		FL_ALT + 'f', (Fl_Callback*)ImpressionistUI::cb_faster_option},
		{"&Safer",		FL_ALT + 's', (Fl_Callback*)ImpressionistUI::cb_safer_option},
		{0},

	{"&Bonus", 0, 0, 0, FL_SUBMENU },
		{"&Undo",			FL_ALT + 'z', (Fl_Callback*)ImpressionistUI::cb_undo},
		{"&Swap Content",	FL_ALT + 's', (Fl_Callback*)ImpressionistUI::cb_swapContent },
		{"&Auto Paint",		FL_ALT + 'a', (Fl_Callback*)ImpressionistUI::cb_autoPaint, 0, FL_MENU_DIVIDER},
		{"&Mosaic",			FL_ALT + 'm', (Fl_Callback*)ImpressionistUI::cb_mosaic},
		{0},


	{"&Help", 0, 0, 0, FL_SUBMENU },
		{"&About",		FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about},
		{0},


	{0}
};


// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Warps",				FL_ALT + 'w', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_WARPS},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {"Scattered Polygons",FL_ALT+'o', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POLYGONS},
  {0}
};

// Stroke direction menu definition
Fl_Menu_Item ImpressionistUI::strokeDirectionMenu[NUM_STROKE_DIRECTION_TYPE + 1] = {
	{"Slider/Right Mouse",	FL_ALT + 's', (Fl_Callback*)ImpressionistUI::cb_strokeDirection, (void*)STROKE_DIRECTION_SLIDER_OR_RIGHT_MOUSE},
	{"Gradient",			FL_ALT + 'g', (Fl_Callback*)ImpressionistUI::cb_strokeDirection, (void*)STROKE_DIRECTION_GRADIENT},
	{"Brush Direction",		FL_ALT + 'b', (Fl_Callback*)ImpressionistUI::cb_strokeDirection, (void*)STROKE_DIRECTION_BRUSH_DIRECTION},
	{0}
};

// TODO add colors selection here



// TODO add paintly choice here
//// Paintly style choice menu definition
//Fl_Menu_Item ImpressionistUI::paintlyTypeMenu[6] = {
//  {"Impressionist",		FL_ALT + 'i', (Fl_Callback*)ImpressionistUI::cb_paintlyChoice, (void*)},
//  {"Expressionist",		FL_ALT + 'e', (Fl_Callback*)ImpressionistUI::cb_paintlyChoice, (void*)},
//  {"Color Wash",		FL_ALT + 'w', (Fl_Callback*)ImpressionistUI::cb_paintlyChoice, (void*)},
//  {"Pointillist",		FL_ALT + 'p', (Fl_Callback*)ImpressionistUI::cb_paintlyChoice, (void*)},
//  {"Customize",			FL_ALT + 'c', (Fl_Callback*)ImpressionistUI::cb_paintlyChoice, (void*)},
//  {0}
//};



//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values
	m_nSize = 10;
	m_nWidth = 1;
	m_nAngle = 0;
	m_nAlpha = 1.00;

	m_nAnotherGradient = false;

	m_nSpacing = 16;
	m_nSizeRandom = false;

	m_nEdgeThreshold = 200;

	// brush dialog definition
	m_brushDialog = new Fl_Window(450, 450, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);

		// Add a stroke direction type choice to the dialog
		m_strokeDirectionChoice = new Fl_Choice(115, 45, 150, 25, "&Stroke Direction");
		m_strokeDirectionChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_strokeDirectionChoice->menu(strokeDirectionMenu);
		m_strokeDirectionChoice->callback(cb_strokeDirection);

		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);


		// Add line width slider to the dialog
		m_LineWidthSlider = new Fl_Value_Slider(10, 110, 300, 20, "Line Width");
		m_LineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineWidthSlider->type(FL_HOR_NICE_SLIDER);
		m_LineWidthSlider->labelfont(FL_COURIER);
		m_LineWidthSlider->labelsize(12);
		m_LineWidthSlider->minimum(1);
		m_LineWidthSlider->maximum(40);
		m_LineWidthSlider->step(1);
		m_LineWidthSlider->value(m_nWidth);
		m_LineWidthSlider->align(FL_ALIGN_RIGHT);
		m_LineWidthSlider->callback(cb_widthSlides);

		// Add line angle slider to the dialog
		m_LineAngleSlider = new Fl_Value_Slider(10, 140, 300, 20, "Line Angle");
		m_LineAngleSlider->user_data((void*)(this));
		m_LineAngleSlider->type(FL_HOR_NICE_SLIDER);
		m_LineAngleSlider->labelfont(FL_COURIER);
		m_LineAngleSlider->labelsize(12);
		m_LineAngleSlider->minimum(0);
		m_LineAngleSlider->maximum(359);
		m_LineAngleSlider->step(1);
		m_LineAngleSlider->value(m_nAngle);
		m_LineAngleSlider->align(FL_ALIGN_RIGHT);
		m_LineAngleSlider->callback(cb_angleSlides);

		// Add alpha silder to the dialog
		m_AlphaValueSlider = new Fl_Value_Slider(10, 170, 300, 20, "Alpha");
		m_AlphaValueSlider->user_data((void*)(this));
		m_AlphaValueSlider->type(FL_HOR_NICE_SLIDER);
		m_AlphaValueSlider->labelfont(FL_COURIER);
		m_AlphaValueSlider->labelsize(12);
		m_AlphaValueSlider->minimum(0.00);
		m_AlphaValueSlider->maximum(1.00);
		m_AlphaValueSlider->step(0.01);
		m_AlphaValueSlider->value(m_nAlpha);
		m_AlphaValueSlider->align(FL_ALIGN_RIGHT);
		m_AlphaValueSlider->callback(cb_alphaSlides);

		// Add warp silder to the dialog
		m_WarpValueSlider = new Fl_Value_Slider(10, 200, 300, 20, "Warp Strength");
		m_WarpValueSlider->user_data((void*)(this));
		m_WarpValueSlider->type(FL_HOR_NICE_SLIDER);
		m_WarpValueSlider->labelfont(FL_COURIER);
		m_WarpValueSlider->labelsize(12);
		m_WarpValueSlider->minimum(0.00);
		m_WarpValueSlider->maximum(20.00);
		m_WarpValueSlider->step(0.01);
		m_WarpValueSlider->value(m_nWarpValue);
		m_WarpValueSlider->align(FL_ALIGN_RIGHT);
		m_WarpValueSlider->callback(cb_warpValueSlides);


		// Add edge clipping light button
		m_EdgeClipping = new Fl_Light_Button(10, 230, 120, 25, "&Edge Clipping");
		m_EdgeClipping->user_data((void*)(this));   // record self to be used by static callback functions
		m_EdgeClipping->callback(cb_edgeClippingLightButton);

		// Add another gradient light button
		m_AnotherGradient = new Fl_Light_Button(240, 260, 150, 25, "&Another Gradient");
		m_AnotherGradient->user_data((void*)(this));   // record self to be used by static callback functions
		m_AnotherGradient->callback(cb_anotherGradientLightButton);

		// Add spacing slider to the dialog
		m_Spacing = new Fl_Value_Slider(10, 295, 160, 25, "Spacing");
		m_Spacing->user_data((void*)(this));
		m_Spacing->type(FL_HOR_NICE_SLIDER);
		m_Spacing->labelfont(FL_COURIER);
		m_Spacing->labelsize(12);
		m_Spacing->minimum(1.00);
		m_Spacing->maximum(16.00);
		m_Spacing->step(1.0);
		m_Spacing->value(m_nSpacing);
		m_Spacing->align(FL_ALIGN_RIGHT);
		m_Spacing->callback(cb_spacingSides);

		// Add size random light button
		m_SizeRandom = new Fl_Light_Button(230, 295, 100, 25, "&Size Rand.");
		m_SizeRandom->user_data((void*)(this));   // record self to be used by static callback functions
		m_SizeRandom->callback(cb_sizeRandomLightButton);

		// Add paint button 
		m_Paint = new Fl_Button(340, 295, 50, 25, "&Paint");
		m_Paint->user_data((void*)(this));
		m_Paint->callback(cb_paint);

		// Add edge threshold to the dialog
		m_EdgeThreshold = new Fl_Value_Slider(10, 310, 200, 25, "Edge Threshold");
		m_EdgeThreshold->user_data((void*)(this));
		m_EdgeThreshold->type(FL_HOR_NICE_SLIDER);
		m_EdgeThreshold->labelfont(FL_COURIER);
		m_EdgeThreshold->labelsize(12);
		m_EdgeThreshold->minimum(0.00);
		m_EdgeThreshold->maximum(500.00);
		m_EdgeThreshold->step(3.0);
		m_EdgeThreshold->value(m_nEdgeThreshold);
		m_EdgeThreshold->align(FL_ALIGN_RIGHT);
		m_EdgeThreshold->callback(cb_edgeThresholdSlides);

		// Add Do It button
		m_DoIt = new Fl_Button(330, 330, 50, 25, "&Do It");
		m_DoIt->user_data((void*)(this));
		m_DoIt->callback(cb_doIt);

	m_brushDialog->end();

	m_MosaicDialog = new Fl_Window(300, 300, "Mosaic");

		m_loadImageButton1 = new Fl_Button(10, 20, 85, 25, "&Load Image");
		m_loadImageButton1->user_data((void*)(this));
		m_loadImageButton1->callback(cb_loadMosaicImage1);

		m_loadImageButton2 = new Fl_Button(110, 20, 85, 25, "&Load Image");
		m_loadImageButton2->user_data((void*)(this));
		m_loadImageButton2->callback(cb_loadMosaicImage2);
		m_loadImageButton2->deactivate();

		m_loadImageButton3 = new Fl_Button(10, 50, 85, 25, "&Load Image");
		m_loadImageButton3->user_data((void*)(this));
		m_loadImageButton3->callback(cb_loadMosaicImage3);
		m_loadImageButton3->deactivate();

		m_loadImageButton4 = new Fl_Button(110, 50, 85, 25, "&Load Image");
		m_loadImageButton4->user_data((void*)(this));
		m_loadImageButton4->callback(cb_loadMosaicImage4);
		m_loadImageButton4->deactivate();

		m_drawMosaicButton = new Fl_Button(60, 150, 85, 25, "&Draw Mosaic");
		m_drawMosaicButton->user_data((void*)(this));
		m_drawMosaicButton->callback(cb_drawMosaic);

}
