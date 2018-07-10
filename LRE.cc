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

#include "LRE.h"

#include "OMNETEvaluator.h"

using namespace std;

void LRE::initialize() {
    string signal_name = par("signal_name");
    EV << "LRE subscribing to '" << signal_name << "' signal." << endl;
    // Subscribe at system level as signals travel upwards in the model hierarchy. In this way we'll catch all signals of this name.
    getSystemModule()->subscribe(signal_name.c_str(), &signal_listener);

    std::string name = par("output_file");
    this->output_file = name;
    std::string progress_name = par("progress_file");
    this->progress_file = progress_name;
    this->progress_interval = par("progress_interval");
    progress_message = new cMessage("progress_message");
    do_progress_report = par("progress_report").boolValue();
    do_progress_report_to_file = par("progress_report_to_file").boolValue();
    if (do_progress_report)
        scheduleAt(simTime() + progress_interval, progress_message);

    // Initialize LRE evaluator.
    string type = par("type");
    int type_num;
    if (type.compare("CDF") == 0)
        type_num = LREEvaluator::TYPE_DLREF;
    else if (type.compare("CCDF") == 0)
        type_num = LREEvaluator::TYPE_DLREG;
    else if (type.compare("PDF") == 0)
        type_num = LREEvaluator::TYPE_DLREP;
    else
        throw std::invalid_argument("Invalid LRE type: '" + type +"'.");

    double x_min = par("xmin").doubleValue(),
           x_max = par("xmax").doubleValue();

    int initial_x_state = par("initial_x_state");
    double bin_size = par("bin_size").doubleValue(),
           y_min = par("ymin").doubleValue(),
           max_error = par("max_error").doubleValue();
    bool enforce_large_sample_condition = par ("enforce_large_sample_condition").boolValue();
    int max_samples = par("max_samples"),
        evaluation_interval = par("evaluation_interval");

    lre_evaluator = new OMNETEvaluator(this, type_num, x_min, x_max, bin_size, max_error, initial_x_state, y_min, enforce_large_sample_condition, max_samples, evaluation_interval);
}

void LRE::lreIsFinished() {
    endSimulation();
}

void LRE::snapshot() {
    lre_evaluator->printSnapshot(do_progress_report_to_file);
}

void LRE::handleMessage(cMessage *msg) {
    if (msg == progress_message) {
        snapshot();
        scheduleAt(simTime() + progress_interval, progress_message);
    } else {
        cout << "LRE::handleMessage: " << msg->getName() << endl;
    }
}

LRE::SignalListener::SignalListener(LRE* parent) {
    this->parent = parent;
}

void LRE::SignalListener::receiveSignal(cComponent *source, simsignal_t signalID, bool b, cObject *details) {
    parent->getEvaluator()->put(double(b));
}

void LRE::SignalListener::receiveSignal(cComponent *source, simsignal_t signalID, long l, cObject *details) {
    parent->getEvaluator()->put(double(l));
}

void LRE::SignalListener::receiveSignal(cComponent *source, simsignal_t signalID, unsigned long l, cObject *details) {
    parent->getEvaluator()->put(double(l));
}

void LRE::SignalListener::receiveSignal(cComponent *source, simsignal_t signalID, double d, cObject *details) {
    parent->getEvaluator()->put(d);
}

void LRE::SignalListener::receiveSignal(cComponent *source, simsignal_t signalID, const SimTime& t, cObject *details) {
    parent->getEvaluator()->put(t.dbl());
}

void LRE::SignalListener::receiveSignal(cComponent *source, simsignal_t signalID, const char *s, cObject *details) {
    throw std::logic_error("LRE doesn't know what to do with a (const char*)-signal.");
}

void LRE::SignalListener::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) {
    throw std::logic_error("LRE doesn't know what to do with a (cObject*)-signal.");
}

LRE::~LRE() {
    delete lre_evaluator;
    if (progress_message->isScheduled())
        cancelEvent(progress_message);
    delete progress_message;
}
