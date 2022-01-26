#pragma once
#include <fstream>

namespace sdk::cached
{
	inline uintptr_t Base = 0;
	inline uintptr_t UWorld = 0;
	inline uintptr_t FreeFn = 0;
	inline uintptr_t GetNameByIndex = 0;
	inline uintptr_t LineSightOfTo = 0;
	inline uintptr_t GetBoneMatrix = 0;
	inline uintptr_t ProjectWorldToScreen = 0;

	namespace objects
	{
		//Engine Render
		inline PVOID Font = 0;
		inline PVOID K2_DrawLine = 0;
		inline PVOID K2_DrawBox = 0;
		inline PVOID K2_DrawText = 0;
		inline PVOID K2_TextSize = 0;

		//Main Functions
		inline PVOID WasInputKeyJustPressed = 0;
		inline PVOID IsInputKeyDown = 0;
		inline PVOID GetMousePosition = 0;
		inline PVOID dingus = 0;
		inline PVOID GetActorBounds = 0;
		inline PVOID K2_SetActorLocation = 0;
		inline PVOID GetMuzzleLocation = 0;
		inline PVOID GetVelocity = 0;
		inline PVOID ClientSetCameraMode = 0;
		inline PVOID SetVisibility = 0;
		inline PVOID SetWeaponVisibility = 0;
		inline PVOID SetCharacterBodyVisibilityForPossession = 0;
		inline PVOID ClientSetViewTarget = 0;
		inline PVOID GetPlatform = 0;
		inline PVOID IsDead = 0;

		//Floating
		inline PVOID StartFloating = 0;
		inline PVOID EndFloating = 0;

		//SetTimeOfDay
		inline PVOID FortKismetLibrary = 0;
		inline PVOID SetTimeOfDay = 0;

		//ConvertToFName
		inline PVOID KismetStringLibrary = 0;
		inline PVOID Conv_StringToName = 0;
	}

	namespace classes
	{
		//Actors Classes
		inline PVOID FortPlayerPawnAthena = 0;
		inline PVOID FortPickup = 0;
		inline PVOID BuildingContainer = 0;
		inline PVOID FortProjectileBase = 0;

		//Not real classes in ue4
		inline PVOID Tiered_Chest = 0;
		inline PVOID Tiered_Ammo = 0;
	}
}



namespace sdk::structs
{
	struct FMatrix
	{
		float M[ 4 ][ 4 ];
	};
	static FMatrix* myMatrix = new FMatrix( );

	template<class T>
	struct TArray
	{
		friend struct FString;

	public:
		inline TArray( )
		{
			Data = nullptr;
			Count = Max = 0;
		};

		inline int Num( ) const
		{
			return Count;
		};

		inline T& operator[]( int i )
		{
			return Data[ i ];
		};

		inline const T& operator[]( int i ) const
		{
			return Data[ i ];
		};

		inline bool IsValidIndex( int i ) const
		{
			return i < Num( );
		}

	private:
		T* Data;
		int32_t Count;
		int32_t Max;
	};

	struct FString : private TArray<wchar_t>
	{
		inline FString( )
		{
		};

		FString( const wchar_t* other )
		{
			Max = Count = *other ? utilities::custom_wcslen( other ) + 1 : 0;

			if ( Count )
			{
				Data = const_cast< wchar_t* >( other );
			}
		};

		inline bool IsValid( ) const
		{
			return Data != nullptr;
		}

		inline const wchar_t* c_str( ) const
		{
			return Data;
		}
	};

	struct FName
	{
		uint32_t ComparisonIndex;
		uint32_t DisplayIndex;
	};

	struct FKey
	{
		FName KeyName;
		unsigned char Padding_00[0x10];
	};

	struct FLinearColor
	{
		float R;
		float G;
		float B;
		float A;
	};

	struct FVector2D
	{
		float X;
		float Y;
	};

	struct FVector
	{
		float X;
		float Y;
		float Z;

		inline float getDistance(const sdk::structs::FVector cmp) {
			if (cmp.X == 0 || cmp.Y == 0 || cmp.Z == 0) return 0;

			float dx = (this->X - cmp.X);
			float dy = (this->Y - cmp.Y);
			float dz = (this->Z - cmp.Z);

			int tmp = (utilities::custom_sqrtf((dx * dx) + (dy * dy) + (dz * dz)));
			return (int)(tmp / 100);
		}
	};

	struct FRotator
	{
		float Pitch;
		float Yaw;
		float Roll;
	};

