#pragma once

#include <Foundation/Basics.h>
#include <QDialog>
#include <Tools/EditorFramework/ui_EditorPluginConfigDlg.h>

class EditorPluginConfigDlg : public QDialog, public Ui_EditorPluginConfigDlg
{
public:
  Q_OBJECT

public:
  EditorPluginConfigDlg(QWidget* parent);


private slots:
  void on_ButtonOK_clicked();
  void on_ButtonCancel_clicked();

private:
  void FillPluginList();
};


