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

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.inet.StandardHost;
import ned.DatarateChannel;


network LREDEMO
{
    @display("bgb=803,500");
    submodules:
        sender: StandardHost {
            @display("p=257,247");
        }
        receiver: StandardHost {
            @display("p=513,247");
        }
        configurator: IPv4NetworkConfigurator {
            @display("p=52.454998,37.32375");
        }
        lre: LRE {
            @display("p=52.454998,112.979996");
        }
    connections:
        sender.pppg++ <--> DatarateChannel <--> receiver.pppg++;
}
