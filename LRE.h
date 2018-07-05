//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __LRE_LRE_H_
#define __LRE_LRE_H_

#include <omnetpp.h>

class LREEvaluator;

using namespace omnetpp;

class LRE : public cSimpleModule {
  private:

    class SignalListener : public cListener {
        public:
            SignalListener(LRE* parent);

        protected:
            virtual void receiveSignal(cComponent *source, simsignal_t signalID, bool b, cObject *details) override;
            virtual void receiveSignal(cComponent *source, simsignal_t signalID, long l, cObject *details) override;
            virtual void receiveSignal(cComponent *source, simsignal_t signalID, unsigned long l, cObject *details) override;
            virtual void receiveSignal(cComponent *source, simsignal_t signalID, double d, cObject *details) override;
            virtual void receiveSignal(cComponent *source, simsignal_t signalID, const SimTime& t, cObject *details) override;
            virtual void receiveSignal(cComponent *source, simsignal_t signalID, const char *s, cObject *details) override;
            virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) override;

        protected:
            LRE* parent = nullptr;
    };

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);

    protected:
        SignalListener signal_listener = SignalListener(this);
        LREEvaluator* lre_evaluator = nullptr;
        std::string output_file = "unnamed_file";

    public:
        ~LRE();

        LREEvaluator* getEvaluator() {
            return lre_evaluator;
        }

        const std::string& getOutputFilename() const {
            return output_file;
        }

        void lreIsFinished();
};

Define_Module(LRE);

#endif

