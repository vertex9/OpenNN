/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.artelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   G E N E T I C   A L G O R I T H M   C L A S S   H E A D E R                                                */
/*                                                                                                              */
/*   Fernando Gomez                                                                                             */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   fernandogomez@artelnics.com                                                                                */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __GENETICALGORITHM_H__
#define __GENETICALGORITHM_H__

// System includes

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <limits>
#include <cmath>
#include <ctime>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

#include "training_strategy.h"

#include "inputs_selection_algorithm.h"

// TinyXml includes

#include "../tinyxml2/tinyxml2.h"

namespace OpenNN
{

///
/// This concrete class represents a genetic algorithm for the inputs selection of a neural network.
///

class GeneticAlgorithm : public InputsSelectionAlgorithm
{
public:
    // DEFAULT CONSTRUCTOR

    explicit GeneticAlgorithm(void);

    // TRAINING STRATEGY CONSTRUCTOR

    explicit GeneticAlgorithm(TrainingStrategy*);

    // XML CONSTRUCTOR

    explicit GeneticAlgorithm(const tinyxml2::XMLDocument&);

    // FILE CONSTRUCTOR

    explicit GeneticAlgorithm(const std::string&);

    // DESTRUCTOR

    virtual ~GeneticAlgorithm(void);

    // ENUMERATIONS

    /// Enumeration of available methods for the initialization of the population.

    enum InitializationMethod{Random, Weigthed};

    /// Enumeration of available methods for the crossover of the population.

    enum CrossoverMethod{Point1, Points2, UniformCrossover};

    /// Enumeration of available methods for the fitness assignement of the population.

    enum FitnessAssignment{ObjectiveBased, RankBased};

    // STRUCTURES

    ///
    /// This structure contains the training results for the genetic algorithm method.
    ///

    struct GeneticAlgorithmResults : public InputsSelectionAlgorithm::InputsSelectionResults
    {
        /// Default constructor.

        explicit GeneticAlgorithmResults(void) : InputsSelectionAlgorithm::InputsSelectionResults()
        {
        }

        /// Destructor.

        virtual ~GeneticAlgorithmResults(void)
        {
        }

        std::string to_string(void) const;

        /// Values of the minimum generalization performance in each generation.

        Vector<double> generation_minimum_generalization_history;

        /// Mean of the generalization performance in each generation.

        Vector<double> generation_mean_history;

        /// Standard deviation of the generalization performance in each generation.

        Vector<double> generation_standard_deviation_history;
    };

    // METHODS

    // Get methods

    const Vector< Vector<bool> >& get_population(void) const;

    const Matrix<double>& get_performance(void) const;

    const Vector<double>& get_fitness(void) const;

    const InitializationMethod& get_initialization_method(void) const;

    const CrossoverMethod& get_crossover_method(void) const;

    const FitnessAssignment& get_fitness_assignment_method(void) const;

    const size_t& get_population_size(void) const;

    const double& get_mutation_rate(void) const;

    const size_t& get_elitism_size(void) const;

    const size_t& get_crossover_first_point(void) const;

    const size_t& get_crossover_second_point(void) const;

    const double& get_selective_pressure(void) const;

    const size_t& get_maximum_generalization_failures(void) const;

    const bool& get_reserve_generation_mean(void) const;

    const bool& get_reserve_generation_standard_deviation(void) const;

    const bool& get_reserve_generation_minimum(void) const;

    std::string write_initialization_method(void) const;

    std::string write_crossover_method(void) const;

    std::string write_fitness_assignment_method(void) const;

    // Set methods

    void set_default(void);

    void set_population(const Vector< Vector<bool> >&);

    void set_performance(const Matrix<double>&);

    void set_fitness(const Vector<double>&);

    void set_inicialization_method(const InitializationMethod&);
    void set_fitness_assignment_method(const FitnessAssignment&);
    void set_crossover_method(const CrossoverMethod&);

    void set_inicialization_method(const std::string&);
    void set_fitness_assignment_method(const std::string&);
    void set_crossover_method(const std::string&);

    void set_population_size(const size_t&);

    void set_mutation_rate(const double&);

    void set_elitism_size(const size_t&);

    void set_crossover_first_point(const size_t&);

    void set_crossover_second_point(const size_t&);

    void set_selective_pressure(const double&);

    void set_maximum_generalization_failures(const size_t&);

    void set_reserve_generation_mean(const bool&);

    void set_reserve_generation_standard_deviation(const bool&);

    void set_reserve_generation_minimum(const bool&);


    // GENETIC METHODS

    // Population methods

    void initialize_population(void);

    void initialize_random_population(void);

    void initialize_weighted_population(void);

    void evaluate_population(void);

    void calculate_fitness(void);

    void calculate_objetive_fitness(void);

    void calculate_rank_fitness(void);

    void evolve_population(void);

    // Selection methods

    void perform_selection(void);

    // Crossover methods

    void perform_crossover(void);

    void perform_1point_crossover(void);

    void perform_2point_crossover(void);

    void perform_uniform_crossover(void);

    // Mutation methods

    void perform_mutation(void);

    // Order selection methods

    size_t get_optimal_individual_index(void) const;

    GeneticAlgorithmResults* perform_inputs_selection(void);

    // Serialization methods

    tinyxml2::XMLDocument* to_XML(void) const;

    void from_XML(const tinyxml2::XMLDocument&);

    void save(const std::string&) const;
    void load(const std::string&);

private:

    // MEMBERS

    // Population stuff

    /// Population matrix.

    Vector< Vector<bool> > population;

    /// Performance of population.

    Matrix<double> performance;

    /// Fitness of population.

    Vector<double> fitness;

    // Training operators

    /// Initialization method used in the algorithm.

    InitializationMethod initialization_method;

    /// Crossover method used in the algorithm.

    CrossoverMethod crossover_method;

    /// Fitness assignemet method used in the algorithm.

    FitnessAssignment fitness_assignment_method;

    /// Initial uses of the variables in the data set.

    Vector<Variables::Use> original_uses;

    /// Size of the population.

    size_t population_size;

    /// Mutation rate.
    /// The mutation rate value must be between 0 and 1.
    /// This is a parameter of the mutation operator.

    double mutation_rate;

    /// Elitism size.
    /// It represents the number of individuals which will always be selected for recombination.
    /// This is a parameter of the selection operator.

    size_t elitism_size;

    /// First point used in the one-point crossover method.
    /// If it is 0 the algorithm selects a random point for each pair of offsprings.

    size_t crossover_first_point;

    /// First point used in the two-point crossover method.
    /// If it is 0 the algorithm selects a random point for each pair of offsprings.

    size_t crossover_second_point;

    /// Linear ranking allows values for the selective pressure greater than 0.
    /// This is a parameter of the fitness assignment operator.

    double selective_pressure;

    // Inputs selection results

    /// True if the mean of generalization performance are to be reserved in each generation.

    bool reserve_generation_mean;

    /// True if the standard deviation of generalization performance are to be reserved in each generation.

    bool reserve_generation_standard_deviation;

    /// True if the minimum of generalization performance are to be reserved in each generation.

    bool reserve_generation_minimum;

    // STOPPING CRITERIA

    /// Maximum number of iterations at which the generalization performance increases.

    size_t maximum_generalization_failures;
};

}

#endif
