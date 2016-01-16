#pragma once

#include <EditorFramework/Plugin.h>
#include <ToolsFoundation/Project/ToolsProject.h>
#include <GuiFoundation/Action/BaseActions.h>

///
class EZ_EDITORFRAMEWORK_DLL ezProjectActions
{
public:
  static void RegisterActions();
  static void UnregisterActions();

  static void MapActions(const char* szMapping);

  static ezActionDescriptorHandle s_hEditorMenu;

  static ezActionDescriptorHandle s_hDocumentCategory;
  static ezActionDescriptorHandle s_hCreateDocument;
  static ezActionDescriptorHandle s_hOpenDocument;
  static ezActionDescriptorHandle s_hRecentDocuments;

  static ezActionDescriptorHandle s_hProjectCategory;
  static ezActionDescriptorHandle s_hCreateProject;
  static ezActionDescriptorHandle s_hOpenProject;
  static ezActionDescriptorHandle s_hRecentProjects;
  static ezActionDescriptorHandle s_hCloseProject;

  static ezActionDescriptorHandle s_hSettingsCategory;
  static ezActionDescriptorHandle s_hEditorSettingsMenu;
  static ezActionDescriptorHandle s_hProjectSettingsMenu;
  static ezActionDescriptorHandle s_hShortcutEditor;
  static ezActionDescriptorHandle s_hEditorPlugins;
  static ezActionDescriptorHandle s_hEnginePlugins;
  static ezActionDescriptorHandle s_hDataDirectories;
  static ezActionDescriptorHandle s_hSettingsDlg;

  static ezActionDescriptorHandle s_hToolsMenu;
  static ezActionDescriptorHandle s_hToolsCategory;
  static ezActionDescriptorHandle s_hReloadResources;
};

///
class EZ_EDITORFRAMEWORK_DLL ezRecentDocumentsMenuAction : public ezLRUMenuAction
{
  EZ_ADD_DYNAMIC_REFLECTION(ezRecentDocumentsMenuAction, ezLRUMenuAction);
public:
  ezRecentDocumentsMenuAction(const ezActionContext& context, const char* szName, const char* szIconPath) : ezLRUMenuAction(context, szName, szIconPath) {}
  virtual void GetEntries(ezHybridArray<ezLRUMenuAction::Item, 16>& out_Entries) override;
  virtual void Execute(const ezVariant& value) override;
};

///
class EZ_EDITORFRAMEWORK_DLL ezRecentProjectsMenuAction : public ezLRUMenuAction
{
  EZ_ADD_DYNAMIC_REFLECTION(ezRecentProjectsMenuAction, ezLRUMenuAction);
public:
  ezRecentProjectsMenuAction(const ezActionContext& context, const char* szName, const char* szIconPath) : ezLRUMenuAction(context, szName, szIconPath) {}
  virtual void GetEntries(ezHybridArray<ezLRUMenuAction::Item, 16>& out_Entries) override;
  virtual void Execute(const ezVariant& value) override;
};

///
class EZ_EDITORFRAMEWORK_DLL ezProjectAction : public ezButtonAction
{
  EZ_ADD_DYNAMIC_REFLECTION(ezProjectAction, ezButtonAction);
public:
  enum class ButtonType
  {
    CreateDocument,
    OpenDocument,
    CreateProject,
    OpenProject,
    CloseProject,
    ReloadResources,
    Shortcuts,
    EditorPlugins,
    DataDirectories,
    SettingsDialog,
    EnginePlugins,
  };

  ezProjectAction(const ezActionContext& context, const char* szName, ButtonType button);
  ~ezProjectAction();

  virtual void Execute(const ezVariant& value) override;

private:
  void ProjectEventHandler(const ezToolsProject::Event& e);

  ButtonType m_ButtonType;
};