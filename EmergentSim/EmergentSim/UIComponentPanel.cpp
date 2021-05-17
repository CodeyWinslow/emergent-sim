#include "UIComponentPanel.h"
#include "PanelButton.h"

EmergentGraphics::UIComponentPanel::UIComponentPanel(SDL_Renderer* renderer, SDL_Rect bounds,
	SDL_Point padding, SDL_Point buttonMargin, SDL_Color backColor) :
	UICanvas::UICanvas(renderer, bounds), m_backColor(backColor),
	m_padding(padding), m_buttonMargin(buttonMargin)
{
	auto onClick = std::function<void()>([this]() {this->PanelButtonClicked();});

	SDL_Rect closeButtonBounds = {m_bounds.x + m_bounds.w + m_buttonMargin.x,
									m_bounds.y + m_buttonMargin.y,
									24, 24};
	SDL_Rect openButtonBounds = { m_bounds.x + 10,
									m_bounds.y,
									24, 24 };
	m_openButton = new PanelButton(renderer, openButtonBounds, { 28,212,98,165 }, onClick);
	m_closeButton = new PanelButton(renderer, closeButtonBounds, { 250,87,117,165 }, onClick);
	m_openButtonImage = new ButtonImage(m_renderer, m_openButtonFilePath, openButtonBounds);
	m_closeButtonImage = new ButtonImage(m_renderer, m_closeButtonFilePath, closeButtonBounds);
	m_openButton->SetActive(false);
	m_openButtonImage->SetActive(false);
	//create things inside
}

EmergentGraphics::UIComponentPanel::~UIComponentPanel()
{
	delete m_openButton;
	delete m_closeButton;
	delete m_openButtonImage;
	delete m_closeButtonImage;
}


void EmergentGraphics::UIComponentPanel::Render() const
{
	if (m_opened)
	{
		SDL_SetRenderDrawColor(m_renderer, m_backColor.r, m_backColor.g, m_backColor.b, m_backColor.a);
		SDL_RenderFillRect(m_renderer, &m_bounds);
		SDL_SetRenderDrawColor(m_renderer, 0,0,0,180);
		SDL_RenderDrawRect(m_renderer, &m_bounds);
		UICanvas::Render();
	}

	m_closeButton->Render();
	m_openButton->Render();
	m_closeButtonImage->Render();
	m_openButtonImage->Render();
}

bool EmergentGraphics::UIComponentPanel::IsHovering() const
{
	bool isHovering = false;
	if (m_opened)
	{
		SDL_Point mousePoint;
		SDL_GetMouseState(&mousePoint.x, &mousePoint.y);
		isHovering = SDL_PointInRect(&mousePoint, &m_bounds);
	}

	return isHovering || UICanvas::IsHovering() || m_closeButton->IsHovering() || m_openButton->IsHovering();
}

void EmergentGraphics::UIComponentPanel::PanelButtonClicked()
{
	m_opened = !m_opened;
	if (m_opened)
	{
		for (UIComponent* comp : m_uiComponents)
		{
			comp->SetActive(true);
		}
		m_openButton->SetActive(false);
		m_openButtonImage->SetActive(false);
		m_closeButton->SetActive(true);
		m_closeButtonImage->SetActive(true);
	}
	else
	{
		for (UIComponent* comp : m_uiComponents)
		{
			comp->SetActive(false);
		}
		m_openButton->SetActive(true);
		m_openButtonImage->SetActive(true);
		m_closeButton->SetActive(false);
		m_closeButtonImage->SetActive(false);
	}
}
