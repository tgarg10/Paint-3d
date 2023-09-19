#include <iostream>
#include <cmath>
#include <vector>
#include <SDL.h>
#undef main

using namespace std;

SDL_Window* window = nullptr;
Uint32 windowFlags = SDL_WINDOW_RESIZABLE;
SDL_Renderer* render = nullptr;
SDL_Surface* surface = nullptr;

int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 720;

int strokeSize = 5;

int taskbarHeight = SCREEN_HEIGHT * 0.11;
int footbarHeight = SCREEN_HEIGHT * 0.05;

Uint8 backgroundColor_R = 253;
Uint8 backgroundColor_G = 236;
Uint8 backgroundColor_B = 166;
Uint8 backgroundColor_A = 255;

Uint8 selectedColor_R = 0;
Uint8 selectedColor_G = 0;
Uint8 selectedColor_B = 0;
Uint8 selectedColor_A = 255;
Uint32 selectedColor;

SDL_Surface* getPixel_Surface = nullptr;
Uint8 getPixel_bpp = 0;

vector<vector<int>> fillZoneList;

bool start() {
	bool error = false;
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Paint 98",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		windowFlags);

	if (window == NULL) {
		cout << "Window Error: " << SDL_GetError();
		error = true;
	}

	return error;
}

void setColor(Uint8 colorR = 0, Uint8 colorG = 0, Uint8 colorB = 0, Uint8 colorA = 255) {
	selectedColor_R = colorR;
	selectedColor_G = colorG;
	selectedColor_B = colorB;
	selectedColor_A = colorA;
}

class Button {
private:
	SDL_Rect buttonRect;
	int x, y, w, h;
	Uint8 color_R, color_G, color_B, color_A;
public:
	void outlineBox() {
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		buttonRect.x = x;
		buttonRect.y = y;
		buttonRect.w = w;
		buttonRect.h = h;
		SDL_RenderDrawRect(render, &buttonRect);
	}

	Button(int _x, int _y, int _w, int _h) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		outlineBox();
	}

	void displayColor(Uint8 _color_R = 0, Uint8 _color_G = 0, Uint8 _color_B = 0, Uint8 _color_A = 255) {
		SDL_SetRenderDrawColor(render, _color_R, _color_G, _color_B, _color_A);
		SDL_Rect colorRect;
		colorRect.x = x;
		colorRect.y = y;
		colorRect.w = w;
		colorRect.h = h;
		color_R = _color_R;
		color_G = _color_G;
		color_B = _color_B;
		color_A = _color_A;
		SDL_RenderFillRect(render, &colorRect);
		outlineBox();
	}

	void displayImage(string imagePath) {
		/*
		SDL_Surface* taskbarSurface = nullptr;
		SDL_Surface* backgroundImage = nullptr;
		surface = SDL_GetWindowSurface(window);
		backgroundImage = SDL_LoadBMP("D:\\cpp\\Projects\\Brain_Password\\Image\\background.bmp");
		SDL_BlitSurface(backgroundImage, NULL, taskbarSurface, NULL);
		SDL_FreeSurface(backgroundImage); // cleaning up memory
		backgroundImage = nullptr;
		SDL_UpdateWindowSurface(window);
		*/
	}

	void handle_events(int mouseX, int mouseY) {
		if (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h) {
			setColor(color_R, color_G, color_B, color_A);
		}
	}
};

Button RedColorButton(SCREEN_WIDTH * 0.7, SCREEN_HEIGHT * 0.02, 20, 20);
Button OrangeColorButton(SCREEN_WIDTH * 0.7 + 30, SCREEN_HEIGHT * 0.02, 20, 20);
Button GreenColorButton(SCREEN_WIDTH * 0.7 + 60, SCREEN_HEIGHT * 0.02, 20, 20);
Button AquaColorButton(SCREEN_WIDTH * 0.7 + 90, SCREEN_HEIGHT * 0.02, 20, 20);
Button BlueColorButton(SCREEN_WIDTH * 0.7 + 120, SCREEN_HEIGHT * 0.02, 20, 20);
Button PinkColorButton(SCREEN_WIDTH * 0.7 + 150, SCREEN_HEIGHT * 0.02, 20, 20);
Button YellowColorButton(SCREEN_WIDTH * 0.7 + 180, SCREEN_HEIGHT * 0.02, 20, 20);
Button BrownColorButton(SCREEN_WIDTH * 0.7 + 210, SCREEN_HEIGHT * 0.02, 20, 20);
Button WhiteColorButton(SCREEN_WIDTH * 0.7 + 240, SCREEN_HEIGHT * 0.02, 20, 20);
Button BlackColorButton(SCREEN_WIDTH * 0.7 + 270, SCREEN_HEIGHT * 0.02, 20, 20);
Button ImageButton(SCREEN_WIDTH * 0.4, SCREEN_HEIGHT * 0.02, 20, 20);

