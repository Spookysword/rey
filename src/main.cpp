// #include <grey/grey.h>
// #include <grey/menu.hpp>

// int main() {
//     initGrey(4);

//     Window win = createWindow(1280, 720, "grey");
//     FontID arial = loadFont(&win, "resources/arial.ttf", 100);

//     // TEXT ENTRY VARS \/

//     float paddingy = 20.0f;

//     float x = 50, y = 50, width= 500, height = getHeightOfText(&win, "|", arial, 50)+paddingy;

//     float bordersize = 10.0f;

//     bool focused = false;
//     char text[256] = "";
//     unsigned int cursor_pos = 0;
//     int text_size = 0;
//     bool insertmode = false;

//     bool text_cursor_visible = true;
//     double text_cursor_timer = 0;
//     float text_cursor_blink_rate = 0.5; // in seconds
//     bool text_cursor_blink_state = true;
//     Color centerColor = Color { 180, 180, 180, 255 };
//     Color borderColor = Color { 20, 20, 20, 255 };
//     Color cursorColor = Color { 200, 200, 200, 255 };
//     Color textColor = Color { 255, 255, 255, 255 };


//     // TEXT ENTRY VARS /\

//     while (!shouldWindowClose(win)) {
//         updateWindow(&win);

//         if (isKeyPressed(win, KEY_F11)) {
//             win.fullscreen = !win.fullscreen;
//         }

//         clearWindowBackground(&win, COLOR_DARK_GREY);

//         // TEXT ENTRY RENDER/UPDATE \/

//         text_cursor_timer += win.deltaTime;
//         if (text_cursor_timer >= text_cursor_blink_rate) {
//             text_cursor_timer = 0;
//             text_cursor_blink_state = !text_cursor_blink_state;
//         }
//         if (win.mouse.x > x && win.mouse.x < x + width && win.mouse.y > y && win.mouse.y < y + height && win.mouse.isPrimaryPressed) {
//             focused = true;
//             text_cursor_timer = 0;
//             text_cursor_blink_state = true;

//         } else if (win.mouse.isPrimaryPressed) {
//             focused = false;
//         }
//         if (focused) {
            
//             if (isKeyPressed(win, KEY_LEFT)) {
//                 text_cursor_timer = 0;
//                 text_cursor_blink_state = true;
//                 if (cursor_pos > 0) {
//                     cursor_pos--;
//                 }
//             }
//             if (isKeyPressed(win, KEY_RIGHT)) {
//                 text_cursor_timer = 0;
//                 text_cursor_blink_state = true;
//                 if (cursor_pos < text_size) {
//                     cursor_pos++;
//                 }
//             }
//             if (isKeyPressed(win, KEY_INSERT)) {
//                 text_cursor_timer = 0;
//                 text_cursor_blink_state = true;
//                 insertmode = !insertmode;
//             }

//             if (isKeyPressed(win, KEY_BACKSPACE)) {
//                 text_cursor_timer = 0;
//                 text_cursor_blink_state = true;
//                 if (cursor_pos > 0) {
//                     cursor_pos--;
//                     for (int i = cursor_pos; i < text_size; i++) {
//                         text[i] = text[i + 1];
//                     }
//                     text_size--;
//                 }
//             }

//             if (isKeyPressed(win, KEY_V) && (isKeyDown(win,KEY_LEFT_CONTROL) || isKeyDown(win,KEY_RIGHT_CONTROL))) {
//                 text_cursor_timer = 0;
//                 text_cursor_blink_state = true;
//                 char* clipboard = (char*)getClipboardText(&win);
//                 if (clipboard != NULL) {
//                     for (int i = 0; i < strlen(clipboard); i++) {
//                         text[text_size] = clipboard[i];
//                         text_size++;
//                         cursor_pos++;
//                     }
//                 }
//             }

