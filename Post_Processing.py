import graphviz


def visualization(unit_num, vector, vector_string, iteration, performance):
    """
    This function can draw the circuit connection graph with input information.
    The graph will be generated in png format in the output folder.

    Parameters
    ----------

    unit_num : integer
        Number of units used on the circuit
    vector : list
        Vector of connections between the units
    vector_string : string
        List of graph connections to be displayed
    iteration : string
        Number of iterations to be displayed
    performance : string
        Score of circuit performance to be displayed
    """
    vec = graphviz.Digraph('Circuit connections')

    vec.attr(rankdir='LR', ranksep="0.3 equally")
    vec.attr('node', shape='box', size='0.02')

    # Draw feed cluster
    with vec.subgraph(name='cluster_feed') as c:
        c.attr(compound='false', color='#ffffff')
        c.node('feed')

    # Draw results cluster
    with vec.subgraph(name='cluster_results') as c:
        c.attr(compound='false', color='#ffffff')
        c.node('%d' % unit_num, 'concentrate')
        c.node('%d' % (unit_num + 1), 'tailings')

    # Draw connection between feed and the first unit
    vec.edge('feed', '%d' % vector[0])

    # Draw connection between all units and concentrate/tailings
    for i in range(unit_num):
        vec.edge(
            '%d:n' % i, '%d:w' % vector[2 * i + 1],
            color="#0000ff", splines='curved'
            )
        vec.edge(
            '%d:s' % i, '%d:w' % vector[2 * i + 2],
            color="#ff0000", splines='curved'
            )

    # Set graph information
    vec.attr(
        label=r'\n\nIteration: %-10s Performance: %-10s vector: %s'
        % (iteration, performance, vector_string)
        )
    vec.attr(fontsize='14')

    # Write to disk
    vec.render(
        filename='circuit', directory='output', cleanup=True, format='png'
        )


if __name__ == "__main__":
    # Read in information
    with open("output/output.txt", "r") as f:
        data = f.readlines()

    vector_string = data[0].strip('\n')
    iteration = data[1].strip('\n')
    performance = data[2].strip('\n')

    vector = list(map(int, vector_string.split()))
    unit_num = int((len(vector) - 1) / 2)

    visualization(unit_num, vector, vector_string, iteration, performance)
