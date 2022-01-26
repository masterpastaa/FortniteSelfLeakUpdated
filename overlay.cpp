#pragma once
#include "includes.hpp"
#include "overlay.hpp"
#include "render/renderer.h"
#include "features.hpp"
#include "minhook/include/MinHook.h"

// main variables
bool						bExecuteOnce = true;
bool						showMenu = true;


// tick
void Loop()
{
	Render::DrawCircle(Vector2(width / 2, height / 2), Settings.aimConfigsPlayers.FovCircle, color(1.f, 1.f, 1.f, 1.f));

	//Fortnite
	boolean inGame = PlayersCpp();

	if (inGame)
		Render::DrawFilledCircle({ 20, 20 }, 5, color(0, 255, 0, 255));
	else
		Render::DrawFilledCircle({ 20, 20 }, 5, color(255, 0, 0, 255));
}


VOID(*PostRender_O)(uintptr_t _this, uintptr_t Canvas) = nullptr;


Vector2 mousePos;

bool inArea(Vector2 area1, Vector2 area2) {
    if (mousePos.x >= area1.x && mousePos.x <= area2.x && mousePos.y >= area1.y && mousePos.y <= area2.y)
        return true;
    else
        return false;
}




void CustomTab(float x, float& y, const wchar_t* content, bool& config) {

    y += 30.f;
    Render::DrawStrokeText(Vector2(x, y), color(1.f, 1.f, 1.f, 1.f), content, false, false, false);

    //Render::DrawRect(Vector2(x + 195 - 2, y - 2), Vector2(21, 21), color(1.f, 1.f, 0.f, 1.f));
    if (inArea(Vector2(x + 195 - 2, y - 2), Vector2(x + 195 + 19, y + 19)))
        if (GetAsyncKeyState(VK_LBUTTON) & 1)
            config = !config;

    if (config)
        Render::DrawStrokeText(Vector2(x + 195, y), color(0.f, 0.4, 0.f, 1.f), xorstr(L"On"), false, false, false);
    else 
        Render::DrawStrokeText(Vector2(x + 195, y), color(1.f, 0.1f, 0.1f, 1.f), xorstr(L"Off"), false, false, false);
}


