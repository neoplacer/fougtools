/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
**
** As a counterpart to the access to the source code and  rights to copy,
** modify and redistribute granted by the license, users are provided only
** with a limited warranty  and the software's author,  the holder of the
** economic rights,  and the successive licensors  have only  limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading,  using,  modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean  that it is complicated to manipulate,  and  that  also
** therefore means  that it is reserved for developers  and  experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards their
** requirements in conditions enabling the security of their systems and/or
** data to be ensured and,  more generally, to use and operate it in the
** same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
**
****************************************************************************/

#include "wait_dialog.h"

#include "../core/task.h"
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QtGui/QApplication>
#include <QtGui/QBoxLayout>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>

namespace qttools {

class WaitDialogPrivate
{
public:
  WaitDialogPrivate(WaitDialog* parent)
    : m_waitLabel(NULL),
      m_progressBar(NULL),
      m_btnBox(NULL),
      m_updateTimer(new QTimer(parent)),
      m_minDuration(1000)
  {
  }

  QLabel* m_waitLabel;
  QProgressBar* m_progressBar;
  QDialogButtonBox* m_btnBox;
  QTimer* m_updateTimer;
  int m_minDuration;
};

WaitDialog::WaitDialog(QWidget* parent)
  : QDialog(parent),
    d_ptr(new WaitDialogPrivate(this))
{
  Q_D(WaitDialog);

  // Create the UI
  this->setObjectName("qttools__WaitDialog");
  this->setWindowTitle(tr("Waiting"));
  this->resize(170, 60);

  d->m_waitLabel = new QLabel(this);
  d->m_btnBox = new QDialogButtonBox(this);
  d->m_btnBox->setStandardButtons(QDialogButtonBox::Abort);
  d->m_progressBar = new QProgressBar(this);
  d->m_progressBar->setValue(0);
  d->m_progressBar->setTextVisible(false);

  QBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(d->m_waitLabel);
  layout->addWidget(d->m_progressBar);
  layout->addWidget(d->m_btnBox);
  layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

  // Configure
  this->setWindowModality(Qt::ApplicationModal);
  connect(d->m_updateTimer, SIGNAL(timeout()), this, SLOT(updateProgress()));
  d->m_updateTimer->setInterval(500);
}

WaitDialog::~WaitDialog()
{
  Q_D(WaitDialog);
  if (this->isWaiting())
    this->stopWait();
  delete d;
}

bool WaitDialog::isWaiting() const
{
  Q_D(const WaitDialog);
  return d->m_updateTimer->isActive();
}

void WaitDialog::setWaitLabel(const QString& text)
{
  Q_D(WaitDialog);
  d->m_waitLabel->setText(text);
}

void WaitDialog::setMinimumDuration(int msecs)
{
  Q_D(WaitDialog);
  d->m_minDuration = msecs;
}

void WaitDialog::startWait()
{
  Q_D(WaitDialog);
  if (this->isWaiting())
    return;
  d->m_progressBar->setValue(0);
  d->m_updateTimer->start();
}

void WaitDialog::stopWait()
{
  Q_D(WaitDialog);
  d->m_updateTimer->stop();
  this->close();
}

void WaitDialog::waitFor(qttools::Task* task, WaitForOption opt)
{
  Q_D(WaitDialog);

  QThread* taskThread = new QThread;
  task->bindToThread(taskThread);
  QEventLoop eventLoop;
  connect(taskThread, SIGNAL(started()), this, SLOT(startWait()));
  connect(taskThread, SIGNAL(finished()), this, SLOT(stopWait()));
  connect(taskThread, SIGNAL(finished()), &eventLoop, SLOT(quit()));
  connect(d->m_btnBox, SIGNAL(rejected()), task, SLOT(stop()));
  taskThread->start();
  eventLoop.exec();
  if (opt == WaitDialog::DeleteTaskOption)
    delete task;
}

void WaitDialog::updateProgress()
{
  Q_D(WaitDialog);

  const int incr = 5;
  const int currValue = d->m_progressBar->value();
  const int newValue = currValue + incr <= d->m_progressBar->maximum() ? currValue + incr :
                                                                         d->m_progressBar->minimum();
  d->m_progressBar->setValue(newValue);
  const int timeSinceStart = (newValue / incr) * d->m_updateTimer->interval();
  if (timeSinceStart >= d->m_minDuration && !this->isVisible())
    this->show();
  QApplication::processEvents();
}

} // namespace qttools
