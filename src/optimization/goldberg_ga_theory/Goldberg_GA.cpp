
#include"Goldberg_GA.h"

Goldberg_GA::Goldberg_GA(int population_size, double max_limit, double min_limit, float selection_pressure, float crossing_over_probability, float mutation_rate)
{
	generation=1;
	
	this->population_size= population_size;

	this->selection_pressure= selection_pressure;
	this->crossing_over_probability= crossing_over_probability;
	this->mutation_rate= mutation_rate;

	selected_population_size= population_size*(1-selection_pressure);

	if(selected_population_size<1)
	{
		selected_population_size=1;
	}

	this->max_limit= max_limit;
	this->min_limit= min_limit;

	printParameters();	
	

	if(initialized_seed==false)
	{

		srand(rand()*time(NULL));

		random.randomize(0.345356);
		//random.randomize(-1);
		
		//random.makeSeed();

		initialized_seed=true;

		printf("initialized\n");
	}
	
	tmp=(double*)malloc(sizeof(double)*population_size);
}

Goldberg_GA::~Goldberg_GA()
{
	int i;

	for(i=0;i<population_size;++i)
	{	
		free(population[i]);
	}
	free(population);
		
	for(i=0;i<population_size;++i)
	{	
		free(selected_population[i]);
	}
	free(selected_population);

}

void Goldberg_GA::printParameters()
{
	printf("population size %d\n",population_size);
	printf("selected population size %d\n",selected_population_size);
	printf("max_limit %f\n",max_limit);
	printf("min_limit %f\n",min_limit);
	printf("selection_pressure %f\n", selection_pressure);
	printf("crossing_over_probability %f\n", crossing_over_probability);
	printf("mutation_rate %f\n", mutation_rate);
}

double Goldberg_GA::optimize(Optimization_Problem** optimization_problem, int number_of_problems, double** solution)
{
	int i;

	if(number_of_problems!=1)
	{
		printf("ERROR: Differential Evolution can only solve one problem at a time, it is not multi-objective\n");
		exit(1);
	}
	
	/////////////// Allocating memory////////////////////

	problem= optimization_problem[0];
	
	//allocating 
	allocatePopulations();


	///////////////// initialization generate random population //////////////////////
	

	for(i=0;i<population_size;++i)
	{	
		generateRandomIndividual(i);
	
		//printf("random %.2f\n",random.uniform(0.0,0.99));

		tmp[i]= problem->objectiveFunction(population[i]);

	}

	plotHistogram("fitness", tmp,population_size);

	///////////////////BEGIN LOOP////////////////////////////////////////

	double best_ever_fitness= 999;

	for(i=0;i<1000;i++)
	{
		newGeneration();	
	
		int best_individual= getBestIndividual();
		double best_fitness= problem->objectiveFunction(population[best_individual]);
		
		if(best_ever_fitness > best_fitness)
		{
			best_ever_fitness= best_fitness;
		}
	}
	
	int best_individual= getBestIndividual();
	double best_fitness= problem->objectiveFunction(population[best_individual]);

	memcpy(*solution,population[best_individual],problem->problem_size*sizeof(double));

	//printf("Best individual %d fitness %f\n",best_individual, best_fitness);
	//printArray(population[best_individual],problem->problem_size);


	return best_ever_fitness;

}

double Goldberg_GA::optimizeDebug(Optimization_Problem** optimization_problem, int number_of_problems, double** solution)
{
	int i;
	
	if(number_of_problems!=1)
	{
		printf("ERROR: Differential Evolution can only solve one problem at a time, it is not multi-objective\n");
		exit(1);
	}

	
	/////////////// Allocating memory////////////////////

	problem= optimization_problem[0];
	
	//allocating 
	allocatePopulations();


	///////////////// initialization generate random population //////////////////////
	

	for(i=0;i<population_size;++i)
	{	
		generateRandomIndividual(i);
	
		//printf("random %.2f\n",random.uniform(0.0,0.99));
		
		tmp[i]=  problem->objectiveFunction(population[i]);
	}
	
	int best_individual= getBestIndividual();
	problem->printDetails(population[best_individual]);

	plotHistogram("fitness", tmp,population_size);

	///////////////////BEGIN LOOP////////////////////////////////////////

	double best_ever_fitness= 999;

	for(i=0;i<1000;i++)
	{
		newGeneration();	
	
		int best_individual= getBestIndividual();
		double best_fitness= problem->objectiveFunction(population[best_individual]);
		
		if(best_ever_fitness > best_fitness)
		{
			best_ever_fitness= best_fitness;
		}
	}
	
	best_individual= getBestIndividual();
	double best_fitness= problem->objectiveFunction(population[best_individual]);
	printf("Best fitness %f\n",best_fitness);
	problem->printDetails(population[best_individual]);


	memcpy(*solution,population[best_individual],problem->problem_size*sizeof(double));

	//printf("Best individual %d fitness %f\n",best_individual, best_fitness);
	//printArray(population[best_individual],problem->problem_size);


	return best_ever_fitness;

}

