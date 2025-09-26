

#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "game.h"
#include <string>
#include <vector>

const unsigned int TARGET_FPS = 50; //frames/second
float dt = 1.0f / TARGET_FPS; //seconds/frame
float time = 0;

class FizziksObject
{
public:
	Vector2 position = { 0,0 };
	Vector2 velocity = { 0,0 };
	float mass = 1; // in kg

	float radius = 15; // circle radius in pixels
	std::string name = "objekt";
	Color color = RED;

	void draw()
	{
		DrawCircle(position.x, position.y, radius, color);

		DrawText(name.c_str(), position.x, position.y, radius * 2, LIGHTGRAY);

		//Draw velocity (for fun)
		DrawLineEx(position, position + velocity, 1, color);
	}
};

class FizziksWorld
{
private:
	unsigned int objektCount = 0;
public:
	std::vector<FizziksObject> objects; // All objects in physics simulation
	Vector2 accelerationGravity = { 0, 9 };

	void add(FizziksObject newObject) // Add to physics simulation
	{
		newObject.name = std::to_string(objektCount);
		objects.push_back(newObject);
		objektCount++;
	}

	// Update state of all physics objects
	void update()
	{
		for (int i = 0; i < objects.size(); i++)
		{
			//vel = change in position / time, therefore     change in position = vel * time 
			objects[i].position = objects[i].position + objects[i].velocity * dt;
			//accel = deltaV / time (change in velocity over time) therefore     deltaV = accel * time
			objects[i].velocity = objects[i].velocity + accelerationGravity * dt;
			
		}
	}
};

float speed = 100;
float angle = 0;
float magnitude = 9.0f;
float direction = 90.0f;
Vector2 LaunchPosition = { 100, 500 };

FizziksWorld world;


//Remove objects offscreen
void cleanup()
{
	//For each object, check if it is offscreen!
	for (int i = 0; i < world.objects.size(); i++)
	{
		//Is it offscreen?
		if (world.objects[i].position.y > GetScreenHeight()
			|| world.objects[i].position.y < 0
			|| world.objects[i].position.x > GetScreenWidth()
			|| world.objects[i].position.x < 0
			)
		{
			//Destroy!
			world.objects.erase(world.objects.begin() + i);
			i--;
		}
	}

}

//Changes world state
void update()
{
	dt = 1.0f / TARGET_FPS;
	time += dt;

	cleanup();
	world.accelerationGravity = { magnitude * cosf(direction * DEG2RAD), magnitude * sinf(direction * DEG2RAD) };
    world.update();
	if (IsKeyPressed(KEY_SPACE))
	{
		FizziksObject newBird;
		newBird.position = LaunchPosition;
		newBird.velocity = { speed * (float)cos(angle * DEG2RAD), -speed * (float)sin(angle * DEG2RAD) };

		//rand() % N produces random number from 0 to N-1
		newBird.radius = (rand() % 26) + 5; // radius from 5-30
		Color randomColor = { rand() % 256 , rand() % 256, rand() % 256, 255 };
		newBird.color = randomColor;

		world.add(newBird); // Add bird to simulation
	}
}

//Display world state
void draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawText("Game2005_Boran_Akkoyun_101557415", 10, float(GetScreenHeight() - 30), 20, LIGHTGRAY);


	GuiSliderBar(Rectangle{ 10, 15, 1000, 20 }, "", TextFormat("%.2f", time), &time, 0, 240);

	GuiSliderBar(Rectangle{ 10, 40, 500, 30 }, "Speed", TextFormat("Speed: %.0f", speed), &speed, -1000, 1000);

	GuiSliderBar(Rectangle{ 10, 80, 500, 30 }, "Angle", TextFormat("Angle: %.0f Degrees", angle), &angle, -180, 180);

	//GuiSliderBar(Rectangle{ 10, 120, 500, 30 }, "Gravity Y", TextFormat("Gravity Y: %.0f Px/sec^2", world.accelerationGravity.y), &world.accelerationGravity.y, -1000, 1000);
	GuiSliderBar(Rectangle{ 10, 120, 500, 30 }, "Gravity Magnitude", TextFormat("Magnitude: %.1f", magnitude), &magnitude, 0, 1000);

	GuiSliderBar(Rectangle{ 10, 160, 500, 30 }, "Gravity Direction", TextFormat("Direction: %.0f Degrees", direction), &direction, -180, 180);

	GuiSliderBar(Rectangle{ 10, 200, 500, 30 }, "Launch X", TextFormat("X: %.0f", LaunchPosition.x), &LaunchPosition.x, 0, GetScreenWidth());


	GuiSliderBar(Rectangle{ 10, 240, 500, 30 }, "Launch Y", TextFormat("Y: %.0f", LaunchPosition.y), &LaunchPosition.y, 0, GetScreenHeight());


	DrawText(TextFormat("Obects: %i", world.objects.size()), 10, 160, 30, LIGHTGRAY);

	DrawText(TextFormat("T: %6.2f", time), GetScreenWidth() - 140, 10, 30, LIGHTGRAY);

	Vector2 startPos = LaunchPosition;
	Vector2 velocity = { speed * cos(angle * DEG2RAD), -speed * sin(angle * DEG2RAD) };

	DrawLineEx(startPos, startPos + velocity, 3, RED);

	//Draw all physics objects!
	for (int i = 0; i < world.objects.size(); i++)
	{
		world.objects[i].draw();
	}

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