	struct FMinimalViewInfo {
		sdk::structs::FVector Location;
		sdk::structs::FRotator Rotation;
		float FOV;
		float OrthoWidth;
		float OrthoNearClipPlane;
		float OrthoFarClipPlane;
		float AspectRatio;
	};

	class FText {
	private:
		char _padding_[0x28];
		PWCHAR Name;
		DWORD Length;
	public:

		inline PWCHAR c_str() {
			return Name;
		}
	};

	struct FPawnHighlight
	{
		float                                              Priority_28_E2E1B5344846E187B9C11B863A7F0698;             // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		FLinearColor                                Inner_21_4CC2801147EA190DE16F59B34F36853E;                // 0x0004(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		FLinearColor                                Outer_22_5A1D7D0543D303E8B54B66A7F7BD2E2E;                // 0x0014(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              FresnelBrightness_23_52B0F96447FF640F47DF2895B0602E92;    // 0x0024(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              FresnelExponent_24_B427CF0C441AA37ED49833BF7579DE6D;      // 0x0028(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              UsesPulse_25_E29229F64E540F0617E4C4987AD77605;            // 0x002C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	};

	struct FViewTargetTransitionParams
	{
		float BlendTime;
		int BlendFunction;
		float BlendExp;
		bool bLockOutgoing;
	};

	enum EViewTargetBlendFunction
	{		
		VTBlend_Linear, // Camera does a simple linear interpolation.
		VTBlend_Cubic, // Camera has a slight ease in and ease out, but amount of ease cannot be tweaked.
		VTBlend_EaseIn, // Camera immediately accelerates, but smoothly decelerates into the target.  Ease amount controlled by BlendExp.
		VTBlend_EaseOut, // Camera smoothly accelerates, but does not decelerate into the target.  Ease amount controlled by BlendExp.
		VTBlend_EaseInOut, // Camera smoothly accelerates and decelerates.  Ease amount controlled by BlendExp.
		VTBlend_PreBlended, // The game's camera system has already performed the blending. Engine should not blend at all
		VTBlend_MAX,
	};

	class AHUD
	{
	public:
		unsigned char Padding_d24Be[0x228];
		char bLostFocusPaused : 1; // 0x228(0x1)
		char bShowHUD : 1; // 0x228(0x1)
		char bShowDebugInfo : 1; // 0x228(0x1)
		unsigned char UnknownBuffer_HaB72 : 5; // 0x228(0x1)
		unsigned char UnknownBuffer_7vY26[0x3]; // 0x229(0x3)
		int32_t CurrentTargetIndex; // 0x22c(0x4)
		char bShowHitBoxDebugInfo : 1; // 0x230(0x1)
		char bShowOverlays : 1; // 0x230(0x1)
		char bEnableDebugTextShadow : 1; // 0x230(0x1)
		unsigned char UnknownBuffer_2aNx7 : 5; // 0x230(0x1)
		unsigned char UnknownBuffer_8HAfk[0x7]; // 0x231(0x7)
		TArray<struct AActor*> PostRenderedActors; // 0x238(0x10)
		unsigned char UnknownBuffer_h7Nua[0x8]; // 0x248(0x8)
		TArray<struct FName> DebugDisplay; // 0x250(0x10)
		TArray<struct FName> ToggledDebugCategories; // 0x260(0x10)
		uintptr_t Canvas; // 0x270(0x8)
		uintptr_t DebugCanvas; // 0x278(0x8)
	};
}

namespace sdk::classes
{
	class UClass {
	public:
		BYTE _padding_0[ 0x40 ];
		UClass* SuperClass;
	};

	class UObject {
	public:
		PVOID VTableObject;
		DWORD ObjectFlags;
		DWORD InternalIndex;
		UClass* Class;
		BYTE _padding_0[ 0x8 ];
		UObject* Outer;

		inline BOOLEAN IsA( PVOID parentClass )
		{
			for ( auto super = this->Class; super; super = super->SuperClass )
				if ( super == parentClass )
					return true;

			return false;
		}
	};

	class FUObjectItem {
	public:
		UObject* Object;
		DWORD Flags;
		DWORD ClusterIndex;
		DWORD SerialNumber;
		DWORD SerialNumber2;
	};

	class TUObjectArray {
	public:
		FUObjectItem* Objects[ 9 ];
	};

	class GObjects {
	public:
		TUObjectArray* ObjectArray;
		BYTE _padding_0[ 0xC ];
		DWORD ObjectCount;
	};

