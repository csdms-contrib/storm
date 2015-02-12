#! /usr/bin/env python
#
# Tests for the C version of `storm`.
#
# Call with:
#   $ nosetests -sv
#
# Mark Piper (mark.piper@colorado.edu)

from nose.tools import *
import os
import shutil
from subprocess import call

# Global variables
start_dir = os.getcwd()
data_dir = os.path.join(start_dir, 'testing', 'data')
c_dir = os.path.join(start_dir, 'c')
input_file = 'wind.in'
output_files = ('wdir.data', 'windx.data', 'windy.data')
output_files_f = ('WDIR.DATA', 'WINDX.DATA', 'WINDY.DATA')
output_file_lengths = (100, 104, 104)
tolerance = 0.01

# Helpers --------------------------------------------------------------

def read(fname):
    '''
    Reads a `storm` output file and returns the numeric values
    as a flattened list.
    '''
    with open(fname, 'r') as fp:
        s = fp.read().split()
    return([float(i) for i in s])

def same(list_c, list_f):
    '''
    Returns True if the numeric members of a list are the same to
    within a floating-point tolerance.
    '''
    if len(list_c) != len(list_f):
        return(False)
    for i in range(len(list_f)):
        r = abs(list_c[i] - list_f[i]) < tolerance
        if r is False: return(False)
    return(True)

# Fixtures -------------------------------------------------------------

def setup_module():
    '''
    Called before any tests are performed.
    '''
    print('*** C tests')
    os.chdir(c_dir)

def teardown_module():
    '''
    Called after all tests have completed.
    '''
    call(['make', 'cleaner'])
    os.chdir(start_dir)

def setup():
    '''
    Called at start of any test using it @with_setup()
    '''
    shutil.copy(os.path.join(data_dir, input_file), c_dir)

def teardown():
    '''
    Called at end of any test using it @with_setup()
    '''
    os.remove(input_file)

# Tests ----------------------------------------------------------------

def test_compile():
    '''
    Test whether `storm` compiles
    '''
    call(['make'])

def test_no_input_file():
    '''
    Check that storm fails without input file
    '''
    r = call(['./storm'])
    assert_not_equal(r, 0)

@with_setup(setup, teardown)
def test_output_files_exist():
    '''
    Test for creation of the three named output files
    '''
    r = call(['./storm'])
    for fname in output_files:
        assert_true(os.path.exists(fname))

@with_setup(setup, teardown)
def test_output_file_lengths():
    '''
    Test the lengths of the named output files
    '''
    r = call(['./storm'])
    for i in range(len(output_files)):
        n_lines = sum(1 for line in open(output_files[i]))
        assert_equal(n_lines, output_file_lengths[i])

@with_setup(setup, teardown)
def test_wdir_output():
    '''
    Test whether the C wdir output matches the Fortran output
    '''
    r = call(['./storm'])
    wdir_c = read(output_files[0])
    wdir_f = read(os.path.join(data_dir, output_files_f[0]))
    assert_true(same(wdir_c, wdir_f))

@with_setup(setup, teardown)
def test_windx_output():
    '''
    Test whether the C windx output matches the Fortran output
    '''
    r = call(['./storm'])
    windx_c = read(output_files[1])
    windx_f = read(os.path.join(data_dir, output_files_f[1]))
    assert_true(same(windx_c, windx_f))

@with_setup(setup, teardown)
def test_windy_output():
    '''
    Test whether the C windy output matches the Fortran output
    '''
    r = call(['./storm'])
    windy_c = read(output_files[2])
    windy_f = read(os.path.join(data_dir, output_files_f[2]))
    assert_true(same(windy_c, windy_f))
