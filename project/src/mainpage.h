// Copyright 2019 Yongwoo Choi

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_


/*! \mainpage Guide for Users
 *
 * \section intro_sec Introduction
 *
 * For the bus scheduling project,
 * This page shows how to run the simulator step by step guide for non-technical users
 * This page describes how the passengers code written down and guide for technical users to improve further.
 *

# Non-technical User Guide
## How to run the program
### Environment requirement
####Your software must compile on a UMN cselabs machine
### A. Base Instruction.
1. Open the terminal
  - Search cmd
  - Find command prompt
  - Click it
2. Clone the repo
  - copy the command below <br>
```
    git clone https://github.umn.edu/umn-csci-3081-f19/repo-choix571
```
  - paste on the terminal(command prompt)
    - enter your cse lab user id when asked
    - enter you cse lab user password when asked
3. Access to the cloned folder
  - copy the command below and paste on the terminal <br>
```
    cd repo-choix571
```
  - Make the simulators
    - go to project folder <br>
```
    cd project
```
    - go to src file <br>
```
    cd src
```
    - make simulators <br>
```
      make
```

Running simulators
- There are 2 simulators you can run
  - configure simulator
  - visualization simulator

#### Right after Base Instruction

### B_1. Configure Simulator
1. go to project folder
  - copy below.
```
    cd ..
```
  - paste on the terminal
you should see
.../repo-choix571/project
then
2. go to config folder.
  ```
  cd config
  ```
3. create the txt file including your own simulator structure.
  - **Structure instruction is at the below**
4. go to project folder
  - Write below on the terminal
  ```
  cd ..
  ```
5. run config simulator
  - Write below on the terminal
```
    ./build/bin/config_sim <config_filename> <length_of_sim> <output_file>
```
    - config_filename : text file in form of ***.txt (E.g. config.txt), which
    must be created at 3.
    - length_of_sim : integer number which indicates how many time the
    simulator will be run.
    - output_file : text file in form of ***.txt (E.G. output.txt), where the output will be saved in.
    - If at least one of the user input is not given by user, it uses default config_filename(config.txt), length_of_sim(20), output_file(on terminal)<br>


---
### Config file structure instruction


Replace [ ] following your purpose

ROUTE_GENERAL, Campus Connector

Stop Name, Long, Lat, Pass Gen Prob

ROUTE, [Outgoing Route Name]

STOP, [First Stop Name], [Longitude], [Latitude], [Passenger Generating Probability]<br>
STOP, [Second Stop Name], [Longitude], [Latitude], [Passenger Generating Probability]<br>
. <br>
. <br>
. <br>
STOP, [Last Stop Name], [Longitude], [Latitude], [Passenger Generating Probability]

Route, [Incoming Route Name]

STOP, [First Stop Name], [Longitude], [Latitude], [Passenger Generating Probability] <br>
STOP, [Second Stop Name], [Longitude], [Latitude], [Passenger Generating Probability] <br>
. <br>
. <br>
. <br>
STOP, [Last Stop Name], [Longitude], [Latitude], [Passenger Generating Probability]<br>

___

> Only if you want to see the visualization of default simulator <br>
#### Right after Base Instruction

### B_2. Visualization Simulator

1. go to project folder
  - copy below.
```
    cd ..
```
  - paste on the terminal
you should see<br>
.../repo-choix571/project<br>
then <br>
2. run vis simulator
  - Write below on the terminal
```
    ./build/bin/vis_sim 8001
```
3. Navigate to the following address on your browser (Firefox/Chrome):
  - copy below
> http://127.0.0.1:8001/web_graphics/project.html <br>
  - paste on the Firefox/Chrome

4. Click Start


<br>
Technical User Guide
======


## What should I know before I get started?

### Basic description how the code works.
 We design simulator separate apart from graphics.
 Simulator updates the bus and the route only.
 Then bus updates the two routes and passengers in the bus.
 Route updates the stops in the route itself, and
 stops update the passengers at the stop.
 Stops are unique to the route. Each route has the uniques stops.
 When passengers are generated in the route, they can only be accessed through
 the route which is in the bus. The speed_ variable in bus class can determine
 how many steps that the bus moves at one time step.
 When the bus arrives at the stop, it unloads passengers, load passengers, and
 update the related variables as well. Each passenger has the destination
 stop when generated. So passenger is required to get off the bus when they
 arrive at the destination stop.
 However, they cannot decide which bus they will get on.
 Passengers, who are generated at the stop of the route,
 have to get on the bus that the route belongs to.

### Code description of Bus update and Route update
 Route update, one of the two updates in the simulator, updates the
 passengers at all stops. It is simple. Bus update is more complicated.
 Here is the logic of the update function in the bus class.
 1. Check if the bus arrives at the stop.
 If it is not arrived, update the passengers in the bus and the passengers at
 the stop and proceed the bus by subtracting remaining distance by speed.
 If it is arrived, proceed to 2.
 2. Unload first because it affects the max capacity of the bus;
 When iterating list of passengers, reverse_iterator is used because erasing
 the front elements in the list result in making second element to the
 first element right away, which causes segmentation error.
 3. Call function for loading passengers in the bus before at the stop;
 Placing load passenger function at the stop before in the bus results
 in the error because load passenger function in the stop class erases
 all the passengers at the stop so load passenger function in the bus class
 cannot handle work right.
 4. Check if it is at the end of the route or not.
 If it is at the end of the route, then check if current route is
 incoming route or outgoing route. If it is incoming route,
 then change the route to outgoing route.
 When changing incoming route to the outgoing route, setting similar to
 the one in constructor is used. Created the SetTransitDistance function
 to have access to the distance_left in route class.
 If current route is at the outgoing route, then set which_route_ to 3.
 This makes the bus to skip the update function from the time.
 5. Update after either case at 4. Updating distance_remaining_
  is handled differently for the better result.

### Problems addressed and solved
 As shown in the UML diagram, bus class does not have direct access to the
 stop class, which was a big problem when loading and the unloading.
 Bus has to use the route to have an access of the stop, and use the stop to
 get the passengers.
 When a bus arrives at the stop, passengers in the bus have to unload
 and passengers at the stop have to load into the bus.
 So Bus update can unloads the passengers in bus and calls the
 getpassengers using route, to get the passengers at the stop.
 With the pointer, bus can load the right passengers and loaded passengers
 can be removed from the stop.

### Design Decisions

When we make a significant decision in how we maintain the project and what we can or cannot support, we will document it in the [repo-choix571/tree/design-decisions repository](https://github.umn.edu/umn-csci-3081-f19/repo-choix571/tree/design-decisions). If you have a question around how we do things, check to see if it is documented there. If it is *not* documented there, please open a new topic on Issues and ask your question.

## How Can I contribute?


### Reporting Bugs

This section guides you through submitting a bug report for Simulator

Before creating bug reports, please check the issues and the information it asks for helps us resolve issues faster. Follow the Styleguides when fixing the bug.

> **Note:** If you find a **Closed** issue that seems like it is the same thing that you're experiencing, open a new issue and include a link to the original issue in the body of your new one.


## Styleguides

### Git Commit Messages

* Use the present tense ("Add feature" not "Added feature") <br>
* Use the imperative mood ("Move cursor to..." not "Moves cursor to...") <br>
    - :structure: `:structure:` when improving the format/structure of the code
    - :improve: `:improve:` when improving performance
    - :edit: `:edit:` when writing docs
    - :bug: `:bug:` when fixing a bug

 *
 *
 */

#endif  // SRC_MAINPAGE_H_