int Goldberg_GA::newGeneration()
{
	int i,j;

	////////////////selection  - N tournaments /////////////////////////
	
	for(i=0;i<selected_population_size;++i)
	{
		int champion_index= simple_tournament(2, population_size);
		tmp[i]=champion_index;
		//tmp[i]=  problem->objectiveFunction(population[champion_index]);

		//copy champion to the selected population
		for(j=0;j<problem->problem_size;++j)
		{
			selected_population[i][j]= population[champion_index][j];
		}

		tmp[i]=  problem->objectiveFunction(selected_population[i]);
	}
	
	//char name[32];
	//sprintf(name,"generation%d",generation);

	//plotHistogram(name,tmp,selected_population_size);
	plotHistogram("selected",tmp,selected_population_size);


	//////////// crossing over //////////////////
			
//	printf("problem_size %d\n", problem->problem_size);
	
	for(i=0;i<population_size;)
	{
		double random_number= random.uniform(0.0,0.99);


//		printf("random number %f cross %f\n", random_number, crossing_over_probability);
		
		//do crossing over (only if the probability of crossing over applies and if the population supports 2 individuals)
		//The population need to support 2 individuals, because this is the number of individuals generated by a crossing over
		if(i+1 < population_size && crossing_over_probability > random_number)
		{
			int father_index;
			int mother_index;


			if(selected_population-1 > 0)
			{
				father_index= (int)random.uniform(0,selected_population_size-1);
				mother_index= (int)random.uniform(0,selected_population_size-1);
			}
			else
			{
				father_index=0;
				mother_index=0;
			}
			
//			printArray(selected_population[father_index], problem->problem_size);
//			printArray(selected_population[mother_index], problem->problem_size);
			

			int variable_to_cut;
			if(problem->problem_size - 2 > 0)
			{
				variable_to_cut= (int) random.uniform(1,problem->problem_size-1);
			}
			else
			{	
				if(problem->problem_size == 2)
				{
					variable_to_cut=1;
				}
				else  //problem_size = 1
				{
					variable_to_cut=0;
				}

			}

//			printf("variable_to_cut %d\n",variable_to_cut);

			for(j=0;j<problem->problem_size;j++)
			{
				if(variable_to_cut > j)
				{
					//printf("mutate\n");
					population[i][j]= selected_population[father_index][j];
					population[i+1][j]= selected_population[mother_index][j];
			
				}
				else
				{
					population[i][j]= selected_population[mother_index][j];
					population[i+1][j]= selected_population[father_index][j];
				}
					
				//mutate
				if(mutation_rate > random.uniform(0.0,0.99))
				{
					//printf("mutate\n");
					generateMutatedVariable(i,j);
				}
				
				if(mutation_rate > random.uniform(0.0,0.99))
				{
					generateMutatedVariable(i+1,j);
				}

			}	
			
//			printArray(population[i], problem->problem_size);
//			printArray(population[i+1], problem->problem_size);
			
			i++;
			i++;

//			printf("crossing\n");

		}
		//only copy chromossome
		else
		{
	
			int copy_index;
			if(selected_population_size -1 > 0)
			{
				copy_index= (int)random.uniform(0,selected_population_size-1);
			}
			else
			{
				copy_index=0;
			}

			//////////// mutation ///////////////////////////
			for(j=0;j<problem->problem_size;j++)
			{

				//mutate
				if(mutation_rate > random.uniform(0.0,0.99))
				{
					//printf("mutate\n");
					generateMutatedVariable(i,j);
				}
				//do not mutate
				else
				{
					population[i][j]= selected_population[copy_index][j];
				}

			}	
	
			i++;
			
		}
	
	}

	generation++;

	return 0;
}

