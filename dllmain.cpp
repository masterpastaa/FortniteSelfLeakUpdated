#include "includes.hpp"


void InitObjects()
{
    //Engine Render
    sdk::cached::objects::K2_DrawLine = sdk::objects::find_object(xorstr(L"Engine.Canvas.K2_DrawLine"));
    if (!sdk::cached::objects::K2_DrawLine) return;

    sdk::cached::objects::K2_DrawBox = sdk::objects::find_object(xorstr(L"Engine.Canvas.K2_DrawBox"));
    if (!sdk::cached::objects::K2_DrawBox) return;

    sdk::cached::objects::Font = sdk::objects::find_object(xorstr(L"/Engine/EngineFonts/Roboto.Roboto"));
    if (!sdk::cached::objects::Font) return;

    sdk::cached::objects::K2_DrawText = sdk::objects::find_object(xorstr(L"Engine.Canvas.K2_DrawText"));
    if (!sdk::cached::objects::K2_DrawText) return;

    sdk::cached::objects::K2_TextSize = sdk::objects::find_object(xorstr(L"Engine.Canvas.K2_TextSize"));
    if (!sdk::cached::objects::K2_TextSize) return;

    //Main Functions
    sdk::cached::objects::WasInputKeyJustPressed = sdk::objects::find_object(xorstr(L"Engine.PlayerController.WasInputKeyJustPressed"));
    if (!sdk::cached::objects::WasInputKeyJustPressed) return;

    sdk::cached::objects::IsInputKeyDown = sdk::objects::find_object(xorstr(L"Engine.PlayerController.IsInputKeyDown"));
    if (!sdk::cached::objects::IsInputKeyDown) return;

    sdk::cached::objects::GetMousePosition = sdk::objects::find_object(xorstr(L"Engine.PlayerController.GetMousePosition"));
    if (!sdk::cached::objects::GetMousePosition) return;

    sdk::cached::objects::dingus = sdk::objects::find_object(xorstr(L"PlayerPawn_Athena.PlayerPawn_Athena_C_.ApplyPawnHighlight"));
    if (!sdk::cached::objects::dingus) return;

    sdk::cached::objects::GetActorBounds = sdk::objects::find_object(xorstr(L"Engine.Actor.GetActorBounds"));
    if (!sdk::cached::objects::GetActorBounds) return;

    sdk::cached::objects::K2_SetActorLocation = sdk::objects::find_object(xorstr(L"Engine.Actor.K2_SetActorLocation"));
    if (!sdk::cached::objects::K2_SetActorLocation) return;

    sdk::cached::objects::GetMuzzleLocation = sdk::objects::find_object(xorstr(L"FortniteGame.FortWeapon.GetMuzzleLocation"));
    if (!sdk::cached::objects::GetMuzzleLocation) return;

    sdk::cached::objects::GetVelocity = sdk::objects::find_object(xorstr(L"Engine.Actor.GetVelocity"));
    if (!sdk::cached::objects::GetVelocity) return;

    sdk::cached::objects::ClientSetCameraMode = sdk::objects::find_object(xorstr(L"Engine.PlayerController.ClientSetCameraMode"));
    if (!sdk::cached::objects::ClientSetCameraMode) return;

    sdk::cached::objects::SetVisibility = sdk::objects::find_object(xorstr(L"Engine.SceneComponent.SetVisibility"));
    if (!sdk::cached::objects::SetVisibility) return;

    sdk::cached::objects::SetWeaponVisibility = sdk::objects::find_object(xorstr(L"FortniteGame.FortWeapon.SetWeaponVisibility"));
    if (!sdk::cached::objects::SetWeaponVisibility) return;

    sdk::cached::objects::SetCharacterBodyVisibilityForPossession = sdk::objects::find_object(xorstr(L"FortniteGame.FortPlayerPawnAthena.SetCharacterBodyVisibilityForPossession"));
    if (!sdk::cached::objects::SetCharacterBodyVisibilityForPossession) return;

    sdk::cached::objects::ClientSetViewTarget = sdk::objects::find_object(xorstr(L"Engine.PlayerController.ClientSetViewTarget"));
    if (!sdk::cached::objects::ClientSetViewTarget) return;

    sdk::cached::objects::GetPlatform = sdk::objects::find_object(xorstr(L"FortniteGame.FortPlayerState.GetPlatform"));
    if (!sdk::cached::objects::GetPlatform) return;

    sdk::cached::objects::IsDead = sdk::objects::find_object(xorstr(L"FortniteGame.FortPawn.IsDead"));
    if (!sdk::cached::objects::IsDead) return;


    //Floating
    sdk::cached::objects::StartFloating = sdk::objects::find_object(xorstr(L"FortniteGame.FortPlayerPawn.StartFloating"));
    if (!sdk::cached::objects::StartFloating) return;

    sdk::cached::objects::EndFloating = sdk::objects::find_object(xorstr(L"FortniteGame.FortPlayerPawn.EndFloating"));
    if (!sdk::cached::objects::EndFloating) return;


    //SetTimeOfDay
    sdk::cached::objects::FortKismetLibrary = sdk::objects::find_object(xorstr(L"FortniteGame.FortKismetLibrary"));
    if (!sdk::cached::objects::FortKismetLibrary) return;

    sdk::cached::objects::SetTimeOfDay = sdk::objects::find_object(xorstr(L"FortniteGame.FortKismetLibrary.SetTimeOfDay"));
    if (!sdk::cached::objects::SetTimeOfDay) return;


    //ConvertToFName
    sdk::cached::objects::KismetStringLibrary = sdk::objects::find_object(xorstr(L"Engine.KismetStringLibrary"));
    if (!sdk::cached::objects::KismetStringLibrary) return;

    sdk::cached::objects::Conv_StringToName = sdk::objects::find_object(xorstr(L"Engine.KismetStringLibrary.Conv_StringToName"));
    if (!sdk::cached::objects::Conv_StringToName) return;



    //Actors Classes
    sdk::cached::classes::FortPlayerPawnAthena = sdk::objects::find_object(xorstr(L"FortniteGame.FortPlayerPawnAthena"));
    if (!sdk::cached::classes::FortPlayerPawnAthena) return;

    sdk::cached::classes::FortPickup = sdk::objects::find_object(xorstr(L"FortniteGame.FortPickupAthena"));
    if (!sdk::cached::classes::FortPickup) return;

    sdk::cached::classes::BuildingContainer = sdk::objects::find_object(xorstr(L"FortniteGame.BuildingContainer"));
    if (!sdk::cached::classes::BuildingContainer) return;

    sdk::cached::classes::FortProjectileBase = sdk::objects::find_object(xorstr(L"FortniteGame.FortProjectileBase"));
    if (!sdk::cached::classes::FortProjectileBase) return;


    return;
}

