#pragma once

/// \file

#include <Foundation/Reflection/Implementation/RTTI.h>
#include <Foundation/Reflection/Implementation/DynamicRTTI.h>
#include <Foundation/Math/Vec4.h>
#include <Foundation/Math/Quat.h>

EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezReflectedClass);

// *********************************************
// ***** Standard POD Types for Properties *****

EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, bool);

EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, float);
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, double);

EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezInt8);
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezUInt8);
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezInt16);
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezUInt16);
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezInt32);
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezUInt32);
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezInt64);
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezUInt64);

// macros won't work with 'const char*'
typedef const char* ezConstCharPtr;
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezConstCharPtr);

EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezTime);
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezColor);
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezVec2);
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezVec3);
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezVec4);
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezQuat);
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezMat3);
EZ_DECLARE_REFLECTABLE_TYPE(EZ_FOUNDATION_DLL, ezMat4);
