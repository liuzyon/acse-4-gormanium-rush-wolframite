# Gormanium-Rush: Optimal mineral recovery using Genetic Algorithms

[![MIT Licence](https://badges.frapsoft.com/os/mit/mit.svg?v=103)](https://opensource.org/licenses/mit-license.php)

Gormanium-Rush is a C++ package to implement optimised mineral recovery using Genetic Algorithms with a Python module for visualization.

## Table of Contents

- [About Gormanium-Rush](#about-gormanium-rush)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)


## About Gormanium-Rush

Gormanium-Rush can determine the optimum circuit configuration and performance for valuable-material-recycling circuit that contains several separation units. Each unit and overall circuit produce two products: a concentrate stream and a tailings stream. Parameters that affect the optimum circuit including the number of units, the price paid for gormanium relative to the cost of disposing of the waste material, and the purity of the input feed. The optimum circuit will be an economic decision based on the balance between how much should be paid for the product and penalised for a lack purity. Therefore, it's a compromise between the overall recovery (total mass of valuable material recovered) and purity (proportion of valuable material to the total material recovered).

The optimization algorithm used to find the solution is the genetic algorithm. It works in a manner similar to natural selection. The heart of the algorithm is a representation of the problem as a vector of numbers (genetic code). In this problem, the genetic code represents the connections in the circuit:
![image](https://github.com/acse-2020/acse-4-gormanium-rush-wolframite/blob/main/resources/circuit-vector.jpg)

The performance of the circuit is evaluated by the adaptability function, and the circuit with better performance is selected by the selection function. In this problem, we use Linear ranking selection.

Post-processing moudule can convert any circuit vector into an image of the circuit that this vector represents. Graphviz library was used in this module.


## Installation

To install Gormanium-Rush, run the following commands:

```
# get the code
git clone https://github.com/acse-2020/acse-4-gormanium-rush-wolframite.git
cd acse-4-gormanium-rush-wolframite

# install pre-requisites
pip install -r requirements.txt
```

The visualization python module requires a working python installation of Graphviz. For conda users a working environment can be 

```
conda env create -f environment.yml
conda activate acse-4-p3
```

or you can (conda) install the packages yourself
```
conda install graphviz python-graphviz
```


## Usage

This section will introduce how to use Gormanium-Rush and give some simple examples.

## Simulator

Run the main simulator with this command:

```
# run main simulator
g++ src/main.cpp
```

Firstly, the parameters used would be printed in console:

```
Starting The Gormanium Rush...
Gormanium feed rate: 10kg/s
Waste feed rate: 100kg/s
Purity of feed stream: 9.09091%
Gormanium price: 100£/kg
Waste cost: 500£/kg
The number of units in a circuit: 10
```

Then the simulating process would start. When the finished, the information of optimized circuit would be print.

```
The best vector is:
3 7 8 10 7 3 11 7 0 10 1 9 2 7 5 4 9 7 6 4 3
At generation: 53
The best performace is: 144.14
```

After this an info.txt would be generated in output folder, which is the dependent file of visualization.


### Visualization

Visualization relys on the file containing circuit configuration information, including circuit vector, iterations times, and performance score.
After reading in this file, the number of units will be automatically calculated and the connection diagram will be drawn.
In general, circuit simulation will automatically generate a document containing the best circuit configuration information. 

The provided eg_info.txt contains these informations:

Citcuit vector: 7 5 1 8 11 9 0 9 6 10 9 4 8 9 2 9 3 4 7 4 5 

Iteration times: 1000

performance score: 165.753

To visualise the output circuit, run the following command:

```
python post_processing.py
```

Then the circuit connection graph will be generated in output folder:
![image](https://github.com/acse-2020/acse-4-gormanium-rush-wolframite/blob/main/output/eg_circuit.png)

You can directly modify info.txt, enter your own vector and draw the circuit connection diagram.


## Contributing

Feel free to dive in! [Open an issue](https://github.com/acse-2020/acse-4-gormanium-rush-wolframite/issues/new) or submit PRs.

### Contributors

This project exists thanks to all the [people who contributed](https://github.com/acse-2020/acse-4-gormanium-rush-wolframite/graphs/contributors).


## License

[MIT](LICENSE) © acse-2020 group Wolframite

