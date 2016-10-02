from matplotlib.pyplot import plot, show
from scipy.integrate import simps
from numpy import array
from os import getcwd, remove
from os.path import join
from subprocess import run, PIPE
from IO import readfile


if __name__ == "__main__":
    # Setup
    currdir = getcwd()
    project_binary = join(currdir, "Release/Gp_Box")
    # Run a help test
    output = run([project_binary, "--help-all"], stdout = PIPE, stderr = PIPE)
    print("Stdout: {0}\nStderr: {1}\n".format(output.stdout.decode('UTF-8'), 
                                              output.stderr.decode('UTF-8')))
    # Run two examples
    run([project_binary, "--r-min=20", "--r-max=100", "--r-num=50", "./test"])
    data = readfile("./test", 3, ",", skip=1)
    r_centers = (array(data[0]) + array(data[1])) / 2.
    plot(r_centers, data[2], '-k', linewidth = 2.5)
    int = simps(data[2], r_centers)
    print("Integral of Ex. 1: {0}".format(int))
    
    run([project_binary, "--r-min=0", "--r-max=110", "--r-num=200", "./test"])
    data = readfile("./test", 3, ",", skip=1)
    r_centers = (array(data[0]) + array(data[1])) / 2.
    plot(r_centers, data[2], '-r')
    int = simps(data[2], r_centers)
    print("Integral of Ex. 2: {0}".format(int))
    show()
    remove("./test")