//------------------------------
//
// File: distributionFactory.h
//
// Description: factory class for distribution.h classes.
//   The gbmDataContainer class is responsible for this.
//
//------------------------------

#ifndef __distributionFactory_h__
#define __distributionFactory_h__

//------------------------------
// Includes
//------------------------------
#include "configStructs.h"
#include "distribution.h"
#include "dataset.h"
#include <map>
#include <memory>
#include <Rcpp.h>

//------------------------------
// Class definition
//------------------------------
class DistributionFactory
{
private:
	//----------------------
	// Private Constructors
	//----------------------
	DistributionFactory(const DistributionFactory&);

	//----------------------
	// Private Operators
	//----------------------
	DistributionFactory& operator= (const DistributionFactory&);

	//-------------------
	// Private Variables
	//-------------------
	typedef CDistribution* (*distCreate)(DataDistParams&);
	std::map<std::string, distCreate> FactoryMap;

public:
	//---------------------
    // Public Constructor
	//---------------------
	DistributionFactory();

	//---------------------
	// Public destructor
	//---------------------
	~DistributionFactory(){};

	//---------------------
	// Public Functions
	//---------------------
	void RegisterDist(const std::string& DistFamily, distCreate PtrDistCreateFn);
	CDistribution* CreateDist(DataDistParams& distParams);
};

#endif // __distributionFactory_h__