void displayTaskbar() {
	/* Fill Rectangle */
	SDL_SetRenderDrawColor(render, 185, 122, 86, 255);
	SDL_Rect backgroundRect;
	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.w = SCREEN_WIDTH;
	backgroundRect.h = taskbarHeight;
	SDL_RenderFillRect(render, &backgroundRect);

	/* Outline Rectangle */
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_Rect outlineRect;
	outlineRect.x = 0;
	outlineRect.y = 0;
	outlineRect.w = SCREEN_WIDTH;
	outlineRect.h = taskbarHeight;
	SDL_RenderDrawRect(render, &outlineRect);

	RedColorButton.displayColor(236, 28, 36, 255);
	OrangeColorButton.displayColor(255, 127, 39, 255);
	GreenColorButton.displayColor(27, 155, 63, 255);
	AquaColorButton.displayColor(140, 255, 251, 255);
	BlueColorButton.displayColor(63, 72, 204, 255);
	PinkColorButton.displayColor(255, 174, 200, 255);
	YellowColorButton.displayColor(255, 242, 0, 255);
	BrownColorButton.displayColor(185, 122, 86, 255);
	WhiteColorButton.displayColor(255, 255, 255, 255);
	BlackColorButton.displayColor(0, 0, 0, 255);
	ImageButton.displayImage("");

	SDL_RenderPresent(render);
}

void displayFootbar() {
	SDL_SetRenderDrawColor(render, 172, 172, 172, 255);
	SDL_Rect backgroundRect;
	backgroundRect.x = 0;
	backgroundRect.y = SCREEN_HEIGHT - footbarHeight;
	backgroundRect.w = SCREEN_WIDTH;
	backgroundRect.h = footbarHeight;
	SDL_RenderFillRect(render, &backgroundRect);
	SDL_RenderPresent(render);
}

void clearBackground(int bgColor_R = backgroundColor_R, int bgColor_G = backgroundColor_G, int bgColor_B = backgroundColor_B, int bgColor_A = backgroundColor_A) {
	SDL_SetRenderDrawColor(render, bgColor_R, bgColor_G, bgColor_B, bgColor_A);
	SDL_Rect backgroundRect;
	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.w = SCREEN_WIDTH;
	backgroundRect.h = SCREEN_HEIGHT;
	SDL_RenderFillRect(render, &backgroundRect);
	SDL_RenderPresent(render);
	displayTaskbar();
	displayFootbar();
}

bool checkForBar(int y) {
	if (y > taskbarHeight && y < SCREEN_HEIGHT - footbarHeight) {
		return true;
	}
	return false;
}

void drawPoint(int _x, int _y, int _size = strokeSize) {
	if (checkForBar(_y)) {
		SDL_SetRenderDrawColor(render, selectedColor_R, selectedColor_G, selectedColor_B, selectedColor_A);
		SDL_Rect pointRect;
		pointRect.x = _x - _size / 2;
		pointRect.y = _y - _size / 2;
		pointRect.w = _size;
		pointRect.h = _size;
		SDL_RenderFillRect(render, &pointRect);
		SDL_RenderPresent(render);
		displayTaskbar();
		displayFootbar();
	}
}

void drawRectangle(int _x1, int _y1, int _x2 = 0, int _y2 = 0) {
	if (checkForBar(_y1) && checkForBar(_y2)) {
		SDL_SetRenderDrawColor(render, selectedColor_R, selectedColor_G, selectedColor_B, selectedColor_A);
		SDL_Rect pointRect;
		pointRect.x = _x1;
		pointRect.y = _y1;
		pointRect.w = _x2 - _x1;
		pointRect.h = _y2 - _y1;
		SDL_RenderDrawRect(render, &pointRect);
		SDL_RenderPresent(render);
	}
}

