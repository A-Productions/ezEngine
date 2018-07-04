#pragma once

#include <Foundation/Containers/DynamicArray.h>
#include <ParticlePlugin/Type/ParticleType.h>
#include <RendererFoundation/Basics.h>

typedef ezTypedResourceHandle<class ezMeshResource> ezMeshResourceHandle;

class EZ_PARTICLEPLUGIN_DLL ezParticleTypeMeshFactory : public ezParticleTypeFactory
{
  EZ_ADD_DYNAMIC_REFLECTION(ezParticleTypeMeshFactory, ezParticleTypeFactory);

public:
  virtual const ezRTTI* GetTypeType() const override;
  virtual void CopyTypeProperties(ezParticleType* pObject) const override;

  virtual void Save(ezStreamWriter& stream) const override;
  virtual void Load(ezStreamReader& stream) override;

  ezString m_sMesh;
  ezString m_sTintColorParameter;
};

class EZ_PARTICLEPLUGIN_DLL ezParticleTypeMesh : public ezParticleType
{
  EZ_ADD_DYNAMIC_REFLECTION(ezParticleTypeMesh, ezParticleType);

public:
  ezParticleTypeMesh();
  ~ezParticleTypeMesh();

  virtual void CreateRequiredStreams() override;

  ezMeshResourceHandle m_hMesh;
  ezTempHashedString m_sTintColorParameter;

  virtual void ExtractTypeRenderData(const ezView& view, ezExtractedRenderData& extractedRenderData, const ezTransform& instanceTransform, ezUInt64 uiExtractedFrame) const override;

protected:
  virtual void InitializeElements(ezUInt64 uiStartIndex, ezUInt64 uiNumElements) override;
  virtual void Process(ezUInt64 uiNumElements) override {}

  ezProcessingStream* m_pStreamPosition = nullptr;
  ezProcessingStream* m_pStreamSize = nullptr;
  ezProcessingStream* m_pStreamColor = nullptr;
  ezProcessingStream* m_pStreamRotationSpeed = nullptr;
  ezProcessingStream* m_pStreamRotationOffset = nullptr;
  ezProcessingStream* m_pStreamAxis = nullptr;

};