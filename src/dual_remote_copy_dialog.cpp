#include "dual_remote_copy_dialog.h"
#include "interface_polish.h"

DualRemoteCopyDialog::DualRemoteCopyDialog(const QString &source,
                                           const QString &destination,
                                           QWidget *parent)
    : QDialog(parent) {
  setWindowTitle("Copy Between Remotes");
  UiPolish::SetWindowDefaults(this, QSize(520, 280));
  auto *layout = new QVBoxLayout(this);
  auto *intro = new QLabel(
      "Choose the folders to copy between the two open remote panes.", this);
  intro->setWordWrap(true);
  UiPolish::SetMuted(intro);
  layout->addWidget(intro);

  auto *form = new QFormLayout;
  mSource = new QLineEdit(source, this);
  mDestination = new QLineEdit(destination, this);
  mSource->setClearButtonEnabled(true);
  mDestination->setClearButtonEnabled(true);
  UiPolish::SetAccessibleFormField(mSource, "Source folder",
                                   "rclone source path from the left pane");
  UiPolish::SetAccessibleFormField(mDestination, "Destination folder",
                                   "rclone destination path from the right pane");
  form->addRow("From", mSource);
  form->addRow("To", mDestination);
  layout->addLayout(form);

  mMirror = new QCheckBox("Mirror destination (sync; may delete destination files)", this);
  mServerSide = new QCheckBox("Request server-side copy across remotes", this);
  mServerSide->setToolTip(
      "Pass --server-side-across-configs. If the remote pair does not support "
      "server-side copy, rclone may transfer data through this computer.");
  layout->addWidget(mMirror);
  layout->addWidget(mServerSide);

  auto *warning = new QLabel(
      "Copy is non-destructive. Mirror mode removes destination files that are "
      "not present in the source.", this);
  warning->setWordWrap(true);
  UiPolish::SetNotice(warning, warning->text());
  layout->addWidget(warning);

  auto *buttons = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok,
                                       this);
  auto *startButton = buttons->button(QDialogButtonBox::Ok);
  startButton->setText("Start Copy");
  UiPolish::SetPrimaryButton(startButton);
  connect(mMirror, &QCheckBox::toggled, startButton,
          [startButton](bool checked) {
            startButton->setText(checked ? "Start Mirror" : "Start Copy");
          });
  UiPolish::SetDialogButtonBox(buttons);
  connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
  layout->addWidget(buttons);
}

QString DualRemoteCopyDialog::sourcePath() const { return mSource->text().trimmed(); }
QString DualRemoteCopyDialog::destinationPath() const { return mDestination->text().trimmed(); }
bool DualRemoteCopyDialog::mirrorDestination() const { return mMirror->isChecked(); }
bool DualRemoteCopyDialog::serverSideAcrossConfigs() const { return mServerSide->isChecked(); }
