#include "raylib.h"
#include "mageData.cpp"
#include <vector>
#include <ctime>



int main() {
	
	InitWindow(1600, 900, "i cast fish");
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(40);

	srand(time(NULL));

	Mage player1Mage; 
	player1Mage.HP = 200;
	player1Mage.Alive = true;
	
	player1Mage.x = 200;			//gracz#1 znajduje się na początku
	player1Mage.y = 750;			//na tych koordynatach.
	player1Mage.width = 200;			
	player1Mage.height = 165;
	player1Mage.speedX = 20;		//szybkość gracza wedlug
	player1Mage.speedY = 20;		//obu osi koordynat
	player1Mage.image = LoadTexture("graphics/redmageP1.png");


	Mage player2Mage;
	player2Mage.HP = 500;
	player2Mage.Alive = true;

	player2Mage.x = 1400;			//gracz#1 znajduje się na początku
	player2Mage.y = 750;			//na tych koordynatach.
	player2Mage.width = 200;
	player2Mage.height = 165;
	player2Mage.speedX = 20;
	player2Mage.speedY = 20;
	player2Mage.image = LoadTexture("graphics/redmageP2.png");
	
	GameState currentState = START_SCREEN;  // inicjalizacja statusu gry
	
	Fish player1Fish;
	Fish player2Fish;

	std::vector<Fish> fishVector;		 	// wektor, gdzie zapisywane są kuli

	while (!WindowShouldClose()) { 
		
			//grawitacja dla graczy
		if (player1Mage.y < 770 && !IsKeyDown(KEY_W)) {
			player1Mage.y += player1Mage.speedY - 10;
		}
		if (player2Mage.y < 770 && !IsKeyDown(KEY_I)) {
			player2Mage.y += player2Mage.speedY - 10;
		}
		
		
			
			//przemieszczanie się gracza #1
		if (player1Mage.HP > 0) {
			if (IsKeyDown(KEY_W) && player1Mage.y > 100) player1Mage.y -= player1Mage.speedY;

			if (IsKeyDown(KEY_S) && player1Mage.y < 770) player1Mage.y += player1Mage.speedY;

			if (IsKeyDown(KEY_A) && player1Mage.x > 40) player1Mage.x -= player1Mage.speedX;

			if (IsKeyDown(KEY_D) && player1Mage.x < 750) player1Mage.x += player1Mage.speedX;

			if (IsKeyPressed(KEY_C)) {
				Fish p1Fish;											// tworzenie kuli oraz 
				p1Fish.owner = 1;										// definicja wszystkich jej cech
				p1Fish.onField = true;									
				p1Fish.x = player1Mage.x + player1Mage.width / 2;		
				p1Fish.y = player1Mage.y - player1Mage.height / 2;
				p1Fish.speed = 30;
				p1Fish.width = 200;
				p1Fish.height = 150;
				p1Fish.radius = 10;
				p1Fish.dmg = 50;
				p1Fish.projectileIMG = LoadTexture("graphics/fishP1.png");// dodanie kuli tekstury
				
				fishVector.push_back(p1Fish);							// dodanie kuli do vektoru					
			}
		}
		
			//przemieszczanie się gracza #2
		if (player2Mage.HP > 0) {
			if (IsKeyDown(KEY_I) && player2Mage.y > 100) player2Mage.y -= player2Mage.speedY;

			if (IsKeyDown(KEY_K) && player2Mage.y < 770) player2Mage.y += player2Mage.speedY;

			if (IsKeyDown(KEY_J) && player2Mage.x > 840) player2Mage.x -= player2Mage.speedX;

			if (IsKeyDown(KEY_L) && player2Mage.x < 1550) player2Mage.x += player2Mage.speedX;

			if (IsKeyPressed(KEY_PERIOD)) {
				Fish p2Fish;										// tworzenie kuli oraz
				p2Fish.owner = 2;									// definicja wszystkich jej cech
				p2Fish.onField = true;	
				p2Fish.x = player2Mage.x - player2Mage.width / 2;
				p2Fish.y = player2Mage.y - player2Mage.height / 2;
				p2Fish.width = 200;
				p2Fish.height = 150;
				p2Fish.speed = -30;
				p2Fish.radius = 10;
				p2Fish.dmg = 50;
				p2Fish.projectileIMG = LoadTexture("graphics/fishP2.png");
				
				fishVector.push_back(p2Fish);
			}
		}
		
		//onowienie każdej kuli w wektorze 
		for (auto& fish : fishVector) {
			if (fish.onField) {
				fish.UpdatePMP1();
				fish.UpdatePMP2();

				//sprawdzenie kolizji kul dla obu graczy
				if (CheckCollisionCircleRec(Vector2{ fish.x, fish.y }, fish.radius, player1Mage.GetRect())) {
					fish.onField = false;
					player1Mage.HP -= fish.dmg;
					UnloadTexture(fish.projectileIMG);
				}
				if (CheckCollisionCircleRec(Vector2{ fish.x, fish.y }, fish.radius, player2Mage.GetRect())) {
					fish.onField = false;
					player2Mage.HP -= fish.dmg;
					UnloadTexture(fish.projectileIMG);
				}
				//if(CheckCollisionRecs(p1Fish.GetRect(), ))
			}
		}

		// oczyszczenie wektora od kul
		fishVector.erase(std::remove_if(fishVector.begin(), fishVector.end(), [](const Fish& fish) { return !fish.onField; }), fishVector.end());
			
			/*
			
		if (player2Mage.HP <= 0) player2Mage.Alive = false;

		if (player2Mage.Alive) {

			if (player2Mage.y >= 700) enemyDirection = -1; // oponent leci do góry
			else if (player2Mage.y <= 150) enemyDirection = 1; // oponent leci do dolu

			player2Mage.y += enemyDirection * player2Mage.speedY;

		}
		else player2Mage.speedY = 0;
		*/
		

		switch (currentState) {
			case START_SCREEN:  // ekran startowy
				BeginDrawing();
					ClearBackground(DARKPURPLE);
					DrawText(">-|||[> I cast fish : The Game <]|||-<", 390, 200, 50, BLACK);
					DrawText("-| made by Horduz Valentyn |-   ", 630, 300, 20, BLACK);
					DrawText("WASD - p1 movement           IJKL - p2 movement", 550, 420, 20, YELLOW);
					DrawText("C - shoot                        PERIOD ('.' key) - shoot", 550, 460, 20, YELLOW);

					DrawText("TWO PLAYERS ARE REQUIRED", 630, 510, 20, GRAY);

					DrawText("PRESS SPACE TO START THE GAME", 600, 600, 20, GRAY);
					if (IsKeyPressed(KEY_SPACE)) {
						currentState = IN_GAME;
					}
				EndDrawing();
				break;

			case IN_GAME:		// sama gra
				BeginDrawing();
					DrawFPS(10, 10);
					ClearBackground(RAYWHITE);
					DrawRectangle(0, 0, 1600, 30, DARKBROWN);
					DrawRectangle(0, 800, 1600, 100, DARKBROWN);

					player1Mage.DrawPlayer1();
					player2Mage.DrawPlayer2();

					for (auto& fish : fishVector) {					// tworzenie kul na ekranie
						if (fish.onField) {
							if (fish.owner == 1) {
								fish.CastPM1();
							}
							else if (fish.owner == 2) {
								fish.CastPM2();
							}
						}
					}

					if (player1Mage.HP < 0 || player2Mage.HP < 0) { // warunki zakończenia gry
						for (auto& fish : fishVector) 
							!fish.onField;
						
						currentState = GAME_OVER;
					}
				EndDrawing();
				break;

			case GAME_OVER:		//koniec gry i wyświetlenie zwycięzcy
				BeginDrawing();
				
				if (player1Mage.HP < 0) { 
					DrawText("     ---Player 2 wins!---\n\nPress Enter to close the game", 900, 300, 30, SKYBLUE); 
					
				}
				if (player2Mage.HP < 0) {
					DrawText("     ---Player 1 wins!---\n\nPress Enter to close the game", 100, 300, 30, SKYBLUE);
				}
				
				if (IsKeyPressed(KEY_ENTER)) { 
					CloseWindow();
					exit(0);	//zamknięcie gry
				}
	
				EndDrawing();
				break;
		}

		

			
	} 
	UnloadTexture(player1Mage.image);
	UnloadTexture(player2Mage.image);
	
	CloseWindow();
}
 
