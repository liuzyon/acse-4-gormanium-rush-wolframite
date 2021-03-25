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

Gormanium-Rush can determine the optimum circuit configuration and performance for valuable-material-recycling circuit that contains several separation units. The circuit produces two products: a concentrate stream and a tailings stream. Parameters that affect the optimum circuit including the number of units, the price paid for gormanium relative to the cost of disposing of the waste material, and the purity of the input feed. The optimization algorithm used to find the solution is the genetic algorithm.


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
This will generate info.txt in output folder, which is the dependent file of visualization.

To visualise the output circuit, run the following command:
```
python post_processing.py
```
Then the circuit connection graph will be generated in output folder.

### Examples
See [here](https://github.com/acse-2020/acse-4-gormanium-rush-wolframite/tree/main/examples) for further examples.


## Contributing

Feel free to dive in! [Open an issue](https://github.com/acse-2020/acse-4-gormanium-rush-wolframite/issues/new) or submit PRs.

### Contributors

This project exists thanks to all the [people who contributed](https://github.com/acse-2020/acse-4-gormanium-rush-wolframite/graphs/contributors).


## License

[MIT](LICENSE) © acse-2020 group Wolframite

