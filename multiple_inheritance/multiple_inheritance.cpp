#include <iostream>

using namespace std;

/**
 * We make all of these methods virtual as well to say that they could be overridden. So, most often
 * when you define methods probably most often you will make them virtual. Only they don't have to be
 * virtual if you are certain you're not going to override them.
 */
class MusicalInstrument {
  public:
    virtual void play() { cout << "Playing instrument ..." << endl; }
    virtual void reset() { cout << "Resetting instrument ..." << endl; }
    virtual ~MusicalInstrument(){};
};

class Machine {
  public:
    virtual void start() { cout << "Starting machine ..." << endl; }
    virtual void reset() { cout << "Resetting machine ..." << endl; }
    virtual ~Machine(){};
};

class Synthesizer : public Machine, public MusicalInstrument {
  public:
    virtual ~Synthesizer(){};
};

// Example command: g++ -Wall -std=c++17 -pthread multiple_inheritance.cpp && ./a.out
int main() {
    Synthesizer *pSynth = new Synthesizer();

    pSynth->play();
    pSynth->start();

    pSynth->Machine::reset();
    pSynth->MusicalInstrument::reset();

    /**
     * We need to specify the reset() method from the Machine parent or from the MusicalInstrument
     * parent, because both Machine and MusicalInstrument has the identical reset() method. Now one
     * reason multiple inheritance is BAD is because this requires us to know how Synthesizer are
     * actually implemented and we want to hide away and encapsulate details of implementation as
     * much as possible. We don't want the user of the Synthesizer class to have to know what the
     * superclasses of Synthesizer are. 
     * 
     * There's also the Diamond problem where we try to do multiple inheritance from classes that
     * share a base class somewhere down the line. Now, D is having the issue as described above to
     * call a method in A.
     *      A
     *     / \
     *    B   C
     *     \ /
     *      D
     * So in general, it's better to avoid multiple inheritance, unless there is a VERY strong and
     * good reason to do it. And if we do use it, it's best if the classes from which a class is
     * derived don't have any methods with identical prototypes like reset() method here.
     * 
     * In a nutshell, multiple inheritance could have the problem potentially with ambiguous methods
     * and we need to disambiguate those methods and that involves knowing implementation details of
     * the derived classes.
     * 
     * Output:
     * Playing instrument ...
     * Starting machine ...
     * Resetting machine ...
     * Resetting instrument ...
     */

    delete pSynth;
    return 0;
}
