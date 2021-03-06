#pragma once

#include <Core/World/Declarations.h>
#include <Foundation/SimdMath/SimdBBoxSphere.h>
#include <Foundation/Strings/HashedString.h>

struct EZ_ALIGN_16(ezSpatialData)
{
  struct Category
  {
    EZ_ALWAYS_INLINE Category()
      : m_uiValue(ezInvalidIndex)
    {
    }

    EZ_ALWAYS_INLINE explicit Category(ezUInt32 uiValue)
      : m_uiValue(uiValue)
    {
    }

    EZ_ALWAYS_INLINE bool operator==(const Category& other) const { return m_uiValue == other.m_uiValue; }
    EZ_ALWAYS_INLINE bool operator!=(const Category& other) const { return m_uiValue != other.m_uiValue; }

    ezUInt32 m_uiValue;

    EZ_ALWAYS_INLINE ezUInt32 GetBitmask() const { return m_uiValue != ezInvalidIndex ? EZ_BIT(m_uiValue) : 0; }
  };

  /// \brief Registers a spatial data category under the given name.
  ///
  /// If the same category was already registered before, it returns that instead.
  /// Asserts that there are no more than 32 unique categories.
  static EZ_CORE_DLL Category RegisterCategory(const char* szCategoryName);

  /// \brief Returns either an existing category with the given name or ezInvalidSpatialDataCategory.
  static EZ_CORE_DLL Category FindCategory(const char* szCategoryName);

  struct Flags
  {
    typedef ezUInt8 StorageType;

    enum Enum
    {
      None = 0,
      AlwaysVisible = EZ_BIT(0),

      Default = None
    };

    struct Bits
    {
      StorageType AlwaysVisible : 1;
    };
  };

  ezGameObject* m_pObject = nullptr;
  ezUInt32 m_uiCategoryBitmask = 0;
  ezBitflags<Flags> m_Flags;

  ezSimdBBoxSphere m_Bounds;

  ezUInt32 m_uiUserData[4] = {};

private:
  struct CategoryData
  {
    ezHashedString m_sName;
  };

  static ezHybridArray<ezSpatialData::CategoryData, 32>& GetCategoryData();
};

struct EZ_CORE_DLL ezDefaultSpatialDataCategories
{
  static ezSpatialData::Category RenderStatic;
  static ezSpatialData::Category RenderDynamic;
};

#define ezInvalidSpatialDataCategory ezSpatialData::Category()