int Goldberg_GA::getBestIndividual()
{
	int i;
	int best_index=0;
	double best_fitness= problem->objectiveFunction(population[best_index]);

	for(i=1;i<population_size;++i)
	{	
		//if(isLower(problem->objectiveFunction(population[i]),best_fitness))
		//if(isGreater(problem->objectiveFunction(population[i]),best_fitness))
		if(problem->objectiveFunction(population[i]) > best_fitness)
		{
			best_index= i;
			best_fitness= problem->objectiveFunction(population[best_index]);
		}
	}
	
	return best_index;
}
	
void Goldberg_GA::generateRandomIndividual(int individual)
{
	int j;

	for(j=0;j<problem->problem_size;++j)
	{
		population[individual][j]= generateRandomVariable(j);
	}
}

double Goldberg_GA::generateRandomVariable(int variable)
{
	return (random.uniform(0.0,1.0)*(max_limit - min_limit) + min_limit);	
}
	
void Goldberg_GA::generateMutatedVariable(int individual, int variable)
{
       	double sinal = -1.0 + 2.0*(rand() % 2);

	population[individual][variable]+= ((double)sinal)*0.001;
}

void Goldberg_GA::allocatePopulations()
{
	int i;

	population= (double**)malloc(sizeof(double*)*population_size);
	for(i=0;i<population_size;++i)
	{	
		population[i]=(double*)malloc(sizeof(double)*problem->problem_size);
	}
		
	selected_population= (double**)malloc(sizeof(double*)*selected_population_size);
	for(i=0;i<selected_population_size;++i)
	{	
		selected_population[i]=(double*)malloc(sizeof(double)*problem->problem_size);
	}
}

//the best fitness among all participants wins
int Goldberg_GA::simple_tournament(int max_participants, int population_size)
{
	int i;
	//long best_index= rand()%population_size;
	int best_index;
	if(population_size -1 > 0)
	{
		best_index= (int)random.uniform(0,population_size-1);
//		printf("best %d\n",best_index);
	}
	else
	{
		best_index=0;
	}

	//float best_fitness= (*fitness_pointer)(population[best_index],generation, array_size);
	double best_fitness= problem->objectiveFunction(population[best_index]);

	for(i=1;i<max_participants;i++)
	{
		//get a random individual
		int new_index= (int)random.uniform(0,population_size-1);
	
		if(population_size -1 > 0)
		{
			new_index= (int)random.uniform(0,population_size-1);
//			printf("new %d\n",new_index);
		}
		else
		{
			new_index=0;
		}
		
		//float new_fitness= (*fitness_pointer)(population[new_index],generation, array_size);
		double new_fitness= problem->objectiveFunction(population[new_index]);
		
		//test fitness and replace the best_fitness in case it is better
		//if(isLower(new_fitness,best_fitness))
		//if(isGreater(new_fitness,best_fitness))
		if(new_fitness > best_fitness)
		{
			best_index= new_index;
			best_fitness= new_fitness;
		}
	}
		

	//printf("best index %ld fitness %.2f\n\n",best_index,best_fitness);
	//printf("best %d\n",best_index);
	
	return best_index;
}
		
// new_fitness > best_fitness ? And treat nans
bool Goldberg_GA::isGreater(double new_fitness, double best_fitness)
{
	//if best_fitness is nan
	//or if new_fitness is not nan and new_fitness is greater than best_fitness
	if( (isnan(best_fitness)) || (!isnan(new_fitness) && new_fitness > best_fitness) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

// new_fitness < best_fitness ? And treat nans
bool Goldberg_GA::isLower(double new_fitness, double best_fitness)
{
	//if best_fitness is nan
	//or if new_fitness is not nan and new_fitness is greater than best_fitness
	if( (isnan(best_fitness)) || (!isnan(new_fitness) && new_fitness < best_fitness) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Goldberg_GA::initialized_seed= false;
