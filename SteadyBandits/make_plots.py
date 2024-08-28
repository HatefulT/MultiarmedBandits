import matplotlib.pyplot as plt
import numpy as np

def make_violins_for_normal_bandits(filename: str, output_filename: str):
    with open(filename, 'r') as f:
        bandit = []
        count_arms = int(f.readline())
        for i in range(count_arms):
            mean, stddev = map(float, f.readline().split(" "))
            bandit.append( [mean, stddev] )
    
    fig, ax = plt.subplots()

    normal = [ np.random.normal(bandit[i][0], bandit[i][1], 1000) for i in range(count_arms)]

    vp = ax.violinplot(normal, np.arange(count_arms), widths=1,
                   showmeans=False, showmedians=False, showextrema=False)

    fig.savefig(output_filename, bbox_inches='tight')
    plt.close(fig)
    
def make_comparative_graph(filenames, output_filename, labels = ['1', '2']):
    data = []
    for filename in filenames:
        data.append([])
        with open(filename, 'r') as f:
            count_data = int(f.readline())
            for i in range(count_data):
                reward_t = float(f.readline())
                if(i == 0):
                    data[-1].append(reward_t)
                    continue
                data[-1].append(data[-1][-1] + reward_t)

    for dat in data:
        for i in range(len(dat)):
            dat[i] /= (i+1.)

    fig, ax = plt.subplots()
    for i, dat in enumerate(data):
        ax.plot(np.arange(len(data[0])), dat, label=labels[i])

    ax.grid()
    fig.legend()
    
    fig.savefig(output_filename, bbox_inches='tight')
    plt.close(fig)

if ( __name__ == "__main__" ):
    make_violins_for_normal_bandits("bandit.txt", "violinplot.png")

    make_comparative_graph(['build/greedy.txt', 'build/epsilongreedy.txt'], 
                           'comparative_graph.png',
                           labels = ['greedy', '$\\varepsilon$-greedy'])
