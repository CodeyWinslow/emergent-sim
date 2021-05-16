#include "UIComponentFloodPanel.h"

EmergentGraphics::UIComponentFloodPanel::UIComponentFloodPanel(SDL_Renderer* renderer, SDL_Point position,
	SDL_Point padding, SDL_Point buttonMargin, SDL_Color backColor) :
	UIComponentPanel::UIComponentPanel(renderer, {position.x, position.y, 0, 0}, padding, buttonMargin, backColor)
{
	ResizePanelAroundComponents();
}

void EmergentGraphics::UIComponentFloodPanel::ResizePanelAroundComponents()
{
	m_bounds.h = m_padding.y;
	m_bounds.w = 2 * m_padding.x;
	for (UIComponent* comp : m_uiComponents)
	{
		SDL_Rect bounds = comp->GetBounds();
		if (m_bounds.w - (2 * m_padding.x) < bounds.w)
			m_bounds.w = bounds.w + (2 * m_padding.x);
		m_bounds.h += bounds.h + m_padding.y;
	}

	int yPos = m_bounds.y + m_padding.y;
	for (UIComponent* comp : m_uiComponents)
	{
		SDL_Rect bounds = comp->GetBounds();
		bounds.y = yPos;
		bounds.x = m_bounds.x + (m_bounds.w / 2) - (bounds.w / 2);
		comp->SetBounds(bounds);

		yPos += bounds.h + m_padding.y;
	}

	m_closeButton->SetBounds({ m_bounds.x + m_bounds.w + m_buttonMargin.x,
							m_bounds.y + m_buttonMargin.y, 20, 20 });
}

void EmergentGraphics::UIComponentFloodPanel::PanelButtonClicked()
{
	UIComponentPanel::PanelButtonClicked();
	if (m_opened)
	{
		ResizePanelAroundComponents();
	}
}
