// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/CNormalChoice.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/09/18 19:34:00 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CNormalChoice_H__
#define CNormalChoice_H__

#include "compareExpressions/CNormalBase.h"
#include <string>
#include <iostream>

class CNormalLogical;
class CNormalFraction;

class CNormalChoice : public CNormalBase
  {
  protected:
    CNormalLogical* mpCondition;
    CNormalFraction* mpTrue;
    CNormalFraction* mpFalse;

  public:
    CNormalChoice();
    CNormalChoice(const CNormalChoice& src);
    virtual ~CNormalChoice();

    virtual CNormalBase * copy() const;

    CNormalChoice& operator=(const CNormalChoice& src);
    bool operator==(const CNormalChoice& rhs) const;
    bool operator<(const CNormalChoice& rhs) const;

    bool setCondition(const CNormalLogical& cond);
    bool setTrueExpression(const CNormalFraction& branch);
    bool setFalseExpression(const CNormalFraction& branch);

    const CNormalLogical& getCondition() const;
    CNormalLogical& getCondition();

    const CNormalFraction& getTrueExpression() const;
    CNormalFraction& getTrueExpression();

    const CNormalFraction& getFalseExpression() const;
    CNormalFraction& getFalseExpression();

    static bool checkConditionTree(const CNormalBase& branch);
    static bool checkExpressionTree(const CNormalBase& branch);

    virtual std::string toString() const;
    virtual bool simplify();

    friend std::ostream& operator<<(std::ostream& os, const CNormalChoice& choice);
  };

#endif /* CNormalChoice_H__ */
