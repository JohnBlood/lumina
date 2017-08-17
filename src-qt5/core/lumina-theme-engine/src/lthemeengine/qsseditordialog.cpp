#include <QFile>
#include <QSettings>
#include "lthemeengine.h"
#include "qsseditordialog.h"
#include "ui_qsseditordialog.h"

QSSEditorDialog::QSSEditorDialog(const QString &filePath, QWidget *parent) : QDialog(parent), m_ui(new Ui::QSSEditorDialog){
  m_ui->setupUi(this);
  m_filePath = filePath;
  QFile file(filePath);
  file.open(QIODevice::ReadOnly);
  m_ui->textEdit->setPlainText(QString::fromUtf8(file.readAll()));
  setWindowTitle(tr("%1 - Style Sheet Editor").arg(file.fileName()));
  QSettings settings(lthemeengine::configFile(), QSettings::IniFormat);
  restoreGeometry(settings.value("QSSEditor/geometry").toByteArray());
  //Generate the list of standard colors for the user to pick
  QStringList colors;
  colors << tr("base (alternate)")+"::::alternate-base"
		<< tr("base")+"::::base"
		<< tr("text (bright)")+"::::bright-text"
		<< tr("button")+"::::button"
		<< tr("text (button)")+"::::button-text"
		<< tr("dark")+"::::dark"
		<< tr("highlight")+"::::highlight"
		<< tr("text (highlight)")+"::::highlighted-text"
		<< tr("light")+"::::light"
		<< tr("link")+"::::link"
		<< tr("link (visited)")+"::::link-visited"
		<< tr("mid")+"::::mid"
		<< tr("midlight")+"::::midlight"
		<< tr("shadow")+"::::shadow"
		<< tr("text")+"::::text"
		<< tr("window")+"::::window"
		<< tr("text (window)")+"::::window-text";
  colors.sort(); //sort by translated display name
  colorMenu = new QMenu(m_ui->tool_color);
  for(int i=0; i<colors.length(); i++){ colorMenu->addAction( colors[i].section("::::",0,0) )->setWhatsThis(colors[i].section("::::",1,1) ); }
  m_ui->tool_color->setMenu(colorMenu);
  connect(colorMenu, SIGNAL(triggered(QAction*)), this, SLOT(colorPicked(QAction*)) );
}

QSSEditorDialog::~QSSEditorDialog(){
  delete m_ui;
}

void QSSEditorDialog::save(){
  QFile file(m_filePath);
  file.open(QIODevice::WriteOnly);
  file.write(m_ui->textEdit->toPlainText().toUtf8());
}

void QSSEditorDialog::hideEvent(QHideEvent *){
  QSettings settings(lthemeengine::configFile(), QSettings::IniFormat);
  settings.setValue("QSSEditor/geometry", saveGeometry());
}

void QSSEditorDialog::on_buttonBox_clicked(QAbstractButton *button){
  QDialogButtonBox::StandardButton id = m_ui->buttonBox->standardButton(button);
  if(id == QDialogButtonBox::Ok){
    save();
    accept();
    }
  else if(id == QDialogButtonBox::Save){ save(); }
  else{ reject(); }
}

void QSSEditorDialog::colorPicked(QAction* act){
  QString id = act->whatsThis();
  if(id.isEmpty()){ return; }
  m_ui->textEdit->insertPlainText( QString("palette(%1)").arg(id) );
}