//             #define _ADDCHAR_NORMAL(a) char temp1[255]="";for(int i=cursor_pos;i<256;i++){temp1[i-cursor_pos]=text[i];}text[cursor_pos]=a;for(int i=0;i<256-cursor_pos-1;i++){text[1+i+cursor_pos]=temp1[i];}
//             #define _ADDCHAR_INSERT(a) text[cursor_pos]=a
//             #define _ADDCHAR(a) if (insertmode) {_ADDCHAR_INSERT(a);} else {_ADDCHAR_NORMAL(a);}
//             #define _MAKEKEY(upc, loc, k) if(isKeyPressed(win,k) && !isKeyDown(win,KEY_LEFT_CONTROL)&& !isKeyDown(win,KEY_RIGHT_CONTROL)){if(isKeyDown(win,KEY_LEFT_SHIFT)||isKeyDown(win,KEY_RIGHT_SHIFT)){_ADDCHAR(upc);}else {_ADDCHAR(loc);}cursor_pos++;text_size++;text_cursor_timer=0;text_cursor_blink_state=true;}
//             _MAKEKEY('A', 'a', KEY_A);_MAKEKEY('B', 'b', KEY_B);_MAKEKEY('C', 'c', KEY_C);_MAKEKEY('D', 'd', KEY_D);
//             _MAKEKEY('E', 'e', KEY_E);_MAKEKEY('F', 'f', KEY_F);_MAKEKEY('G', 'g', KEY_G);_MAKEKEY('H', 'h', KEY_H);
//             _MAKEKEY('I', 'i', KEY_I);_MAKEKEY('J', 'j', KEY_J);_MAKEKEY('K', 'k', KEY_K);_MAKEKEY('L', 'l', KEY_L);
//             _MAKEKEY('M', 'm', KEY_M);_MAKEKEY('N', 'n', KEY_N);_MAKEKEY('O', 'o', KEY_O);_MAKEKEY('P', 'p', KEY_P);
//             _MAKEKEY('Q', 'q', KEY_Q);_MAKEKEY('R', 'r', KEY_R);_MAKEKEY('S', 's', KEY_S);_MAKEKEY('T', 't', KEY_T);
//             _MAKEKEY('U', 'u', KEY_U);_MAKEKEY('V', 'v', KEY_V);_MAKEKEY('W', 'w', KEY_W);_MAKEKEY('X', 'x', KEY_X);
//             _MAKEKEY('Y', 'y', KEY_Y);_MAKEKEY('Z', 'z', KEY_Z);_MAKEKEY(')', '0', KEY_0);_MAKEKEY('!', '1', KEY_1);
//             _MAKEKEY('@', '2', KEY_2);_MAKEKEY('#', '3', KEY_3);_MAKEKEY('$', '4', KEY_4);_MAKEKEY('%', '5', KEY_5);
//             _MAKEKEY('^', '6', KEY_6);_MAKEKEY('&', '7', KEY_7);_MAKEKEY('*', '8', KEY_8);_MAKEKEY('(', '9', KEY_9);
//             _MAKEKEY(' ', ' ', KEY_SPACE);_MAKEKEY('>', '.', KEY_PERIOD);_MAKEKEY('<', ',', KEY_COMMA);_MAKEKEY('_', '-', KEY_MINUS);
//             _MAKEKEY('+', '=', KEY_EQUAL);_MAKEKEY('{', '[', KEY_LEFT_BRACKET);_MAKEKEY('}', ']', KEY_RIGHT_BRACKET);_MAKEKEY('|', '\\', KEY_BACKSLASH);
//             _MAKEKEY('"', '\'', KEY_APOSTROPHE);_MAKEKEY(':', ';', KEY_SEMICOLON);_MAKEKEY('?', '/', KEY_SLASH);_MAKEKEY('~', '`', KEY_GRAVE_ACCENT);

//         }
//         char text2[256] = "";
//         int offset = 0;
//         int amount = text_size;
//         bool overflowleft = false;
//         bool overflowright = false;
//         for (int i = 0; i < cursor_pos; i++) {
//             text2[i] = text[i];
//         }
//         if (getWidthOfText(&win, text2, arial, 50)+bordersize > width-bordersize) {
//             overflowleft = true;
//             if (cursor_pos < text_size) { 
//                 overflowright = true;
//             }
//             while (getWidthOfText(&win, text2, arial, 50)+bordersize > width-bordersize) {
//                 memmove(text2, text2+1, strlen(text2));
//                 offset += 1;
//             }
//         } else if (getWidthOfText(&win, text, arial, 50)+bordersize > width-bordersize) {
//             overflowright = true;
//             for (int i = 0; i < text_size; i++) {
//                 text2[i] = text[i];
//             }

