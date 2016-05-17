#include <RendererCore/PCH.h>
#include <RendererCore/Shader/Implementation/Helper.h>
#include <RendererCore/ShaderCompiler/ShaderManager.h>
#include <RendererCore/ShaderCompiler/ShaderParser.h>

namespace
{
  static ezHashTable<const char*, const ezRTTI*> s_NameToTypeTable;

  void InitializeTables()
  {
    if (!s_NameToTypeTable.IsEmpty())
      return;

    s_NameToTypeTable.Insert("float", ezGetStaticRTTI<float>());
    s_NameToTypeTable.Insert("float2", ezGetStaticRTTI<ezVec2>());
    s_NameToTypeTable.Insert("float3", ezGetStaticRTTI<ezVec3>());
    s_NameToTypeTable.Insert("float4", ezGetStaticRTTI<ezVec4>());
    s_NameToTypeTable.Insert("Color", ezGetStaticRTTI<ezColor>());
    s_NameToTypeTable.Insert("Texture", ezGetStaticRTTI<ezString>());
    s_NameToTypeTable.Insert("Texture2D", ezGetStaticRTTI<ezString>());
    s_NameToTypeTable.Insert("Texture3D", ezGetStaticRTTI<ezString>());
    s_NameToTypeTable.Insert("TextureCube", ezGetStaticRTTI<ezString>());
  }

  bool IsIdentifier(ezUInt32 c)
  {
    return !ezStringUtils::IsIdentifierDelimiter_C_Code(c);
  }

  void SkipWhitespace(ezStringView& s)
  {
    while (s.IsValid() && ezStringUtils::IsWhiteSpace(s.GetCharacter()))
    {
      ++s;
    }
  }

  void FillType(ezShaderParser::ParameterDefinition& def)
  {
    InitializeTables();

    def.m_pType = nullptr;
    if (s_NameToTypeTable.TryGetValue(def.m_sType.GetData(), def.m_pType))
    {
      if (def.m_sType.IsEqual("Texture2D") || def.m_sType.IsEqual("Texture"))
      {
        def.m_Attributes.PushBack(EZ_DEFAULT_NEW(ezAssetBrowserAttribute, "Texture 2D"));
      }
      else if (def.m_sType.IsEqual("Texture3D"))
      {
        def.m_Attributes.PushBack(EZ_DEFAULT_NEW(ezAssetBrowserAttribute, "Texture 3D"));
      }
      else if (def.m_sType.IsEqual("TextureCube"))
      {
        def.m_Attributes.PushBack(EZ_DEFAULT_NEW(ezAssetBrowserAttribute, "Texture Cube"));
      }
    }
  }

  void ParseAttribute(ezStringView& s, ezShaderParser::ParameterDefinition& def)
  {
    SkipWhitespace(s);

    if (!s.IsValid() || s.GetCharacter() != '@')
      return;

    ++s; //skip @

    const char* szNameStart = s.GetData();
    while (s.IsValid() && IsIdentifier(s.GetCharacter()))
    {
      ++s;
    }

    ezStringView sAttributeName(szNameStart, s.GetData());

    SkipWhitespace(s);

    if (!s.IsValid() || s.GetCharacter() != '(')
      return;

    ++s; //skip (

    const char* szValueStart = s.GetData();
    while (s.IsValid() && s.GetCharacter() != ')')
    {
      ++s;
    }

    if (!s.IsValid() || s.GetCharacter() != ')')
      return;

    ++s; //skip )

    ezStringView sAttributeValue(szValueStart, s.GetData());
  }
}

//static
void ezShaderParser::ParseMaterialParameterSection(ezStreamReader& stream, ezHybridArray<ParameterDefinition, 16>& out_Parameter)
{
  ezString sContent;
  sContent.ReadAll(stream);

  ezShaderHelper::ezTextSectionizer Sections;
  ezShaderHelper::GetShaderSections(sContent.GetData(), Sections);

  ezUInt32 uiFirstLine = 0;
  ezStringView s = Sections.GetSectionContent(ezShaderHelper::ezShaderSections::MATERIALPARAMETER, uiFirstLine);
  
  SkipWhitespace(s);

  while (s.IsValid())
  {
    const char* szTypeStart = s.GetData();
    while (s.IsValid() && IsIdentifier(s.GetCharacter()))
    {
      ++s;
    }

    ParameterDefinition def;
    def.m_sType = ezStringView(szTypeStart, s.GetData());
    FillType(def);
        
    SkipWhitespace(s);

    const char* szNameStart = s.GetData();
    while (s.IsValid() && IsIdentifier(s.GetCharacter()))
    {
      ++s;
    }

    def.m_sName = ezStringView(szNameStart, s.GetData());

    while (s.IsValid() && s.GetCharacter() != ';')
    {
      ParseAttribute(s, def);

      SkipWhitespace(s);
    }

    if (!s.IsValid())
      break;

    ++s; //skip ;

    if (!def.m_sType.IsEmpty() && !def.m_sName.IsEmpty())
    {
      out_Parameter.PushBack(def);
    }

    SkipWhitespace(s);
  }
}

