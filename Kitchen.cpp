/**
 * @file Kitchen.cpp
 * @brief This file contains the definition of the Kitchen class, which manages and stores a collection of dishes in a virtual bistro simulation.
 *
 * The Kitchen class provides functionality to add, serve, and remove dishes based on various criteria, as well as methods to track total preparation time,
 * elaborate dishes, and other statistics related to the kitchen's dishes.
 *
 * @date [10/15/2024]
 * @author [Farhana Sultana]
 */

#include "Kitchen.hpp"
/**
 * Default constructor.
 * Default-initializes all private members.
 */
Kitchen::Kitchen() : ArrayBag<Dish>(), total_prep_time_{0}, count_elaborate_{0} {

}// end default constructor

/**
 * @param : A reference to a `Dish` being added to the kitchen.
 * @post : If the given `Dish` is not already in the kitchen, adds the
 * `Dish` to the kitchen and updates the preparation time sum and elaborate
 * dish count if the dish is elaborate.
 * @return : Returns true if a `Dish` was successfully added to the kitchen, false otherwise.
 * Hint: Use the above definition of equality to help determine if a
 * `Dish` is already in the kitchen.
 */
bool Kitchen::newOrder(const Dish& a_dish) 
{
    if (add(a_dish)) 
    {
        totalPrepTime += a_dish.getPrepTime();
        if(a_dish.getIngredientCount() >= 5 && a_dish.getPrepTime() >= 60) 
            count_elaborate_++;
        
        return true;
    }
    else
    {
        return false;
    }
}
/**
     * @param : A reference to a `Dish` leaving the kitchen.
     * @return : Returns true if a dish was successfully removed from the kitchen (i.e.,items_), false otherwise.
     * @post : Removes the dish from the kitchen and updates the preparation time sum.
     * If the `Dish` is elaborate, it also updates the elaborate count.
     */
bool Kitchen::serveDish(const Dish& a_dish) 
{
    if (remove(a_dish)) 
    {
        totalPrepTime -= a_dish.getPrepTime();
        if(a_dish.getIngredientCount() >= 5 && a_dish.getPrepTime() >= 60)
            count_elaborate_--;
        
        return true;
    }
    else
    {
    return false;
    }
}
/**
 * @return : The integer sum of preparation times for all the dishes currently in the kitchen.
 */
int Kitchen::getPrepTimeSum() {
    return total_prep_time_;
}
/**
 * @return : The average preparation time (int) of all the dishes in the
 * kitchen. The lowest possible average prep time should be 0.
 * @post : Computes the average preparation time (double) of the kitchen rounded to the NEAREST integer.
 */
int Kitchen::calculateAvgPrepTime()
{
    return (total_prep_time_>0) ? round(double(total_prep_time_) / item_count_) : 0.0;
}

// Return the count of elaborate dishes in the kitchen
int Kitchen::elaborateDishCount() {
    return count_elaborate_;
}

/**
 * @return : The percentage (double) of all the elaborate dishes in the
 * kitchen. The lowest possible percentage should be 0%.
 * @post : Computes the percentage of elaborate dishes in the kitchen
 * rounded up to 2 decimal places.
 */
double Kitchen::calculateElaboratePercentage() 
{
    double elaborate_percent = (count_elaborate_>0) ?  (double(count_elaborate_) / item_count_) * 100: 0.0;
    return std::ceil(elaborate_percent*100.0) / 100.0; //round up to 2 decimal places

}

/**
 * @param : A reference to a string representing a cuisine type with a value in
 * ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN","FRENCH", "OTHER"].
 * @return : An integer tally of the number of dishes in the kitchen of the given cuisine type.
 * If the argument string does not match one of the expected cuisine types, the tally is zero.
 * NOTE: No pre-processing of the input string necessary, only uppercase input will match.
 */