void drawTriangle(int _x1, int _y1, int _x2 = 0, int _y2 = 0) {
	if (checkForBar(_y1) && checkForBar(_y2)) {
		SDL_SetRenderDrawColor(render, selectedColor_R, selectedColor_G, selectedColor_B, selectedColor_A);
		int base_X1 = _x1;
		int base_Y1 = _y2;
		int base_X2 = _x2;
		int base_Y2 = _y2;

		int tip_X = (_x1 + _x2) / 2;
		int tip_Y = _y1;

		SDL_RenderDrawLine(render, base_X1, base_Y1, base_X2, base_Y2);
		SDL_RenderDrawLine(render, tip_X, tip_Y, base_X1, base_Y1);
		SDL_RenderDrawLine(render, tip_X, tip_Y, base_X2, base_Y2);
		SDL_RenderPresent(render);
	}
}

void drawCircle(int _x1, int _y1, int _x2 = 0, int _y2 = 0) {
	if (checkForBar(_y1) && checkForBar(_y2)) {
		SDL_SetRenderDrawColor(render, selectedColor_R, selectedColor_G, selectedColor_B, selectedColor_A);

		int center_X = (_x1 + _x2) / 2;
		int center_Y = (_y1 + _y2) / 2;
		
		int pixelX1, pixelX2, pixelY1, pixelY2;

		if (_x1 < _x2) {
			pixelX1 = _x1;
			pixelX2 = _x2;
		}
		else {
			pixelX1 = _x2;
			pixelX2 = _x1;
		}

		if (_y1 < _y2) {
			pixelY1 = _y1;
			pixelY2 = _y2;
		}
		else {
			pixelY1 = _y2;
			pixelY2 = _y1;
		}

		int interceptAsqr = pow(pixelX2 - center_X, 2);
		int interceptBsqr = pow(pixelY2 - center_Y, 2);

		while (pixelX1 <= pixelX2) {
			int oldPixelY = pixelY1;
			while (pixelY1 <= pixelY2) {
				double eqnVal = pow(pixelX1 - center_X, 2) / interceptAsqr + pow(pixelY1 - center_Y, 2) / interceptBsqr;
				if (eqnVal > 0.93 && eqnVal < 0.97) { // ellipse equation
					SDL_RenderDrawPoint(render, pixelX1, pixelY1);
				}
				/* Circle Only
				if ((pixelX2 - centerX) > (pixelY2 - centerY))
					radius = (pixelY2 - centerY);
				else 
					radius = (pixelX2 - centerX);
				int centerDist = round(sqrt(pow((pixelX1 - center_X), 2) + pow((pixelY1 - center_Y), 2)));
				if (radius == centerDist || radius == centerDist + 1) {
					SDL_RenderDrawPoint(render, pixelX1, pixelY1);
				}
				*/
				pixelY1 += 1;
			}
			pixelY1 = oldPixelY;
			pixelX1 += 1;
		}

		SDL_RenderPresent(render);
	}
}

SDL_Color getPixelColor(int pixel_X, int pixel_Y) {
	SDL_Color pixelColor;

	Uint8* pPixel = (Uint8*)getPixel_Surface->pixels + pixel_Y * getPixel_Surface->pitch + pixel_X * getPixel_bpp;

	Uint32 pixelData;

	switch (getPixel_bpp) {
	case 1:
		pixelData = *pPixel;
		break;
	case 2:
		pixelData = *(Uint16*)pPixel;
		break;
	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			pixelData = pPixel[0] << 16 | pPixel[1] << 8 | pPixel[2];
		else
			pixelData = pPixel[0]| pPixel[1] << 8 | pPixel[2] << 16;
		break;
	case 4:
		pixelData = *(Uint32*)pPixel;
		break;
	}

	SDL_GetRGBA(pixelData, getPixel_Surface->format, &pixelColor.r, &pixelColor.g, &pixelColor.b, &pixelColor.a);
	
	return pixelColor;
}

