#pragma once
#include <memory>
#include <vector>
#include<functional> 

#include "Solver.h"
#include "System.h"
#include "Constraint.h"
//#include "NewtonRaphson.h"
#include "KineIntegrator.h"

namespace MbD {
	class System;
	class NewtonRaphson;

	class SystemSolver : public Solver
	{
		//system parts jointsMotions forcesTorques sensors variables icTypeSolver setsOfRedundantConstraints errorTolPosKine errorTolAccKine 
		//iterMaxPosKine iterMaxAccKine basicIntegrator tstartPasts tstart hmin hmax tend toutFirst hout direction corAbsTol corRelTol 
		//intAbsTol intRelTol iterMaxDyn orderMax translationLimit rotationLimit 
	public:
		static std::shared_ptr<SystemSolver> Create(System* x);
		SystemSolver(System* x) : system(x) {
		}
		void initialize() override;
		void initializeLocally() override;
		void initializeGlobally() override;
		void runAllIC();
		void runPosIC();
		void runVelIC();
		void runAccIC();
		bool needToRedoPosIC();
		void preCollision();
		void runCollisionDerivativeIC();
		void runBasicCollision();
		void runBasicKinematic();
		void partsJointsMotionsDo(const std::function <void(std::shared_ptr<Item>)>& f);

		System* system;
		std::shared_ptr<NewtonRaphson> icTypeSolver;
		std::shared_ptr<std::vector<std::vector<std::shared_ptr<Constraint>>>> setsOfRedundantConstraints;

		double errorTolPosKine = 1.0e-6;
		double errorTolAccKine = 1.0e-6;
		int iterMaxPosKine = 25;
		int iterMaxAccKine = 25;
		std::shared_ptr <KineIntegrator> basicIntegrator;
		std::shared_ptr<std::vector<double>> tstartPasts;
		double tstart = 0;
		double tend = 25;
		double toutFirst = 0.0;
		double hmin = 1.0e-9;
		double hmax = 1.0;
		double hout = 1.0e-1;
		double direction = 1;
		double corAbsTol = 0;
		double corRelTol = 0;
		double intAbsTol = 0;
		double intRelTol = 0;
		int iterMaxDyn = 0;
		int orderMax = 0;
		double translationLimit = 0;
		double rotationLimit = 0;
	};
}

