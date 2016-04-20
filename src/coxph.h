//------------------------------------------------------------------------------
//
//  File:       coxph.h
//
//  Description:   Cox proportional hazard object
//
//  History:    3/26/2001   gregr created
//              2/14/2003   gregr: adapted for R implementation
//
//------------------------------------------------------------------------------

#ifndef __coxph_h__
#define __coxph_h__

//------------------------------
// Includes
//------------------------------

#include "distribution.h"
#include "matrix.h"
#include <memory>

//------------------------------
// Class definition
//------------------------------
class CCoxPH : public CDistribution
{

public:
	//---------------------
	// Factory Function
	//---------------------
	static CDistribution* Create(DataDistParams& distParams);

	//---------------------
	// Public destructor
	//---------------------
    virtual ~CCoxPH();

    //---------------------
    // Public Functions
    //---------------------
    void ComputeWorkingResponse(const CDataset* pData,
    		const double *adF,
				double *adZ);

    double InitF(const CDataset* pData);
    
    void FitBestConstant(const CDataset* pData,
    		const double *adF,
			 unsigned long cTermNodes,
			 double* adZ,
			 CTreeComps* pTreeComps);
    
    double Deviance(const CDataset* pData,
    				const double *adF,
                    bool isValidationSet=false);

    double BagImprovement(const CDataset& data,
    					  const double *adF,
    					  const bag& afInBag, const double shrinkage, const double* adFadj);


private:
    //----------------------
    // Private Constructors
    //----------------------
    CCoxPH(double* stats, int* sortedEnd, int* sortedSt, int* strats, bool tiedTimes);

    //----------------------
    // Private Functions
    //----------------------
    double LogLikelihood(const int n, const double* time2, const double* status,
						const double* weight, const double* eta, const int* strata,
						const int* sort2, double* resid, int method=0);

    double LogLikelihoodTiedTimes(const int n, const double *time1, const double *time2,
			  	  	  	  	  	  const double* status, const double* weight, const double* eta,
			  	  	  	  	  	  const int* strata, const int* sort1, const int* sort2, double* resid, int method=0);

    //-------------------
    // Private Variables
    //-------------------
    vector<double> vecdP;
    vector<double> vecdRiskTot;
    vector<double> vecdG;
    vector<unsigned long> veciK2Node;
    vector<unsigned long> veciNode2K;

    matrix<double> matH;
    matrix<double> matHinv;
    double* status;
    int* sortedEndTimes;
    int* sortedStartTimes;
    int* strata;
    bool isUpdatedCoxPh;
    const bool areTiedTimes;
};

#endif // __coxph_h__



