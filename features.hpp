#pragma once

namespace exploitsVars {
	AFortPawn* TargetPawn;
	sdk::structs::FRotator o_CamRot;
}

namespace exploitsFunctions {

	void(*o_GetViewPoint)(uintptr_t, sdk::structs::FMinimalViewInfo*, BYTE) = nullptr;
	void hk_GetViewPoint(uintptr_t this_LocalPlayer, sdk::structs::FMinimalViewInfo* OutViewInfo, BYTE StereoPass)
	{
		if (fakeunload) {
			return o_GetViewPoint(this_LocalPlayer, OutViewInfo, StereoPass);
		}

		o_GetViewPoint(this_LocalPlayer, OutViewInfo, StereoPass);

		if (Settings.aimConfigsPlayers.Silent)
		{
			if (GetAsyncKeyState(VK_RBUTTON)) {
				OutViewInfo->Rotation = exploitsVars::o_CamRot;
			}
		}

		OutViewInfo->FOV = 100.f;
	}

	sdk::structs::FVector calculate_prediction(AFortPawn* LocalPawn, AFortPawn* Target)
	{
		//Get the enemy location
		auto targetPosition = Target->GetBone(68);

		//Get the local location
		auto localPosition = LocalPawn->GetBone(68);

		//Calculate the difference
		sdk::structs::FVector Difference = targetPosition;
		Difference.X -= localPosition.X;
		Difference.Y -= localPosition.Y;
		Difference.Z -= localPosition.Z;
		
		//Calculate the distance
		float dist = utilities::custom_sqrtf(Difference.X * Difference.X + Difference.Y * Difference.Y + Difference.Z * Difference.Z);

		//Calculate the Scale Value
		auto Ping = LocalPawn->PlayerState()->CompressedPing() * 4;
		auto ScaleValue = float(Ping) + float(dist * 0.0193f);
		if (ScaleValue < 1.0f) ScaleValue = 1.0;
		
		//Get the enemy velocity
		auto Velocity = Target->GetVelocity();

		//Calculate the velocity
		float fVelocity = utilities::custom_sqrtf(Velocity.X * Velocity.X + Velocity.Y * Velocity.Y + Velocity.Z * Velocity.Z);

		if (fVelocity > 100.0f) 
		{
			Velocity.X *= ScaleValue / fVelocity; Velocity.Y *= ScaleValue / fVelocity; Velocity.Z *= ScaleValue / fVelocity;

			//Add the calculated values to the original target location
			targetPosition.X += Velocity.X;
			targetPosition.Y += Velocity.Y;
			targetPosition.Z += Velocity.Z;
		}

		return targetPosition;

	}
	
	void(*o_GetPlayerViewPoint)(uintptr_t, sdk::structs::FVector*, sdk::structs::FRotator*) = nullptr;
	void hk_GetPlayerViewPoint(uintptr_t this_PlayerController, sdk::structs::FVector* Location, sdk::structs::FRotator* Rotation) {

		if (fakeunload) {
			return o_GetPlayerViewPoint(this_PlayerController, Location, Rotation);
		}

		o_GetPlayerViewPoint(this_PlayerController, Location, Rotation);

		if (Settings.aimConfigsPlayers.Memory || Settings.aimConfigsPlayers.Silent)
		{
			exploitsVars::o_CamRot = *Rotation;

			sdk::cached::PlayerController = ((UWorld*)(utilities::read<uintptr_t>(sdk::cached::UWorld)))->OwningGameInstance()->LocalPlayers()->LocalPlayer()->PlayerController();
			auto LocalPawn = sdk::cached::PlayerController->LocalPawn();
			if (LocalPawn)
			{
				if (GetAsyncKeyState(VK_RBUTTON))
				{
					if (exploitsVars::TargetPawn)
					{

						auto rootHead = exploitsVars::TargetPawn->GetBone(68);
						sdk::structs::FVector camloc = *Location;

						if (Settings.aimConfigsPlayers.SniperPrediction)
						{
							rootHead = calculate_prediction(LocalPawn, exploitsVars::TargetPawn);
						}

						sdk::structs::FVector VectorPos;
						VectorPos.X = rootHead.X - camloc.X;
						VectorPos.Y = rootHead.Y - camloc.Y;
						VectorPos.Z = rootHead.Z - camloc.Z;

						float distance = (double)(utilities::custom_sqrtf(VectorPos.X * VectorPos.X + VectorPos.Y * VectorPos.Y + VectorPos.Z * VectorPos.Z));

						sdk::structs::FRotator rot;
						rot.Pitch = -((utilities::custom_acosf(VectorPos.Z / distance) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510)) - 90.f);
						rot.Yaw = utilities::custom_atan2f(VectorPos.Y, VectorPos.X) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510);
						rot.Roll = 0;

						*Rotation = rot;
					}
				}
			}
		}
	}
}




