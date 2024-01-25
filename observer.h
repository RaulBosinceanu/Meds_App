#pragma once
#include <vector>

using std::vector;

/**
* Abstract class with update method
*/
class Observer {

public:
    virtual void update() = 0;

};


/**
* Abstract class for Subject - class that notify changes in it's state
*/
class Observable {

private:
    vector<Observer*> observers;

public:
    /**
     * Method that add a observer in vector
     * @param obs
     */
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }

    /**
     * Method that delete a observer in vector
     * @param obs
     */
    void removeObserver(Observer* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

    /**
     * Method that call update for each observer
     */
    void notify() {
        for (auto obs: observers) {
            obs->update();
        }
    }
};
