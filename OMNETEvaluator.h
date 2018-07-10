#ifndef LRE_GIT_OMNETEVALUATOR_H_
#define LRE_GIT_OMNETEVALUATOR_H_

#include "lre-src/LREEvaluator.h"

class OMNETEvaluator : public LREEvaluator {
public:
    OMNETEvaluator(LRE* parent, int type, double xMin, double xMax, double intSize, double error,
                  double preFirst, double gMin, bool forceRMinusAOk, int maxNrv, int skipInterval) : LREEvaluator(type, xMin, xMax, intSize, error, preFirst, gMin, forceRMinusAOk, maxNrv,  skipInterval) {
          this->parent = parent;
  }



  void put(double value) {
    LREEvaluator::put(value);

    // Inform user about progress.
    if (parent->doProgressReport()) {
        double current_x_level = evaluator->curXLev();
        if (current_x_level > last_x_level) {
            std::ofstream file_stream;
            file_stream.open(std::string("current_lre_level").c_str(), std::ios_base::app);
            if (last_x_level == -DBL_MAX) {
                file_stream << simTime().dbl() << "\t\t" << "init" << "\t" << current_x_level << std::endl;
                std::cout << "LRE x-level change " << "init" << " -> " << current_x_level << "." << std::endl;
            } else {
                file_stream << simTime().dbl() << "\t\t" << last_x_level << "\t" << current_x_level << std::endl;
                std::cout << "LRE x-level change " << last_x_level << " -> " << current_x_level << "." << std::endl;
            }
            file_stream.close();


            last_x_level = current_x_level;
        }
    }

    const wns::evaluation::statistics::DLRE::Phase& current_phase = evaluator->getPhase();
    if (current_phase == wns::evaluation::statistics::DLRE::Phase::finish) {
        std::cout << "LRE has finished. Stopping simulation, and writing output to '" << parent->getOutputFilename() << "'." << std::endl;
        printResult();
        parent->lreIsFinished();
    }
  }

protected:
  LRE* parent = nullptr;  
};

#endif
