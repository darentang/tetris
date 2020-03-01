from tetris import PyTetris
import cv2
import numpy as np

scale = 20
game = PyTetris(20, 10, 10)

keymap = {
    # left
    81: (-1, 0),
    # up
    82: (0, 1),
    # right
    83: (1, 0),
    # down
    84: (0, -1),
}

key = -1

while True:
    screen = game.get_state(*keymap.get(key, (0, 0)))
    screen = screen.transpose(1, 2, 0).astype("float32").repeat(scale, axis=0).repeat(scale, axis=1)
    screen = cv2.cvtColor(screen, cv2.COLOR_RGB2BGR)
    cv2.imshow('screen', screen)
    key = cv2.waitKey(20)
    if key == ord('q'):
        break


