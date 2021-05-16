#include "ToolsPanel.h"
#include "PanelButton.h"

EmergentGraphics::ToolsPanel::ToolsPanel(SDL_Renderer* renderer, SDL_Rect openedBounds,
	SDL_Rect closedBounds, SDL_Color backColor) :
	UICanvas::UICanvas(renderer, openedBounds), m_openedBounds(openedBounds), m_closedBounds(closedBounds),
	m_backColor(backColor)
{
	auto onClick = std::function<void()>([this]() {this->PanelButtonClicked();});

	SDL_Rect closeButtonBounds = {openedBounds.x + openedBounds.w + 10,
									openedBounds.y + 10,
									20, 20};
	SDL_Rect openButtonBounds = { closedBounds.x + closedBounds.w + 10,
									closedBounds.y + 10,
									20, 20 };
	m_openButton = new PanelButton(renderer, openButtonBounds, { 28,212,98,165 }, onClick);
	m_closeButton = new PanelButton(renderer, closeButtonBounds, { 250,87,117,165 }, onClick);

	//create things inside
}

EmergentGraphics::ToolsPanel::~ToolsPanel()
{
	delete m_openButton;
	delete m_closeButton;
}


void EmergentGraphics::ToolsPanel::Render() const
{
	if (m_opened)
	{
		SDL_SetRenderDrawColor(m_renderer, m_backColor.r, m_backColor.g, m_backColor.b, m_backColor.a);
		SDL_RenderFillRect(m_renderer, &m_openedBounds);
		SDL_SetRenderDrawColor(m_renderer, 0,0,0,180);
		SDL_RenderDrawRect(m_renderer, &m_openedBounds);
		UICanvas::Render();
		m_closeButton->Render();
	}
	else
	{
		m_openButton->Render();
	}
}

bool EmergentGraphics::ToolsPanel::IsHovering() const
{
	if (m_opened)
	{
		bool isHovering = false;
		SDL_Point mousePoint;
		SDL_GetMouseState(&mousePoint.x, &mousePoint.y);
		isHovering = SDL_PointInRect(&mousePoint, &m_openedBounds);
		return isHovering || UICanvas::IsHovering() || m_closeButton->IsHovering();
	}

	return m_openButton->IsHovering();
}

void EmergentGraphics::ToolsPanel::PanelButtonClicked()
{
	m_opened = !m_opened;
}
