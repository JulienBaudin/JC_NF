#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "cours1.hpp"

//Surcharge du vector
// void export_csv(std::string f_name) const;

class SinglePath
{
	public:
		
		SinglePath(double start, double end, size_t nbSteps);
		~SinglePath(){};
		
		void InsertValue(double val);
		double GetState(double time);
		std::vector<double> GetAllValues();
		
		
	protected:
	
		std::vector<double> Values;
		double StartTime;
		double EndTime;
		size_t Nbsteps;
	
};

class RandomProcess
{
	public:
	
		RandomProcess(RandomGenerator* gen, int dim);//dim taille du vector chaque élément est un path entier, 
		//chq élément est un singlepath
		~RandomProcess(){};
		
		virtual void Simulate(double startTime,double EndTime, size_t nbSteps) = 0;
		SinglePath* GetPath(int pos = 0);
		double Expectation(size_t nb_simulation);
		
	protected:
	
		RandomGenerator* Generator;
		std::vector<SinglePath*> Paths; //On évite de faire des copies avec le pointeur qui pointe vers le vrai objet
		int dimension;
		
};


class Brownian1D : public RandomProcess
{
	public:
	
		Brownian1D(RandomGenerator* Gen);
		~Brownian1D(){};
		
		void Simulate(double startTime,double endTime,size_t nbSteps);
};

class BlackScholes1D : public RandomProcess
{
	public:
	
		BlackScholes1D(RandomGenerator* Gen, double spot, double rate, double vol);
		~BlackScholes1D(){};
		
	protected:
	
		double Spot;
		double Rate;
		double Vol;
};

class BSEuler1D : public BlackScholes1D
{
	public:
	
		BSEuler1D(RandomGenerator* Gen, double spot, double rate, double vol);
		~BSEuler1D(){};
		
		void Simulate(double startTime,double EndTime,size_t nbSteps);
		
};

class BlackScholes2D:public RandomProcess
{
	public:
	
		BlackScholes2D(RandomGenerator* Gen, double spot1,double spot2,double rate1, double rate2
		,double vol1,double vol2,double rho);
		~BlackScholes2D(){};
		
	protected:
	
		double Spot1;
		double Rate1;
		double Vol1;
		double Spot2;
		double Rate2;
		double Vol2;
		double Rho;
};
class BSEuler2D : public BlackScholes2D
{
	public:
	
		BSEuler2D(RandomGenerator* Gen, double spot1,double spot2,double rate1, double rate2
		,double vol1,double vol2,double rho);
		~BSEuler2D(){};
		
		void Simulate(double startTime,double EndTime,size_t nbSteps);
		
};

