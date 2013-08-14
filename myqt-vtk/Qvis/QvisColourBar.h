/*

  This is mostly taken from QvisGaussianOpacityBar, with a bunch oif changes
  to handle rectanlges instead of Gaussians.

*/

#ifndef QVIS_COLOUR_BAR_H
#define QVIS_COLOUR_BAR_H
//---------------------------------------------------------------------------
#include "QvisAbstractOpacityBar.h"
//---------------------------------------------------------------------------
class QPixmap;
//---------------------------------------------------------------------------
class QvisColourBar : public QvisAbstractOpacityBar
{
    Q_OBJECT
  public:
                  QvisColourBar(QWidget *parent=NULL, const char *name=NULL);
                 ~QvisColourBar();
    void          setBackgroundColourData(int N, int *data);
    virtual void  getRawOpacities(int, float *);

  protected:
    void          paintToPixmap(int,int);
};

#endif
