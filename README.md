# Gormanium-Rush: Optimal mineral recovery using Genetic Algorithms

[![Build Status for the Core backend](https://github.com/devitocodes/devito/workflows/CI-core/badge.svg)](https://github.com/devitocodes/devito/actions?query=workflow%3ACI-core)
[![Build Status with MPI](https://github.com/devitocodes/devito/workflows/CI-mpi/badge.svg)](https://github.com/devitocodes/devito/actions?query=workflow%3ACI-mpi)
[![Build Status on GPU](https://github.com/devitocodes/devito/workflows/CI-gpu/badge.svg)](https://github.com/devitocodes/devito/actions?query=workflow%3ACI-gpu)
[![Code Coverage](https://codecov.io/gh/devitocodes/devito/branch/master/graph/badge.svg)](https://codecov.io/gh/devitocodes/devito)
[![Slack Status](https://img.shields.io/badge/chat-on%20slack-%2336C5F0)](https://join.slack.com/t/devitocodes/shared_invite/zt-gtd2yxj9-Y31YKk_7lr9AwfXeL2iMFg)
[![asv](http://img.shields.io/badge/benchmarked%20by-asv-blue.svg?style=flat)](https://devitocodes.github.io/devito-performance)
[![PyPI version](https://badge.fury.io/py/devito.svg)](https://badge.fury.io/py/devito)
[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/devitocodes/devito/master)

Gormanium-Rush is a C++ and Python package to implement optimized mineral recovery using Genetic Algorithms.

## Table of Contents

- [About Gormanium-Rush](#about-gormanium-rush)
- [Installation](#installation)
- [Usage](#usage)
- [Performance](#performance)
- [Contributing](#contributing)
- [License](#license)


## About Gormanium-Rush

Gormanium-Rush can determine the optimum circuit configuration and performance for valuable-material-recycling circuit that contains serveral separation units. The circuit produces two products: a concentrate stream and a tailings stream. Parameters that affect the optimum circuit including the number of units, the price paid for gormanium relative to the cost of disposing of the waste material, and the purity of the input feed. The optimization algorithm used to find the solution is the genetic algorithm.


## Installation

To install Gormanium-Rush, run the following commands:
```
# get the code
git clone https://github.com/acse-2020/acse-4-gormanium-rush-wolframite.git
cd acse-4-gormanium-rush-wolframite

# install pre-requisites
pip install -r requirements.txt
```

### Automated testing


## Usage

To use Gormanium-Rush, first run the main simulator with this command:
```
# run main simulator
gcc src/main.cpp
```
This will generate and output.txt, which is the dependent file of visualization.

To visulize the output circuit, run the following command:
```
python Post_Processing.py
```
Then the circuit connection graph will be generate in output folder.


## Performance(API)

If you are interested in any of the following

* Generation of parallel code (CPU, GPU, multi-node via MPI);
* Performance tuning;
* Benchmarking operators;

then you should take a look at this
[README](https://github.com/devitocodes/devito/blob/master/benchmarks/user).

You may also be interested in
[TheMatrix](https://github.com/devitocodes/thematrix) -- a cross-architecture
benchmarking framework showing the performance of several production-grade
seismic operators implemented with Devito. This is now our flagship project
towards neat, open, and reproducible science.


## Contributing

Feel free to dive in! [Open an issue](https://github.com/acse-2020/acse-4-gormanium-rush-wolframite/issues/new) or submit PRs.

### Contributors

This project exists thanks to all the people who contribute. 
<a href="https://github.com/acse-2020/acse-4-gormanium-rush-wolframite/graphs/contributors"><img src="https://opencollective.com/acse-4-gormanium-rush-wolframite/contributors.svg?width=890&button=false" /></a>


## License

[MIT](LICENSE) © acse-2020 group Wolframite
