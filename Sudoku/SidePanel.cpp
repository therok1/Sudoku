#include "SidePanel.h"

SidePanel::SidePanel()
{
	m_AnchorPoint.SetX(0);
	m_AnchorPoint.SetY(0);
	m_Position.SetX(0);
	m_Position.SetY(0);
	m_SqSize.SetX(50);
	m_SqSize.SetY(50);

	for (int i = 1; i < 10; i++)
	{
		m_Numbers.push_back(i);
	}

	for (int i = 0; i < m_Numbers.size(); i++)
	{
		m_Buttons.push_back(std::make_unique<Button>(m_SqSize.GetX(), m_SqSize.GetY()));
		m_Buttons[i]->SetColour({ 255, 0, 0, 255 });
		m_Buttons[i]->SetText(std::to_string(m_Numbers[i]));
		m_Buttons[i]->SetFocusable(true);
	}

	m_Numbers.shrink_to_fit();
	m_Buttons.shrink_to_fit();
}

void SidePanel::GeneratePanel()
{
	for (int i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->SetX(0);
		m_Buttons[i]->SetY(i * m_SqSize.GetY());
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

void SidePanel::Select(enum GameState State, enum GameState DesiredState, int& Selected)
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
		if (!A)
		{
			m_Buttons[i]->SetX(PositionX - static_cast<int>(m_Buttons[i]->GetRect().w * m_AnchorPoint.GetX()));
			m_Position.SetX(PositionX - static_cast<int>(m_Buttons[i]->GetRect().w * m_AnchorPoint.GetX()));
		}
		else
		{
			m_Buttons[i]->SetX((m_Buttons[i]->GetRect().w * i) + static_cast<int>(Window.Width * PercentX) - static_cast<int>(m_Buttons[i]->GetRect().w * m_AnchorPoint.GetX()));
			m_Position.SetX(static_cast<int>(Window.Width * PercentX) - static_cast<int>(m_Buttons[i]->GetRect().w * m_AnchorPoint.GetX()));
		}
	}
}

void SidePanel::SetY(int PositionY, bool A, float PercentY)
{
	for (int i = 0; i < m_Buttons.size(); i++)
	{
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
	}
}

void SidePanel::SetAnchorPoint(float AnchorX, float AnchorY)
{
	m_AnchorPoint.SetX(AnchorX);
	m_AnchorPoint.SetY(AnchorY);

	SetX(m_Position.GetX());
	SetY(m_Position.GetY());
}
