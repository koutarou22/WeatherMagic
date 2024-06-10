#include "Field.h"
#include <assert.h>

Field::Field(GameObject* scene)
{
	hImage = LoadGraph("Assets/bgchar.png");
	assert(hImage > 0);
}

Field::~Field()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Field::Update()
{
}

void Field::Draw()
{
}