void pixelSpread(int pixelX, int pixelY, Uint8 initialColor_R, Uint8 initialColor_G, Uint8 initialColor_B, Uint8 initialColor_A) {
	SDL_Color abovePixel, belowPixel, leftPixel, rightPixel;
	SDL_Rect drawPointRect;
	drawPointRect.w = 1; 
	drawPointRect.h = 1;
	SDL_RenderDrawPoint(render, pixelX, pixelY);

	vector<int> pixelCoords;

	abovePixel = getPixelColor(pixelX, pixelY + 1);
	belowPixel = getPixelColor(pixelX, pixelY - 1);
	leftPixel = getPixelColor(pixelX - 1, pixelY);
	rightPixel = getPixelColor(pixelX + 1, pixelY);

	if (initialColor_R == abovePixel.r && initialColor_G == abovePixel.g && initialColor_B == abovePixel.b && initialColor_A == abovePixel.a && pixelY > taskbarHeight && pixelY < SCREEN_HEIGHT - footbarHeight) {
		pixelCoords = { pixelX, pixelY + 1};
		drawPointRect.x = pixelX;
		drawPointRect.y = pixelY + 1;
		SDL_FillRect(getPixel_Surface, &drawPointRect, selectedColor);
		fillZoneList.push_back(pixelCoords);
	}
	if (initialColor_R == belowPixel.r && initialColor_G == belowPixel.g && initialColor_B == belowPixel.b && initialColor_A == belowPixel.a && pixelY > taskbarHeight && pixelY < SCREEN_HEIGHT - footbarHeight) {
		pixelCoords = { pixelX, pixelY - 1 };
		drawPointRect.x = pixelX;
		drawPointRect.y = pixelY - 1;
		SDL_FillRect(getPixel_Surface, &drawPointRect, selectedColor);
		fillZoneList.push_back(pixelCoords);
	}
	if (initialColor_R == leftPixel.r && initialColor_G == leftPixel.g && initialColor_B == leftPixel.b && initialColor_A == leftPixel.a && pixelX > 0 && pixelX < SCREEN_WIDTH && pixelY > taskbarHeight && pixelY < SCREEN_HEIGHT - footbarHeight) {
		pixelCoords = { pixelX - 1, pixelY};
		drawPointRect.x = pixelX - 1;
		drawPointRect.y = pixelY;
		SDL_FillRect(getPixel_Surface, &drawPointRect, selectedColor);
		fillZoneList.push_back(pixelCoords);
	}
	if (initialColor_R == rightPixel.r && initialColor_G == rightPixel.g && initialColor_B == rightPixel.b && initialColor_A == rightPixel.a && pixelX > 0 && pixelX < SCREEN_WIDTH && pixelY > taskbarHeight && pixelY < SCREEN_HEIGHT - footbarHeight) {
		pixelCoords = { pixelX + 1, pixelY };
		drawPointRect.x = pixelX + 1;
		drawPointRect.y = pixelY;
		SDL_FillRect(getPixel_Surface, &drawPointRect, selectedColor);
		fillZoneList.push_back(pixelCoords);
	}
	SDL_UpdateWindowSurface(window);
}

void fillCanvas(int _x, int _y, int fillColor_R, int fillColor_G, int fillColor_B, int fillColor_A) {
	getPixel_Surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(render, NULL, SDL_PIXELFORMAT_ARGB8888, getPixel_Surface->pixels, getPixel_Surface->pitch);

	getPixel_bpp = getPixel_Surface->format->BytesPerPixel;

	selectedColor = SDL_MapRGBA(getPixel_Surface->format, selectedColor_R, selectedColor_G, selectedColor_B, selectedColor_A);
	SDL_SetRenderDrawColor(render, fillColor_R, fillColor_G, fillColor_B, fillColor_A);

	SDL_Color initialPixel = getPixelColor(_x, _y);
	if (!checkForBar(_y) && initialPixel.r != fillColor_R || initialPixel.g != fillColor_G || initialPixel.b != fillColor_B || initialPixel.a != fillColor_A) {
		fillZoneList.empty();
		vector<int> initialPixelCoords = { _x, _y };

		SDL_Rect drawPointRect;
		drawPointRect.w = 1;
		drawPointRect.h = 1;
		drawPointRect.x = _x;
		drawPointRect.y = _y;
		
		SDL_UpdateWindowSurface(window);
		SDL_FillRect(getPixel_Surface, &drawPointRect, selectedColor);
		fillZoneList.push_back(initialPixelCoords);

		while (fillZoneList.size() > 0) {
			vector<int> pixelCoords = fillZoneList[0];
			fillZoneList.erase(fillZoneList.begin());
			pixelSpread(pixelCoords[0], pixelCoords[1], initialPixel.r, initialPixel.g, initialPixel.b, initialPixel.a);
		}

		SDL_RenderPresent(render);
	}
}

void getClickedColor(int _x, int _y) {
	getPixel_Surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(render, NULL, SDL_PIXELFORMAT_ARGB8888, getPixel_Surface->pixels, getPixel_Surface->pitch);

	getPixel_bpp = getPixel_Surface->format->BytesPerPixel;

	SDL_Color clickedColor = getPixelColor(_x, _y);

	setColor(clickedColor.r, clickedColor.g, clickedColor.b, clickedColor.a);
}