void Init()
{
    // Image Info
    sdk::cached::Base = utilities::imageBase();

    // UWorld
    sdk::cached::UWorld = utilities::scan(sdk::cached::Base, xorstr("48 89 05 ? ? ? ? 48 8B 4B 78"));
    sdk::cached::UWorld = RELATIVE(sdk::cached::UWorld, 7);
    if (!sdk::cached::UWorld) return;

    // FreeFn
    sdk::cached::FreeFn = utilities::scan(sdk::cached::Base, xorstr("48 85 C9 0F 84 ? ? ? ? 53 48 83 EC 20 48 89 7C 24 30 48 8B D9 48 8B 3D ? ? ? ? 48 85 FF 0F 84 ? ? ? ? 48 8B 07 4C 8B 40 30 48 8D 05 ? ? ? ? 4C 3B C0"));
    if (!sdk::cached::FreeFn) return;

    // GetObjectName
    sdk::cached::GetNameByIndex = utilities::scan(sdk::cached::Base, xorstr("48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B F2 4C 8B F1 E8 ? ? ? ? 45 8B 06 33 ED 41 0F B7 16 41 C1 E8 10 89 54 24 24 44 89 44 24 ? 48 8B 4C 24 ? 48 C1 E9 20 8D 3C 09 4A 03 7C C0 ? 0F B7 17 C1 EA 06 41 39 6E 04"));
    if (!sdk::cached::GetNameByIndex) return;

    //GObjects
    auto objects = utilities::scan(sdk::cached::Base, xorstr("48 8B 05 ? ? ? ? 48 8B 0C C8 48 8B 04 D1"));
    sdk::classes::objects = decltype(sdk::classes::objects)(RELATIVE(objects, 7));

    // LineSightOfTo
    sdk::cached::LineSightOfTo = utilities::scan(sdk::cached::Base, xorstr("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 8A E9"));
    if (!sdk::cached::LineSightOfTo) return;

    // GetBoneMatrix
    sdk::cached::GetBoneMatrix = utilities::scan(sdk::cached::Base, xorstr("E8 ? ? ? ? 48 8B 47 30 F3 0F 10 45"));
    sdk::cached::GetBoneMatrix = RELATIVE(sdk::cached::GetBoneMatrix, 5);
    if (!sdk::cached::GetBoneMatrix) return;

    // ProjectWorldToScreen
    sdk::cached::ProjectWorldToScreen = utilities::scan(sdk::cached::Base, xorstr("40 53 55 56 57 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 33 DB"));
    if (!sdk::cached::ProjectWorldToScreen) return;

    //InitObjects
    InitObjects();

    //Render
    overlay::Init();
}

bool __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return false;

    Init();

    return true;
}