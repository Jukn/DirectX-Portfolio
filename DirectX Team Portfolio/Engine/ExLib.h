#pragma once

// direct x header
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi1_2.h>

// direct 2d header
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

//for ComPtr
#include <wrl.h>

// additional Lib header
#include "FMOD/fmod.h"
#include "FMOD/fmod.hpp"
#include <FBXSDK/fbxsdk.h>

// link direct x library
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "dxgi.lib")

// link direct 2d library
#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "dwrite.lib")

// link additional Lib library
#pragma comment (lib, "fmod_vc.lib")
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")

#pragma comment(lib, "Engine.lib")

using namespace Microsoft::WRL;					// for ComPtr

