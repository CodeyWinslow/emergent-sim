#pragma once
#include <SDL.h>
#include <string>
#include "SDL_Logger.h"
#include "IEventObserver.h"
#include "PauseButton.h"

struct Entity
{
	int x, y;
	SDL_Color color;
};
class Sandbox {
public:
	Sandbox()
	{
		width = 80;
		height = 80;
		garbage = new Entity * *[height];

		int x =0 , y = 0;
		for (int ii = 0; ii < height; ++ii,++y)
		{
			garbage[ii] = new Entity * [width];
			for (int ent = 0; ent < width; ++ent, ++x)
			{
				garbage[ii][ent] = new Entity{ x,y,{255,0,0} };
			}

			x = 0;
		}
	}

	~Sandbox()
	{
		for (int ii = 0; ii < height; ++ii)
		{
			for (int jj = 0; jj < width; ++jj)
			{
				delete garbage[ii][jj];
			}
			delete[] garbage[ii];
		}
		delete[] garbage;
	}

	int GetWidth() { return width; }
	int GetHeight() { return height; }
	Entity** operator[] (int index) { return garbage[index]; }

private:
	Entity*** garbage;
	int width;
	int height;
};

class SimDisplay : public IEventObserver
{
public:
	SimDisplay(Sandbox& sim, std::string windowTitle, int windowWidth, int windowHeight);
	~SimDisplay();
	bool Update();
	void Handle(SDL_Event& e);

private:
	Sandbox& m_sandbox;

	SDL_Window* m_window;
	SDL_Surface* m_screenSurface;
	SDL_Renderer* m_renderer;

	PauseButton m_pauseButton;

	SDL_Logger m_logger;

	float m_gridWidthToPixels = 1.0f;
	const int m_defaultWidthToPixels = 40;

	void DrawEntities();
	void DrawEntity(const Entity* entity, float scale = 0.75f);
	void DrawGrid();
	void DrawUI();
	void HandleScroll(SDL_MouseWheelEvent& e);
	void ScrollZoomOut();
	void ScrollZoomIn();

};
