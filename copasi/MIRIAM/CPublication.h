// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/Attic/CPublication.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/02 13:35:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

/**
 *  CPublications: Stores publication details such as pubmed URL.
 *
 *
 */

#ifndef COPASI_CPUBLICATION
#define COPASI_CPUBLICATION

#include <string>

#include "report/CCopasiContainer.h"

#include "CRDFObject.h"

class CPublication : public CCopasiContainer
  {
    // Attributes
  private:

    std::string mKey;

    /** Object in RDF Graph corresponding to this object.*/
    CRDFObject* mpRDFObj;

    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & objectName
     * @param CRDFObject* pRDFObj
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CPublication(const std::string & objectName, const CCopasiContainer * pParent = NULL,
                 CRDFObject* pRDFObj = NULL);

    /**
     * Copy constructor
     * @param "const CPublication &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CPublication(const CPublication & src,
                 const CCopasiContainer * pParent = NULL);

    ~CPublication();
    void initObjects();

    /** Add the given name to Last name to get the full Name.
         *
         */

    const std::string getURL() const;

    void setURL(const std::string URL);

    CRDFObject& getRDFObject();

    const std::string getObjectName() const;

    /**
        *  Returns a string with the name of this Publication.
        *  @return std::string key
        */
    virtual const std::string & getKey() const;
  };

#endif //COPASI_CPUBLICATION
