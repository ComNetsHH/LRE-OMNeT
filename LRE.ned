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
package demo;

simple LRE
{
	parameters:
	    // Will subscribe to the signal of this name.
	    string signal_name = default("demo_signal");
	    string output_file = default("lre_output");
	    // Can be any of {CDF, CCDF, PDF}. 
	    string type = default("CCDF");
	    // Minimum value on x-axis.
	    double xmin = default(0);
	    // Maximum value on x-axis.
	    double xmax = default(500);
	    // Bin size on x-axis.
	    double bin_size = default(1.0);
	    // Maximum allowed relative error.
	    double max_error = default(0.05);
	    // Whether to enforce the 'large sample condition'.
	    bool enforce_large_sample_condition = default(false);
	    // Minimum value on y-axis where relative error is enforced (intended reliability).
	    double ymin = default(1e-5);
	    // Maximum number of samples to be considered (after this evaluation will stop and each bin will be evaluated if result is confident).
	    int max_samples = default(100000000);
	    // Evaluating if result is confident for each bin is expensive, if >0 evaluation will only be done every n samples.
	    int evaluation_interval = default(0);
	    // Initital state value on x-axis.	 
	    int initial_x_state = default(0);   
	    
    @display("i=block/cogwheel");
    @class(LRE);
}