int Kitchen::tallyCuisineTypes(const std::string &cuisineType) 
{
  int frequency = 0;
  int curr_index = 0;   
  while (curr_index < item_count_)
  {
    if (items_[curr_index].getCuisineType() == cuisinetype)
    {
      frequency++;
    } 

    curr_index++; 
  }

  return frequency;
}


/**
* @param : A reference to an integer representing the preparation time
* threshold of the dishes to be removed from the kitchen.
* @post : Removes all dishes from the kitchen whose preparation time is
* less than the given time.
* @return : The number of dishes removed from the kitchen.
*/
int Kitchen::releaseDishesBelowPrepTime(int threshold) {
    int removedCount = 0;
    int i,j;

    for (i = 0; i < getCurrentSize(); ++i) {
        if (items_[i].getPrepTime() < threshold){
            // Shift all to the left
            for (j = i; j < getCurrentSize()-1; ++j) {
                items_[j] = items_[j+1];
            }
            item_count_--;
            removedCount++;
            i--;
        }
    }

    return removedCount;
}

/**
     * @param : A reference to a string representing a cuisine type with a value in
     * ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN","FRENCH", "OTHER"].
     * @post : Removes all dishes from the kitchen whose cuisine type matches the given type.
     * @return : The number of dishes removed from the kitchen.
     * NOTE: No pre-processing of the input string necessary, uppercase input will match.
     * If the input string does not match one of the expected cuisine
     * types, do not remove any dishes.
     *
     */
int Kitchen::releaseDishesOfCuisineType(const std::string &cuisine_type){
    int removed_count = 0;
    int i,j;
    for (i = 0; i < getCurrentSize(); ++i) {
        if (items_[i].getCuisineType() == cuisine_type){
            // Shift all to the left
            for (j = i; j < getCurrentSize()-1; ++j) {
                items_[j] = items_[j+1];
            }
            item_count_--;
            removed_count++;
            i--;
        }
    }

    return removed_count;
}

/**
     * @post : Outputs a report of the dishes currently in the kitchen in the
     * form:
     *      "ITALIAN: {x}\nMEXICAN: {x}\nCHINESE: {x}\nINDIAN:{x}\nAMERICAN: {x}\nFRENCH: {x}\nOTHER: {x}\n\n
     *      AVERAGE PREP TIME: {x}\ELABORATE: {x}%\n"
     * Note that the average preparation time should be rounded to the NEAREST integer, and the
     * percentage of elaborate dishes in the kitchen should be rounded to 2 decimal places.
     *      Example output:
     *          ITALIAN: 2
     *          MEXICAN: 3
     *          CHINESE: 2
     *          INDIAN: 1
     *          AMERICAN: 1
     *          FRENCH: 2
     *          OTHER: 2
     *          AVERAGE PREP TIME: 62
     *          ELABORATE DISHES: 53.85%
     */
void Kitchen::kitchenReport()
{
  int italian = tallyCuisineType("ITALIAN");
  int mexican = tallyCuisineType("MeXICAN");
  int chinese = tallyCuisineType("CHINESE");
  int indian = tallyCuisineType("INDIAN");
  int american = tallyCuisineType("AMERICAN");
  int french = tallyCuisineType("FRENCH");
  int other = tallyCuisineType("OTHER");
    
  std::cout << "ITALIAN: " << italian << std::endl;
  std::cout << "MEXICAN: " << mexican << std::endl;
  std::cout << "CHINESE: " << chinese << std::endl;
  std::cout << "INDIAN: " << indian << std::endl;
  std::cout << "AMERICAN: " << american << std::endl;
  std::cout << "FRENCH: " << french << std::endl;
  std::cout << "OTHER: " << other << std::endl;
  std::cout << "\nAVERAGE PREP TIME: " << calculateAvgPrepTime() << std::endl;
  std::cout << "ELABORATE DISHES: " << std::fixed << std::setprecision(2) << calculateElaboratePercentage() << "%.\n\n";
}