VOID PostRender(uintptr_t _this, uintptr_t Canvas)
{
	if (fakeunload or !Canvas) {
		return PostRender_O(_this, Canvas);
	}

	if (bExecuteOnce) {
        sdk::cached::Canvas = (UCanvas*)(Canvas);
        width = sdk::cached::Canvas->SizeX();
        height = sdk::cached::Canvas->SizeY();


        sdk::cached::PlayerController = ((UWorld*)(utilities::read<uintptr_t>(sdk::cached::UWorld)))->OwningGameInstance()->LocalPlayers()->LocalPlayer()->PlayerController();

        sdk::cached::keys::LButton.KeyName = sdk::structs::FName{ sdk::objects::Conv_StringToName(xorstr(L"LeftMouseButton")).ComparisonIndex, 0 };
        sdk::cached::keys::Insert.KeyName = sdk::structs::FName{ sdk::objects::Conv_StringToName(xorstr(L"Insert")).ComparisonIndex, 0 };

		bExecuteOnce = false;
	}

    sdk::cached::PlayerController = ((UWorld*)(utilities::read<uintptr_t>(sdk::cached::UWorld)))->OwningGameInstance()->LocalPlayers()->LocalPlayer()->PlayerController();

    if (GetAsyncKeyState(VK_INSERT) & 1) {
        showMenu = !showMenu;
    }

    Loop();
    
    if (showMenu)
    {
        mousePos = sdk::cached::PlayerController->GetMousePosition();

        static Vector2 menuPos = Vector2(35, 50);
        static Vector2 dragPos;

        float width = 260;
        float height = 910;

        Render::DrawFilledRect(Vector2(menuPos.x - 15, menuPos.y), Vector2(width, height), color(0.005f, 0.005f, 0.005f, 1.f), false);
        Render::DrawRect(Vector2(menuPos.x - 15, menuPos.y), Vector2(width, height), color(0.1f, 0.f, 1.f, 1.f), 1, false);
        Render::DrawStrokeText(Vector2(menuPos.x, menuPos.y + 5), color(1.f, 1.f, 0.f, 1.f), xorstr(L"Fartnight"), false, false, false);

        float tmp_y = menuPos.y;

        //Players ESP
        tmp_y += 48;
        Render::DrawStrokeText(Vector2(menuPos.x, tmp_y), color(0.1f, 0.f, 1.f, 1.f), xorstr(L"Players ESP"), false, false, false);
        CustomTab(menuPos.x, tmp_y, xorstr(L"ESP: "), Settings.visualsConfigsPlayers.ESP);
        CustomTab(menuPos.x, tmp_y, xorstr(L"Box2D: "), Settings.visualsConfigsPlayers.Box2D);
        CustomTab(menuPos.x, tmp_y, xorstr(L"Box3D: "), Settings.visualsConfigsPlayers.Box3D);
        CustomTab(menuPos.x, tmp_y, xorstr(L"Skeleton: "), Settings.visualsConfigsPlayers.Skeleton);
        CustomTab(menuPos.x, tmp_y, xorstr(L"Lines: "), Settings.visualsConfigsPlayers.Lines);
        CustomTab(menuPos.x, tmp_y, xorstr(L"Names: "), Settings.visualsConfigsPlayers.Names);
        CustomTab(menuPos.x, tmp_y, xorstr(L"Weapon: "), Settings.visualsConfigsPlayers.Weapon);
        CustomTab(menuPos.x, tmp_y, xorstr(L"Distance: "), Settings.visualsConfigsPlayers.Distance);
        CustomTab(menuPos.x, tmp_y, xorstr(L"Platform: "), Settings.visualsConfigsPlayers.Platform);
        CustomTab(menuPos.x, tmp_y, xorstr(L"TargetLine: "), Settings.visualsConfigsPlayers.TargetLine);


        //Players Aimbot
        tmp_y += 48;
        Render::DrawStrokeText(Vector2(menuPos.x, tmp_y), color(0.1f, 0.f, 1.f, 1.f), xorstr(L"Players Aimbot"), false, false, false);
        CustomTab(menuPos.x, tmp_y, xorstr(L"Memory: "), Settings.aimConfigsPlayers.Memory);
        CustomTab(menuPos.x, tmp_y, xorstr(L"Silent: "), Settings.aimConfigsPlayers.Silent);
        CustomTab(menuPos.x, tmp_y, xorstr(L"BulletTP: "), Settings.aimConfigsPlayers.BulletTP);
        CustomTab(menuPos.x, tmp_y, xorstr(L"SniperPrediction: "), Settings.aimConfigsPlayers.SniperPrediction);


        //World ESP
        tmp_y += 48;
        Render::DrawStrokeText(Vector2(menuPos.x, tmp_y), color(0.1f, 0.f, 1.f, 1.f), xorstr(L"World ESP"), false, false, false);
        CustomTab(menuPos.x, tmp_y, xorstr(L"ESP: "), Settings.visualsConfigsWorld.ESP);
        CustomTab(menuPos.x, tmp_y, xorstr(L"Loot: "), Settings.visualsConfigsWorld.Loot);
        CustomTab(menuPos.x, tmp_y, xorstr(L"Chest: "), Settings.visualsConfigsWorld.Chest);
        CustomTab(menuPos.x, tmp_y, xorstr(L"AmmoBox: "), Settings.visualsConfigsWorld.AmmoBox);


        //Exploits
        tmp_y += 48;
        Render::DrawStrokeText(Vector2(menuPos.x, tmp_y), color(0.1f, 0.f, 1.f, 1.f), xorstr(L"Exploits"), false, false, false);
        CustomTab(menuPos.x, tmp_y, xorstr(L"DayTime: "), Settings.exploitsConfigs.DayTime);
        CustomTab(menuPos.x, tmp_y, xorstr(L"FirstCamera: "), Settings.exploitsConfigs.FirstCamera);
        CustomTab(menuPos.x, tmp_y, xorstr(L"Floating: "), Settings.exploitsConfigs.Floating);
        CustomTab(menuPos.x, tmp_y, xorstr(L"Chams: "), Settings.exploitsConfigs.Chams);
        CustomTab(menuPos.x, tmp_y, xorstr(L"HeatMapChams: "), Settings.exploitsConfigs.HeatMapChams);
        

        if (inArea(Vector2(menuPos.x - 15, menuPos.y), Vector2(menuPos.x + width, menuPos.y + height))) {
            if (GetAsyncKeyState(VK_LBUTTON)) {

                auto mousePos_tmp = mousePos;
                mousePos_tmp.x -= width; //sizex
                mousePos_tmp.y -= height; //sizey

                if (dragPos.x == 0)
                {
                    dragPos.x = (mousePos_tmp.x - menuPos.x);
                    dragPos.y = (mousePos_tmp.y - menuPos.y);
                }
                menuPos.x = mousePos_tmp.x - dragPos.x;
                menuPos.y = mousePos_tmp.y - dragPos.y;
            }
            else
                dragPos = Vector2(0, 0);
        }
        else
            dragPos = Vector2(0, 0);
    }

    
    Settings.aimConfigsPlayers.FovCircle = 1200;



	if (GetAsyncKeyState(VK_F7))
	{
		fakeunload = true;
	}
	
	return PostRender_O(_this, Canvas);
}

