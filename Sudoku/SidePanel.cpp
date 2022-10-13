#include "SidePanel.h"

SidePanel::SidePanel()
{
	m_Padding = 2;

	m_AnchorPoint.SetX(0);
	m_AnchorPoint.SetY(0);
	m_Position.SetX(0);
	m_Position.SetY(0);
	m_SqSize.SetX(40);
	m_SqSize.SetY(40);

	m_Buttons.reserve(9);
	m_Numbers.reserve(9);

	for (int i = 1; i < 10; i++)
	{
		m_Numbers.push_back(i);
	}

	for (int i = 0; i < m_Numbers.size(); i++)
	{
		m_Buttons.push_back(std::make_unique<Button>(m_SqSize.GetX(), m_SqSize.GetY()));
		m_Buttons[i]->SetText(std::to_string(m_Numbers[i]));
		m_Buttons[i]->SetFontSize(16);

		if (i % 2)
		{
			m_Buttons[i]->SetColour({ 215, 242, 250, 255 });
		}
		else
		{
			m_Buttons[i]->SetColour({ 197, 228, 237, 255 });
		}
	}
}

void SidePanel::GeneratePanel()
{
	for (int i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->SetX(i * (m_SqSize.GetX() + 2 * m_Padding));
		m_Buttons[i]->SetY(0);
	}
}

void SidePanel::Update()
{
	for (auto& Button : m_Buttons)
	{
		Button->Update();
	}
}

void SidePanel::Render()
{
	for (auto& Button : m_Buttons)
	{
		Button->Render();
	}
}

void SidePanel::Select(enum GameState State, enum GameState DesiredState, Uint8& Selected)
{
	for (auto& Button : m_Buttons)
	{
		if (Button->MouseRelease(State, DesiredState))
		{
			Selected = std::stoi(Button->GetText());
		}
	}
}

void SidePanel::SetX(int PositionX, bool A, float PercentX)
{
	for (int i = 0; i < m_Buttons.size(); i++)
	{
		/*
		if (!A)
		{
			m_Buttons[i]->SetX(PositionX - static_cast<int>(m_Buttons[i]->GetRect().w * m_AnchorPoint.GetX()));
			m_Position.SetX(PositionX - static_cast<int>(m_Buttons[i]->GetRect().w * m_AnchorPoint.GetX()));
		}
		else
		{
			m_Buttons[i]->SetX(static_cast<int>(Window.Width * PercentX) - static_cast<int>(m_Buttons[i]->GetRect().w * m_AnchorPoint.GetX()));
			m_Position.SetX(static_cast<int>(Window.Width * PercentX) - static_cast<int>(m_Buttons[i]->GetRect().w * m_AnchorPoint.GetX()));
		}
		*/
		if (!A)
		{
			m_Buttons[i]->SetX(m_Padding + ((m_Buttons[i]->GetRect().w + 2 * m_Padding) * i) + (PositionX - static_cast<int>((m_Buttons[i]->GetRect().w + 2 * m_Padding) * m_Buttons.size() * m_AnchorPoint.GetX())));
			m_Position.SetX(PositionX - static_cast<int>(m_Buttons[i]->GetRect().w * m_Buttons.size() * m_AnchorPoint.GetX()));
		}
		else
		{
			m_Buttons[i]->SetX((m_Buttons[i]->GetRect().w * i) + static_cast<int>(Window.Width * PercentX) - static_cast<int>(m_Buttons[i]->GetRect().w * m_Buttons.size() * m_AnchorPoint.GetX()));
			m_Position.SetX(static_cast<int>(Window.Width * PercentX) - static_cast<int>(m_Buttons[i]->GetRect().w * m_Buttons.size() * m_AnchorPoint.GetX()));
		}
	}
}

void SidePanel::SetY(int PositionY, bool A, float PercentY)
{
	for (int i = 0; i < m_Buttons.size(); i++)
	{
		/*
		if (!A)
		{
			m_Buttons[i]->SetY((m_Buttons[i]->GetRect().h * i) + (PositionY - static_cast<int>(m_Buttons[i]->GetRect().h * m_Buttons.size() * m_AnchorPoint.GetY())));
			m_Position.SetY(PositionY - static_cast<int>(m_Buttons[i]->GetRect().h * m_Buttons.size() * m_AnchorPoint.GetY()));
		}
		else
		{
			m_Buttons[i]->SetY((m_Buttons[i]->GetRect().h * i) + static_cast<int>(Window.Height * PercentY) - static_cast<int>(m_Buttons[i]->GetRect().h * m_Buttons.size() * m_AnchorPoint.GetY()));
			m_Position.SetY(static_cast<int>(Window.Height * PercentY) - static_cast<int>(m_Buttons[i]->GetRect().h * m_Buttons.size() * m_AnchorPoint.GetY()));
		}
		*/
		if (!A)
		{
			m_Buttons[i]->SetY(PositionY - static_cast<int>(m_Buttons[i]->GetRect().h * m_AnchorPoint.GetY()));
			m_Position.SetY(PositionY - static_cast<int>(m_Buttons[i]->GetRect().h * m_AnchorPoint.GetY()));
		}
		else
		{
			m_Buttons[i]->SetY(static_cast<int>(Window.Height * PercentY) - static_cast<int>(m_Buttons[i]->GetRect().h * m_AnchorPoint.GetY()));
			m_Position.SetY(static_cast<int>(Window.Height * PercentY) - static_cast<int>(m_Buttons[i]->GetRect().h * m_AnchorPoint.GetY()));
		}
	}
}

void SidePanel::SetAnchorPoint(float AnchorX, float AnchorY)
{
	m_AnchorPoint.SetX(AnchorX);
	m_AnchorPoint.SetY(AnchorY);

	SetX(m_Position.GetX());
	SetY(m_Position.GetY());
}
