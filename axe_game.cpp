#include "raylib.h"

#define internal static

struct PlayerPawn
{
	int pos_x;
	int pos_y;
	int circle_radius;
	int left = pos_x - circle_radius;
	int right = pos_x + circle_radius;
	int top = pos_y - circle_radius;
	int bottom = pos_y + circle_radius;
};

struct AxeActor
{
	int pos_x;
	int pos_y;
	int length;
	int left = pos_x;
	int right = pos_x + length;
	int top = pos_y;
	int bottom = pos_y + length;
};

internal bool
hasCollidedWithAxe(PlayerPawn *pawn, AxeActor *axe)
{
	return
		(axe->bottom >= pawn->top) &&
		(axe->top <= pawn->bottom) &&
		(axe->right >= pawn->left) &&
		(axe->left <= pawn->right);

}

int main()
{
	int width{800};
	int height{450};

	InitWindow(width, height, "Axe Game");

	// initialize player
	PlayerPawn player = {};
	player.pos_x = 200;
	player.pos_y = 200;
	player.circle_radius = 25;


	// axe coordinates
	AxeActor axe = {};
	axe.pos_x = 400;
	axe.pos_y = 0;
	axe.length = 50;

	int direction{10};

	// Game Loop starts here
	SetTargetFPS(60);
	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		ClearBackground(WHITE);
		DrawText(FormatText("Player: %i,%i", player.pos_x,player.pos_y), 10, 10, 20, LIGHTGRAY);
		DrawText(FormatText("Axe: %i,%i", axe.pos_x,axe.pos_y), 10, 30, 20, LIGHTGRAY);

		// Check if the player has collided with the axe
		if (!hasCollidedWithAxe(&player, &axe))
		{
			DrawText("Game Over!", 400, 200, 20, RED);
		}
		else
		{
			// Draw Assets
			DrawCircle(player.pos_x, player.pos_y, player.circle_radius, BLUE);
			DrawRectangle(axe.pos_x, axe.pos_y, axe.length, axe.length, RED);

			axe.pos_y += direction;
			if (axe.pos_y > height || axe.pos_y < 0)
			{
				direction = -direction;
			}

			if (IsKeyDown(KEY_RIGHT) && player.pos_x < width)
			{
				player.pos_x += 10;
			}
			if (IsKeyDown(KEY_LEFT) && player.pos_x > 0)
			{
				player.pos_x -= 10;
			}
		}

		EndDrawing();
	}
}