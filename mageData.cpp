#include "raylib.h"
#include <string>

struct Mage {  //struktura gracza
	
	float x, y;
	float speedX, speedY;
	float width, height;
	int HP; 
	Texture2D image;
	Vector2 position;
	bool Alive;
		
	

	void DrawPlayer1() {
		
		DrawTexture(image, x - width / 2, y - height / 2, WHITE);
	}
	void DrawPlayer2() {
		
		DrawTexture(image, x - width / 2, y - height / 2, WHITE);
	}

	Rectangle GetRect() {
		return Rectangle{ x - width / 2, y - height / 2, width/2, height };
	}
	
};

struct Fish { //struktura kuli
	float x, y, speed, width, height, radius, dmg;
	int owner;
	bool onField;
	Texture2D projectileIMG;


	void CastPM1() {
		
		if (onField) DrawTexture(projectileIMG, x, y, WHITE);
			//DrawCircle(x + 5, y, radius, color);
	}
	void CastPM2() {
		if (onField) DrawTexture(projectileIMG, x, y, WHITE);
			//DrawCircle(x - 5, y, radius, color);
	}
	void UpdatePMP1() {  //onowienie pozycji kuli gracza#1 na ekranie 
		x += speed; 
		if (x > GetScreenWidth()) {
			onField = false; 
		}
	}
	void UpdatePMP2() {  //onowienie pozycji kuli gracza#2 na ekranie
		x += speed;
		if (x < 0) {
			onField = false;
		}
	}

	
	Rectangle GetRect() {  //powraca dane do funkcji powiązanej z kolizją

		return Rectangle{ x - width / 2, y - height / 2, width, height };
	}

};

enum GameState {
	START_SCREEN,
	IN_GAME,
	GAME_OVER,
	GAME_SHUTDOWN
};
