#include "UI.h"

UI::UI(GameObject* parent)
{
}

void UI::Initialize()
{
	hStkL = LoadGraph("Assets/UI/XboxBottunUI/stickL.png");
	assert(hStkL > 0);

	hAttB = LoadGraph("Assets/UI/XboxBottunUI/attackB.png");
	assert(hAttB > 0);
	
	hJumpA = LoadGraph("Assets/UI/XboxBottunUI/jumpA.png");
	assert(hJumpA > 0);

	hChaPad = LoadGraph("Assets/UI/XboxBottunUI/changePad.png");
	assert(hChaPad > 0);
	
	hStkR = LoadGraph("Assets/UI/XboxBottunUI/stickR.png");
	assert(hStkR > 0);
	
	hExplanLRB = LoadGraph("Assets/UI/XboxBottunUI/LBRBexplan.png");
	assert(hExplanLRB > 0);
}

void UI::Update()
{
}

void UI::Draw()
{
	//ç∂äÒÇπ
	/*DrawGraph(0,   685, hStkL, TRUE);
	DrawGraph(83, 685, hAttB, TRUE);
	DrawGraph(160, 685, hJumpA, TRUE);
	DrawGraph(280, 685, hChaPad, TRUE);
	DrawGraph(410, 685, hStkR, TRUE);
	DrawGraph(525, 685, hExplanLRB, TRUE);*/
	//âEäÒÇπ
	DrawGraph(580, 685, hStkL, TRUE);
	DrawGraph(663, 685, hAttB, TRUE);
	DrawGraph(740, 685, hJumpA, TRUE);
	DrawGraph(860, 685, hChaPad, TRUE);
	DrawGraph(990, 685, hStkR, TRUE);
	DrawGraph(1105, 685, hExplanLRB, TRUE);
	
}

void UI::Release()
{
	DeleteGraph(hStkR);
	DeleteGraph(hStkL);
	DeleteGraph(hExplanLRB);
	DeleteGraph(hJumpA);
	DeleteGraph(hChaPad);
	DeleteGraph(hAttB);
}
