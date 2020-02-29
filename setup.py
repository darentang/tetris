from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

extensions = [Extension("tetris", ["src/tetris_wrapper.pyx"])]

setup(
    name="tetris", 
    ext_modules=cythonize(extensions)
)
