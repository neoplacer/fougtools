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

#include "widget_tools.h"

#include <QtGui/QAbstractScrollArea>
#include <QtGui/QScrollBar>
#include <QtGui/QWidget>

namespace qttools {

/*! \brief Move position of \p widget so it is displayed stuck to the right of \p nextTo
 */
void moveWidgetRightTo(QWidget* widget, const QWidget* nextTo)
{
  const QRect frameGeom = nextTo->frameGeometry();
  widget->move(nextTo->mapToGlobal(QPoint(frameGeom.width(), 0)));
}

/*! \brief Move position of \p widget so it is displayed stuck to the left of \p nextTo
 */
void moveWidgetLeftTo(QWidget* widget, const QWidget* nextTo)
{
  //const QRect nextToFrameGeom = nextTo->frameGeometry();
  const QRect widgetFrameGeom = widget->frameGeometry();
  widget->move(nextTo->mapToGlobal(QPoint(-widgetFrameGeom.width(), 0)));
}

/*! \brief Current slide positions of the horizontal and vertical scroll bars
 */
QPair<int, int> horizAndVertScrollValue(const QAbstractScrollArea* area)
{
  return qMakePair(area->horizontalScrollBar()->value(),
                   area->verticalScrollBar()->value());
}

/*! \brief Set the current slide positions of the horizontal and vertical scroll bars to \p values
 */
void setHorizAndVertScrollValue(QAbstractScrollArea* area, const QPair<int, int>& values)
{
  area->horizontalScrollBar()->setValue(values.first);
  area->verticalScrollBar()->setValue(values.second);
}

} // namespace qttools