	inline GObjects* objects = nullptr;
}

namespace sdk::objects
{
	inline void free_object( uintptr_t address )
	{
		if (!utilities::isValidPointer(address)) return;
		auto function = reinterpret_cast<void(__fastcall*)(__int64)>(cached::FreeFn);
		return SpoofCall(function, (__int64)address);
	}

	inline const wchar_t* get_name_by_index(int idx)
	{
		std::wstring name = xorstr(L"");

		if (!idx) return xorstr(L"");

		auto function = reinterpret_cast<structs::FString * (__fastcall*)(int* index, structs::FString * res)>(cached::GetNameByIndex);

		int index = idx;

		structs::FString fObjectName;
		SpoofCall(function, &index, &fObjectName);

		if (!fObjectName.IsValid()) return xorstr(L"");

		auto objectName = fObjectName.c_str();

		name = objectName;
		free_object((uintptr_t)fObjectName.c_str());

		return name.c_str();
	}

	inline const wchar_t* get_object_name(classes::UObject* object)
	{
		std::wstring name = xorstr(L"");

		if (!object) return xorstr(L"");

		auto function = reinterpret_cast<structs::FString * (__fastcall*)(int* index, structs::FString * res)>(cached::GetNameByIndex);

		int index = utilities::read<int>(reinterpret_cast<uint64_t>(object) + 0x18);

		structs::FString fObjectName;
		SpoofCall(function, &index, &fObjectName);

		if (!fObjectName.IsValid()) return xorstr(L"");

		auto objectName = fObjectName.c_str();

		name = objectName;
		free_object((uintptr_t)fObjectName.c_str());

		return name.c_str();
	}

	inline const wchar_t* get_full_object_name(classes::UObject* object)
	{
		std::wstring name = xorstr(L"");

		for (auto i = 0; object; object = object->Outer, i++)
		{
			if (!object) return xorstr(L"");

			auto function = reinterpret_cast<structs::FString * (__fastcall*)(int* index, structs::FString * res)>(cached::GetNameByIndex);

			int index = utilities::read<int>(reinterpret_cast<uint64_t>(object) + 0x18);

			structs::FString fObjectName;
			SpoofCall(function, &index, &fObjectName);

			if (!fObjectName.IsValid()) break;

			auto objectName = fObjectName.c_str();

			name = objectName + std::wstring(i > 0 ? xorstr(L".") : xorstr(L"")) + name;
			free_object((uintptr_t)fObjectName.c_str());
		}

		return name.c_str();
	}

	inline void NumChunks(sdk::classes::TUObjectArray* ObjectArray, int* start, int* end)
	{
		int cStart = 0, cEnd = 0;

		if (!cEnd)
		{
			while (true)
			{
				if (ObjectArray->Objects[cStart] == nullptr)
				{
					cStart++;
				}
				else
				{
					break;
				}
			}

			cEnd = cStart;
			while (true)
			{
				if (ObjectArray->Objects[cEnd] == nullptr)
				{
					break;
				}
				cEnd++;
			}
		}

		*start = cStart;
		*end = cEnd;
	}

	inline sdk::classes::UObject* GetObjByIndex(sdk::classes::TUObjectArray* ObjectArray, int32_t index)
	{
		int cStart = 0, cEnd = 0;
		int chunkIndex, chunkSize = 0xFFFF, chunkPos;
		sdk::classes::FUObjectItem* Object;

		NumChunks(ObjectArray , &cStart, &cEnd);

		chunkIndex = index / chunkSize;
		if (chunkSize * chunkIndex != 0 &&
			chunkSize * chunkIndex == index)
		{
			chunkIndex--;
		}

		chunkPos = cStart + chunkIndex;
		if (chunkPos < cEnd)
		{
			Object = ObjectArray->Objects[chunkPos] + (index - chunkSize * chunkIndex);
			if (!Object) { return nullptr; }

			return Object->Object;
		}

		return nullptr;
	}


