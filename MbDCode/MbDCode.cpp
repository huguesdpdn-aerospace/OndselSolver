/*********************************************************************
 * @file  MbDCode.cpp
 *
 * @brief Program to assemble a piston crank system.
 *********************************************************************/

#include <iostream>	
#include "System.h"
#include "Constant.h"
#include "FullColumn.h"
#include "FullMatrix.h"
#include "DiagonalMatrix.h"
#include "Part.h"
#include "Joint.h"
#include "CylindricalJoint.h"
#include "RevoluteJoint.h"
#include "ZRotation.h"
#include "PartFrame.h"
#include "MarkerFrame.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"
#include "Product.h"
#include "Symbolic.h"
#include "SystemSolver.h"
#include "MbDCode.h"
#include "Time.h"
#include "CREATE.h"

using namespace MbD;

int main()
{
	std::cout << "Hello World!\n";
	System& TheSystem = System::getInstance("TheSystem");
	std::cout << "TheSystem.getName() " << TheSystem.getName() << std::endl;
	auto systemSolver = TheSystem.systemSolver;
	systemSolver->errorTolPosKine = 1.0e-6;
	systemSolver->errorTolAccKine = 1.0e-6;
	systemSolver->iterMaxPosKine = 25;
	systemSolver->iterMaxAccKine = 25;
	systemSolver->tstart = 0;
	systemSolver->tend = 25.0;
	systemSolver->hmin = 2.5e-8;
	systemSolver->hmax = 25.0;
	systemSolver->hout = 1.0;
	systemSolver->corAbsTol = 1.0e-6;
	systemSolver->corRelTol = 1.0e-6;
	systemSolver->intAbsTol = 1.0e-6;
	systemSolver->intRelTol = 1.0e-6;
	systemSolver->iterMaxDyn = 4;
	systemSolver->orderMax = 5;
	systemSolver->translationLimit = 9.6058421285615e9;
	systemSolver->rotationLimit = 0.5;

	std::string str;
	FColDsptr qX, qE, qXdot, omeOpO;
	FColDsptr rpmp;
	FMatDsptr aApm;
	FRowDsptr fullRow;
	//
	auto assembly1 = CREATE<Part>::With("/Assembly1");
	std::cout << "assembly1->getName() " << assembly1->getName() << std::endl;
	assembly1->m = 0.0;
	assembly1->aJ = std::make_shared<DiagonalMatrix<double>>(ListD{ 0, 0, 0 });
	qX = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	qE = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0, 1 });
	assembly1->setqX(qX);
	assembly1->setqE(qE);
	qXdot = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	omeOpO = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0, 1 });
	assembly1->setqXdot(qXdot);
	assembly1->setomeOpO(omeOpO);
	std::cout << "assembly1->getqX() " << assembly1->getqX()->toString() << std::endl;
	std::cout << "assembly1->getqE() " << assembly1->getqE()->toString() << std::endl;
	TheSystem.addPart(assembly1);
	{
		auto partFrame = assembly1->partFrame;
		auto marker1 = CREATE<MarkerFrame>::With("/Assembly1/Marker1");
		rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.38423366582893, 6.8384291794733e-9, -0.048029210642807 });
		marker1->setrpmp(rpmp);
		aApm = std::make_shared<FullMatrix<double>>(ListListD{
			{ 1, 0, 0 },
			{ 0, 0, 1 },
			{ 0, -1, 0 }
			});
		marker1->setaApm(aApm);
		partFrame->addMarkerFrame(marker1);
		//
		auto marker2 = CREATE<MarkerFrame>::With("/Assembly1/Marker2");
		rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.0, 0.0, 0.0 });
		marker2->setrpmp(rpmp);
		aApm = std::make_shared<FullMatrix<double>>(ListListD{
			{ 1, 0, 0 },
			{ 0, 1, 0 },
			{ 0, 0, 1 }
			});
		marker2->setaApm(aApm);
		partFrame->addMarkerFrame(marker2);
	}
	assembly1->asFixed();
	//
	auto crankPart1 = CREATE<Part>::With("/Assembly1/Part1");
	qX = std::make_shared<FullColumn<double>>(ListD{ 0.38423366582893, 6.8384291794733e-9, -0.048029210642807 });
	qE = std::make_shared<FullColumn<double>>(ListD{ 0.0, 0.0, 1.4248456266393e-10, 1.0 });
	crankPart1->setqX(qX);
	crankPart1->setqE(qE);
	TheSystem.parts->push_back(crankPart1);
	{
		auto partFrame = crankPart1->partFrame;
		auto marker1 = CREATE<MarkerFrame>::With("/Assembly1/Part1/Marker1");
		rpmp = std::make_shared<FullColumn<double>>(ListD{ -0.38423368514246, -2.6661567755108e-17, 0.048029210642807 });
		marker1->setrpmp(rpmp);
		aApm = std::make_shared<FullMatrix<double>>(ListListD{
			{ 1, 0, 0 },
			{ 0, 1, 0 },
			{ 0, 0, 1 }
			});
		marker1->setaApm(aApm);
		partFrame->addMarkerFrame(marker1);
		//
		auto marker2 = CREATE<MarkerFrame>::With("/Assembly1/Part1/Marker2");
		rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.38423368514246, -2.6661567755108e-17, 0.048029210642807 });
		marker2->setrpmp(rpmp);
		aApm = std::make_shared<FullMatrix<double>>(ListListD{
			{ 1, 0, 0 },
			{ 0, 1, 0 },
			{ 0, 0, 1 }
			});
		marker2->setaApm(aApm);
		partFrame->addMarkerFrame(marker2);
	}
	//
	auto conrodPart2 = CREATE<Part>::With("/Assembly1/Part2");
	qX = std::make_shared<FullColumn<double>>(ListD{ 0.38423366582893,  0.49215308269277,  0.048029210642807 });
	qE = std::make_shared<FullColumn<double>>(ListD{ 0.0, 0.0, 0.89871701272344, 0.4385290538168 });
	conrodPart2->setqX(qX);
	conrodPart2->setqE(qE);
	TheSystem.parts->push_back(conrodPart2);
	{
		auto partFrame = conrodPart2->partFrame;
		auto marker1 = CREATE<MarkerFrame>::With("/Assembly1/Part2/Marker1");
		rpmp = std::make_shared<FullColumn<double>>(ListD{ -0.6243797383565, 1.1997705489799e-16, -0.048029210642807 });
		marker1->setrpmp(rpmp);
		aApm = std::make_shared<FullMatrix<double>>(ListListD{
			{1.0, 2.7755575615629e-16, 0.0},
			{-2.7755575615629e-16, 1.0, 0.0},
			{0.0, 0.0, 1.0} 
			});
		marker1->setaApm(aApm);
		partFrame->addMarkerFrame(marker1);
		//
		auto marker2 = CREATE<MarkerFrame>::With("/Assembly1/Part2/Marker2");
		rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.6243797383565, -2.1329254204087e-16, -0.048029210642807 });
		marker2->setrpmp(rpmp);
		aApm = std::make_shared<FullMatrix<double>>(ListListD{
			{1.0, 2.4980018054066e-16, 2.2204460492503e-16},
			{-2.4980018054066e-16, 1.0, 4.1633363423443e-17},
			{-2.2204460492503e-16, -4.1633363423443e-17, 1.0} 
			});
		marker2->setaApm(aApm);
		partFrame->addMarkerFrame(marker2);
	}
	//
	auto pistonPart3 = CREATE<Part>::With("/Assembly1/Part3");
	qX = std::make_shared<FullColumn<double>>(ListD{ -1.284772285311e-18, 1.4645982581368, -4.788228906425e-17 });
	qE = std::make_shared<FullColumn<double>>(ListD{ 0.70710678118655, 0.70710678118655, 0.0, 0.0 });
	pistonPart3->setqX(qX);
	pistonPart3->setqE(qE);
	TheSystem.parts->push_back(pistonPart3);
	{
		auto partFrame = pistonPart3->partFrame;
		auto marker1 = CREATE<MarkerFrame>::With("/Assembly1/Part3/Marker1");
		rpmp = std::make_shared<FullColumn<double>>(ListD{ -0.48029210642807, 7.6201599718927e-18, -2.816737703896e-17 });
		marker1->setrpmp(rpmp);
		aApm = std::make_shared<FullMatrix<double>>(ListListD{
			{9.2444637330587e-33, 1.0, 2.2204460492503e-16},
			{1.0, -9.2444637330587e-33, -1.0785207688569e-32},
			{-1.0785207688569e-32, 2.2204460492503e-16, -1.0} 
			});
		marker1->setaApm(aApm);
		partFrame->addMarkerFrame(marker1);
		//
		auto marker2 = CREATE<MarkerFrame>::With("/Assembly1/Part3/Marker2");
		rpmp = std::make_shared<FullColumn<double>>(ListD{ 0.48029210642807, 1.7618247880058e-17, 2.5155758471256e-17 });
		marker2->setrpmp(rpmp);
		aApm = std::make_shared<FullMatrix<double>>(ListListD{
			{6.9388939039072e-18, -6.4146353042213e-50, 1.0},
			{1.0, -6.9388939039072e-18, 6.9388939039072e-18},
			{-6.9388939039072e-18, 1.0, -7.4837411882581e-50} 
			});
		marker2->setaApm(aApm);
		partFrame->addMarkerFrame(marker2);
	}
	//
	auto cylJoint4 = CREATE<CylindricalJoint>::With("/Assembly1/Joint4");
	cylJoint4->connectsItoJ(pistonPart3->partFrame->endFrame("/Assembly1/Part3/Marker2"), assembly1->partFrame->endFrame("/Assembly1/Marker1"));
	TheSystem.jointsMotions->push_back(cylJoint4);

	auto revJoint3 = CREATE<RevoluteJoint>::With("/Assembly1/Joint3");
	revJoint3->connectsItoJ(conrodPart2->partFrame->endFrame("/Assembly1/Part2/Marker2"), pistonPart3->partFrame->endFrame("/Assembly1/Part3/Marker1"));
	TheSystem.jointsMotions->push_back(revJoint3);
	
	auto revJoint2 = CREATE<RevoluteJoint>::With("/Assembly1/Joint2");
	revJoint2->connectsItoJ(crankPart1->partFrame->endFrame("/Assembly1/Part1/Marker2"), conrodPart2->partFrame->endFrame("/Assembly1/Part2/Marker1"));
	TheSystem.jointsMotions->push_back(revJoint2);
	
	auto revJoint1 = CREATE<RevoluteJoint>::With("/Assembly1/Joint1");
	revJoint1->connectsItoJ(assembly1->partFrame->endFrame("/Assembly1/Marker2"), crankPart1->partFrame->endFrame("/Assembly1/Part1/Marker1"));
	TheSystem.jointsMotions->push_back(revJoint1);
	
	auto rotMotion1 = CREATE<ZRotation>::With("/Assembly1/Motion1");
	rotMotion1->connectsItoJ(assembly1->partFrame->endFrame("/Assembly1/Marker2"), crankPart1->partFrame->endFrame("/Assembly1/Part1/Marker1"));
	auto omega = std::make_shared<Constant>(6.2831853071796);
	auto timeScale = std::make_shared<Constant>(0.04);
	rotMotion1->phiBlk = std::make_shared<Product>(omega, timeScale, TheSystem.time);
	TheSystem.jointsMotions->push_back(rotMotion1);
	//
	TheSystem.runKINEMATICS();
}