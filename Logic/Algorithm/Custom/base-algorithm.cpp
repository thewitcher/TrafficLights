#include "base-algorithm.h"

unsigned int BaseAlgorithm::S_GENOME_SIZE = 2;
float BaseAlgorithm::S_REPLACEMENT_PROBABILITY = 0.5;
int BaseAlgorithm::S_POPULATION_SIZE = 10;
int BaseAlgorithm::S_GENERATIONS = 5;
int BaseAlgorithm::S_SCORE_FREQUENCY = 1;
int BaseAlgorithm::S_FLUSH_FREQUENCY = 5;
float BaseAlgorithm::S_MUTATION = 0.02;
float BaseAlgorithm::S_CROSSOVER = 0.2;
char* BaseAlgorithm::S_LOG_FILE = ( char* )"log_file.txt";


BaseAlgorithm::BaseAlgorithm()
{
}
