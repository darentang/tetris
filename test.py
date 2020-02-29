from tetris import PyTetris
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

import numpy as np


game = PyTetris(20, 10, 1)
fig = plt.figure()
ax = fig.add_subplot(111)

def animate():
    im = plt.imshow(np.zeros((20, 10)))
    for i in range(100):
        s = game.get_state(1, np.random.randint(0, 3))
        im.set_data(s.transpose(1, 2, 0))
        fig.canvas.draw()

win = fig.canvas.manager.window
fig.canvas.manager.window.after(200, animate)
plt.show()