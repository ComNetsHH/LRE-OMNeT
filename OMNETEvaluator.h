#ifndef LRE_GIT_OMNETEVALUATOR_H_
#define LRE_GIT_OMNETEVALUATOR_H_

#include "lre-src/LREEvaluator.h"

class OMNETEvaluator : public LREEvaluator {
public:
    OMNETEvaluator(LRE* parent, int type, double xMin, double xMax, double intSize, double error,
                  double preFirst, double gMin, bool forceRMinusAOk, int maxNrv, int skipInterval) : LREEvaluator(type, xMin, xMax, intSize, error, preFirst, gMin, forceRMinusAOk, maxNrv,  skipInterval) {
          this->parent = parent;
  }

    virtual ~OMNETEvaluator() {
        printResult();
    }

  void put(double value) {
    LREEvaluator::put(value);

    // Inform user about progress.
    if (parent->doProgressReport()) {
        double current_x_level = evaluator->curXLev();
        if (current_x_level > last_x_level) {
            std::cout << "LRE x-level change " << ((last_x_level == -DBL_MAX) ? std::string("init") : std::to_string(last_x_level)) << " -> " << current_x_level << "." << std::endl;
            last_x_level = current_x_level;
        }
    }

    const wns::evaluation::statistics::DLRE::Phase& current_phase = evaluator->getPhase();
    if (current_phase == wns::evaluation::statistics::DLRE::Phase::finish) {
        parent->lreIsFinished();
    }
  }

  void printResult() {
      LREEvaluator::printResult(parent->getOutputFilename());
  }

protected:
  LRE* parent = nullptr;  
};

#endif
