#include "main.h"
#include "renderer.h"
#include "Scene.h"
#include "Game.h"
#include "shop.h"
#include "score.h"


//グローバル変数
//現在実行中のシーン番号
static SCENE g_SceneIndex = SCENE::SCENE_NONE;
static SCENE g_SceneNextIndex = g_SceneIndex;

void InitScene(SCENE no)
{
	g_SceneIndex = g_SceneNextIndex = no;

	switch (g_SceneIndex)
	{
	case SCENE::SCENE_NONE:
		break;
	case SCENE::SCENE_SHOP:
		InitShop();
		break;
	case SCENE::SCENE_GAME:
		InitGame();
		break;
	case SCENE::SCENE_SCORE:
		break;
	
	}
}
void UninitScene()
{
	switch (g_SceneIndex)
	{
	case SCENE::SCENE_NONE:
		break;

	case SCENE::SCENE_SHOP:
		UninitShop();

		break;
	case SCENE::SCENE_GAME:
		UninitGame();
		break;
	case SCENE::SCENE_SCORE:
		UninitScore();
		break;
	}
}
void UpdateScene()
{
	switch (g_SceneIndex)
	{
	case SCENE::SCENE_NONE:
		break;

	case SCENE::SCENE_SHOP:
		UpdateShop();
		break;

	case SCENE::SCENE_GAME:
		UpdateGame();
		break;
	case SCENE::SCENE_SCORE:
		break;
	}
}
void DrawScene()
{
	switch (g_SceneIndex)
	{
	case SCENE::SCENE_NONE:
		break;

	case SCENE::SCENE_SHOP:
		DrawShop();

		break;

	case SCENE::SCENE_GAME:
		DrawGame();
		break;
	case SCENE::SCENE_SCORE:
		DrawScore();
		break;
	}
}

void SetScene(SCENE no)
{
	g_SceneNextIndex = no;
}

void CheckScene()
{
	if (g_SceneIndex != g_SceneNextIndex)
	{
		UninitScene();
		InitScene(g_SceneNextIndex);
	}
}
