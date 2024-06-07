from distutils.core import setup
from Cython.Build import cythonize
# setup(ext_modules = cythonize(["qwen7b_graph_aiagent.py"]))

extensions = [
    'call_calc.py'
]

setup(
    ext_modules = cythonize(extensions),
    script_name='setup.py',
    script_args=['build_ext', '--build-lib', './']
)
