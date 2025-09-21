/*
This project uses the Raylib framework to provide us functionality for math, graphics, GUI, input etc.
See documentation here: https://www.raylib.com/, and examples here: https://www.raylib.com/examples.html
*/

#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "game.h"

const unsigned int TARGET_FPS = 50; //frames/second
float dt = 1.0f / TARGET_FPS; //seconds/frame
float time = 0;
//float x = 500;
//float y = 500;
//float frequency = 2;
//float frequency2 = 1;
//float amplitude = 100;
float launchSpeed = 100;
float launchAngle = 0;
Vector2 LaunchPosition = { 100, 500 };
Vector2 position = LaunchPosition;
Vector2 velocity = { 0,0 };
Vector2 accelerationGravity = { 0, 9 };
//Changes world state
void update()
{
	dt = 1.0f / TARGET_FPS;
	time += dt;

	//vel = change in position / time, therefore Change in position = vel * time
	position = position + velocity * dt;

	//accel = deltav / time (change in velocity over time) therefore deltaV = accel * time
	velocity = velocity + accelerationGravity * dt;
	if (IsKeyPressed ( KEY_SPACE))
	{
		position = LaunchPosition;
		velocity = { launchSpeed * (float)cos(launchAngle * DEG2RAD), -launchSpeed * (float)sin(launchAngle * DEG2RAD) };
	}

	//x = x + (-sin(time * frequency)) * frequency * amplitude * dt;
	//y = y + (cos(time * frequency)) * frequency * amplitude * dt;
}

//Display world state
void draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawText("Game2005_Boran_Akkoyun_101557415", 10, float(GetScreenHeight() - 30), 20, LIGHTGRAY);

	GuiSliderBar(Rectangle{ 10, 15, 1000, 20 }, "", TextFormat("%.2f", time), &time, 0, 240);

	GuiSliderBar(Rectangle{ 10, 40, 500, 30 }, "Speed", TextFormat("Speed: %.0f", launchSpeed), &launchSpeed, -1000, 1000);

	GuiSliderBar(Rectangle{ 10, 80, 500, 30 }, "Angle", TextFormat("Angle: %.Of Degrees", launchAngle), &launchAngle, -180, 180);

	GuiSliderBar(Rectangle{ 10, 120, 500, 30 }, "Gravity Y", TextFormat("Gravity Y: %.0f Px/sec^2", accelerationGravity.y), &accelerationGravity.y, -1000, 1000);

	GuiSliderBar(Rectangle{ 10, 160, 500, 30 }, "Launch X", TextFormat("X: %.0f", LaunchPosition.x), &LaunchPosition.x, 0, GetScreenWidth());
	 

	GuiSliderBar(Rectangle{ 10, 200, 500, 30 }, "Launch Y", TextFormat("Y: %.0f", LaunchPosition.y), &LaunchPosition.y,   0, GetScreenHeight());



	DrawText(TextFormat("T: %6.2f", time), GetScreenWidth() - 140, 10, 30, LIGHTGRAY);

	Vector2 velocity = { launchSpeed * cos(launchAngle * DEG2RAD), -launchSpeed * sin(launchAngle * DEG2RAD) };

	DrawLineEx(LaunchPosition, Vector2Add(LaunchPosition, velocity), 3, RED);

	DrawCircle(position.x, position.y, 15, RED);


	//DrawCircle(x, y, 70, RED);
	//DrawCircle(500 + cos(time * frequency2) * amplitude, 500 + sin(time * frequency2) * amplitude, 70, GREEN);

	EndDrawing();

}

int main()
{
	InitWindow(InitialWidth, InitialHeight, "Game2005_Boran_Akkoyun_101557415");
	SetTargetFPS(TARGET_FPS);

	while (!WindowShouldClose()) // Loops TARGET_FPS times per second
	{
		update();
		draw();
	}

	CloseWindow();
	return 0;
}