//             while (getWidthOfText(&win, text2, arial, 50)+bordersize > width-bordersize) {
//                 text2[amount-1] = 0;
//                 amount--;
//             }

//         } else {
//             for (int i = 0; i < text_size; i++) {
//                 text2[i] = text[i];
//             }
//         }

//         if (win.mouse.isPrimaryPressed && focused) {
//             char temparr[256] = "";
//             int awayfrom = 9999;
//             if (win.mouse.x >= (x+getWidthOfText(&win, text2, arial, 50))) {
//                 cursor_pos = strlen(text2)+offset;
//                 awayfrom = -1;
//             }
//             for (int i = 0; i < strlen(text2); i++) {
//                 temparr[i] = text2[i];
//                 int af = abs(win.mouse.x-(x+getWidthOfText(&win, temparr, arial, 50)-getWidthOfChar(&win, temparr[i], arial, 50)/2));
//                 if (awayfrom >= af) {
//                     awayfrom = af;
//                     cursor_pos = i+offset;
//                 } else {
//                     break;
//                 }
//             }
//         }


//         drawRectangle(&win, x, y, width, height, 0, borderColor);
//         drawRectangle(&win, x+bordersize/2, y+bordersize/2, width-bordersize, height-bordersize, 0, centerColor);
//         if (overflowleft) {
//             drawRectangle(&win, x, y+bordersize/2, bordersize/2, height-bordersize, 0, centerColor);
//         }
//         if (overflowright) {
//             drawRectangle(&win, x+width-bordersize/2, y+bordersize/2, bordersize/2, height-bordersize, 0, centerColor);
//         }
//         drawText(&win, text2, arial, x+bordersize, y, 50, textColor);
//         if (text_cursor_visible && focused && text_cursor_blink_state) {
//             char temp[256] = "";
//             for (int i = 0; i < cursor_pos-offset; i++) {
//                 if (!text2[i]) continue;
//                 temp[i] += text2[i];
//             }
//             if (!insertmode) {
//                 drawRectangle(&win, x+bordersize+getWidthOfText(&win, temp, arial, 50)-2.5, y+paddingy/4, 5, height-paddingy/2, 0, cursorColor);
//             } else {
//                 drawRectangle(&win, x+bordersize+getWidthOfText(&win, temp, arial, 50)-2.5, y+paddingy/4, 5+getWidthOfChar(&win, text2[cursor_pos], arial, 50), height-paddingy/2, 0, cursorColor);
//             }
//         }



//         // TEXT ENTRY RENDER/UPDATE /\


//         renderWindow(win);
//     }
    
//     deleteFont(&win, arial);
//     deleteWindow(&win);
//     closeGrey();
// }

#include <grey/grey.h>

#define VERT(a, b, c) Vertice_create(v##a, COLOR_WHITE, vt##b, vn0)

