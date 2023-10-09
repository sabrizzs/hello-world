import matplotlib.pyplot as plt

clients = ['0 clients', '10 clients', '100 clients']
cpu_percentages = [0.00, 6.99, 24.22]

net_io_tx = [2.92, 21.4, 155]
net_io_rx = [0, 19.1, 145]

fig, axs = plt.subplots(2, 1, figsize=(10, 10))

axs[0].bar(clients, cpu_percentages, color='blue')
axs[0].set_ylabel('CPU %')
axs[0].set_title('Uso de CPU por Número de Clientes')

axs[1].bar(clients, net_io_tx, label='NET I/O (Tx)', color='green')
axs[1].bar(clients, net_io_rx, label='NET I/O (Rx)', bottom=net_io_tx, color='orange')
axs[1].set_ylabel('NET I/O (kB)')
axs[1].set_title('Uso de NET I/O por Número de Clientes')
axs[1].legend()

for i, (tx, rx) in enumerate(zip(net_io_tx, net_io_rx)):
    axs[1].text(i, tx + rx + 10, f'{tx:.2f} / {rx:.2f}', ha='center', va='bottom', fontsize=10)

plt.tight_layout()
plt.show()
