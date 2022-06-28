# [rey](https://rey-modules.ml)
A collection of code in C, designed to make game development as easy as possible. We currently have native C and C++ support.

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