void erasePoint(int _x, int _y, int _size = strokeSize) {
	if (checkForBar(_y)) {
		SDL_SetRenderDrawColor(render, backgroundColor_R, backgroundColor_G, backgroundColor_B, backgroundColor_A);
		SDL_Rect pointRect;
		pointRect.x = _x - _size / 2;
		pointRect.y = _y - _size / 2;
		pointRect.w = _size;
		pointRect.h = _size;
		SDL_RenderFillRect(render, &pointRect);
		SDL_RenderPresent(render);
		displayTaskbar();
		displayFootbar();
	}
}

void saveImage() {
	getPixel_Surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(render, NULL, SDL_PIXELFORMAT_ARGB8888, getPixel_Surface->pixels, getPixel_Surface->pitch);

	SDL_SaveBMP(getPixel_Surface, "image1.bmp");
}

bool init() {
	bool error = false;

	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	clearBackground();

	// Surface 
	/*
	surface = SDL_GetWindowSurface(window);
	backgroundImage = SDL_LoadBMP("D:\\cpp\\Projects\\Brain_Password\\Image\\background.bmp");
	SDL_BlitSurface(backgroundImage, NULL, surface, NULL);
	SDL_FreeSurface(backgroundImage); // cleaning up memory
	SDL_UpdateWindowSurface(window);
	*/

	bool running = true;
	bool drawing = false;

	bool point = true;
	bool rectangle = false;
	bool triangle = false;
	bool circle = false;
	bool eraser = false;
	bool fill = false;
	bool selectColor = false;

	int mouse_X_button = 0;
	int mouse_Y_button = 0;

	int _size = strokeSize;

	displayTaskbar();
	displayFootbar();
	while (running) {
		SDL_Event inputEvent;
		while (SDL_PollEvent(&inputEvent)) {
			int mouse_X_motion = inputEvent.motion.x;
			int mouse_Y_motion = inputEvent.motion.y;
			if (drawing) {
				if (point) {
					drawPoint(mouse_X_motion, mouse_Y_motion, _size);
				}
				else if (eraser) {
					erasePoint(mouse_X_motion, mouse_Y_motion, _size);
				}
			}
			switch (inputEvent.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch (inputEvent.key.keysym.sym) {
				case SDLK_ESCAPE:
					running = false;
					break;
				case SDLK_c:
					clearBackground();
					break;
				case SDLK_d:
					point = true;
					rectangle = false;
					triangle = false;
					circle = false;
					eraser = false;
					fill = false;
					selectColor = false;
					break;
				case SDLK_r:
					point = false;
					rectangle = true;
					triangle = false;
					circle = false;
					eraser = false;
					fill = false;
					selectColor = false;
					break;
				case SDLK_t:
					point = false;
					rectangle = false;
					triangle = true;
					circle = false;
					eraser = false;
					fill = false;
					selectColor = false;
					break; 
				case SDLK_o:
					point = false;
					rectangle = false;
					triangle = false;
					circle = true;
					eraser = false;
					fill = false;
					selectColor = false;
					break;
				case SDLK_e:
					point = false;
					rectangle = false;
					triangle = false;
					circle = false;
					eraser = true;
					fill = false;
					selectColor = false;
					break;
				case SDLK_f:
					point = false;
					rectangle = false;
					triangle = false;
					circle = false;
					eraser = false;
					fill = true;
					selectColor = false;
					break;
				case SDLK_q:
					point = false;
					rectangle = false;
					triangle = false;
					circle = false;
					eraser = false;
					fill = false;
					selectColor = true;
					break;
				case SDLK_s:
					saveImage();
					break;
				case SDLK_1: // Red
					setColor(236, 28, 36);
					if (eraser) {
						point = true;
						eraser = false;
					}
					break;
				case SDLK_2: // Orange
					setColor(255, 127, 39);
					if (eraser) {
						point = true;
						eraser = false;
					}
					break;
				case SDLK_3: // Green
					setColor(27, 155, 63);
					if (eraser) {
						point = true;
						eraser = false;
					}
					break;
				case SDLK_4: // Aqua
					setColor(140, 255, 251);
					if (eraser) {
						point = true;
						eraser = false;
					}
					break;
				case SDLK_5: // Blue
					setColor(63, 72, 204);
					if (eraser) {
						point = true;
						eraser = false;
					}
					break;
				case SDLK_6: // Pink
					setColor(255, 174, 200);
					if (eraser) {
						point = true;
						eraser = false;
					}
					break;
				case SDLK_7: // Yellow
					setColor(255, 242, 0);
					if (eraser) {
						point = true;
						eraser = false;
					}
					break;
				case SDLK_8: // Brown
					setColor(185, 122, 86);
					if (eraser) {
						point = true;
						eraser = false;
					}
					break;
				case SDLK_9: // White
					setColor(255, 255, 255);
					if (eraser) {
						point = true;
						eraser = false;
					}
					break;
				case SDLK_0: // Black
					setColor(0, 0, 0);
					if (eraser) {
						point = true;
						eraser = false;
					}
					break;
				case SDLK_EQUALS:
					_size += 2;
					break;
				case SDLK_MINUS:
					if (_size > 2) {
						_size -= 2;
					}
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (inputEvent.button.button == SDL_BUTTON_LEFT) {
					drawing = true;
					mouse_X_button = inputEvent.button.x;
					mouse_Y_button = inputEvent.button.y;

					RedColorButton.handle_events(mouse_X_button, mouse_Y_button);
					OrangeColorButton.handle_events(mouse_X_button, mouse_Y_button);
					GreenColorButton.handle_events(mouse_X_button, mouse_Y_button);
					AquaColorButton.handle_events(mouse_X_button, mouse_Y_button);
					BlueColorButton.handle_events(mouse_X_button, mouse_Y_button);
					PinkColorButton.handle_events(mouse_X_button, mouse_Y_button);
					YellowColorButton.handle_events(mouse_X_button, mouse_Y_button);
					BrownColorButton.handle_events(mouse_X_button, mouse_Y_button);
					WhiteColorButton.handle_events(mouse_X_button, mouse_Y_button);
					BlackColorButton.handle_events(mouse_X_button, mouse_Y_button);

					if (point) {
						drawPoint(mouse_X_button, mouse_Y_button, _size);
					}
					else if (rectangle) {
						drawRectangle(mouse_X_button, mouse_Y_button);
					}
					else if (triangle) {
						drawTriangle(mouse_X_button, mouse_Y_button);
					}
					else if (circle) {
						drawCircle(mouse_X_button, mouse_Y_button);
					}
					else if (eraser) {
						erasePoint(mouse_X_button, mouse_Y_button, _size);
					}
					else if (fill) {
						fillCanvas(mouse_X_button, mouse_Y_button, selectedColor_R, selectedColor_G, selectedColor_B, selectedColor_A);
					}
					else if (selectColor) {
						getClickedColor(mouse_X_button, mouse_Y_button);
						selectColor = false;
						point = true;
					}
				}
				break;
			case SDL_MOUSEBUTTONUP:
				drawing = false;
				if (rectangle) {
					drawRectangle(mouse_X_button, mouse_Y_button, mouse_X_motion, mouse_Y_motion);
				} else if (triangle) {
					drawTriangle(mouse_X_button, mouse_Y_button, mouse_X_motion, mouse_Y_motion);
				} else if (circle) {
					drawCircle(mouse_X_button, mouse_Y_button, mouse_X_motion, mouse_Y_motion);
				}

				break;
			}
		}
	}
	return error;
}

int exit() {
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);

	SDL_FreeSurface(getPixel_Surface);

	getPixel_Surface = nullptr;
	render = nullptr;
	window = nullptr;
	
	SDL_Quit();
	return 0;
}

int main(int argc, char* argv[]) {

	if (start()) {
		cout << "Error! Terminating...";
		return 1;
	}
	else {
		init();
	}

	exit();
	return 0;
}

/*
* TODO
* add more colours
* make Fill tool faster
* 
* display point size increase and decrease in right corner when +/- pressed & color selected
* complete buttons with images 
* select and move tool
*/

/*
* CONTROLS
* ESC - escape
* C   : clear screen
* D   : draw on screen
* E   : get eraser
* R   : draw rectangle on screen
* T   : draw triangle on screen
* O   : draw circle on screen
* F   : fill background with selected Color
* S   : save image
* Q   : get clicked color
* +/- : resize object
*
* Colors:
* 1   : Red color Toggle
* 2   : Orange color Toggle
* 3   : Green color Toggle
* 4   : Aqua color Toggle
* 5   : Blue color Toggle
* 6   : Pink color Toggle
* 7   : Yellow color Toggle
* 8   : Brown color Toggle
* 9   : White color Toggle
* 0   : Black color Toggle
*/