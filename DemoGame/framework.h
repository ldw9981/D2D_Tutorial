﻿// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

// Windows 헤더 파일
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <comdef.h>
#include <d2d1helper.h>
#include <string>
#include <vector>
#include <list>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <dxgi1_4.h>

// 프로젝트에서 공통적으로 사용할 헤더파일이므로 pch처럼 cpp 제일 앞부분에 추가한다.