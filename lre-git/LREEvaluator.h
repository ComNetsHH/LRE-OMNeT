#ifndef LRE_GIT_LREEVALUATOR_H_
#define LRE_GIT_LREEVALUATOR_H_

#include "dlre.h"
#include "dlref.h"
#include "dlreg.h"
#include "dlrep.h"
#include "stateval.h"
#include <boost/shared_ptr.hpp>
#include "../LRE.h"
#include <iostream>
#include <fstream>
#include <float.h>

/**
* Wraps LRE functionality into object.
*/
class LREEvaluator {
private:
    /** DLRE inside a smart pointer. Needs to be a copyable pointer. */
    boost::shared_ptr<wns::evaluation::statistics::DLRE> evaluator;
    double last_x_level = -DBL_MAX;
    LRE* parent = nullptr;

    /** Common initialization for all constructors. */
    void init(int type, double xMin, double xMax, double intSize, double error,
                    double preFirst, double gMin,
                    bool forceRMinusAOk, int maxNrv, int skipInterval) {
        std::string name, description;
        wns::evaluation::statistics::StatEval::formatType format;
        switch (type) {
            case 1:
                name = "DLREF";
                description = "";
                evaluator.reset(new wns::evaluation::statistics::DLREF(
                                xMin,
                                xMax,
                                intSize,
                                error,
                                preFirst,
                                name,
                                description,
                                forceRMinusAOk,
                                gMin,
                                maxNrv,
                                skipInterval,
                                format
                ));
                break;
            case 2:
                name = "DLREG";
                description = "Equidistant";
                evaluator.reset(new wns::evaluation::statistics::DLREG(
                                xMin,
                                xMax,
                                intSize,
                                error,
                                preFirst,
                                name,
                                description,
                                forceRMinusAOk,
                                gMin,
                                maxNrv,
                                skipInterval,
                                format
                ));
                break;
            case 3:
                name = "DLREP";
                description = "Probability Function";
                evaluator.reset(new wns::evaluation::statistics::DLREP(
                                xMin,
                                xMax,
                                intSize,
                                error,
                                preFirst,
                                name,
                                description,
                                forceRMinusAOk,
                                // gMin,
                                maxNrv,
                                skipInterval,
                                format
                ));
                break;
            default:
                std::cerr << "Invalid evaluator type: " << type << std::endl;
                exit(-1);
        }

        std::ofstream file_stream;
        file_stream.open(std::string("current_lre_level").c_str());
        file_stream << "TIME\t\tX_LEVEL_FROM\t\tX_LEVEL_TO" << std::endl;
        file_stream.close();
    }

public:
  static const int   TYPE_DLRE = 0,
              TYPE_DLREF = 1,
              TYPE_DLREG = 2,
              TYPE_DLREP = 3;

    /** Full constructor. */
    LREEvaluator(LRE* parent, int type, double xMin, double xMax, double intSize, double error,
                    double preFirst, double gMin,
                    bool forceRMinusAOk, int maxNrv, int skipInterval) {
            this->parent = parent;
            this->init(type, xMin, xMax, intSize, error, preFirst, gMin, forceRMinusAOk, maxNrv,  skipInterval);
    }

    /** Convenience constructor for default values. */
    LREEvaluator(LRE* parent, int type, double xMin, double xMax){
        this->parent = parent;
        this->init(type, xMin, xMax, 0.01, 0.05, 0.1, 1E-2, 0, 100000, 0);
    }

    ~LREEvaluator() {
        printResult();
    }

    /** Puts new variable to probe. */
    void put(double value) {
        this->evaluator->put(value);

        double current_x_level = evaluator->curXLev();
        if (current_x_level > last_x_level) {
            std::ofstream file_stream;
            file_stream.open(std::string("current_lre_level").c_str(), std::ios_base::app);
            file_stream << simTime().dbl() << "\t\t" << last_x_level << "\t\t" << current_x_level << std::endl;
            file_stream.close();
            last_x_level = current_x_level;
        }

        const wns::evaluation::statistics::DLRE::Phase& current_phase = evaluator->getPhase();
        if (current_phase == wns::evaluation::statistics::DLRE::Phase::finish) {
            std::cout << "LRE has finished. Stopping simulation, and writing output to '" << parent->getOutputFilename() << "'." << std::endl;
            printResult();
            parent->lreIsFinished();
        }
    }

    void printResult() {
        std::ostream &stream = std::cout;
        this->evaluator->print(stream);

        std::ofstream file_stream;
        file_stream.open(parent->getOutputFilename().c_str());
        this->evaluator->print(file_stream);
    }
};

#endif /* LRE_GIT_LREEVALUATOR_H_ */
