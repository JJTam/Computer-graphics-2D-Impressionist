# COMP-4411-Project1-Impressionist
<p>Impressionist is an interactive program that creates pictures that look like impressionistic paintings. It is based on a paper and a program by Paul Haeberli. Here is the web <a href="http://graphics.stanford.edu/courses/cs248-99/haeberli/">"Paint by Numbers"</a>.</p>
<p>To create an impressionistic picture, the user loads an existing image and paints a seqence of "brush strokes" onto a blank pixel canvas. These brush strokes pick up color from the original image, giving the look of a painting.</p> 

## Basic Requirement
1. Implement 5 different brush types: single line, scattered lines, scattered points, (filled) circles, and scattered (filled) circles. See the sample solution for an example of each brush's appearance. Note that scattered brushes should sample from each location they color individually, not just use a single color for each splotch.
2. Add sliders to control various brush attributes. You need to include sliders for the line thickness and brush angle, in addition to the existing brush size slider.
3. Add the ability to control the brush direction. The stroke direction should be controlled four different ways: using a slider value, using the right mouse button to drag out a direction line, using the direction of the cursor movement, and using directions that are perpendicular to the gradient of the image. You can use a radio box to allow the user to select which method to use.
4. Allow the user to change the opacity (alpha value) of the brush stroke. An alpha value slider should be added to the controls window.

## Bells and Whistles

<pre style="word-wrap: break-word; white-space: pre-wrap;">Impressionist Bells and Whistles checklist for grading
(submit with your project ONLY if you have implemented any of the following B&amp;Ws)

HKUST login(s): 

Delete yes/no when appropriate

W per new brush						yes
	- scattered polygon brush
W border clipping					yes
W (red) marker						yes
W swap								yes
B RGB scale							yes
B blur/sharp brush					yes/no
B 1 level undo						yes
B dissolve							yes/no 
BW fade in/out input on output canvas			yes/no
BW mural (blending)					yes/no
BW alpha brush						yes/no
BW automatic paint whole image				yes
BW gradient from user-specified image			yes
BW edge clipping					yes/no
2B user-specified kernel				yes/no
2B edge detection + user-specified edge clipping	yes/no
2B multiresolution					yes
2B warp brush						yes/no
2B curved brush following image gradient		yes/no
4B mosaic						yes
4B impressionist video with temporal coherency		yes/no
8B Bayesian matting					yes/no
</pre>
