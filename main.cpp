#include <grey/grey.h>

int main() {
	initGrey(8);

	

	Window win = createWindow(1280, 720, "simple shapes");

	

	
	while (!shouldWindowClose(win)) {
		updateWindow(&win);
		
		clearWindowBackground(&win, COLOR_DARK_GREY);

		

		
		renderWindow(win);
	}
	deleteWindow(&win);
	closeGrey();
}