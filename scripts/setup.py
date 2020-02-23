from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

ext = Extension(
    name="ctetris",
    sources=["scripts/wrapper.pyx"],
    libraries=["tetris_core"],
    library_dirs=["lib"],
    include_dirs=["include"]
)
setup(
    name="ctetris",
    ext_modules=cythonize([ext]),
)