/**
 * CFunctionDB
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CFunctionDB
#define COPASI_CFunctionDB

#include <string>

#include "utilities/utilities.h"
#include "CKinFunction.h"

class CFunctionDB
  {
    // Attributes

  private:
    /**
     *  Filename which contains the function database
     */
    string mFilename;

    /**
     *  Vector of the currently loaded functions
     *  @supplierCardinality 0..*
     */
    CCopasiVectorNS < CFunction > mLoadedFunctions;

    // Operations

  public:
    /**
     *
     */
    CFunctionDB();

    /**
     *
     */
    void initialize();

    /**
     *
     */
    ~CFunctionDB();

    /**
     *
     */
    void cleanup();

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return mFail
     */
    C_INT32 load(CReadConfig & configbuffer);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     */
    C_INT32 save(CWriteConfig & configbuffer);

    /**
     *
     */
    void setFilename(const string & filename);

    /**
     *
     */
    string getFilename() const;

    /**
     *  Load the function functionName from the database
     *  @param "const string" &functionName
     *  @return CKinFunction &
     */
    CFunction * dBLoad(const string & functionName);

    /**
     *  Add the function to the database
     *  @param CKinFunction &function
     *  @return C_INT32 Fail
     */

    void add
      (CFunction * function);

    /**
     *  Delete the function functionName from the database
     *  @param "const string" &functionName
     *  @return C_INT32 Fail
     */
    void dBDelete(const string & functionName);

    /**
     *  Search for a function among the loaded functions. If no
     *  function is found NULL is returned
     *  @param "const string" &functionName
     *  @return CFunction *
     */
    CFunction * findFunction(const string & functionName);

    /**
     *  Search for a function among the loaded functions. If no
     *  function is found the database is searched and the apropriate 
     *  function is loaded.
     *  @param "const string" &functionName
     *  @return CFunction *
     */
    CFunction * findLoadFunction(const string & functionName);

    /**
     *  Retrieves the vector of loaded functions.
     *  @return "CCopasiVectorNS < CKinFunction > &" loadedFunctions
     */
    CCopasiVectorNS < CFunction > & loadedFunctions();

    /**
     *  Retrieves the vector of functions that are suitable for a
    *  number of substrates, products and reversibility status.
     *  @param "const unsigned C_INT32" noSubstrates the number of substrates
     *  @param "const unsigned C_INT32" noProducts the number of products
     *  @param "const TriLogic" reversible the reversibility status
     *  @return "CCopasiVectorN < CKinFunction > " suitableFunctions
     */
    CCopasiVectorN < CFunction > suitableFunctions(const unsigned C_INT32 noSubstrates,
        const unsigned C_INT32 noProducts,
        const TriLogic reversible);
  };

#endif // COPASI_CFunctionDB
