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