//static
void ezShaderParser::ParsePermutationSection(ezStreamReader& stream, ezHybridArray<ezHashedString, 16>& out_PermVars)
{
  ezString sContent;
  sContent.ReadAll(stream);

  ezShaderHelper::ezTextSectionizer Sections;
  ezShaderHelper::GetShaderSections(sContent.GetData(), Sections);

  ezUInt32 uiFirstLine = 0;
  ezStringView sPermutations = Sections.GetSectionContent(ezShaderHelper::ezShaderSections::PERMUTATIONS, uiFirstLine);
  ParsePermutationSection(sPermutations, out_PermVars);
}

//static
void ezShaderParser::ParsePermutationSection(ezStringView s, ezHybridArray<ezHashedString, 16>& out_PermVars)
{
  SkipWhitespace(s);

  ezStringBuilder sToken;
  while (s.IsValid())
  {
    while (s.IsValid() && IsIdentifier(s.GetCharacter()))
    {
      sToken.Append(s.GetCharacter());
      ++s;
    }
    
    out_PermVars.ExpandAndGetRef().Assign(sToken.GetData());
    sToken.Clear();
    
    SkipWhitespace(s);
  }
}

//static
void ezShaderParser::ParsePermutationVarConfig(ezStringView s, ezVariant& out_DefaultValue, ezHybridArray<ezHashedString, 16>& out_EnumValues)
{
  SkipWhitespace(s);

  if (s.StartsWith("bool"))
  {
    bool bDefaultValue = false;

    const char* szDefaultValue = s.FindSubString("=");
    if (!ezStringUtils::IsNullOrEmpty(szDefaultValue))
    {
      ++szDefaultValue;
      ezConversionUtils::StringToBool(szDefaultValue, bDefaultValue);
    }

    out_DefaultValue = bDefaultValue;
  }
  else if (s.StartsWith("enum"))
  {
    const char* szOpenBracket = s.FindSubString("{");
    const char* szCloseBracket = s.FindLastSubString("}");

    if (ezStringUtils::IsNullOrEmpty(szOpenBracket) || ezStringUtils::IsNullOrEmpty(szCloseBracket))
    {
      ezLog::Error("No brackets found for enum definition.");
    }

    ezStringBuilder sEnumValues = ezStringView(szOpenBracket + 1, szCloseBracket);

    ezHybridArray<ezStringView, 32> enumValues;
    sEnumValues.Split(false, enumValues, ",");

    ezUInt32 uiDefaultValue = 0;
    ezUInt32 uiCurrentValue = 0;
    for (ezStringView& sName : enumValues)
    {
      sName.Trim(" \r\n\t");

      const char* szValue = sName.FindSubString("=");
      if (!ezStringUtils::IsNullOrEmpty(szValue))
      {
        sName = ezStringView(sName.GetStartPosition(), szValue);
        sName.Trim(" \r\n\t");

        ++szValue;

        ezInt32 iValue = 0;
        if (ezConversionUtils::StringToInt(szValue, iValue).Succeeded() && iValue >= 0)
        {
          uiCurrentValue = iValue;
        }
        else
        {
          ezLog::Error("Invalid enum value '%s'. Only positive numbers are allowed.", szValue);
        }
      }

      if (sName.IsEqual_NoCase("default"))
      {
        uiDefaultValue = uiCurrentValue;
      }

      if (out_EnumValues.GetCount() <= uiCurrentValue)
      {
        out_EnumValues.SetCount(uiCurrentValue + 1);
      }

      if (ezStringUtils::IsNullOrEmpty(out_EnumValues[uiCurrentValue].GetData()))
      {
        ezString sFinalName = sName;
        out_EnumValues[uiCurrentValue].Assign(sFinalName.GetData());
      }
      else
      {
        ezLog::Error("A enum value with '%d' already exists: '%s'", uiCurrentValue, out_EnumValues[uiCurrentValue].GetData());
      }

      ++uiCurrentValue;
    }

    out_DefaultValue = uiDefaultValue;
  }
  else
  {
    ezLog::Error("Unknown permutation var type");
  }
}