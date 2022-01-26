#pragma once

static float width;
static float height;

class color
{
public:
	float R, G, B, A;

	color()
	{
		R = G = B = A = 0;
	}

	color(float R, float G, float B, float A)
	{
		this->R = R;
		this->G = G;
		this->B = B;
		this->A = A;
	}
};



static bool fakeunload = false;



#define RELATIVE(addr, size) ((uintptr_t)((UINT_PTR)(addr) + *(PINT)((UINT_PTR)(addr) + ((size) - sizeof(INT))) + (size)))

namespace utilities
{
	inline BOOL IsInScreen(Vector2 Pos) {
		if (((Pos.x <= 0 or Pos.x > width) and (Pos.y <= 0 or Pos.y > height)) or ((Pos.x <= 0 or Pos.x > width) or (Pos.y <= 0 or Pos.y > height))) {
			return FALSE;
		}
		else {
			return TRUE;
		}
	}

	inline color getColorFromTier(BYTE Tier) {
		color color = { 1.f, 1.f, 0.9f, 1.f };

		if (Tier == 1)
			color = { 1.f, 1.f, 0.9f, 1.f };
		else if (Tier == 2)
			color = { 0.0f, 0.95f, 0.0f, 1.f };
		else if (Tier == 3)
			color = { 0.4f, 0.65f, 1.0f, 1.f };
		else if (Tier == 4)
			color = { 0.7f, 0.25f, 0.85f, 1.f };
		else if (Tier == 5)
			color = { 0.85f, 0.65f, 0.0f, 1.f };

		return color;
	}

	inline uintptr_t imageBase()
	{
		return *(uintptr_t*)(__readgsqword(0x60) + 0x10);
	}

	inline bool isValidPointer(uintptr_t address)
	{
		if (!SpoofCall(IsBadWritePtr, (LPVOID)address, (UINT_PTR)8))
			return true;
		else
			return false;
	}

	template <typename R>
	inline R read(uintptr_t address)
	{
		R buffer{};

		if (!isValidPointer(address))
			return buffer;

		buffer = *(R*)address;

		return buffer;
	}

	template <typename W>
	inline void write(uintptr_t address, const W& value)
	{
		W buffer{};

		if (!isValidPointer(address))
			return;

		*(W*)address = value;
	}


	inline float custom_sqrtf(float _X)
	{
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(_X)));
	}

	inline float custom_sinf(float _X)
	{
		return _mm_cvtss_f32(_mm_sin_ps(_mm_set_ss(_X)));
	}

	inline float custom_cosf(float _X)
	{
		return _mm_cvtss_f32(_mm_cos_ps(_mm_set_ss(_X)));
	}

	inline float custom_acosf(float _X)
	{
		return _mm_cvtss_f32(_mm_acos_ps(_mm_set_ss(_X)));
	}

	inline float custom_tanf(float _X)
	{
		return _mm_cvtss_f32(_mm_tan_ps(_mm_set_ss(_X)));
	}

	inline float custom_atan2f(float _X, float _Y)
	{
		return _mm_cvtss_f32(_mm_atan2_ps(_mm_set_ss(_X), _mm_set_ss(_Y)));
	}

	inline int custom_compare(const char* X, const char* Y)
	{
		while (*X && *Y) {
			if (*X != *Y) {
				return 0;
			}
			X++;
			Y++;
		}

		return (*Y == '\0');
	}

	inline int custom_wcompare(const wchar_t* X, const wchar_t* Y)
	{
		while (*X && *Y) {
			if (*X != *Y) {
				return 0;
			}
			X++;
			Y++;
		}

		return (*Y == L'\0');
	}
	
	inline const wchar_t* custom_wcsstr(const wchar_t* X, const wchar_t* Y)
	{
		while (*X != L'\0') {
			if ((*X == *Y) && custom_wcompare(X, Y)) {
				return X;
			}
			X++;
		}
		return NULL;
	}

	inline const char* custom_strstr(const char* X, const char* Y)
	{
		while (*X != '\0') {
			if ((*X == *Y) && custom_compare(X, Y)) {
				return X;
			}
			X++;
		}
		return NULL;
	}

	inline int custom_strlen(const char* string)
	{
		int cnt = 0;
		if (string)
		{
			for (; *string != 0; ++string) ++cnt;
		}
		return cnt;
	}

	inline int custom_wcslen(const wchar_t* string)
	{
		int cnt = 0;
		if (string)
		{
			for (; *string != 0; ++string) ++cnt;
		}
		return cnt;
	}

	inline uintptr_t scan(uintptr_t pModuleBaseAddress, const char* sSignature)
	{
		static auto patternToByte = [](const char* pattern)
		{
			auto       bytes = std::vector<int>{};
			const auto start = const_cast<char*>(pattern);
			const auto end = const_cast<char*>(pattern) + custom_strlen(pattern);

			for (auto current = start; current < end; ++current)
			{
				if (*current == '?')
				{
					++current;
					if (*current == '?')
						++current;
					bytes.push_back(-1);
				}
				else
					bytes.push_back(SpoofCall(strtoul, (const char*)current, &current, 16));
			}
			return bytes;
		};

		const auto dosHeader = (PIMAGE_DOS_HEADER)pModuleBaseAddress;
		const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)pModuleBaseAddress + dosHeader->e_lfanew);

		const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
		auto       patternBytes = patternToByte(sSignature);
		const auto scanBytes = reinterpret_cast<std::uint8_t*>(pModuleBaseAddress);

		const auto s = patternBytes.size();
		const auto d = patternBytes.data();

		for (auto i = 0ul; i < sizeOfImage - s; ++i)
		{
			bool found = true;

			for (auto j = 0ul; j < s; ++j)
			{
				if (scanBytes[i + j] != d[j] && d[j] != -1)
				{
					found = false;
					break;
				}
			}

			if (found)
			{
				return reinterpret_cast<uintptr_t>(&scanBytes[i]);
			}
		}

		return NULL;
	}
}

//Settings
struct {

	struct aimPlayers {

		bool Memory;
		bool Silent;
		int FovCircle;
		bool BulletTP;
		bool SniperPrediction;

	} aimConfigsPlayers;

	struct exploits {

		bool DayTime;
		float DayTime_value;
		bool FirstCamera;
		bool Floating;
		bool Chams;
		bool HeatMapChams;

	} exploitsConfigs;

	struct visualsPlayers {

		bool ESP;
		bool Box2D;
		bool Box3D;
		bool Skeleton;
		bool Lines;
		bool Names;
		bool Weapon;
		bool Distance;
		bool Platform;
		bool TargetLine;

	} visualsConfigsPlayers;

	struct visualsWorld {

		bool ESP;
		bool Loot;
		bool Chest;
		bool AmmoBox;

	} visualsConfigsWorld;

} Settings;