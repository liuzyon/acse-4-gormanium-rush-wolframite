# How to use these examples

Before you start using this part, please [install](https://github.com/acse-2020/acse-4-gormanium-rush-wolframite#installation) it.

## Visualization

Visualization needs the file containing circuit configuration information, including circuit vector, iterations times, and performance score.
After reading in this file, the number of units will be automatically calculated and the connection diagram will be drawn.
In general, circuit simulation will automatically generate a document containing the best circuit configuration information. 

The provided eg_info.txt contains these informations:
Citcuit vector: 7 5 1 8 11 9 0 9 6 10 9 4 8 9 2 9 3 4 7 4 5 
Iteration times: 1000
performance score: 165.753

To visualise the output circuit, run command:

```
python eg_post_processing.py
```

Then you would get the following graph in output folder:
![image](https://github.com/acse-2020/acse-4-gormanium-rush-wolframite/blob/main/output/eg_circuit.png)

You can directly modify eg_info.txt, enter your own vector and draw the circuit connection diagram.
