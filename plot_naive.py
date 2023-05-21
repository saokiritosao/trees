import matplotlib.pyplot as plt

f1 = open("test_q_sort_cen.txt")


x = [int(i) for i in f1.readline().split()]

y1 = [int(i) for i in f1.readline().split()]

print(x, y1, sep='\n')

plt.plot(x, y1, label='naive_rand')


plt.legend(fontsize=14)

plt.savefig("plot_naive_rand.png")
plt.show()