bool Floating_Disabled = true;
bool FirstCamera_Disabled = true;







int PlayersCpp() {

	AFortPawn* closestActor = 0;
	float closestDist = FLT_MAX;

	auto GWorld = utilities::read<uintptr_t>(sdk::cached::UWorld);
	auto World = (UWorld*)GWorld;
	sdk::cached::PlayerController = World->OwningGameInstance()->LocalPlayers()->LocalPlayer()->PlayerController();
	auto LocalPawn = sdk::cached::PlayerController->LocalPawn();

	auto PersistentLevel = World->PersistentLevel();


	
	sdk::structs::FVector LocalPawn_loc = LocalPawn->GetBone(68);


	auto levels = World->Levels();

	for (int a = 0; a < levels.Num(); a++)
	{
		auto actors = levels[a]->ActorArray();

		for (int i = 0; i < actors.Num(); i++)
		{
			auto actor = actors[i];
			if (!actor || actor == LocalPawn)
				continue;


			if (Settings.aimConfigsPlayers.BulletTP)
			{
				if (closestActor)
				{
					if (actor->IsA(sdk::cached::classes::FortProjectileBase))
					{
						if (utilities::custom_wcsstr(actor->ObjectName(), xorstr(L"B_Prj_Bullet_Sniper")))
						{
							actor->K2_SetActorLocation(closestActor->GetBone(68), false, true); //68
						}
					}
				}
			}

			if (actor->IsA(sdk::cached::classes::FortPlayerPawnAthena))
			{
				if (actor->IsDead()) continue;

				if (Settings.exploitsConfigs.Chams)
				{
					actor->Dingus(color(255.f, 0.f, 0.f, 255.f), color(255.f, 0.f, 0.f, 255.f));
				}
				if (Settings.exploitsConfigs.HeatMapChams)
				{
					actor->Dingus(color(1.f, 0.f, 0.f, 1.f), color(0.f, 1.f, 0.f, 1.f));
				}



				auto isVisible = sdk::cached::PlayerController->IsVisible(actor);

				auto WorldHead = actor->GetBone(68);
				auto Head = sdk::cached::PlayerController->WorldToScreen(WorldHead);

				if (LocalPawn) {

					auto dx = Head.x - (width / 2);
					auto dy = Head.y - (height / 2);
					auto dist = utilities::custom_sqrtf(dx * dx + dy * dy);

					if (dist < Settings.aimConfigsPlayers.FovCircle && dist < closestDist) {
						closestDist = dist;
						closestActor = actor;
					}
				}


				auto Top = sdk::cached::PlayerController->WorldToScreen({ WorldHead.X, WorldHead.Y, WorldHead.Z + 20 });
				auto Bottom = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(0));

				float TextOffset_Top = Top.y + 5;
				float TextOffset_Bottom = Bottom.y;

				color col = color(1.f, 0, 0, 1.f);

				//if (isVisible)
				//	col = color(0, 255, 0, 255);

				if (Settings.visualsConfigsPlayers.ESP)
				{
					if (Settings.visualsConfigsPlayers.Box2D)
					{
						float Height = Bottom.y - Top.y;
						float Width = Height * 0.55;

						Vector2 min;
						min.x = Bottom.x + Width / 2;
						min.y = Bottom.y;

						Vector2 max;
						max.x = Top.x - Width / 2;
						max.y = Top.y;

						Vector2 size;
						size.x = min.x - max.x;
						size.y = min.y - max.y;

						Render::DrawRect(max, size, col);
					}

					if (Settings.visualsConfigsPlayers.Box3D)
					{
						sdk::structs::FVector WorldOrigin;
						sdk::structs::FVector WorldBoxExtent;
						actor->GetActorBounds(bool(LocalPawn), false, &WorldOrigin, &WorldBoxExtent);

						Render::Box3D(sdk::cached::PlayerController, WorldOrigin, WorldBoxExtent, col);
					}


					if (Settings.visualsConfigsPlayers.Skeleton)
					{
						auto head = Head;
						auto neck = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(66));
						auto rightChest = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(8));
						auto leftChest = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(37));
						auto leftShoulder = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(38));
						auto rightShoulder = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(9));
						auto leftElbow = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(94));
						auto rightElbow = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(10));
						auto leftWrist = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(62));
						auto rightWrist = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(33));
						auto pelvis = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(2));
						auto leftAss = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(76));
						auto rightAss = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(69));
						auto leftKnee = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(77));
						auto rightKnee = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(70));
						auto leftAnkle = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(78));
						auto rightAnkle = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(71));

						Render::DrawLine(neck, leftChest, col, 1, true);
						Render::DrawLine(neck, rightChest, col, 1, true);
						Render::DrawLine(leftChest, leftShoulder, col, 1, true);
						Render::DrawLine(rightChest, rightShoulder, col, 1, true);
						Render::DrawLine(leftShoulder, leftElbow, col, 1, true);
						Render::DrawLine(rightShoulder, rightElbow, col, 1, true);
						Render::DrawLine(leftElbow, leftWrist, col, 1, true);
						Render::DrawLine(rightElbow, rightWrist, col, 1, true);
						Render::DrawLine(neck, pelvis, col, 1, true);
						Render::DrawLine(pelvis, leftAss, col, 1, true);
						Render::DrawLine(pelvis, rightAss, col, 1, true);
						Render::DrawLine(leftAss, leftKnee, col, 1, true);
						Render::DrawLine(rightAss, rightKnee, col, 1, true);
						Render::DrawLine(leftKnee, leftAnkle, col, 1, true);
						Render::DrawLine(rightKnee, rightAnkle, col, 1, true);
					}

					if (Settings.visualsConfigsPlayers.Lines)
					{
						auto enemyScreen = sdk::cached::PlayerController->WorldToScreen(actor->GetBone(2));

						Render::DrawLine(Vector2(width / 2, height), enemyScreen, col, 1, true);
					}

					if (Settings.visualsConfigsPlayers.Names)
					{
						auto name = xorstr(L"kreugher_1337");

						TextOffset_Top -= sdk::cached::Canvas->K2_TextSize(name).y;
						Vector2 calculation = Vector2(Top.x, TextOffset_Top);

						Render::DrawStrokeText(calculation, col, name);
					}

					if (Settings.visualsConfigsPlayers.Weapon)
					{
						auto weapon_data = actor->CurrentWeapon()->WeaponData();
						if (!weapon_data) continue;

						auto _name = weapon_data->DisplayName();
						if (!_name) continue;

						auto tier = weapon_data->Tier();
						auto name = _name->c_str();
						if (!name) continue;

						TextOffset_Bottom += sdk::cached::Canvas->K2_TextSize(name).y;
						auto calculation = Vector2(Bottom.x, TextOffset_Bottom);

						Render::DrawStrokeText(calculation, utilities::getColorFromTier(tier), name);
					}

					if (Settings.visualsConfigsPlayers.Distance)
					{
						int dist = WorldHead.getDistance(LocalPawn_loc);

						auto text = std::wstring(xorstr(L"[")) + std::to_wstring(dist) + std::wstring(xorstr(L"m]"));

						TextOffset_Bottom += sdk::cached::Canvas->K2_TextSize(text.c_str()).y;
						auto calculation = Vector2(Bottom.x, TextOffset_Bottom);

						Render::DrawStrokeText(calculation, col, text.c_str());
					}

					if (Settings.visualsConfigsPlayers.Platform)
					{
						auto platform = actor->PlayerState()->GetPlatform();
						if (!platform.IsValid()) continue;

						auto platform_name = platform.c_str();

						if (utilities::custom_wcsstr(platform_name, xorstr(L"PSN"))) {
							Render::DrawStrokeText(Head, color(1.f, 1.f, 0.f, 1.f), xorstr(L"PlayStation"));
						}
						else if (utilities::custom_wcsstr(platform_name, xorstr(L"XBL"))) {
							Render::DrawStrokeText(Head, color(1.f, 1.f, 0.f, 1.f), xorstr(L"Xbox"));
						}
						else if (utilities::custom_wcsstr(platform_name, xorstr(L"WIN"))) {
							Render::DrawStrokeText(Head, color(1.f, 1.f, 0.f, 1.f), xorstr(L"Windows"));
						}
						else if (utilities::custom_wcsstr(platform_name, xorstr(L"MAC"))) {
							Render::DrawStrokeText(Head, color(1.f, 1.f, 0.f, 1.f), xorstr(L"MacOS"));
						}
						else if (utilities::custom_wcsstr(platform_name, xorstr(L"LNX"))) {
							Render::DrawStrokeText(Head, color(1.f, 1.f, 0.f, 1.f), xorstr(L"Linux"));
						}
						else if (utilities::custom_wcsstr(platform_name, xorstr(L"IOS"))) {
							Render::DrawStrokeText(Head, color(1.f, 1.f, 0.f, 1.f), xorstr(L"Ios"));
						}
						else if (utilities::custom_wcsstr(platform_name, xorstr(L"AND"))) {
							Render::DrawStrokeText(Head, color(1.f, 1.f, 0.f, 1.f), xorstr(L"Android"));
						}
						else if (utilities::custom_wcsstr(platform_name, xorstr(L"SWT"))) {
							Render::DrawStrokeText(Head, color(1.f, 1.f, 0.f, 1.f), xorstr(L"NintendoSwitch"));
						}
						else {
							Render::DrawStrokeText(Head, color(1.f, 1.f, 0.f, 1.f), platform_name);
						}
					}
				}
			}

			if (Settings.visualsConfigsWorld.ESP)
			{
				if (Settings.visualsConfigsWorld.Loot)
				{
					if (actor->IsA(sdk::cached::classes::FortPickup))
					{
						auto loc = actor->RootComponent()->RelativeLocation();

						int dist = loc.getDistance(LocalPawn_loc);
						if (dist > 120) continue;

						auto item = actor->ItemDefinition();
						if (!item) continue;

						auto _name = item->DisplayName();
						if (!_name) continue;

						auto name = _name->c_str();
						if (!name) continue;

						if (utilities::custom_wcsstr(name, xorstr(L"Ammo: "))) continue;

						auto screen = sdk::cached::PlayerController->WorldToScreen(loc);
						Render::DrawStrokeText(screen, utilities::getColorFromTier(item->Tier()), (std::wstring(name) + xorstr(L" [") + std::to_wstring(dist) + xorstr(L"m]")).c_str());
					}
				}

				if (Settings.visualsConfigsWorld.Chest || Settings.visualsConfigsWorld.AmmoBox)
				{
					if (actor->IsA(sdk::cached::classes::BuildingContainer))
					{
						auto loc = actor->RootComponent()->RelativeLocation();

						int dist = loc.getDistance(LocalPawn_loc);
						if (dist > 120) continue;

						//Get Classes the first time
						if (!sdk::cached::classes::Tiered_Chest)
						{
							auto currentClass = ((sdk::classes::UObject*)actor)->Class;
							auto currentClassName = sdk::objects::get_object_name((sdk::classes::UObject*)currentClass);
							if (utilities::custom_wcsstr(currentClassName, xorstr(L"Tiered_Chest")))
							{
								sdk::cached::classes::Tiered_Chest = PVOID(currentClass);
							}
						}
						if (!sdk::cached::classes::Tiered_Ammo)
						{
							auto currentClass = ((sdk::classes::UObject*)actor)->Class;
							auto currentClassName = sdk::objects::get_object_name((sdk::classes::UObject*)currentClass);
							if (utilities::custom_wcsstr(currentClassName, xorstr(L"Tiered_Ammo")))
							{
								sdk::cached::classes::Tiered_Ammo = PVOID(currentClass);
							}
						}

						if (actor->bAlreadySearched()) continue;

						auto screen = sdk::cached::PlayerController->WorldToScreen(loc);

						if (Settings.visualsConfigsWorld.Chest)
						{
							if (sdk::cached::classes::Tiered_Chest && actor->IsA(sdk::cached::classes::Tiered_Chest))
							{
								Render::DrawStrokeText(screen, color(1.f, 1.f, 0, 1.f), (std::wstring(xorstr(L"Chest")) + xorstr(L" [") + std::to_wstring(dist) + xorstr(L"m]")).c_str());
							}
						}

						if (Settings.visualsConfigsWorld.AmmoBox)
						{
							if (sdk::cached::classes::Tiered_Ammo && actor->IsA(sdk::cached::classes::Tiered_Ammo))
							{
								Render::DrawStrokeText(screen, color(1.f, 1.f, 1.f, 1.f), (std::wstring(xorstr(L"AmmoBox")) + xorstr(L" [") + std::to_wstring(dist) + xorstr(L"m]")).c_str());
							}
						}
					}
				}
				
			}
		}

		
	}


	if (LocalPawn)
	{
		if (closestActor)
		{
			sdk::structs::FViewTargetTransitionParams TransitionParams;
			TransitionParams.BlendTime = 1.f;
			TransitionParams.BlendExp = 2.f;
			TransitionParams.BlendFunction = sdk::structs::EViewTargetBlendFunction::VTBlend_EaseIn;
			TransitionParams.bLockOutgoing = true;

			if (GetAsyncKeyState(VK_F8) & 1)
			{
				sdk::cached::PlayerController->ClientSetViewTarget(closestActor, TransitionParams);
			}
			if (GetAsyncKeyState(VK_F9) & 1)
			{
				sdk::cached::PlayerController->ClientSetViewTarget(LocalPawn, TransitionParams);
			}
			

			//if (GetAsyncKeyState(VK_RBUTTON))
				exploitsVars::TargetPawn = closestActor;
			//else
			//	exploitsVars::TargetPawn = 0;


			if (Settings.visualsConfigsPlayers.ESP)
			{
				if (Settings.visualsConfigsPlayers.TargetLine)
				{
					if (GetAsyncKeyState(VK_RBUTTON))
					{
						auto weapon = LocalPawn->CurrentWeapon();
						if (!weapon) return false;

						auto weapon_data = LocalPawn->CurrentWeapon()->WeaponData();
						if (!weapon_data) return false;

						auto _name = weapon_data->DisplayName();
						if (!_name) return false;

						auto name = _name->c_str();
						if (!name) return false;

						if (!utilities::custom_wcsstr(name, xorstr(L"Harvesting")))
						{
							sdk::structs::FVector WorldMuzzle = weapon->GetMuzzleLocation(0);
							auto localScreen = sdk::cached::PlayerController->WorldToScreen(WorldMuzzle);

							auto enemyScreen = sdk::cached::PlayerController->WorldToScreen(closestActor->GetBone(2));


							color col = color(1.f, 0, 0, 1.f);

							if (utilities::IsInScreen(localScreen) && utilities::IsInScreen(enemyScreen))
								Render::DrawLine(localScreen, enemyScreen, col, 1);
						}
					}					
				}
			}
		}
		else
			exploitsVars::TargetPawn = 0;



		if (Settings.exploitsConfigs.DayTime)
		{
			World->SetTimeOfDay(Settings.exploitsConfigs.DayTime_value);
		}

		if (Settings.exploitsConfigs.Floating)
		{
			LocalPawn->StartFloating();
			Floating_Disabled = false;
		}
		else {
			if (!Floating_Disabled)
			{
				LocalPawn->EndFloating();
				Floating_Disabled = true;
			}
		}


		if (Settings.exploitsConfigs.FirstCamera)
		{
			sdk::cached::PlayerController->ClientSetCameraMode(sdk::objects::Conv_StringToName(xorstr(L"FirstPerson")));
			LocalPawn->SetCharacterBodyVisibilityForPossession(false);
			FirstCamera_Disabled = false;
		}
		else {
			if (!FirstCamera_Disabled)
			{
				sdk::cached::PlayerController->ClientSetCameraMode(sdk::objects::Conv_StringToName(xorstr(L"Default")));
				LocalPawn->SetCharacterBodyVisibilityForPossession(true);
				FirstCamera_Disabled = true;
			}
		}
		

	}
	else
		exploitsVars::TargetPawn = 0;

	//Return inGame
	return bool(LocalPawn);
}