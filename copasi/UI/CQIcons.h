// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQIcons.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:37:49 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQICONS_H
#define CQICONS_H

#include <QPixmap>

class CQIcons
{
public:
  enum IconID
  {
    Pause,
    Continue,
    Stop,
    SelectObject,
    Add,
    Copy,
    Delete,
    View,
    Edit,
    Save,
    Up,
    Down,
    unknown_ID
  };

  static QPixmap getIcon(const IconID & id);
};

#endif // CQICONS_H