	inline const wchar_t* fix_objectname(const wchar_t* objname)
	{
		wchar_t* _4 = (wchar_t*)objname;

		for (int i = 0; i < utilities::custom_wcslen(_4); i++)
		{
			if (_4[i] == L'_')
			{
				if (_4[i + 1] == L'0' ||
					_4[i + 1] == L'1' ||
					_4[i + 1] == L'2' ||
					_4[i + 1] == L'3' ||
					_4[i + 1] == L'4' ||
					_4[i + 1] == L'5' ||
					_4[i + 1] == L'6' ||
					_4[i + 1] == L'7' ||
					_4[i + 1] == L'8' ||
					_4[i + 1] == L'9')
					_4[i] = L'$';

				for (int idx = 1; idx < 7; idx++) {

					if (_4[i + idx] == L'.') break;

					if (_4[i + idx] == L'0' ||
						_4[i + idx] == L'1' ||
						_4[i + idx] == L'2' ||
						_4[i + idx] == L'3' ||
						_4[i + idx] == L'4' ||
						_4[i + idx] == L'5' ||
						_4[i + idx] == L'6' ||
						_4[i + idx] == L'7' ||
						_4[i + idx] == L'8' ||
						_4[i + idx] == L'9') {
						_4[i + idx] = L'$';
					}
				}

			}
		}

		std::wstring str = _4;
		str.erase(std::remove(str.begin(), str.end(), '$'), str.end());
		return str.c_str();
	}

	inline PVOID find_object(const wchar_t* objectname)
	{
		for (auto index = 0x0; index < classes::objects->ObjectCount; index++)
		{
			auto object = GetObjByIndex(classes::objects->ObjectArray, index);
			const wchar_t* tmp_name = get_full_object_name(object);
			const wchar_t* name = fix_objectname(tmp_name);

			if ((utilities::custom_wcsstr(name, objectname)))
			{
				return object;
			}				
		}

		return 0;
	}

	inline bool process_event(uintptr_t address, void* fnobject, void* parms)
	{
		if (!utilities::isValidPointer(address)) return false;
		auto index = *reinterpret_cast<void***>(address); if (!index) return false;
		auto fProcessEvent = static_cast<void(*)(void* address, void* fnobject, void* parms)>(index[0x4B]); if (!fProcessEvent) return false;
		SpoofCall(fProcessEvent, (void*)address, (void*)fnobject, (void*)parms);
		return true;
	}

	inline sdk::structs::FName Conv_StringToName(const wchar_t* String)
	{
		struct
		{
			sdk::structs::FString                                     inString;                                                 // (Parm, ZeroConstructor)
			sdk::structs::FName                                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		} params;

		params.inString = String;

		sdk::objects::process_event((uintptr_t)sdk::cached::objects::KismetStringLibrary, sdk::cached::objects::Conv_StringToName, &params);

		return params.ReturnValue;
	}
}


// Structs

class APlayerState {
public:
	uintptr_t TeamIndex() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return utilities::read<uintptr_t>((uintptr_t)this + 0xF28);
	}

	char CompressedPing() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return utilities::read<char>((uintptr_t)this + 0x220);
	}

	sdk::structs::FString GetPlatform()
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return xorstr(L"");
		
		struct
		{
			sdk::structs::FString                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
		} params;

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::GetPlatform, &params);

		return params.ReturnValue;
	}
};


class AFortItemDefinition {
public:
	sdk::structs::FText* DisplayName() {
		if (!utilities::isValidPointer((uintptr_t)this)) return {};
		return reinterpret_cast<sdk::structs::FText*>(*(uintptr_t*)((uintptr_t)this + 0x88));
	}

	UINT8 Tier() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return utilities::read<UINT8>((uintptr_t)this + 0x6C);
	}
};

class AFortWeapon {
public:
	AFortItemDefinition* WeaponData() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return (AFortItemDefinition*)(utilities::read<uintptr_t>((uintptr_t)this + 0x378));
	}

	sdk::structs::FVector GetMuzzleLocation(int PatternIndex)
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return { 0, 0, 0 };

		struct
		{
			int								PatternIndex;
			sdk::structs::FVector			ReturnValue;
		} params;

		params.PatternIndex = PatternIndex;

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::GetMuzzleLocation, &params);

		return params.ReturnValue;
	}

	void SetWeaponVisibility(bool bDesiredVisibility, bool bForceUpdate)
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return;

		struct
		{
			bool                                               bDesiredVisibility;                                       // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bForceUpdate;                                             // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
		} params;

		params.bDesiredVisibility = bDesiredVisibility;
		params.bForceUpdate = bForceUpdate;

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::SetWeaponVisibility, &params);
	}
};

class ARootComponent {
public:

	sdk::structs::FVector RelativeLocation() {
		if (!utilities::isValidPointer((uintptr_t)this)) return { 0, 0, 0 };
		return utilities::read<sdk::structs::FVector>((uintptr_t)this + 0x11C);
	}

	void SetVisibility(bool bNewVisibility, bool bPropagateToChildren)
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return;

		struct
		{
			bool                                               bNewVisibility;                                           // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bPropagateToChildren;                                     // (Parm, ZeroConstructor, IsPlainOldData)
		} params;

