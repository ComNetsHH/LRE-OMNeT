Integration of the **Limited Relative Error algorithm** into OMNeT++
---

The LRE algorithm comes as a stand-alone implementation [here](https://github.com/ComNetsHH/LRE). It is included in this project as a Git submodule.

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.1313027.svg)](https://doi.org/10.5281/zenodo.1313027)


Usage
---

A novel LRE network entity is implemented that encapsulates the algorithm's functionality. This OMNeT++ project builds as a shared library. To use the entity, link against this library and then add the entity into your network description.

The algorithm can be configured through the NED parameters specified in the [LRE.ned](https://github.com/ComNetsHH/LRE-OMNeT/blob/master/LRE.ned). An example setup can be found in the [omnetpp.ini](https://github.com/ComNetsHH/LRE-OMNeT/blob/master/omnetpp.ini), which can also be run as an OMNeT++ project to see how LRE works in a trivial example network.

Generally the LRE entity subscribes to a signal whose name must be provided by the user. The simulation time should be disabled or set to a very large value. LRE will update its internal analysis each time a signal emission is captured, and if the relative errors calculated at each Markov chain state is small enough, LRE will end the simulation. 

Initialize submodule
---

After cloning this repository, you have to
```
git submodule init
git submodule update
```
to pull the LRE implementation.
