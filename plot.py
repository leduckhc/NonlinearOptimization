import pandas as pd
import os

# if os.path.exists("bin/solution_gradient_descent.csv")

try: 
    df = pd.read_csv("bin/solution_gradient_descent.csv")

    fig = df.plot.line(x="iter", y="residual", color='black').get_figure()
    fig.savefig('bin/solution_gradient_descent_residual.png')

    ax = df.plot.line(x="x0", y="x1", color='black')
    ax.set_aspect("equal")
    ax.get_figure().savefig("bin/solution_gradient_descent_xsol.png")
except:
    pass

try:
    df = pd.read_csv("bin/solution_conjugate_gradient.csv")

    fig = df.plot.line(x="iter", y="residual", color='black').get_figure()
    fig.savefig('bin/solution_conjugate_gradient_residual.png')

    ax = df.plot.line(x="x0", y="x1", color='black')
    ax.set_aspect("equal")
    ax.get_figure().savefig("bin/solution_conjugate_gradient_xsol.png")
except:
    pass
