import matplotlib.pyplot as plt
import numpy as np

def make_violins_for_normal_bandits(filename: str):
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

    plt.show()
    

if ( __name__ == "__main__" ):
    make_violins_for_normal_bandits("build/bandit.txt")
