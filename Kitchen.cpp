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
Kitchen::Kitchen() : ArrayBag<Dish>(), total_prep_time_(0),count_elaborate_(0) {

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
bool Kitchen::newOrder(const Dish& a_dish) {
    bool success = add(dish); //Add only if not found and return the status
    if (success){
        total_prep_time_ += dish.getPrepTime();
        if (dish.getIngredients().size() >= 5 && dish.getPrepTime() >= 60){
            count_elaborate_++;
        }
    }
    return success;
}

/**
     * @param : A reference to a `Dish` leaving the kitchen.
     * @return : Returns true if a dish was successfully removed from the kitchen (i.e.,items_), false otherwise.
     * @post : Removes the dish from the kitchen and updates the preparation time sum.
     * If the `Dish` is elaborate, it also updates the elaborate count.
     */
bool Kitchen::serveDish(const Dish& a_dish) {
    bool remove_success = remove(dish);

    if (remove_success){
        total_prep_time_ -= dish.getPrepTime();
        if (dish.getIngredients().size() >= 5 && dish.getPrepTime() >= 60){
            count_elaborate_--;
        }
    }
    return remove_success;
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
int Kitchen::calculateAvgPrepTime() {
    int current_size = getCurrentSize();
    double average;

    if (current_size == 0){
        return 0;
    }

    average = static_cast<double>(total_prep_time_)/current_size;
    return static_cast<int>(average + 0.5); // rounding and truncate method
}

int Kitchen::elaborateDishCount() {
    return count_elaborate_;
}

/**
 * @return : The percentage (double) of all the elaborate dishes in the
 * kitchen. The lowest possible percentage should be 0%.
 * @post : Computes the percentage of elaborate dishes in the kitchen
 * rounded up to 2 decimal places.
 */
double Kitchen::calculateElaboratePercentage() {
    int totalDishes = getCurrentSize();
    double percentage;

    // If there are no dishes, return 0% to avoid division by zero
    if (totalDishes == 0) {
        return 0.0;
    }

    // Calculate the percentage
    percentage = (static_cast<double>(count_elaborate_) / totalDishes) * 100;

    // Round the result to 2 decimal places
    return round(percentage * 100) / 100.0;
}

/**
 * @param : A reference to a string representing a cuisine type with a value in
 * ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN","FRENCH", "OTHER"].
 * @return : An integer tally of the number of dishes in the kitchen of the given cuisine type.
 * If the argument string does not match one of the expected cuisine types, the tally is zero.
 * NOTE: No pre-processing of the input string necessary, only uppercase input will match.
 */
int Kitchen::tallyCuisineTypes(const std::string& cuisineType) {
    int count = 0;

    // Count the number of dishes with the matching cuisine type
    for (int i = 0; i < getCurrentSize(); ++i) {
        if (items_[i].getCuisineType() == cuisineType){
            count++;
        }
    }

    return count;
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
    int counts[] = {0,0,0,0,0,0,0};
    int i;
    std::string cuisine_type;

    for(i=0; i < getCurrentSize(); i++){
        cuisine_type =  items_[i].getCuisineType();
        if (cuisine_type == "ITALIAN"){
            counts[0] = counts[0] + 1;
        }
        else if (cuisine_type == "MEXICAN"){
            counts[1] = counts[1] + 1;
        }
        else if (cuisine_type == "CHINESE"){
            counts[2] = counts[2] + 1;
        }
        else if (cuisine_type == "INDIAN"){
            counts[3] = counts[3] + 1;
        }
        else if (cuisine_type == "AMERICAN"){
            counts[4] = counts[4] + 1;
        }
        else if (cuisine_type == "FRENCH"){
            counts[5] = counts[5] + 1;
        }
        else if (cuisine_type == "OTHER"){
            counts[6] = counts[6] + 1;
        }
    }
    std::cout << "ITALIAN: "<< counts[0] <<"\nMEXICAN: " << counts[1] << "\nCHINESE: " << counts[2]
    <<"\nINDIAN: " << counts[3] << "\nAMERICAN: " << counts[4] << "\nFRENCH: " << counts[5] << "\nOTHER: " << counts[6]
    <<std::endl << std::endl;

    std::cout << "AVERAGE PREP TIME: " << calculateAvgPrepTime() <<"\nELABORATE DISHES: "<< calculateElaboratePercentage() << "%\n\n";
}


