// CKinFunction
// 
// CKinFunction.cpp based on UDKType.cpp from
// (C) Pedro Mendes 1995-2000
//
// Created for Copasi by Stefan Hoops
// (C) Stefan Hoops 2001

#ifndef COPASI_CKinFunction
#define COPASI_CKinFunction

#include <string>

#include "CReadConfig.h"
#include "CWriteConfig.h"
#include "CNodeK.h"

class CModel; // this should not be hear

// a class of kinetic functions
class CKinFunction
{
// Implementation
public:
    /**
     *  Default constructor
     */
    CKinFunction();

    /**
     *  This creates a kinetic function with a name an description
     *  @param "const string" &name
     *  @param "const string" &description
     */
    CKinFunction(const string &name, const string &description);

    /**
     *  Destructor
     */
    ~CKinFunction();

    /**
     * This adds a node to the function tree
     * @param "const char" type
     * @param "const char" subtype
     */
    int AddNode(const char type, const char subtype);

    /**
     * This adds a node of type N_NUMBER to the function tree
     * @param "const double" constant
     */
    int AddNode(const double constant);

    /**
     * This adds a node of type N_IDENTIFIER to the function tree
     * @param "const string" &name
     */
    int AddNode(const string &name);

    /**
     *  This calculates the value of the fuction tree
     *  @param "const CModel" &model
     *  @param double *s
     *  @param int r
     *  @return double
     */
    double CalcValue(CModel &model, double *s, int r);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    int Save(CWriteConfig &configbuffer);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    int Load(CReadConfig &configbuffer);

    /**
     *  This parses the function into a binary tree
     */
    int Parse(void);

    /**
     *  The finds the first occurence of an identifier with the given name
     *  @param "const string" &name
     *  @return int index of the identifier or -1 if not found
     */
    int FindId(const string &name);

    /**
     *  This returns the value of mReversible
     *  @return short
     */
    short IsReversible(void);

    /**
     *  This retrieves the name of the function
     *  @return string
     */
    string GetName(void);

    /**
     *  This returns the number of substrates in the function
     *  @return int
     */
    int SubstratesNo(void);

    /**
     *  This returns the number of products in the function
     *  @return int
     */
    int ProductsNo(void);

    /**
     *  This returns the number of modifiers in the function
     *  @return int
     */
    int ModifiersNo(void);

    /**
     *  This returns the number of parameters in the function
     *  @return int
     */
    int ParametersNo(void);

    /**
     *  This retrieves the name of the parameter with the given index
     *  @param int index
     *  @return string
     */
    string GetParameterName(int i);

    /**
     *  This retrieves the name of the modifier with the given index
     *  @param int index
     *  @return string
     */
    string GetModifierName(int i);

    /**
     *  This sets the name of the parameter with the given index
     *  @param "const string" &name
     *  @param int index
     */
    void SetParameterName(const string &name, int index);

    /**
     *  This sets the name of the modifier with the given index
     *  @param "const string" &name
     *  @param int index
     */
    void SetModifierName(const string &name, int index);
    
    /**
     *  This returns the vector of substrates of the function
     *  @return "vector < CNodeK * >"
     */
    vector < CNodeK * > *Substrates(void);
    
    /**
     *  This returns the vector of products of the function
     *  @return "vector < CNodeK * >"
     */
    vector < CNodeK * > *Products(void);
    
    /**
     *  This returns the vector of modifiers of the function
     *  @return "vector < CNodeK * >"
     */
    vector < CNodeK * > *Modifiers(void);
    
    /**
     *  This returns the vector of parameters of the function
     *  @return "vector < CNodeK * >"
     */
    vector < CNodeK * > *Parameters(void);
    
    /**
     *  This sets the type of the identifier with the given name
     *  @param "const string" &name
     *  @param int type
     */
    void SetIdentifierType(const string &name, int type);

    /**
     *  This retrieves the type of the identifier with the given name
     *  @param "const string" &name
     *  @return int type
     */
    int GetIdentifierType(const string &name);

private:
    /**
     *  This clears all nodes of the function tree
     */
    void ClearNodes(void);

    /**
     *  This  connects the nodes to build the binary function tree
     */
    int ConnectNodes(void);

    /**
     *  This function is part of the algorithm that builds the binary tree
     *  @param int priority
     *  @return CNodeK *
     */
    CNodeK *ParseExpression(int priority);

    /**
     *  This function is part of the algorithm that builds the binary tree
     *  @return CNodeK *
     */
    CNodeK *ParsePrimary(void);

    /**
     *  The name of the function
     */
    string mName;         // a name for the function

    /**
     *  The description of the function
     */
    string mDescription;  // string representation of the function

    /**
     *  The vector of nodes of the binary tree of the function
     */
    CNodeKVector mNodes;  // an array of NodeK (the binary tree)

    /**
     *  This indicates whether the function is reversible
     */
    int mReversible;      // TRUE if this is a reversible type


    /**
     *  Internal variable (We should get rid of this)
     */
    int nidx;            


    /**
     *  The vector of substrates
     */
    vector < CNodeK * > mSubstrates;  // number of substrates

    /**
     *  The vector of products
     */
    vector < CNodeK * > mProducts;  // number of products

    /**
     *  The vector of modifiers
     */
    vector < CNodeK * > mModifiers;    // number of modifiers

    /**
     *  The vector of parameters
     */
    vector < CNodeK * > mParameters;          // number of parameters

};

#endif // COPASI_CKinFunction