void VirtualTableFunctionSwap(void* VTable, void* FunctionToSwap, void** pOriginal, int Index)
{
    DWORD Old;

    void* pVTableFunction = (void*)((uint64_t)VTable + Index);
    *pOriginal = *(PVOID*)(pVTableFunction);

    VirtualProtectEx((HANDLE)-1, pVTableFunction, 8, PAGE_EXECUTE_READWRITE, &Old);
    *(PVOID*)pVTableFunction = FunctionToSwap;
    VirtualProtectEx((HANDLE)-1, pVTableFunction, 8, Old, &Old);
}


uint32_t overlay::Init()
{
	MessageBoxA(0, xorstr("Init"), 0, MB_ICONINFORMATION);

	auto LocalPlayer = ((UWorld*)(utilities::read<uintptr_t>(sdk::cached::UWorld)))->OwningGameInstance()->LocalPlayers()->LocalPlayer();
	if (!LocalPlayer) return FALSE;

	auto UViewportClient = utilities::read<uintptr_t>(uintptr_t(LocalPlayer) + 0x70);
	if (!UViewportClient) return FALSE;


    //PostRender
	void** PostRender_VTable = *(void***)(UViewportClient);
    DWORD OldProtection;
	VirtualProtect(&PostRender_VTable[107], 8, PAGE_EXECUTE_READWRITE, &OldProtection);
	PostRender_O = decltype(PostRender_O)(PostRender_VTable[107]);
	PostRender_VTable[107] = &PostRender;
	VirtualProtect(&PostRender_VTable[107], 8, OldProtection, &OldProtection);


    //GetPlayerViewPoint
    auto GetPlayerViewPoint_VFTable = *(uintptr_t*)(uintptr_t(LocalPlayer->PlayerController()));
    auto GetPlayerViewPoint_addr = *(uintptr_t*)(GetPlayerViewPoint_VFTable + 0x788);

    //GetViewPoint
    auto GetViewPoint_VFTable = *(uintptr_t*)(uintptr_t(LocalPlayer));

    
    MH_Initialize();

    //GetPlayerViewPoint
    MH_CreateHook((PVOID)GetPlayerViewPoint_addr, exploitsFunctions::hk_GetPlayerViewPoint, reinterpret_cast<PVOID*>(&exploitsFunctions::o_GetPlayerViewPoint));
    MH_EnableHook((PVOID)GetPlayerViewPoint_addr);

    //GetViewPoint
    VirtualTableFunctionSwap((void*)GetViewPoint_VFTable, exploitsFunctions::hk_GetViewPoint, (void**)&exploitsFunctions::o_GetViewPoint, 0x2B0);

    MessageBoxA(0, xorstr("Done"), 0, MB_ICONINFORMATION);




	return TRUE;
}