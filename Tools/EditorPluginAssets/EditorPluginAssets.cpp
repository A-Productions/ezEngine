#include <PCH.h>
#include <EditorPluginAssets/EditorPluginAssets.h>
#include <EditorPluginAssets/TextureAsset/TextureAssetObjects.h>
#include <ToolsFoundation/Reflection/ToolsReflectionUtils.h>
#include <Foundation/Reflection/Reflection.h>
#include <EditorFramework/EditorApp/EditorApp.moc.h>
#include <GuiFoundation/Action/ActionMapManager.h>
#include <EditorFramework/Actions/ProjectActions.h>
#include <EditorFramework/Actions/AssetActions.h>
#include <GuiFoundation/Action/StandardMenus.h>
#include <GuiFoundation/Action/DocumentActions.h>
#include <GuiFoundation/Action/CommandHistoryActions.h>

void OnLoadPlugin(bool bReloading)
{
  ezQtEditorApp::GetSingleton()->RegisterPluginNameForSettings("AssetsPlugin");

  // Texture Asset
  {
    // Menu Bar
    {
      ezActionMapManager::RegisterActionMap("TextureAssetMenuBar");
      ezProjectActions::MapActions("TextureAssetMenuBar");
      ezStandardMenus::MapActions("TextureAssetMenuBar", ezStandardMenuTypes::File | ezStandardMenuTypes::Edit | ezStandardMenuTypes::Panels | ezStandardMenuTypes::Help);
      ezDocumentActions::MapActions("TextureAssetMenuBar", "Menu.File", false);
      ezCommandHistoryActions::MapActions("TextureAssetMenuBar", "Menu.Edit");
    }

    // Tool Bar
    {
      ezActionMapManager::RegisterActionMap("TextureAssetToolBar");
      ezDocumentActions::MapActions("TextureAssetToolBar", "", true);
      ezCommandHistoryActions::MapActions("TextureAssetToolBar", "");
      ezAssetActions::MapActions("TextureAssetToolBar", true);
    }
  }

  // Material Asset
  {
    // Menu Bar
    {
      ezActionMapManager::RegisterActionMap("MaterialAssetMenuBar");
      ezProjectActions::MapActions("MaterialAssetMenuBar");
      ezStandardMenus::MapActions("MaterialAssetMenuBar", ezStandardMenuTypes::File | ezStandardMenuTypes::Edit | ezStandardMenuTypes::Panels | ezStandardMenuTypes::Help);
      ezDocumentActions::MapActions("MaterialAssetMenuBar", "Menu.File", false);
      ezCommandHistoryActions::MapActions("MaterialAssetMenuBar", "Menu.Edit");
    }

    // Tool Bar
    {
      ezActionMapManager::RegisterActionMap("MaterialAssetToolBar");
      ezDocumentActions::MapActions("MaterialAssetToolBar", "", true);
      ezCommandHistoryActions::MapActions("MaterialAssetToolBar", "");
      ezAssetActions::MapActions("MaterialAssetToolBar", true);
    }
  }

  // Render Pipeline Asset
  {
    // Menu Bar
    {
      ezActionMapManager::RegisterActionMap("RenderPipelineAssetMenuBar");
      ezProjectActions::MapActions("RenderPipelineAssetMenuBar");
      ezStandardMenus::MapActions("RenderPipelineAssetMenuBar", ezStandardMenuTypes::File | ezStandardMenuTypes::Edit | ezStandardMenuTypes::Panels | ezStandardMenuTypes::Help);
      ezDocumentActions::MapActions("RenderPipelineAssetMenuBar", "Menu.File", false);
      ezCommandHistoryActions::MapActions("RenderPipelineAssetMenuBar", "Menu.Edit");
    }

    // Tool Bar
    {
      ezActionMapManager::RegisterActionMap("RenderPipelineAssetToolBar");
      ezDocumentActions::MapActions("RenderPipelineAssetToolBar", "", true);
      ezCommandHistoryActions::MapActions("RenderPipelineAssetToolBar", "");
      ezAssetActions::MapActions("RenderPipelineAssetToolBar", true);
    }
  }

  // Mesh Asset
  {
    // Menu Bar
    {
      ezActionMapManager::RegisterActionMap("MeshAssetMenuBar");
      ezProjectActions::MapActions("MeshAssetMenuBar");
      ezStandardMenus::MapActions("MeshAssetMenuBar", ezStandardMenuTypes::File | ezStandardMenuTypes::Edit | ezStandardMenuTypes::Panels | ezStandardMenuTypes::Help);
      ezDocumentActions::MapActions("MeshAssetMenuBar", "Menu.File", false);
      ezCommandHistoryActions::MapActions("MeshAssetMenuBar", "Menu.Edit");
    }

    // Tool Bar
    {
      ezActionMapManager::RegisterActionMap("MeshAssetToolBar");
      ezDocumentActions::MapActions("MeshAssetToolBar", "", true);
      ezCommandHistoryActions::MapActions("MeshAssetToolBar", "");
      ezAssetActions::MapActions("MeshAssetToolBar", true);
    }
  }

  // Surface Asset
  {
    // Menu Bar
    {
      ezActionMapManager::RegisterActionMap("SurfaceAssetMenuBar");
      ezProjectActions::MapActions("SurfaceAssetMenuBar");
      ezStandardMenus::MapActions("SurfaceAssetMenuBar", ezStandardMenuTypes::File | ezStandardMenuTypes::Edit | ezStandardMenuTypes::Panels | ezStandardMenuTypes::Help);
      ezDocumentActions::MapActions("SurfaceAssetMenuBar", "Menu.File", false);
      ezCommandHistoryActions::MapActions("SurfaceAssetMenuBar", "Menu.Edit");
    }

    // Tool Bar
    {
      ezActionMapManager::RegisterActionMap("SurfaceAssetToolBar");
      ezDocumentActions::MapActions("SurfaceAssetToolBar", "", true);
      ezCommandHistoryActions::MapActions("SurfaceAssetToolBar", "");
      ezAssetActions::MapActions("SurfaceAssetToolBar", true);
    }
  }
}

void OnUnloadPlugin(bool bReloading)
{

}

ezPlugin g_Plugin(false, OnLoadPlugin, OnUnloadPlugin);

EZ_DYNAMIC_PLUGIN_IMPLEMENTATION(EZ_EDITORPLUGINASSETS_DLL, ezEditorPluginAssets);