		params.bNewVisibility = bNewVisibility;
		params.bPropagateToChildren = bPropagateToChildren;

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::SetVisibility, &params);
	}
};

class UFortItemDefinition {
public:
	sdk::structs::FText* DisplayName() {
		if (!utilities::isValidPointer(uintptr_t(this))) return 0;
		return reinterpret_cast<sdk::structs::FText*>(utilities::read<uintptr_t>((uintptr_t)this + 0x88));
	}

	BYTE Tier() {
		if (!utilities::isValidPointer(uintptr_t(this))) return false;
		return utilities::read<BYTE>((uintptr_t)this + 0x6C);
	}
};

class AFortPawn {
public:
	const wchar_t* ObjectName() {
		if (!utilities::isValidPointer((uintptr_t)this)) return xorstr(L"");
		return sdk::objects::get_object_name((sdk::classes::UObject*)this);
	}

	uintptr_t Mesh() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return utilities::read<uintptr_t>((uintptr_t)this + 0x280);
	}

	UFortItemDefinition* ItemDefinition() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return (UFortItemDefinition*)(utilities::read<uintptr_t>((uintptr_t)this + (0x2A0 + 0x18)));
	}

	BOOL bAlreadySearched() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return ((utilities::read<BYTE>((uintptr_t)this + 0xdf1) >> 7) & 1); //BuildingContainer.bAlreadySearched
	}

	AFortWeapon* CurrentWeapon() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return (AFortWeapon*)(utilities::read<uintptr_t>((uintptr_t)this + 0x5F8));
	}

	ARootComponent* RootComponent() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return (ARootComponent*)(utilities::read<uintptr_t>((uintptr_t)this + 0x130));
	}

	APlayerState* PlayerState() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return (APlayerState*)(utilities::read<uintptr_t>((uintptr_t)this + 0x238));
	}

	BOOL IsA(PVOID parentClass)
	{
		if (!utilities::isValidPointer(uintptr_t(this))) return false;

		sdk::classes::UObject* object = (sdk::classes::UObject*)this;
		for (auto super = object->Class; super; super = super->SuperClass)
			if (super == parentClass)
				return true;

		return false;
	}

	void Dingus(color InnerCol, color OuterCol)
	{
		if (!utilities::isValidPointer(uintptr_t(this))) return;
		
		struct APlayerPawn_Athena_C_ApplyPawnHighlight_Params
		{
			uintptr_t Source;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
			sdk::structs::FPawnHighlight                              HitGlow;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
		} params;

		sdk::structs::FPawnHighlight HitGlow;

		HitGlow.FresnelBrightness_23_52B0F96447FF640F47DF2895B0602E92 = 0.f;
		HitGlow.FresnelExponent_24_B427CF0C441AA37ED49833BF7579DE6D = 0;
		HitGlow.Inner_21_4CC2801147EA190DE16F59B34F36853E = { (float)InnerCol.R, (float)InnerCol.G, (float)InnerCol.B, (float)InnerCol.A };//{ 1.f, 0.f, 0.f, 1.f };//{ (float)col.R, (float)col.G, (float)col.B, (float)col.A };
		HitGlow.Outer_22_5A1D7D0543D303E8B54B66A7F7BD2E2E = { (float)OuterCol.R, (float)OuterCol.G, (float)OuterCol.B, (float)OuterCol.A };//{ 0.f, 1.f, 0.f, 1.f };//{ (float)col.R, (float)col.G, (float)col.B, (float)col.A };
		HitGlow.Priority_28_E2E1B5344846E187B9C11B863A7F0698 = 0.f;
		HitGlow.UsesPulse_25_E29229F64E540F0617E4C4987AD77605 = 0.f;


		params.Source = uintptr_t(this);
		params.HitGlow = HitGlow;

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::dingus, &params);

	}

	BOOL K2_SetActorLocation(const sdk::structs::FVector NewLocation, bool bSweep, bool bTeleport)
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;

		struct
		{
			sdk::structs::FVector			NewLocation;
			bool							bSweep;
			int								SweepHitResult;
			bool							bTeleport;
			bool							ReturnValue;
		} params;

		params.NewLocation = NewLocation;
		params.bSweep = bSweep;
		params.bTeleport = bTeleport;

		sdk::objects::process_event((uintptr_t)this, sdk::cached::objects::K2_SetActorLocation, &params);

		return params.ReturnValue;
	}

	void GetActorBounds(bool bOnlyCollidingComponents, bool bIncludeFromChildActors, sdk::structs::FVector* Origin, sdk::structs::FVector* BoxExtent)
	{
		if (!utilities::isValidPointer(uintptr_t(this))) return;
		
		struct
		{
			bool							bOnlyCollidingComponents;
			sdk::structs::FVector			Origin;
			sdk::structs::FVector			BoxExtent;
			bool							bIncludeFromChildActors;
		} params;

		params.bOnlyCollidingComponents = bOnlyCollidingComponents;
		params.bIncludeFromChildActors = bIncludeFromChildActors;

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::GetActorBounds, &params);

		if (Origin != nullptr)
			*Origin = params.Origin;
		if (BoxExtent != nullptr)
			*BoxExtent = params.BoxExtent;
	}
	
	sdk::structs::FVector GetBone(int Id)
	{
		if(!utilities::isValidPointer(uintptr_t(this))) return { 0, 0, 0 };

		auto mesh = Mesh();
		if (!mesh) return { 0, 0, 0 };

		auto function = ((sdk::structs::FMatrix * (__fastcall*)(uintptr_t, sdk::structs::FMatrix*, int))(sdk::cached::GetBoneMatrix));
		SpoofCall(function, mesh, sdk::structs::myMatrix, Id);

		return { sdk::structs::myMatrix->M[3][0], sdk::structs::myMatrix->M[3][1], sdk::structs::myMatrix->M[3][2] };
	}

	sdk::structs::FVector GetVelocity()
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return { 0, 0, 0 };

		struct
		{
			sdk::structs::FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		} params;

		sdk::objects::process_event((uintptr_t)this, sdk::cached::objects::GetVelocity, &params);

		return params.ReturnValue;
	}

	BOOL SetCharacterBodyVisibilityForPossession(bool bVisible)
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;

		struct
		{
			bool                                               bVisible;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		} params;

		params.bVisible = bVisible;

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::SetCharacterBodyVisibilityForPossession, &params);

		return params.ReturnValue;
	}

	VOID StartFloating()
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return;

		struct
		{
		} params;

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::StartFloating, &params);
	}

	VOID EndFloating()
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return;

		struct
		{
		} params;

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::EndFloating, &params);
	}

	bool IsDead()
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return false;
		
		struct
		{
			bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		} params;

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::IsDead, &params);

		return params.ReturnValue;
	}
};

