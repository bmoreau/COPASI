/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiMessage.cpp,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/02/25 01:43:29 $
   End CVS Header */

// CCopasiMessage
//
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001

#include <string>
#include <iostream>

#include <time.h>
#include <stdio.h>
#include <stdarg.h>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "CCopasiMessage.h"
#include "messages.h"
#include "CCopasiException.h"

std::string TimeStamp();
#define INITIALTEXTSIZE 1024

std::stack< CCopasiMessage > CCopasiMessage::mMessageStack;

CCopasiMessage CCopasiMessage::getLastMessage()
{
  if (mMessageStack.empty())
    CCopasiMessage(CCopasiMessage::RAW,
                   MCCopasiMessage + 1);

  CCopasiMessage Message(mMessageStack.top());
  mMessageStack.pop();

  return Message;
}

void CCopasiMessage::clearStack()
{
  while (mMessageStack.size()) mMessageStack.pop();

  return;
}

CCopasiMessage::CCopasiMessage(void):
    mText(),
    mType(CCopasiMessage::RAW),
    mNumber(0)
{}

CCopasiMessage::CCopasiMessage(const CCopasiMessage & src):
    mText(src.mText),
    mType(src.mType),
    mNumber(src.mNumber)
{}

CCopasiMessage::CCopasiMessage(CCopasiMessage::Type type,
                               const char *format, ...)
{
  C_INT32 TextSize = INITIALTEXTSIZE;
  C_INT32 Printed = 0;

  va_list Arguments; // = NULL;
  va_start(Arguments, format);

  char *Text = NULL;
  Text = new char[TextSize + 1];

  Printed = vsnprintf(Text, TextSize + 1, format, Arguments);

  while (Printed < 0 || TextSize < Printed)
    {
      delete [] Text;

      (Printed < 0) ? TextSize *= 2 : TextSize = Printed;
      Text = new char[TextSize + 1];

      Printed = vsnprintf(Text, TextSize, format, Arguments);
    }

  mText = Text;
  mType = type;
  mNumber = 0;

  va_end(Arguments);

  handler();
}

CCopasiMessage::CCopasiMessage(CCopasiMessage::Type type,
                               unsigned C_INT32 number, ...)
{
  C_INT32 i = 0;

  C_INT32 TextSize = INITIALTEXTSIZE;
  C_INT32 Printed = 0;

  while (Messages[i].No != number && Messages[i].Text)
    i++;

  if (!Messages[i].Text)
    fatalError();

  va_list Arguments; // = NULL;
  va_start(Arguments, number);

  char *Text = NULL;
  Text = new char[TextSize + 1];

  Printed = vsnprintf(Text, TextSize, Messages[i].Text, Arguments);

  while (Printed < 0 || TextSize < Printed)
    {
      delete [] Text;

      (Printed < 0) ? TextSize *= 2 : TextSize = Printed;
      Text = new char[TextSize + 1];

      Printed = vsnprintf(Text, TextSize, Messages[i].Text, Arguments);
    }

  mText = Text;
  mType = type;
  mNumber = number;

  va_end(Arguments);

  handler();
}

void CCopasiMessage::handler()
{
  std::string Text = mText;

  switch (mType)
    {
    case RAW:
      mText = "";
      break;

    case TRACE:
      mText = ">TRACE   ";
      mText += TimeStamp();
      mText += "< ";
      break;

    case WARNING:
      mText = ">WARNING ";
      mText += TimeStamp();
      mText += "< ";
      break;

    case ERROR:
      mText = ">ERROR   ";
      mText += TimeStamp();
      mText += "< ";
      break;
    }

  mText += Text;

  if (mType != RAW) lineBreak();

  mMessageStack.push(*this);

  if (mType == ERROR)
    {
#ifdef COPASI_DEBUG
      DebugFile << mText << std::endl;
#endif // COPASI_DEBUG

      throw CCopasiException(*this);
    }
  else
    {
      std::cout << mText << std::endl;
    }
}

// overload assignment operator
CCopasiMessage &CCopasiMessage::operator=(const CCopasiMessage &RHS)
{
  mText = RHS.mText;
  mType = RHS.mType;
  mNumber = RHS.mNumber;

  return *this;
}
CCopasiMessage::~CCopasiMessage(void) {}
const std::string & CCopasiMessage::getText(void) const {return mText;}
const CCopasiMessage::Type & CCopasiMessage::getType(void) const {return mType;}
const unsigned C_INT32 & CCopasiMessage::getNumber(void) const {return mNumber;}

std::string TimeStamp()
{
  time_t Time;
  tm *sTime = NULL;
  char str[20];

  time(&Time);
  sTime = localtime(&Time);

  if (sTime)
    {
      sprintf(str, "%d-%.02d-%.02d %.02d:%.02d:%.02d",
              sTime->tm_year + 1900,
              sTime->tm_mon + 1,
              sTime->tm_mday,
              sTime->tm_hour,
              sTime->tm_min,
              sTime->tm_sec);
    }
  else
    {
      sprintf(str, "0000-00-00 00:00:00");
    }

  return (std::string) str;
}

void CCopasiMessage::lineBreak()
{
  std::string Search("\n");
  std::string Replace("\n>                           < ");
  std::string::size_type pos = 0;

  while (true)
    {
      pos = mText.find(Search, pos);

      if (pos == std::string::npos)
        break;

      mText.replace(pos, Search.length(), Replace);

      pos += Replace.length();
    }
}
