import matplotlib.pyplot as plt

tab_names = ["close_hash"]

for name in tab_names:

            f = open("test_" + name + ".txt")

            x = [int(i) for i in f.readline().split()]
            y = [int(i) for i in f.readline().split()]

            plt.plot(x, y, label=name)

            plt.legend(fontsize=14)   

            plt.savefig("plot_"+ name + ".png")  

            plt.clf()    

            f.close()   