class APlayerController {
public:
	AFortPawn* LocalPawn() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return (AFortPawn*)(utilities::read<uintptr_t>((uintptr_t)this + 0x2A8));
	}

	BOOL IsVisible(PVOID TargetActor) {
		//if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		//if (!utilities::isValidPointer((uintptr_t)TargetActor)) return 0;

		//sdk::structs::FVector ViewPoint;
		//auto LineOfSight = reinterpret_cast<bool(__fastcall*)(PVOID PlayerController, PVOID TargetActor, sdk::structs::FVector* ViewPoint)>(sdk::cached::LineSightOfTo);
		//return SpoofCall(LineOfSight, (PVOID)this, TargetActor, &ViewPoint);
		return true;
	}

	Vector2 WorldToScreen(sdk::structs::FVector WorldLocation)
	{
		if (!utilities::isValidPointer(uintptr_t(this))) return Vector2(0, 0);

		sdk::structs::FVector2D Output;

		auto WorldToScreen = reinterpret_cast<bool(__fastcall*)(uintptr_t, sdk::structs::FVector, sdk::structs::FVector2D*, char)>(sdk::cached::ProjectWorldToScreen);
		SpoofCall(WorldToScreen, (uintptr_t)this, WorldLocation, &Output, (char)0);

		return { Output.X, Output.Y };
	}

	VOID ClientSetCameraMode(sdk::structs::FName NewCamMode)
	{
		if (!utilities::isValidPointer(uintptr_t(this))) return;

		struct
		{
			sdk::structs::FName                                       NewCamMode;                                               // (Parm, ZeroConstructor, IsPlainOldData)
		} params;

		params.NewCamMode = NewCamMode;

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::ClientSetCameraMode, &params);
	}

	VOID ClientSetViewTarget(AFortPawn* Actor, sdk::structs::FViewTargetTransitionParams TransitionParams)
	{
		if (!utilities::isValidPointer(uintptr_t(this))) return;

		struct
		{
			uintptr_t A;                                                        // (Parm, ZeroConstructor, IsPlainOldData)
			sdk::structs::FViewTargetTransitionParams                 TransitionParams;                                         // (Parm) FViewTargetTransitionParams
		} params;

		params.A = uintptr_t(Actor);
		params.TransitionParams = TransitionParams;

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::ClientSetViewTarget, &params);
	}

	bool WasInputKeyJustPressed(sdk::structs::FKey Key)
	{		
		if (!utilities::isValidPointer(uintptr_t(this))) return false;

		struct
		{
			sdk::structs::FKey                                        Key;                                                      // (Parm)
			bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		} params;

		params.Key = Key;

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::WasInputKeyJustPressed, &params);

		return params.ReturnValue;
		
	}

	bool IsInputKeyDown(sdk::structs::FKey Key)
	{		
		if (!utilities::isValidPointer(uintptr_t(this))) return false;
		
		struct APlayerController_IsInputKeyDown_Params
		{
			sdk::structs::FKey                                        Key;                                                      // (Parm)
			bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		} params;

		params.Key = Key;

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::IsInputKeyDown, &params);

		return params.ReturnValue;
		
	}

	Vector2 GetMousePosition()
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return { 0, 0 };
		
		struct
		{
			float                                              LocationX;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
			float                                              LocationY;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
			bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		} params;

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::GetMousePosition, &params);

		Vector2 ret;
		ret.x = params.LocationX;
		ret.y = params.LocationY;

		return ret;
	}
};