int main() {
	initGrey(0);

	Window win = createWindow(1280, 720, "grey");
	float sensitivity = 50.0f;
	Texture aggg = new3DTexture(&win, "resources/white.png", FILTER_LINEAR);
	float speed = 0.01f;
    bool locked = false;

	while (!shouldWindowClose(win)) {
		updateWindow(&win);

		if (isKeyDown(win, KEY_W)) {
			win.camera = Camera_move(win.camera, win.camera.forward, speed);
		}
		if (isKeyDown(win, KEY_S)) {
			win.camera = Camera_move(win.camera, win.camera.forward, -speed);
		}
		if (isKeyDown(win, KEY_A)) {
			win.camera = Camera_move(win.camera, Camera_left(win.camera), speed);
		}
		if (isKeyDown(win, KEY_D)) {
			win.camera = Camera_move(win.camera, Camera_right(win.camera), speed);
		}
		if (isKeyDown(win, KEY_SPACE)) {
			win.camera = Camera_move(win.camera, win.camera.up, speed);
		}
		if (isKeyDown(win, KEY_LEFT_SHIFT)) {
			win.camera = Camera_move(win.camera, win.camera.up, -speed);
		}

		if (isKeyPressed(win, KEY_ESCAPE)) {
			setMouseLocked(&win, FALSE);
            locked = false;
		}
		if (win.mouse.isPrimaryPressed) {
			setMousePos(&win, win.width / 2, win.height / 2);
			setMouseLocked(&win, TRUE);
            locked = true;
		}
        if (locked) {
            double dx = win.mouse.x - win.width / 2;
            double dy = win.mouse.y - win.height / 2;

            bool rotY = dx != 0;
            bool rotX = dy != 0;

            if (rotY) {
                win.camera = Camera_rotateY(win.camera, dx * sensitivity/win.width);
            }
            if (rotX) {
                win.camera = Camera_rotateX(win.camera, dy * sensitivity/win.height);
            }
            if (rotX || rotY) 
                setMousePos(&win, win.width / 2, win.height / 2);
        }

		win.transform.camera = win.camera;

		Vec3 v1 = Vec3_new( 1.00f, -1.00f, -1.00f);
		Vec3 v2 = Vec3_new( 1.00f, -1.00f,  1.00f);
		Vec3 v3 = Vec3_new(-1.00f, -1.00f,  1.00f);
		Vec3 v4 = Vec3_new(-1.00f, -1.00f, -1.00f);
		Vec3 v5 = Vec3_new( 1.00f,  1.00f, -0.99f);
		Vec3 v6 = Vec3_new( 0.99f,  1.00f,  1.01f);
		Vec3 v7 = Vec3_new(-1.00f,  1.00f,  1.00f);
		Vec3 v8 = Vec3_new(-1.00f,  1.00f, -1.00f);
		//14
		Vec2 vt1 = Vec2_new(1.000000f, 0.333333);
		Vec2 vt2 = Vec2_new(1.000000f, 0.666667);
		Vec2 vt3 = Vec2_new(0.666667f, 0.666667);
		Vec2 vt4 = Vec2_new(0.666667f, 0.333333);
		Vec2 vt5 = Vec2_new(0.666667f, 0.000000);
		Vec2 vt6 = Vec2_new(0.000000f, 0.333333);
		Vec2 vt7 = Vec2_new(0.000000f, 0.000000);
		Vec2 vt8 = Vec2_new(0.333333f, 0.000000);
		Vec2 vt9 = Vec2_new(0.333333f, 1.000000);
		Vec2 vt10 = Vec2_new(0.000000f, 1.000000);
		Vec2 vt11 = Vec2_new(0.000000f, 0.666667);
		Vec2 vt12 = Vec2_new(0.333333f, 0.333333);
		Vec2 vt13 = Vec2_new(0.333333f, 0.666667);
		Vec2 vt14 = Vec2_new(1.000000f, 0.000000);


		Vec3 vn0 = Vec3_new(0.0, 0.0, 0.0);

		Vertices verts;
		verts.size = 12*3;


		verts.vertices = new Vertice[12*3] {
			VERT(2,1,1), VERT(3,2,1), VERT(4,3,1),
			VERT(8,1,2), VERT(7,4,2), VERT(6,5,2),
			VERT(5,6,3), VERT(6,7,3), VERT(2,8,3),
			VERT(6,8,4), VERT(7,5,4), VERT(3,4,4),
			VERT(3,9,5), VERT(7,10,5), VERT(8,11,5),
			VERT(1,12,6), VERT(4,13,6), VERT(8,11,6),
			VERT(1,4,1), VERT(2,1,1), VERT(4,3,1),
			VERT(5,14,2), VERT(8,1,2), VERT(6,5,2),
			VERT(1,12,3), VERT(5,6,3), VERT(2,8,3),
			VERT(2,12,4), VERT(6,8,4), VERT(3,4,4),
			VERT(4,13,5), VERT(3,9,5), VERT(8,11,5),
			VERT(5,6,6), VERT(1,12,6), VERT(8,11,6)
		};

		draw3DShape(&win, aggg, verts);
		renderWindow(win);
	}

	deleteWindow(&win);
	closeGrey();
}