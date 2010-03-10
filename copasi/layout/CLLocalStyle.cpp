// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLLocalStyle.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/03/10 12:26:12 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CLLocalStyle.h"

#include <assert.h>

#include <copasi/report/CCopasiRootContainer.h>
#include <copasi/report/CKeyFactory.h>

/**
 * Constructor.
 */
CLLocalStyle::CLLocalStyle(CCopasiContainer* pParent): CLStyle("LocalStyle", pParent)
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("LocalStyle", this);
}

/**
 * Copy Constructor.
 */
CLLocalStyle::CLLocalStyle(const CLLocalStyle& source, CCopasiContainer* pParent):
    CLStyle(source, pParent),
    mKeyList(source.mKeyList)
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("LocalStyle", this);
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLLocalStyle::CLLocalStyle(const LocalStyle& source, CCopasiContainer* pParent):
    CLStyle(source, "LocalStyle", pParent)
{
  this->mKey = CCopasiRootContainer::getKeyFactory()->add("LocalStyle", this);
  CLStyle::readIntoSet(CLStyle::createStringFromSet(source.getIdList()), this->mKeyList);
}

/**
 * Returns the number of keys in the key set.
 */
unsigned int CLLocalStyle::getNumKeys() const
{
  return this->mKeyList.size();
}

/**
 * Sets the key list.
 */
void CLLocalStyle::setKeyList(const std::set<std::string>& keyList)
{
  this->mKeyList = keyList;
}

/**
 * Returns the key list.
 */
const std::set<std::string>& CLLocalStyle::getKeyList() const
{
  return this->mKeyList;
}

/**
 * Checks if a certain key is in the set or not.
 */
bool CLLocalStyle::isKeyInSet(const std::string& key) const
{
  return (this->mKeyList.find(key) != this->mKeyList.end());
}

/**
 * Adds another key to the set.
 */
void CLLocalStyle::addKey(const std::string& key)
{
  this->mKeyList.insert(key);
}

/**
 * Removes an key from the set.
 */
void CLLocalStyle::removeKey(const std::string& key)
{
  this->mKeyList.erase(key);
}

/**
 * Converts this object to the corresponding SBML object.
 */
LocalStyle* CLLocalStyle::toSBML() const
{
  LocalStyle* pLS = new LocalStyle();
  this->addSBMLAttributes(pLS);
  std::set<std::string> s;
  CLStyle::readIntoSet(CLStyle::createStringFromSet(this->mKeyList), s);
  pLS->setIdList(s);
  return pLS;
}
