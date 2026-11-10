#pragma once

#include "pch.h"

class DualRemoteCopyDialog : public QDialog {
  Q_OBJECT
public:
  DualRemoteCopyDialog(const QString &source, const QString &destination,
                       QWidget *parent = nullptr);
  QString sourcePath() const;
  QString destinationPath() const;
  bool mirrorDestination() const;
  bool serverSideAcrossConfigs() const;

private:
  QLineEdit *mSource = nullptr;
  QLineEdit *mDestination = nullptr;
  QCheckBox *mMirror = nullptr;
  QCheckBox *mServerSide = nullptr;
};