class ULocalPlayer {
public:
	APlayerController* PlayerController() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return (APlayerController*)(utilities::read<uintptr_t>((uintptr_t)this + 0x30));
	}
};

class ULocalPlayers {
public:
	ULocalPlayer* LocalPlayer() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return (ULocalPlayer*)(utilities::read<uintptr_t>((uintptr_t)this));
	}
};

class UGameInstance {
public:
	ULocalPlayers* LocalPlayers() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return (ULocalPlayers*)(utilities::read<uintptr_t>((uintptr_t)this + 0x38));
	}
};

class AActors {
public:
	AFortPawn* GetCurrentActor(int i) {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return (AFortPawn*)(utilities::read<uintptr_t>((uintptr_t)this + i * sizeof(uintptr_t)));
	}
};

class ULevel {
public:
	AActors* Actors() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return (AActors*)(utilities::read<uintptr_t>((uintptr_t)this + 0x98));
	}

	INT ActorCount() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return (int)(utilities::read<uintptr_t>((uintptr_t)this + 0xA0));
	}

	sdk::structs::TArray<AFortPawn*> ActorArray() {
		if (!utilities::isValidPointer((uintptr_t)this)) return {};
		return utilities::read<sdk::structs::TArray<AFortPawn*>>((uintptr_t)this + 0x98);
	}	
};

class UWorld {
public:

	UGameInstance* OwningGameInstance() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return (UGameInstance*)(utilities::read<uintptr_t>((uintptr_t)this + 0x190));
	}

	ULevel* PersistentLevel() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return (ULevel*)(utilities::read<uintptr_t>((uintptr_t)this + 0x30));
	}

	sdk::structs::TArray<ULevel*> Levels() {
		if (!utilities::isValidPointer((uintptr_t)this)) return {};
		return utilities::read<sdk::structs::TArray<ULevel*>>((uintptr_t)this + 0x148);
	}

	VOID SetTimeOfDay(float TimeOfDay)
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return;
		
		struct
		{
			uintptr_t WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
			float                                              TimeOfDay;                                                // (Parm, ZeroConstructor, IsPlainOldData)
		} params;

		params.WorldContextObject = uintptr_t(this);
		params.TimeOfDay = TimeOfDay;

		sdk::objects::process_event(uintptr_t(sdk::cached::objects::FortKismetLibrary), sdk::cached::objects::SetTimeOfDay, &params);

	}
};

class UCanvas {
public:

	int32_t SizeX() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return utilities::read<int32_t>((uintptr_t)this + 0x40);
	}

	int32_t SizeY() {
		if (!utilities::isValidPointer((uintptr_t)this)) return 0;
		return utilities::read<int32_t>((uintptr_t)this + 0x44);
	}

	void K2_DrawLine(Vector2 ScreenPositionA, Vector2 ScreenPositionB, float Thickness, color RenderColor)
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return;
		
		struct
		{
			sdk::structs::FVector2D                                   ScreenPositionA;                                          // (Parm, ZeroConstructor, IsPlainOldData)
			sdk::structs::FVector2D                                   ScreenPositionB;                                          // (Parm, ZeroConstructor, IsPlainOldData)
			float                                              Thickness;                                                // (Parm, ZeroConstructor, IsPlainOldData)
			sdk::structs::FLinearColor                                RenderColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
		} params;

		params.ScreenPositionA = { ScreenPositionA.x, ScreenPositionA.y };
		params.ScreenPositionB = { ScreenPositionB.x, ScreenPositionB.y };
		params.Thickness = Thickness;
		params.RenderColor = { (float)RenderColor.R, (float)RenderColor.G, (float)RenderColor.B, (float)RenderColor.A };

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::K2_DrawLine, &params);
	}

	void K2_DrawBox(Vector2 ScreenPosition, Vector2 ScreenSize, float Thickness, color RenderColor)
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return;
		
		struct
		{
			sdk::structs::FVector2D                                   ScreenPosition;                                           // (Parm, ZeroConstructor, IsPlainOldData)
			sdk::structs::FVector2D                                   ScreenSize;                                               // (Parm, ZeroConstructor, IsPlainOldData)
			float                                              Thickness;                                                // (Parm, ZeroConstructor, IsPlainOldData)
			sdk::structs::FLinearColor                                RenderColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
		} params;

		params.ScreenPosition = { ScreenPosition.x, ScreenPosition.y };
		params.ScreenSize = { ScreenSize.x, ScreenSize.y };
		params.Thickness = Thickness;
		params.RenderColor = { (float)RenderColor.R, (float)RenderColor.G, (float)RenderColor.B, (float)RenderColor.A };

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::K2_DrawBox, &params);
	}

	void K2_DrawText(Vector2 ScreenPosition, color RenderColor, sdk::structs::FString RenderText, bool bCentered = true, bool bOutlined = true)
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return;
		
		struct
		{
			uintptr_t RenderFont;                                               // (Parm, ZeroConstructor, IsPlainOldData)
			sdk::structs::FString                                     RenderText;                                               // (Parm, ZeroConstructor)
			sdk::structs::FVector2D                                   ScreenPosition;                                           // (Parm, ZeroConstructor, IsPlainOldData)
			sdk::structs::FVector2D                                   Scale;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
			sdk::structs::FLinearColor                                RenderColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
			float                                              Kerning;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
			sdk::structs::FLinearColor                                ShadowColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
			sdk::structs::FVector2D                                   ShadowOffset;                                             // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bCentreX;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bCentreY;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bOutlined;                                                // (Parm, ZeroConstructor, IsPlainOldData)
			sdk::structs::FLinearColor                                OutlineColor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
		} params;

		params.RenderFont = uintptr_t(sdk::cached::objects::Font);
		params.RenderText = RenderText;
		params.ScreenPosition = { ScreenPosition.x, ScreenPosition.y };
		params.Scale = { 0.6f, 0.6f };
		params.RenderColor = { (float)RenderColor.R, (float)RenderColor.G, (float)RenderColor.B, (float)RenderColor.A };
		params.Kerning = false;
		params.ShadowColor = { 0.f, 0.f, 0.f, 0.f };
		params.ShadowOffset = { ScreenPosition.x + 1, ScreenPosition.y + 1 };

		if (bCentered)
		{
			params.bCentreX = true;
			params.bCentreY = true;
		}
		else
		{
			params.bCentreX = false;
			params.bCentreY = false;
		}

		params.bOutlined = bOutlined;
		params.OutlineColor = { 0.0f, 0.0f, 0.0f, 1.f };

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::K2_DrawText, &params);
	}

	Vector2 K2_TextSize(sdk::structs::FString RenderText)
	{
		if (!utilities::isValidPointer((uintptr_t)this)) return { 0, 0 };
		
		struct
		{
			uintptr_t RenderFont;                                               // (Parm, ZeroConstructor, IsPlainOldData)
			sdk::structs::FString                                     RenderText;                                               // (Parm, ZeroConstructor)
			sdk::structs::FVector2D                                   Scale;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
			sdk::structs::FVector2D                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		} params;

		params.RenderFont = uintptr_t(sdk::cached::objects::Font);
		params.RenderText = RenderText;
		params.Scale = { 0.6f, 0.6f };

		sdk::objects::process_event(uintptr_t(this), sdk::cached::objects::K2_TextSize, &params);

		return { params.ReturnValue.X, params.ReturnValue.Y };
	}
};

namespace sdk::cached
{
	inline UCanvas* Canvas = 0;
	inline APlayerController* PlayerController;

	namespace keys
	{
		inline sdk::structs::FKey LButton;
		inline sdk::structs::FKey Insert;
	}
}