# [rey](https://greyengine.org/rey/)
A collection of code in different programming languages, designed to make game development as easy as possible. We currently have native C support.

# Setting up
In order to get started with the *latest* version, you would need to download the main source code and open up the solution (crey.sln). Inside the main.c, you will find some basic boilerplate that gets a window to pop up on screen.

# Window

## Basic Window boilerplate
```
#include <grey.h>

int main()
{
	// Starts up all graphics with the amount of MSAA
	initGrey(0);

	// Creating a Window object with width, height, and a title.
	Window win = createWindow(1280, 720, "grey");

	// Main Window loop
	while (!shouldWindowClose(win)) {
		// Updating general variables about the Window
		updateWindow(&win);

		/* Any cool draw functions here! */

		// Draws everything you've requested up to this point
		renderWindow(win);
	}

	// Deletes all used memory for the Window object.
	deleteWindow(&win);
	// Free up any spare used memory and close all graphics related stuff.
	closeGrey();
}
```
This code here is basically the bare minimum to get a Window in grey to pop up. For more information about what all of this does and how to use it, please read below!

## Initiating/Closing grey
```
int main()
{
	// Starts up all graphics with the amount of MSAA
	initGrey(4);
	
	/* Cool grey stuff here */
	
	// Free up any spare used memory and close all graphics related stuff.
	closeGrey();
}
```
grey is set up by calling the initGrey() function and should be called at the beginning, and it is closed by using the closeGrey() function and should be called at the end. You might notice that initGrey takes a parameter called **sampleRate**. This is used to control the amount of [anti-aliasing](https://techguided.com/what-is-anti-aliasing/) in your program. The higher the number, the smoother edges look, but the more performance is sacrificed.

## Creating a Window
```
Window win = createWindow(1280, 720, "grey");
```
The creation of a window is handled in the createWindow() function which takes three parameters. The first one, 1280 in this sample code, is the **width** of the window. The second one, 720, is the **height** of the window. The third, "grey" in this sample code, is the **title** of the window. All of these three variables are accessible and modifiable at any time by simply using **win.width, win.height, & win.title** (of course switching out **win** with the name of your window).

## Deleting a Window
```
deleteWindow(&win);
```
Like most objects made in grey, they must be deleted at the end of the program. This is done in case you want to free up certain memory while the games still running, *like loading and deloading all of the assets for a level in your game once you get to it*. Having all of your assets for all of the game loaded at any time is generally bad practice if you are building a large scale game.

## Main Window loop
```
// Main Window loop
while (!shouldWindowClose(win)) {
	// Updating general variables about the Window
	updateWindow(&win);

	/* Any cool draw functions here! */

	// Draws everything you've requested up to this point
	renderWindow(win);
}
```
As you may know, most applications run by drawing frames over and over again. In order to do this, you need to create what is known as a **main loop**, which essentially repeats itself for the duration of the application's lifespan. In order to do this in grey, you use the **shouldWindowClose()** function, which returns whether or not the Window object passed in is ready to close or not. From there, it's very easy to make a simple while loop out of it which will run while the Window object shouldn't be closed. Inside this loop, two functions are called every frame: **updateWindow()**, which takes the memory address of the passed in Window, updates everything about it, and clears anything drawn from last frame, & **renderWindow()**, which takes any draw functions called prior to that point and renders them using the Window passed in. In between these two functions is what will be executed and drawn every frame.

# Drawing basic shapes
There are many functions that can draw different stuff in grey, such as shapes. This is a general overview of the most basic ones. Reminder that all draw functions should be called in the main loop, between **updateWindow()** and **renderWindow()**. Also, be aware that grey can draw stuff like textures, but those are in their own respective sections since drawing it includes loading and deleting it.

## Colors
```
// Defining a color (R, G, B, A)
Color lightPink = { 255, 158, 234, 255 };
// Making it a bit more green
lightPink[1] = 180;
// Making it slightly transparent
lightPink[3] = 200;
```
Before you get started drawing, you might want to understand how colors work in grey. A color is really just 4 unsigned ints, AKA 4 numbers that can't go in the negatives. Each number represents their respective red, green, blue, and alpha channels in a range from 0 to 255. If you want to see what these values look like real time, it's best to use [Google's own color picker](https://www.google.com/search?q=color+picker), which will show you what color you're picking and it's RGB value in the bottom left which you can just stick into grey with 255 for the alpha channel. Also, just to note, alpha controls transparency, AKA how much you can see through the color.

### Default colors
```
// Chromakey
#define COLOR_BLACK (unsigned int [4]){ 0, 0, 0, 255 }
#define COLOR_WHITE (unsigned int [4]){ 255, 255, 255, 255 }
#define COLOR_LIGHT_GREY (unsigned int [4]){ 128, 128, 128, 255 }
#define COLOR_DARK_GREY (unsigned int [4]){ 63, 63, 63, 255 }
#define grey (unsigned int [4]){ 15, 15, 15, 255 }
// Primary
#define COLOR_RED (unsigned int [4]){ 255, 0, 0, 255 }
#define COLOR_GREEN (unsigned int [4]){ 0, 255, 0, 255 }
#define COLOR_BLUE (unsigned int [4]){ 0, 0, 255, 255 }
// Secondary
#define COLOR_YELLOW (unsigned int [4]){ 255, 255, 0, 255 }
#define COLOR_CYAN (unsigned int [4]){ 0, 255, 255, 255 }
#define COLOR_MAGENTA (unsigned int [4]){ 255, 0, 255, 255 }
// Tertiary
#define COLOR_ORANGE (unsigned int [4]){ 255, 128, 0, 255 }
#define COLOR_CHARTREUSE (unsigned int [4]){ 128, 255, 0, 255 }
#define COLOR_SPRING_GREEN (unsigned int [4]){ 0, 255, 128, 255 }
#define COLOR_AZURE (unsigned int [4]){ 0, 128, 255, 255 }
#define COLOR_VIOLET (unsigned int [4]){ 128, 0, 255, 255 }
#define COLOR_ROSE (unsigned int [4]){ 255, 0, 128, 255 }
// Soft Primary
#define COLOR_SOFT_RED (unsigned int [4]){ 255, 50, 50, 255 }
#define COLOR_SOFT_GREEN (unsigned int [4]){ 50, 255, 50, 255 }
#define COLOR_SOFT_BLUE (unsigned int [4]){ 50, 50, 255, 255 }
// Soft Secondary
#define COLOR_SOFT_YELLOW (unsigned int [4]){ 255, 255, 50, 255 }
#define COLOR_SOFT_CYAN (unsigned int [4]){ 50, 255, 255, 255 }
#define COLOR_SOFT_MAGENTA (unsigned int [4]){ 255, 50, 255, 255 }
// Soft Tertiary
#define COLOR_SOFT_ORANGE (unsigned int [4]){ 255, 128, 50, 255 }
#define COLOR_SOFT_CHARTREUSE (unsigned int [4]){ 128, 255, 50, 255 }
#define COLOR_SOFT_SPRING_GREEN (unsigned int [4]){ 50, 255, 128, 255 }
#define COLOR_SOFT_AZURE (unsigned int [4]){ 50, 128, 255, 255 }
#define COLOR_SOFT_VIOLET (unsigned int [4]){ 128, 50, 255, 255 }
#define COLOR_SOFT_ROSE (unsigned int [4]){ 255, 50, 128, 255 }
// Miscellaneous
#define COLOR_DISCORD (unsigned int [4]){ 54, 57, 63, 255 }
#define COLOR_SIMPLE (unsigned int [4]){ 0, 159, 141, 255 }
```
grey already has a lot of default built in colors, all of which can be referenced and used here.

### Switching colors around with setColor()
```
// Function definition
void setColor(Color* oldColor, Color newColor);

// Example, chaing playerColor to blue
setColor(&playerColor, COLOR_BLUE);
```
Changing colors in C/C++ can be very hard. This is because you have to change each 4 values manually, you can't just go: **color1 = color2;** or vice versa. So, we made a cool function called setColor() that takes the memory address of whatever color you want to change for the first parameter and whatever new color you want to change that one to for the second parameter.

## Drawing a background color
```
// Function definition
void clearWindowBackground(Window* win, Color color);
// Example:
clearWindowBackground(&win, COLOR_WHITE);
```
Before anything is drawn in grey, you might want to adjust the background color. On default, every frame, the background is cleared with the color black. If you want to clear it with a different color, you can use the **clearWindowBackground()** function. It takes the memory address of which window you'd like to clear the background of as the first parameter and the color that you'd like to clear the screen with as the second parameter. Reminder that this should be called before anything is drawn in the frame since it draws over anything drawn previously.

## Drawing a rectangle
```
// Function definition
void drawRectangle(Window* win, float x, float y, float width, float height, float rotation, Color color);
// Example
if (player.isVisible()) {
	drawRectangle(&win, player.x, player.y, player.width, player.height, player.rotation, player.color);
}
```
In order to draw a rectangle, you should use the **drawRectangle()** function (defined above). The first parameter is the address of which Window you want to draw the rectangle on. The second and third parameter control the x & y position of the rectangle. Note that grey uses top left to bottom right coordinates, meaning that a rectangle at (0, 0) will draw in the top left of the Window screen. The size of the grid spans the Window's width and height in pixels. The fourth and fifth parameter controls the rectangle's width and height in pixels. The sixth parameter controls the rotation of the rectangle in degrees, rotated around the center of the rectangle. The seventh and final parameter controls the color of the rectangle. All of these put together slaps a nice rectangle on the Window.

## Drawing a circle
```
// Function definition
void drawCircle(Window* win, float x, float y, float radius, Color color);
// Example
if (ball.isActive) {
	drawCircle(&win, ball.x, ball.y, ball.radius, ball.color);
}
```
Drawing a circle is as easy as pi with the **drawCircle()** function. The first parameter takes the memory address of the Window that you want to draw the circle on, the second and third parameter is the x and y of the circle (see "**Drawing a rectangle**" for more information about coordinates), the fourth parameter takes the radius of the circle in pixels, and the fifth and final parameter takes the color of the circle.

## Drawing a triangle
```
// Function definition
void drawTriangle(Window* win, float x1, float y1, float x2, float y2, float x3, float y3, Color color);
// Example
drawTriangle(&win, 0, 100, 50, 0, 100, 100, COLOR_SOFT_ORANGE);
```
Drawing a triangle is a bit special compared to the other shapes. This is because instead of taking an x, y, and some kind of size, **drawTriangle()** instead directly takes three points and connects them like a triangle. The first parameter is the memory address of the Window that you want to draw it in, the second & third are the first x and y coordinates, the fourth and fifth are the second set of coordinates, the sixth and seventh are the third, and the sixth and final parameter specifies the color that the triangle should be drawn with. These three points are then automatically connected and filled in.

## Drawing a rounded rectangle
```
// Function definition
void drawRoundedRect(Window* win, float x, float y, float width, float height, float radius, float rotation, Color color);
// Example
drawRoundedRect(&win, 50, 150, 100, 200, 25, 0, COLOR_SOFT_GREEN);
```
A lot of the time, modern designed aren't simply built with rectangles and circles and other simplistic shapes. Sometimes, they can be a combination, like a rounded rectangle, AKA a rectangle with round edges. Drawing this couldn't be easier with **drawRoundedRect()**. The parameters are a sort of mix-mash with drawRectangle() and drawCircle(), with the first one taking the Window's memory address that you'd like to draw it on, the second and third taking x and y coordinates, the fourth and fifth taking the width and height of the rectangle, the sixth taking the radius of the smooth edges AKA the roundedness of the rectangle, the seventh taking rotation, and the eighth taking the color that it should be drawn with.

## Drawing a line
```
// Function definition
void drawLine(Window* win, float x1, float y1, float x2, float y2, float thickness, Color color);
// Example
if (player1.isAlive() && player2.isAlive()) {
	drawLine(&win, player1.x, player1.y, player2.x, player2.y, 10, COLOR_MAGENTA);
}
```
**drawLine()** simply draws a line between two points with a specified thickness. Parameter one is the Window's memory address that you'd like to draw the line on, parameter two and three are the x and y coordinates of the first point, parameter four and five are the x and y coordinates of the second point, parameter six is the thickness of the line pixel wise, and parameter seven specifies the color of the line.

# Drawing advanced shapes
There are also some advanced draw functions that draw shapes in more specific detail in case you want a feature that the normal draw functions don't contain. Most advanced draw functions are just more specific about colors and points.

## Drawing a polygon
```
// Function definition
void drawPolygon(Window* win, float* xs, float* ys, int points, Color color);
// Example (Draws a pentagon!)
float xs[5] = { 50, 100, 85, 15, 0 };
float ys[5] = { 0, 40, 100, 100, 40 };
drawPolygon(&win, xs, ys, 5, COLOR_SOFT_ORANGE);
```
Unfortunately, we can't make a function for every single shape out there. However, with the **drawPolygon()** function, you can make any shape you'd like! It simply takes a list of coordinate points and connects them automatically, allowing you to make any shape you like. In the demo code above, it actually draws a pentagon which there is currently no function for in grey. The first parameter for this function takes the memory address of the Window you'd like to draw it on, the second and third parameters take a list of x and y coordinates to be connected, the fourth parameter takes the amount of coordinate points that are in each list (not combined, singularly, both lists must have the same length), and the fifth parameter takes the color that the shape should be drawn with.

## Drawing gradients with advanced rectangles
```
// Function definition
void drawAdvancedRect(Window* win, float x, float y, float width, float height, float rotation, Color topLeft, Color topRight, Color bottomLeft, Color bottomRight);
// Example
drawAdvancedRect(&win, 0, 0, win.width, win.height, 0, COLOR_WHITE, COLOR_WHITE, COLOR_BLACK, COLOR_BLACK);
```
With normal shapes, drawing gradients is impossible, but the **drawAdvancedRect()** function gives you control over the color of each point of your rectangle, allowing the easy creation of gradients. The first parameter is the memory address of the Window that you'd like to draw it on, the second and third parameters are the x and y position, the fourth and fifth parameters are the width and height, the sixth parameter controls the rotation, and the seventh through tenth parameters control the color of each edge of the rectangle.

## Drawing gradients with advanced triangles
```
// Function definition
void drawAdvancedTriangle(Window* win, float x1, float y1, float x2, float y2, float x3, float y3, Color color1, Color color2, Color color3);
// Example
drawAdvancedTriangle(&win, 0, 100, 50, 0, 100, 100, COLOR_BLACK, COLOR_WHITE, COLOR_BLACK);
```
If you'd also like to draw a gradient triangle, that can be done with the **drawAdvancedTriangle()** function. The first parameter is the memory address of the Window you'd like to draw it on, the second and third parameter control the x and y position of the first point, the third & fourth and fifth & six parameters control the other x and y positions of the other two points, and the seventh, eighth, and ninth parameters control the colors of each point of the triangle.

## Drawing gradients with advanced lines
```
// Function definition
void drawAdvancedLine(Window* win, float x1, float y1, float x2, float y2, float thickness, Color color1, Color color2);
// Example
if (player1.isAlive && player2.isAlive) {
	drawAdvancedLine(&win, player1.x, player1.y, player2.x player2.y, 10, player1.color, player2.color);
}
```
In case you ever want to draw a line between two points as a gradient as well, the **drawAdvancedLine()** function is for you. The first parameter is the memory address of the window you'd like to draw it in, the second and third parameter specify the x and y coordinates of the first point, the fourth and fifth parameter specify the coordinates for the second point, the sixth parameter controls the thickness of the line, and the seventh and eighth control the color of the two different points which will fade into each other as a gradient along the line.

# Textures
```
// Loads a Garfield texture (called before main loop)
Texture garfield = newTexture(&win, "resources/garfield.png", FILTER_LINEAR);
// Draws the Garfield texture (during the main loop)
drawTexture(&win, garfield, 0, 0, 100, 100, 0, COLOR_WHITE);
// Deletes the Garfield texture (after the main loop)
deleteTexture(&win, garfield);
```
For most game makers, simple shapes won't cut it, so of course, grey has nice and easy support for textures. Above is some sample code showing simple boilerplate for textures, and the sections down below will describe each step in more detail.

## Loading a texture
```
// Function defintion
Texture newTexture(Window* win, const char* path, int filter);
// Example: Loads a Garfield texture (called before main loop)
Texture garfield = newTexture(&win, "resources/garfield.png", FILTER_LINEAR);
```
To load a texture in grey, simply make a Texture object and use the **newTexture()** function to fill in the information. The first parameter simply takes the memory address of the Window that you plan to draw the texture with. The second parameter is the path to the image, and ***this is extremely important***. When compiling the program using Visual Studio, the path of the image starts at the directory of the whole project (where crey.sln is). However, when running the .exe that gets compiled, it uses the path of the .exe itself to find the image. This means that before giving your compiled .exe to other people, you must put the image next to the .exe as it is in the Visual Studio directory. The third, and final parameter, takes the filtering method that will be used to upscale & downscale the image. There are two types of filters, FILTER_NEAREST and FILTER_LINEAR. FILTER_NEAREST will upscale and downscale the image pixel by pixel, which is nice for things like pixel art, but can make high quality images look pixel-y. FILTER_LINEAR will upscale and downscale the image by trying to smooth everything out, averaging the neighboring pixels to a value, which is nice for high quality images, but can make things like pixel art look blurry. If this description wasn't enough, LearnOpenGL shows the difference between the two nicely in [this image.](https://learnopengl.com/img/getting-started/texture_filtering.png)

## Drawing a texture
```
// Function definition
void drawTexture(Window* win, Texture texture, float x, float y, float width, float height, float rotation, Color color);
// Example: Draws the Garfield texture (during the main loop)
drawTexture(&win, garfield, 0, 0, 100, 100, 0, COLOR_WHITE);
```
After loading a texture, drawing it couldn't be easier with **drawTexture()**. It works very similarly to drawRectangle(), taking almost the same parameters. The first parameter is the memory address of the Window that you'd like to draw the texture in. Reminder that this must be the same Window that you loaded it with! The second parameter is the texture that you'd like to draw. The third and forth parameter control the x and y coordinates that the texture will draw at. The fifth and sixth parameter control the width and height of the texture. The seventh parameter controls the rotation of the texture. The eighth, and final parameter, controls the color of the texture. Note that this feature works best with greyscale images, and if you'd like to leave the texture's color unmodified, simply use COLOR_WHITE.

## Deleting a texture
```
// Function definition
void deleteTexture(Window* win, Texture texture);
// Example: Deletes the Garfield texture (after the main loop)
deleteTexture(&win, garfield);
```
Deleting a texture is done by using the **deleteTexture()** function. Note that this doesn't *need* to be done since most operating systems automatically free image data at the end of the program, but it's useful if you plan to load or deload textures at certain intervals, like many large scale games with many assets may do. Just be careful since deleting a texture and drawing it will lead to messy results. The first parameter is the memory address of the Window that the texture was loaded in. The second, and final parameter, is the texture that you'd like to delete.

# Fonts
```
// Loading font 'Arial' (before main loop)
FontID arial = loadFont(&win, "resources/arial.ttf", 50);
// Drawing text with Arial (during main loop)
drawText(&win, "Hello text!", arial, 0, 0, 50, COLOR_WHITE);
// Deleting font (after main loop)
deleteFont(&win, arial);
```
Drawing fonts & text is, of course, essential to most apps, so grey has nice and easy support for it. Above is some sample code that goes through the whole process of using a font. More detail on what each step does is listed below.

## Loading a font
```
// Function definition
FontID loadFont(Window* win, const char* filePath, float size);
// Example: Loading font 'Arial' (before main loop)
FontID arial = loadFont(&win, "resources/arial.ttf", 50);
```
Loading a font is done in grey with the **loadFont()** function. Simply make a FontID object and assign it a value with loadFont(). The first parameter is the memory address of the Window that you plan to use the font with. The second parameter is the file path to the font. Be aware that it follows the same rules as texture loading, so read the "**Loading a texture**" chapter before this! The third parameter controls the size of the font, in pixels, that you plan to render it in. Drawing over this size can lead to blurriness so be aware!

## Drawing a font / Drawing text
```
// Function definition
void drawText(Window* win, const char* text, FontID font, float x, float y, float scale, Color color);
// Example: Drawing text with Arial (during main loop)
drawText(&win, "Hello text!", arial, 0, 0, 50, COLOR_WHITE);
```
Drawing text with a font in grey is achieved using the **drawText()** function. The first parameter is the memory address of the Window that you'd like to draw the text on. Be aware that this must be the same Window that you loaded it in with. The second parameter is the text that you'd like to render. The third parameter is the font that you'd like to render the text with. The fourth and fifth parameter control the x and y of the text, starting at the top left of the first letter. The sixth parameter controls the size of the text in pixels. It's recommended to put the same (or less) size that you loaded the font with originally. The seventh and final parameter controls the color of the text.

## Deleting a font
```
// Function definition
void deleteFont(Window* win, FontID font);
// Example: Deleting font (after main loop)
deleteFont(&win, arial);
```
Deleting a font is very simple with the **deleteFont()** function. The first parameter is the memory address of the Window that the font was loaded with. The second and final parameter is the font that you'd like to delete.

## Width & height of text
```
// Function definitions
float getWidthOfText(Window* win, const char* text, FontID font, float scale);
float getHeightOfText(Window* win, const char* text, FontID font, float scale);
```
The width and height of text, when rendered, can be inconsistent. The size of certain letters can be different than one another, and the size differences can vary between fonts, so the two functions **getWidthOfText()** and **getHeightOfText()** handle it for you. You can simply pass in similar arguments to the normal drawText() function and get the result of the total width and height of the text. The parameters are the same for both functions. The first parameter is the Window that the font was loaded into with. The second parameter is the text that you plan to render. The third parameter is the font. The fourth and final parameter is the size, in pixels, that you plan to render the text with. Both of these functions return, as a float, the width or height, in pixels, of the text you plan to render.
